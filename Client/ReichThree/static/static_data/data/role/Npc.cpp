/*!
 * \file Npc.cpp
 * \date 02-23-2017 16:29:15
 *
 * \author yuechuanxu
 */
#include "stdafx.h"
#include "Npc.h"
#include "Player.h"
#include "../NpcProtectorData.h"
#include "../../config/GlobalCfg.h"
#include "../ItemData.h"
#include "../../config/NpcBadgeCfg.h"
#include "../../config/NpcTypeCfg.h"
#include "common/Heartbeat.h"
//#include "../../config/EssenceCfg.h"
#include <LogUtil.h>
#include "../../config/PlayerAttrNameCfg.h"

using namespace NS;


Npc::Npc(int32 id, int32 insId, int32 defId)
	: Monster(id, insId, 0)
{
	m_category = MapObj::Category::Npc;
	m_isCanOpenDoor = false;
}

void Npc::SetProtectorUuid(NS::I64 nProtectorUuid)
{
	m_ProtectorUuid = nProtectorUuid;
	auto&& data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByUuid(m_ProtectorUuid);
	if (!data)
	{
		return;
	}

	auto&& pBadge = NpcBadgeCfg::getInstance().findNpcBadgeCfg(data->itemid, data->level);
	if (!pBadge || pBadge->n_Mob == 0)
	{
		return;
	}

	m_nExtSkillId = pBadge->n_extSkill;
	m_nExtSkillCoolTm = pBadge->n_extSkillTm;

	const MonsterCfg::MonsterType* pMonsterType = MonsterCfg::getInstance().findMonsterType(pBadge->n_Mob);
	if (pMonsterType)
	{
		if (pMonsterType->n_type == MonsterFuncType::battleNpc)
		{
			m_isBattleNpc = true;
		}
		m_monsterType = pMonsterType;
	}
	ResetSkillTm();
}

int Npc::CalculateMaxHp() const
{
	int nMaxHp = static_cast<int>(getAttr(MsgPB::ROLE_EFFECT_HPM));
	if (nMaxHp != 0)
	{
		return nMaxHp;
	}
	if (!m_isBadgeNpc)
		return m_monsterType->n_HPM;
	return (int)getBaseAttr(MsgPB::ROLE_EFFECT_HPM, true);
}

int Npc::getMaxMp() const
{
	if (!m_isBadgeNpc)
		return m_monsterType->n_MPM;
	return (int)getBaseAttr(MsgPB::ROLE_EFFECT_MPM,true);
}

float Npc::getBaseAttr(MsgPB::ROLE_EFFECT_TYPE type, bool isInhert) const
{
	assert(m_monsterType);
	if (!m_monsterType) { return{}; }
	AttrMap attrs{};
	if (!m_isBadgeNpc)
		m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, attrs, -1);
	else
	{
		if (m_isMyNpc)
		{
			auto me = PlayerMgr::getInstance().getSelf();
			if (me)
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgBadgeNpc, attrs, me->getLevel());
			else
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, attrs, -1);
		}
		else
		{
			if (m_isAtPvpTower)
			{
				if (m_enemyPlayerLevel != 0)
					m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgBadgeNpc, attrs, m_enemyPlayerLevel);
				else
					m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, attrs, -1);
			}
			else
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, attrs, -1);
		}
	}
	auto it = attrs.find(type);
	return (it == attrs.end()) ? 0.f : it->second;
}

float Npc::getAttr(MsgPB::ROLE_EFFECT_TYPE type) const
{
	auto it = m_attrs.find(type);
	if (it != m_attrs.end())
	{
		if (type == MsgPB::ROLE_EFFECT_CHASE)
		{
			if (m_isAcceSpeed)
			{
				return it->second * 0.8;//GlobalCfg::getInstance().getNpcMoveCoeff();
			}
			else
				return it->second;
		}
		return it->second;
	}
	return 0.0f;
}

void Npc::setPos(const glm::vec3& pos)
{
    Monster::setPos(pos);
}

const std::shared_ptr<ItemData> Npc::getCurrNorWeapon() const
{
	auto&& data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByNpcMapObjId(getId());
	if (!data)
	{
		return nullptr;
	}
	std::shared_ptr<ItemData> pItemData = ItemPacketMgr::getInstance().findItemDataByUuid(data->weaponId1);
	if (pItemData)
	{
		// 装备特殊效果
		const ArmorCfg::ArmorType* pArmorType = pItemData->getArmorCfg();
		if (pArmorType && pArmorType->m_equipPos == MsgPB::ARMOR_EQUIP_WEAPON)
		{
			return pItemData;
		}
	}
	return nullptr;
}

void Npc::calcStarAddAttr(AttrMap& attrsBase, int nStar)
{
	const float addRate1[] = { 0.3f,0.3f,0.2f,0.2f,0.2f,0.2f };
	const float addRate2[] = { 0.8f,0.8f,0.5f,0.5f,0.3f,0.3f };
	if (nStar == 0) return;
	for (int i = 0; i < 6; i++)
	{
		float fRate = 0.f;
		if (nStar == 1) {
			fRate = addRate1[i];
		}else if (nStar == 2) {
			fRate = addRate2[i];
		}
		if (attrsBase.find(ROLE_EFFECT_TYPE(i + 1)) != attrsBase.end())
		{
			attrsBase[ROLE_EFFECT_TYPE(i + 1)] *= (1.f + fRate);
		}
	}
}

void Npc::calcAttr(bool bInherBuff)
{	
	m_attrs.clear();
	m_effectSum.CleanUp();

	if (!m_monsterType) return;

	bzbee::int32 nDefId = getDefId();
	int nStar = 0;

	auto data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByUuid(m_ProtectorUuid);
	if (!m_isMyNpc)
		data = NpcProtectorDataMgr::getInstance()->getDefNpcProtectorDataByDefId(nDefId);
	if (data)
	{
		if (data->equipId != 0) {
			auto itemData = ItemPacketMgr::getInstance().findItemDataByUuid(data->equipId);
			if (itemData) {
				// 武器攻击速度不带入npc
				itemData->sumEffect(m_effectSum, false);
			}
		}
		if (data->weaponId1 != 0) {
			auto itemData = ItemPacketMgr::getInstance().findItemDataByUuid(data->weaponId1);
			if (itemData) {
				// 武器攻击速度不带入npc
				itemData->sumEffect(m_effectSum, false);
			}
		}
		if (data->weaponId2 != 0) {
			auto itemData = ItemPacketMgr::getInstance().findItemDataByUuid(data->weaponId2);
			if (itemData) {
				// 武器攻击速度不带入npc
				itemData->sumEffect(m_effectSum, false);
			}
		}
		nStar = data->comfort;
	}
	// Buff 增加属性;
	if (bInherBuff)
		sumEffectBuf(m_effectSum);
	//ItemUseCountData::getInstance().sumEffect(m_effectSum)

	// 计算 当前属性;
	AttrMap baseAttr;
	if (!m_isBadgeNpc)
		m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, baseAttr, -1);
	else
	{
		if (m_isMyNpc)
		{
			auto me = PlayerMgr::getInstance().getSelf();
			if (me)
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgBadgeNpc, baseAttr, me->getLevel());
			else
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, baseAttr, -1);
		}
		else
		{
			if (m_isAtPvpTower)
			{
				if (m_enemyPlayerLevel == 0)
					m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, baseAttr, -1);
				else
					m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgBadgeNpc, baseAttr, m_enemyPlayerLevel);
			}
			else
			{
				m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, baseAttr, -1);
			}
		}
	}

	calcStarAddAttr(baseAttr, nStar);
	recalculateByEffectSum(m_attrs, baseAttr, m_effectSum);

	if (m_calcAttrTriggerAchieveCallback)
	{
		m_calcAttrTriggerAchieveCallback(this);
	}
	setMaxHp((int)getAttr(MsgPB::ROLE_EFFECT_HPM));
	if (!isInitialized()) {
		if (getHp() <= 0) {
			setHp(getMaxHp());
		}
	}
	setInitialzed();
}

void Npc::setHp(int hp, bool setDisplay)
{
	int nHurt = getHp() - hp;
	Role::setHp(hp, setDisplay);
	if (nHurt > 0 && getMaxHp() > 0) {
		m_fAnger += 3.f;//(nHurt * 1000.f / getMaxHp());
	}
}

bool Npc::CanWeaponSkill()
{
	auto&& data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByUuid(m_ProtectorUuid);
	if (!data || data->comfort < 2)
	{
		return false;
	}
	return m_fAnger > 99.f;
}

void Npc::CostAnger()
{
	m_fAnger = 0.f;
}

void Npc::NormalAnger()
{
	m_fAnger += 10;
}

void Npc::ResetSkillTm()
{
	if (m_nExtSkillId == 0 || m_nExtSkillCoolTm == 0) {
		return;
	}
	m_n64ExSkillTm = Heartbeat::getInstance().getServerTimeMs() + m_nExtSkillCoolTm*1000;
}

bool Npc::IsCanExtSkill()
{
	auto&& data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByUuid(m_ProtectorUuid);
	if (!data || data->comfort < 1)
	{
		return false;
	}
	if (m_n64ExSkillTm == 0 ||
		m_n64ExSkillTm > Heartbeat::getInstance().getServerTimeMs()) {
		return false;
	}
	return true;
}

std::string Npc::GetBattleSound(int nSountTpy)
{
	int nGender = 0;
	auto data = NpcProtectorDataMgr::getInstance()->getNpcProtectorDataByUuid(m_ProtectorUuid);
	if (data && data->templateid == 1470005) {
		nGender = 1;
	}

	if (nSountTpy == SOUND_TPY_ATK) {
		int nIdx = std::rand() % 8;
		if (nIdx > 1) return "";
		if (nGender == 0) {
			return fmt::format("SoundWave'/Game/Sound/player/male/atk{0}.atk{1}'", nIdx + 1, nIdx + 1);
		}
		else {
			return fmt::format("SoundWave'/Game/Sound/player/female/atk{0}.atk{1}'", nIdx + 1, nIdx + 1);
		}
	}
	else if (nSountTpy == SOUND_TPY_HIT) {
		int nIdx = std::rand() % 12;
		if (nIdx > 2) return "";
		if (nGender == 0) {
			return fmt::format("SoundWave'/Game/Sound/player/male/hit{0}.hit{1}'", nIdx + 1, nIdx + 1);
		}
		else {
			return fmt::format("SoundWave'/Game/Sound/player/female/hit{0}.hit{1}'", nIdx + 1, nIdx + 1);
		}
	}
	else if (nSountTpy == SOUND_TPY_DEAD) {
		if (nGender == 0) {
			return "SoundWave'/Game/Sound/player/male/dead.dead'";
		}
		else {
			return "SoundWave'/Game/Sound/player/female/dead.dead'";
		}
	}
	return "";
}

//////////////////////////////////////////////////////////////////////////


NpcMgr& NpcMgr::getInstance()
{
	static NpcMgr mgr;
	return mgr;
}

std::shared_ptr<Npc> NpcMgr::getNpcByDefId(int32 defId)
{
	for (auto&& npc : m_npcs)
	{
		if (npc.second->getDefId() == defId)
		{
			return npc.second;
		}
	}

	return nullptr;
}

std::shared_ptr<Npc> NpcMgr::getNpcByProtectorUuid(NS::I64 protectorId)
{
	for (auto&& npc : m_npcs)
	{
		if (npc.second->GetProtectorUuid() == protectorId)
		{
			return npc.second;
		}
	}

	return nullptr;
}

std::shared_ptr<Npc> NpcMgr::getNpc(int32 mapObjId)
{
	auto iter = m_npcs.find(mapObjId);
	return (iter == m_npcs.end()) ? nullptr : iter->second;
}


bool NpcMgr::addNpc(const std::shared_ptr<Npc>& npc)
{
	if (!npc) { return false; }
	bool hasInserted{};
	std::tie(std::ignore, hasInserted) = m_npcs.emplace(npc->getId(), npc);
	if (!hasInserted)
	{
		LOGE("duplicate map obj id: {0}.", npc->getId());
		return false;
	}
	MapObjMgr::getInstance().addObj(npc);
	
	return true;
}

void NpcMgr::Clear()
{
	m_npcs.clear();
}


bool NpcMgr::removeNpc(int32 mapObjId)
{
	return m_npcs.erase(mapObjId) == 1 && MapObjMgr::getInstance().removeObj(mapObjId);
}



