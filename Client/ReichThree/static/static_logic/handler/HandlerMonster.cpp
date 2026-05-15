/*!
 * \file HandlerBuilding.cpp
 *
 * \author xiaobowang;
 * \date 2017/3/17
 *
 */
#include "stdafx.h"
#include "../common/MsgMgr.h"
#include "../GameAppExtern.h"
#include "config/BuffCfg.h"
#include "config/MapSettingCfg.h"
#include "data/NpcProtectorData.h"
#include "data/ConvoyData.h"
//#include "config/"
#include "HandlerMonster.h"
#include "data/role/Npc.h"

using namespace NS;

static HandlerMonster* g_HandlerMonster = nullptr;
HandlerMonster& HandlerMonster::getInstance()
{
    assert(g_HandlerMonster);
    return *g_HandlerMonster;
}

HandlerMonster::HandlerMonster()
{
    assert(!g_HandlerMonster);
	g_HandlerMonster = this;
    reset();
}

HandlerMonster::~HandlerMonster()
{
	g_HandlerMonster = nullptr;
}

bool HandlerMonster::initialize()
{
	REGISTER_S2C(onMsgMobAppearance);
	REGISTER_S2C(onMsgMapObjectLeaveView);
	
    return true;
}

void HandlerMonster::terminate()
{
    reset();
}

bool HandlerMonster::reset()
{
    return true;
}


std::shared_ptr<Monster> HandlerMonster::addMonster(int mapObjId, int insId, int defId, const glm::vec3& pos, bool createWithLocal,
	NS::I64 serverMapObjId, bzbee::uint8 eventType, int nGroupId)
{
	const MonsterCfg::MonsterType* pMonsterType = MonsterCfg::getInstance().findMonsterType(defId);
	if (!pMonsterType)
	{
		return nullptr;
	}
	std::shared_ptr<Monster> monster = MonsterDataMgr::getInstance().getMonster(mapObjId);
	if (!monster)
	{
		monster = std::make_shared<Monster>(mapObjId, insId, defId);
		if (!monster || !monster->getMonsterType()) { return {}; }
		MonsterDataMgr::getInstance().addMonster(monster);
	}
	monster->setName(monster->getMonsterType()->s_name);
	monster->setPos(pos);
	monster->calcAttr();
	return monster;
}

std::shared_ptr<Guard> HandlerMonster::addGuard(int mapObjId, int insId, int defId, const glm::vec3& pos, bool createWithLocal,
	NS::I64 serverMapObjId, bzbee::uint8 eventType, int nGroupId)
{
	const MonsterCfg::MonsterType* pMonsterType = MonsterCfg::getInstance().findMonsterType(defId);
	if (!pMonsterType)
	{
		return nullptr;
	}
	std::shared_ptr<Guard> guard = GuardDataMgr::getInstance().getGuard(mapObjId);
	if (!guard)
	{
		guard = std::make_shared<Guard>(mapObjId, insId, defId);
		if (!guard || !guard->getMonsterType()) { return {}; }
		GuardDataMgr::getInstance().addGuard(guard);
	}
	guard->setName(guard->getMonsterType()->s_name);
	guard->setPos(pos);
	guard->calcAttr();
	return guard;
}


void HandlerMonster::onMsgMapObjectLeaveView(const MsgPB::MsgMapObjectLeaveView & msg)
{
	bool bRemove = MonsterDataMgr::getInstance().removeMonster(msg.mapobjectid())
		|| GuardDataMgr::getInstance().removeMonster(msg.mapobjectid());
	HandlerMonsterEvent evt;
	evt.m_type = HandlerMonsterEvent::EventMonster::EventMonster_DisAppearance;
	evt.mapObjId = msg.mapobjectid();
	POST_DATA_EVENT(evt);
}

void HandlerMonster::onMsgMobAppearance(const MsgPB::MsgMobAppearance& msg)
{
	auto&& pMapCfg = MapSettingCfg::getInstance().findMap(MapDataMgr::getInstance().getMapId());


	bool bConvoyMon = true;
	if (pMapCfg && pMapCfg->dungeontype == MapSettingCfg::Convoy_Dungeon &&
		msg.animalserverobjid() != 0 && ConvoyDataMgr::getInstance().GetCurrConvoyGen(msg.animalserverobjid()) != nullptr)
	{
		bConvoyMon = false;
	}

	if(!bConvoyMon) {
		int mapObjId{ msg.mapobjectid() }, insId{ msg.mobinsid() }, defId{ msg.mobdefid() };
		
		if (msg.mobdefid() > 1000001) {
			auto guard = addGuard(mapObjId, insId, defId, glm::vec3(msg.movepath().pos().x(), msg.movepath().pos().y(), 0),
				msg.has_islocalserver() && msg.islocalserver(), msg.animalserverobjid(), /*evtInfo ? evtInfo->m_type : 0*/0, msg.groupid());
			if (!guard)
			{
				//LOGE("add monster failed, mapObjId: {0}, insId: {1}, defId: {2}.", mapObjId, insId, defId);
				return;
			}

			guard->setGroupId(msg.groupid());
			guard->setGuardUuid(msg.animalserverobjid());

			guard->calcAttr();
			guard->onInit();
			guard->setHp(guard->getMaxHp());

			HandlerGuardEvent evt;
			evt.m_type = HandlerGuardEvent::EventType::EventType_Appearance;
			evt.uuid = msg.animalserverobjid();
			evt.mapObjId = msg.mapobjectid();
			evt.insId = msg.mobinsid();
			evt.defId = msg.mobdefid();
			evt.bSolider = false;
			POST_DATA_EVENT(evt);
		}
		else {
			int mapObjId{ msg.mapobjectid() }, insId{ msg.mobinsid() }, defId{ msg.mobdefid() };
			auto monster = addMonster(mapObjId, insId, defId, glm::vec3(msg.movepath().pos().x(), msg.movepath().pos().y(), 0),
				msg.has_islocalserver() && msg.islocalserver(), msg.animalserverobjid(), /*evtInfo ? evtInfo->m_type : 0*/0, msg.groupid());
			if (!monster)
			{
				//LOGE("add monster failed, mapObjId: {0}, insId: {1}, defId: {2}.", mapObjId, insId, defId);
				return;
			}

			monster->setGroupId(msg.groupid());
			monster->setMasterUuid(msg.animalserverobjid());


			// add buff
			for (int i{}; i < msg.buff_infos_size(); ++i)
			{
				auto&& buffInfo = msg.buff_infos(i);
				auto&& buffType = BuffCfg::getInstance().findBuffType(buffInfo.buff_dataid());
				if (!buffType)
				{
					continue;
				}

				Buff buff{ buffType };
				buff.setIdx(buffInfo.index());
				buff.setAliveTime(buffInfo.alive_timer());
				buff.setHeapCounter(buffInfo.heap_counter());
				monster->addBuff(buff);
			}

			monster->calcAttr();
			monster->onInit();
			monster->setHp(monster->getMaxHp());
			monster->setMp(monster->getMaxMp());

			HandlerGuardEvent evt;
			evt.m_type = HandlerGuardEvent::EventType::EventType_Appearance;
			evt.uuid = msg.animalserverobjid();
			evt.mapObjId = msg.mapobjectid();
			evt.insId = msg.mobinsid();
			evt.defId = msg.mobdefid();
			evt.bSolider = true;
			POST_DATA_EVENT(evt);
		}
	}
	else {
		int mapObjId{ msg.mapobjectid() }, insId{ msg.mobinsid() }, defId{ msg.mobdefid() };
		auto monster = addMonster(mapObjId, insId, defId, glm::vec3(msg.movepath().pos().x(), msg.movepath().pos().y(), 0),
			msg.has_islocalserver() && msg.islocalserver(), msg.animalserverobjid(), /*evtInfo ? evtInfo->m_type : 0*/0, msg.groupid());
		if (!monster)
		{
			//LOGE("add monster failed, mapObjId: {0}, insId: {1}, defId: {2}.", mapObjId, insId, defId);
			return;
		}

		monster->setHp(msg.hp());
		monster->setMp(msg.mp());
		monster->setGroupId(msg.groupid());
		if (msg.animalserverobjid() != 0) {
			if (pMapCfg && pMapCfg->type == 3) {  //副本
				monster->setMasterUuid(msg.animalserverobjid());
			}
			else {
				if (defId >= 1481001 && defId <= 1489999) {  //自己的塔防
					monster->setTowerDefenceUuid(msg.animalserverobjid());
				}
				else {
					monster->setSurvivalUuid(msg.animalserverobjid());
				}
			}
		}

		// add buff
		for (int i{}; i < msg.buff_infos_size(); ++i)
		{
			auto&& buffInfo = msg.buff_infos(i);
			auto&& buffType = BuffCfg::getInstance().findBuffType(buffInfo.buff_dataid());
			if (!buffType)
			{
				continue;
			}

			Buff buff{ buffType };
			buff.setIdx(buffInfo.index());
			buff.setAliveTime(buffInfo.alive_timer());
			buff.setHeapCounter(buffInfo.heap_counter());
			monster->addBuff(buff);
		}

		monster->calcAttr();
		monster->onInit();

		HandlerMonsterEvent evt;
		evt.m_type = HandlerMonsterEvent::EventMonster::EventMonster_Appearance;
		evt.mapObjId = mapObjId;
		evt.insId = insId;
		evt.defId = defId;
		evt.survivalUuid = msg.animalserverobjid();
		POST_DATA_EVENT(evt);
	}
}






