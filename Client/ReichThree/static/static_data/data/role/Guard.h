
/*!
 * \file Monster.h
 *
 * \author zhijieli
 * \date 2016/12/22
 *
 * 
 */

#pragma once

#include "data/role/Role.h"
#include "../../config/MonsterCfg.h"
#include "../../data/ConvoyData.h"
#include <unordered_map>
#include <memory>

class Guard : public Role
{
public:
	Guard(bzbee::int32 id, bzbee::int32 insId, bzbee::int32 defId);

	void onInit() override;

	const MonsterCfg::MonsterType* getMonsterType() const { return m_monsterType; }
	bzbee::int32 getInsId() const { return m_insId; }
	bzbee::int32 getDefId() const { return m_defId; }
	NS::I64 getGuardUuid() const { return m_npcUuid; }
	bzbee::uint8 getEventType() const { return m_eventType; }

	void setGuardUuid(NS::I64 npcUuid) { m_npcUuid = npcUuid; }

	virtual void calcAttr(bool bInherBuff = true) override;

	virtual float getBaseAttr(MsgPB::ROLE_EFFECT_TYPE type, bool isInhert) const override;

	virtual std::string GetBattleSound(int nSountTpy) override;

	bool CanWeaponSkill();
	void CostAnger();
	void NormalAnger();

	void ResetSkillTm();
	bool IsCanExtSkill();

protected:
	bzbee::int32 m_defId{};
	bzbee::int32 m_insId{};
	bzbee::uint8 m_eventType{};		// The event from where the monster appears.
	NS::I64 m_npcUuid{};
	const MonsterCfg::MonsterType* m_monsterType{};
	bool m_isLeaving{};

	float m_fAnger{ 0.f };  //怒气值,武器技能使用
	NS::I64 m_n64ExSkillTm{ 0 };
	int  m_nExtSkillId{ 0 };
	int  m_nExtSkillCoolTm{ 0 };

	int  m_nComfel{ 0 };
};

//////////////////////////////////////////////////////////////////////////
class GuardDataMgr
{
public:
	using MapObjId2Guard = std::unordered_map<bzbee::uint, std::shared_ptr<Guard>>;
public:
	static GuardDataMgr& getInstance();

	std::shared_ptr<Guard> getGuard(bzbee::int32 mapObjId);

	std::shared_ptr<Guard> getGuardByTypeId(int mobTypeId);

	bool addGuard(const std::shared_ptr<Guard>& monster);
	bool removeMonster(bzbee::int32 mapObjId);
	int getNumMonster() const { return (int)m_guards.size(); }
	bool isHaveCreate(NS::I64 serverMapObjId);
	void Clear() { m_guards.clear(); }
	

	const MapObjId2Guard& getAllGurads() const { return m_guards; }

private:
	
	MapObjId2Guard m_guards;
};
