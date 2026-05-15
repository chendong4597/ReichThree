
#include "stdafx.h"
#include "RankData.h"

using namespace NS;
using namespace MsgPB;

DonateRankData::DonateRankData()
{

}

DonateRankData::~DonateRankData()
{

}

//------------------------------------------------------------------------------------------------
// TowerBuildMgr
//------------------------------------------------------------------------------------------------

RankDataMgr::RankDataMgr()
{

}

RankDataMgr::~RankDataMgr()
{

}

void RankDataMgr::terminate()
{
	Clear();
}

void RankDataMgr::Clear()
{
	m_donateRank.clear();
}


RankDataMgr& RankDataMgr::getInstance()
{
	static RankDataMgr s_rankDataMgr;
	return s_rankDataMgr;
}

bool RankDataMgr::AddDonateRank(NS::I64 iggId, NS::I64 donatenum, int nRankIdx)
{
	DonateRankData data;
	data.m_iggId = iggId;
	data.m_donatenum = donatenum;
	data.m_rankIdx = nRankIdx;
	m_donateRank.push_back(data);

	return true;
}



