/*!
* \file ItemData.h
*
* \author ChenBk
* \date 12/01/2016
*
*
*/
#pragma once
#include "msg/MsgConvoy.pb.h"
#include <array>
#include <map>
#include "BaseTypeDefine.h"

using namespace NS;

//TowerBuildMgr
//------------------------------------------------------------------
class ConvoyDataMgr
{
public:
	typedef struct conInfo
	{
		NS::int32 itemId{ 0 };      //武将ID
		NS::int32 Lv{ 0 };  	//等级
	} ConvoyGeneralInfo;

	typedef struct conHis
	{
		NS::I64 bat_iggid{ 0 };   //玩家ID
		NS::int32 bat_end{ 0 };   //胜负关系
	} ConvoyBattleHis;

	typedef struct convData
	{
		NS::I64 m_iggId{ 0 };
		NS::I64 m_uuid{ 0 };
		NS::int32 m_convoyId{ 0 };
		NS::int32 m_perLv{ 0 };
		std::vector<ConvoyGeneralInfo> vecInfo;
		std::vector<ConvoyBattleHis> vecHis;
	} ConvoyData;

	typedef struct convBatInfo
	{
		NS::I64 uuid{0};      //武将ID
		NS::int32 itemId{ 0 };      //武将外形
		NS::int32 tempId{ 0 };      //武将外形
		NS::int32 troopIdx{ 0 };  //阵法位置
		NS::int32 lv{ 0 };      //武将外形
		NS::int32  equip{ 0 };
		NS::int32  weapon1{ 0 };
		NS::int32  weapon2{ 0 };
		NS::int32 HPM{ 0 };
		NS::int32 MPM{ 0 };
		NS::int32 AD{ 0 };
		NS::int32 AP{ 0 };
		NS::int32 ARM{ 0 };
		NS::int32 MARM{ 0 };
		NS::int32 comfel{ 0 };
	} ConvoyBatInfo;

	typedef struct convBatData
	{
		NS::I64 m_con_iggId{ 0 };
		NS::I64 m_uuid{ 0 };
		NS::int32 m_convoyId{ 0 };
		std::vector<convBatInfo> m_vecBatGen;
	} ConvoyBatData;
public:
	typedef std::vector<ConvoyData> ConvoyDataVec;					//所有数据, Key: UUID

public:
	ConvoyDataMgr();
	virtual ~ConvoyDataMgr();

	static ConvoyDataMgr& getInstance();
	void terminate();

	void Clear();

	void RefreshConvoy(const MsgPB::MsgConvoyListS2C& msg);
	const ConvoyDataVec& GetConvoys() { return m_vecConvoy; }

	const ConvoyData* GetConvoy(NS::I64 iggid, NS::I64 uuid);

	const ConvoyBatData& GetCurrConvoy() { return m_curConvoy; }
	const ConvoyBatInfo* GetCurrConvoyGen(NS::I64 uuid);
	void UpdateCurrConvoy(const MsgPB::MsgConvoyRobberyS2C& msg);
private:
	ConvoyDataVec m_vecConvoy;

	ConvoyBatData m_curConvoy;
};
