
#include "stdafx.h"
#include "ConvoyData.h"

using namespace NS;
using namespace MsgPB;

//------------------------------------------------------------------------------------------------
// TowerBuildMgr
//------------------------------------------------------------------------------------------------

ConvoyDataMgr::ConvoyDataMgr()
{

}

ConvoyDataMgr::~ConvoyDataMgr()
{

}

void ConvoyDataMgr::terminate()
{
	Clear();
}

void ConvoyDataMgr::Clear()
{
	m_vecConvoy.clear();
}


ConvoyDataMgr& ConvoyDataMgr::getInstance()
{
	static ConvoyDataMgr s_convoyDataMgr;
	return s_convoyDataMgr;
}

void ConvoyDataMgr::RefreshConvoy(const MsgPB::MsgConvoyListS2C& msg)
{
	Clear();
	for (size_t i = 0; i < msg.list_info_size(); i++)
	{
		ConvoyData data;
		data.m_iggId = msg.list_info(i).con_iggid();
		data.m_convoyId = msg.list_info(i).convoyid();
		data.m_uuid = msg.list_info(i).uuid();
		int nLvAll = 0;
		int nNum = 0;
		for (int j = 0; j < msg.list_info(i).info_size(); j++)
		{
			ConvoyGeneralInfo info;
			info.itemId = msg.list_info(i).info(j).itemid();
			info.Lv = msg.list_info(i).info(j).lv();
			nLvAll += info.Lv;
			nNum++;
			data.vecInfo.push_back(info);
		}
		data.m_perLv = static_cast<int>(nLvAll/nNum);
		for (int j = 0; j < msg.list_info(i).his_size(); j++)
		{
			ConvoyBattleHis info;
			info.bat_iggid = msg.list_info(i).his(j).bat_iggid();
			info.bat_end = msg.list_info(i).his(j).bat_end();
			data.vecHis.push_back(info);
		}
		m_vecConvoy.push_back(data);
	}
}

const ConvoyDataMgr::ConvoyData* ConvoyDataMgr::GetConvoy(NS::I64 iggid, NS::I64 uuid)
{
	for (size_t i = 0; i < m_vecConvoy.size() ; i++)
	{
		if (m_vecConvoy[i].m_iggId == iggid && m_vecConvoy[i].m_uuid == uuid) {
			return &(m_vecConvoy[i]);
		}
	}
	return nullptr;
}

const ConvoyDataMgr::ConvoyBatInfo* ConvoyDataMgr::GetCurrConvoyGen(NS::I64 uuid)
{
	for (int i = 0; i < m_curConvoy.m_vecBatGen.size(); i++)
	{
		if (m_curConvoy.m_vecBatGen[i].uuid == uuid) {
			return &(m_curConvoy.m_vecBatGen[i]);
		}
	}
	return nullptr;
}

void ConvoyDataMgr::UpdateCurrConvoy(const MsgPB::MsgConvoyRobberyS2C& msg)
{
	m_curConvoy.m_uuid = msg.uuid();
	m_curConvoy.m_convoyId = msg.convoy_id();
	m_curConvoy.m_con_iggId = msg.con_iggid();
	m_curConvoy.m_vecBatGen.clear();
	for (int i = 0; i < msg.data_size(); i++)
	{
		convBatInfo info;
		info.uuid = msg.data(i).uuid();
		info.itemId = msg.data(i).itemid();
		info.tempId = msg.data(i).tempid();   //武将外形
		info.lv = msg.data(i).lv();
		info.troopIdx = msg.data(i).troopidx();  //阵法位置
		info.equip = msg.data(i).equip();
		info.weapon1 = msg.data(i).weapon1();
		info.weapon2 = msg.data(i).weapon2();
		info.HPM = msg.data(i).hpm();
		info.MPM = msg.data(i).mpm();
		info.AD = msg.data(i).ad();
		info.AP = msg.data(i).ap();
		info.ARM = msg.data(i).arm();
		info.MARM = msg.data(i).marm();
		info.comfel = msg.data(i).comfel();
		m_curConvoy.m_vecBatGen.push_back(info);
	}
}




