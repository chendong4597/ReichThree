/*!
 * \file Monster.cpp
 *
 * \author zhijieli
 * \date 2016/12/22
 *
 * 
 */
#include "stdafx.h"
#include "Guard.h"
//#include "data/NpcProtectorData.h"
#include "LogUtil.h"
#include <RandomUtil.h>
#include "../ItemData.h"
#include "../../config/NpcBadgeCfg.h"
#include "../../config/NpcTypeCfg.h"
#include "common/Heartbeat.h"
#include "msg/MsgGameDef.pb.h"
#include "../../config/GlobalCfg.h"

Guard::Guard(bzbee::int32 id, bzbee::int32 insId, bzbee::int32 defId)
	: Role(id)
	, m_insId(insId)
	, m_defId(defId)
{
	m_category = MapObj::Category::Monster;

	m_monsterType = MonsterCfg::getInstance().findMonsterType(m_defId);
	if (!m_monsterType)
	{
		LOGE("monster defId not found: {0}.", m_defId);
		m_defId = 1;
		m_monsterType = MonsterCfg::getInstance().findMonsterType(m_defId);
		if (!m_monsterType) { return; }
	}

	//setHp(m_monsterType->n_HPM);
	setMp(m_monsterType->n_MPM);
	setLevel(m_monsterType->n_MobLv);
}


void Guard::onInit()
{
	Role::onInit();
}

bool Guard::CanWeaponSkill()
{
	if (m_nComfel < 2)
	{
		return false;
	}
	return m_fAnger > 99.f;
}

void Guard::CostAnger()
{
	m_fAnger = 0.f;
}

void Guard::NormalAnger()
{
	m_fAnger += 10;
}

void Guard::ResetSkillTm()
{
	if (m_nExtSkillId == 0 || m_nExtSkillCoolTm == 0) {
		return;
	}
	m_n64ExSkillTm = Heartbeat::getInstance().getServerTimeMs() + m_nExtSkillCoolTm * 1000;
}

bool Guard::IsCanExtSkill()
{
	if (m_nComfel < 1) return false;
	if (m_n64ExSkillTm == 0 ||
		m_n64ExSkillTm > Heartbeat::getInstance().getServerTimeMs()) {
		return false;
	}
	return true;
}

void Guard::calcAttr(bool bInherBuff)
{
	m_attrs.clear();
	m_effectSum.CleanUp();
	

	// 计算 当前属性
	AttrMap baseAttr;
	m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, baseAttr, -1);

	if (m_npcUuid != 0) {
		const ConvoyDataMgr::ConvoyBatInfo* pInfo = ConvoyDataMgr::getInstance().GetCurrConvoyGen(m_npcUuid);
		if (pInfo) {
			baseAttr[ROLE_EFFECT_AD] = static_cast<float>(pInfo->AD);
			baseAttr[ROLE_EFFECT_AP] = static_cast<float>(pInfo->AP);
			baseAttr[ROLE_EFFECT_ARM] = static_cast<float>(pInfo->ARM);
			baseAttr[ROLE_EFFECT_MARM] = static_cast<float>(pInfo->MARM);
			baseAttr[ROLE_EFFECT_HPM] = static_cast<float>(pInfo->HPM);
			baseAttr[ROLE_EFFECT_MPM] = static_cast<float>(pInfo->HPM);

			m_nComfel = pInfo->comfel;
			auto&& pBadge = NpcBadgeCfg::getInstance().findNpcBadgeCfg(pInfo->itemId, pInfo->lv);
			if (pBadge)
			{
				m_nExtSkillId = pBadge->n_extSkill;
				m_nExtSkillCoolTm = pBadge->n_extSkillTm;
			}
			ResetSkillTm();
		}
	}

	recalculateByEffectSum(m_attrs, baseAttr, m_effectSum);
	setMaxHp((int)getAttr(MsgPB::ROLE_EFFECT_HPM));
	if (!isInitialized()) {
		if (getHp() <= 0) {
			setHp(getMaxHp());
		}
	}
	setInitialzed();
}

float Guard::getBaseAttr(MsgPB::ROLE_EFFECT_TYPE type, bool isInhert) const
{
	assert(m_monsterType);
	if (!m_monsterType) { return{}; }
	AttrMap attrs{};
	m_monsterType->getAttr(MonsterCfg::MonsterCfgType::MonsterCfgMob, attrs, -1);
	auto it = attrs.find(type);
	return (it == attrs.end()) ? 0.f : it->second;
}

std::string Guard::GetBattleSound(int nSountTpy)
{
	assert(m_monsterType);
	if (!m_monsterType) { return{}; }

	std::string strSound = "";
	if (nSountTpy == SOUND_TPY_ATK) {
		if (m_monsterType->s_atk_sound.empty()) {
			return "";
		}
		int nIdx = std::rand() % 100;
		if (nIdx <= m_monsterType->n_atk_tri) strSound = m_monsterType->s_atk_sound;
	}
	else if (nSountTpy == SOUND_TPY_HIT) {
		if (m_monsterType->s_hit_sound.empty()) {
			return "";
		}
		int nIdx = std::rand() % 100;
		if (nIdx <= m_monsterType->n_hit_tri) strSound = m_monsterType->s_hit_sound;
	}
	else if (nSountTpy == SOUND_TPY_DEAD) {
		if (m_monsterType->s_dead_sound.empty()) {
			return "";
		}
		int nIdx = std::rand() % 100;
		if (nIdx <= m_monsterType->n_dead_tri) strSound = m_monsterType->s_dead_sound;
	}
	if (strSound.empty()) {
		return "";
	}
	else {
		return fmt::format("SoundWave'/Game/Sound/effect/{0}.{1}'", strSound, strSound);
	}
}




//////////////////////////////////////////////////////////////////////////
GuardDataMgr& GuardDataMgr::getInstance()
{
	static GuardDataMgr mgr;
	return mgr;
}

std::shared_ptr<Guard> GuardDataMgr::getGuard(bzbee::int32 mapObjId)
{
	auto iter = m_guards.find(mapObjId);
	return (iter == m_guards.end()) ? nullptr : iter->second;
}

std::shared_ptr<Guard> GuardDataMgr::getGuardByTypeId(int mobTypeId)
{
	for (auto&& pir : m_guards)
	{
		auto&& pMobType = pir.second->getMonsterType();

		if (pMobType && pMobType->n_ID == mobTypeId)
		{
			return pir.second;
		}
	}

	return nullptr;
}

bool GuardDataMgr::addGuard(const std::shared_ptr<Guard>& monster)
{
	if (!monster) { return false; }
	if (getGuard(monster->getId()))
	{
		LOGE("duplicate map obj id: {0}, override.", monster->getId());
	}
	m_guards[monster->getId()] = monster;
	return MapObjMgr::getInstance().addObj(monster);;
}

bool GuardDataMgr::removeMonster(bzbee::int32 mapObjId)
{
	return m_guards.erase(mapObjId) == 1 && MapObjMgr::getInstance().removeObj(mapObjId);
}

bool GuardDataMgr::isHaveCreate(NS::I64 serverMapObjId)
{
	return false;
}
