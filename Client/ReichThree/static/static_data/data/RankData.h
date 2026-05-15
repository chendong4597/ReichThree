/*!
* \file ItemData.h
*
* \author ChenBk
* \date 12/01/2016
*
*
*/
#pragma once
#include "msg/MsgRank.pb.h"
#include <array>
#include <map>
#include "BaseTypeDefine.h"

using namespace NS;



class DonateRankData
{
public:
	DonateRankData();
	virtual ~DonateRankData();

public:
	NS::I64 m_iggId{ 0 };
	NS::I64 m_donatenum{ 0 };
	int m_rankIdx{ 0 };
};

//TowerBuildMgr
//------------------------------------------------------------------
class RankDataMgr
{
public:
	typedef std::vector<DonateRankData> DonateRankDataVec;					//所有数据, Key: UUID

public:
	RankDataMgr();
	virtual ~RankDataMgr();

	static RankDataMgr& getInstance();
	void terminate();

	void Clear();

	//add\remove
	bool AddDonateRank(NS::I64 iggId, NS::I64 donatenum, int nRankIdx);
	const DonateRankDataVec& GetDonateRankDatas() { return m_donateRank; }
private:
	DonateRankDataVec m_donateRank;
};
