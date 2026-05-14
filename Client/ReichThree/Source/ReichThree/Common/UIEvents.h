#pragma once
#include "GameAppExtern.h"
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"


#define DECLARE_UI_MYEVENT(evt) DECLARE_EVENT_OneParam(UEgine, F##evt, const evt&) \
public: \
	F##evt& On##evt() { return m_evt##evt; } \
private: \
	F##evt m_evt##evt;

#define UI_REGISTER_MYEVENT(evt , fun_name) HandlerUIEvents::getInstance().On##evt().AddUObject(this, fun_name); 
#define UI_UN_REGISTER_MYEVENT(evt, widget) HandlerUIEvents::getInstance().On##evt().RemoveAll(widget); 

#define UI_DISPATCH_MYEVENT(evtname , evt) HandlerUIEvents::getInstance().On##evtname().Broadcast(evt);


//*************************************************************************************************
//
//*************************************************************************************************
class WindowEvent// : public bzbee::Event
{
public:
	enum class EventType
	{
		Unknown,
	};
public:
	WindowEvent() {};
	virtual ~WindowEvent() {};

public:
	EventType m_type;
	NS::I64 nParam{};
	NS::int32 nParam1{};
	NS::int32 nParam2{};
	NS::int32 nParam3{};
	NS::I64   nParam4{};
};

//*************************************************************************************************
//
//*************************************************************************************************
class HandlerUIEvents// : public NS::MsgHandler
{
public:
	HandlerUIEvents();
	virtual ~HandlerUIEvents();

	static HandlerUIEvents& getInstance();

public:
	DECLARE_UI_MYEVENT(WindowEvent);
	
};



