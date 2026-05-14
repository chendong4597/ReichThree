// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIEvents.h"
#include "GameAppExtern.h"
#include "Delegates/DelegateCombinations.h"
#include "RootEventObject.generated.h"



#define DECLARE_MYEVENT_POST(evt_name) DECLARE_EVENT_OneParam(UEgine, F##evt_name, const evt_name&) \
public: \
	virtual bool postEvent(const evt_name& evt) override { m_evt##evt_name.Broadcast(evt); return true;} \
	F##evt_name& On##evt_name() { return m_evt##evt_name; } \
private: \
	F##evt_name m_evt##evt_name;


#define RG_REGISTER_MYEVENT(evt , fun_name) UReichGameInstance::getRootObject()->On##evt().AddUObject(this, fun_name); 
#define UNRG_REGISTER_MYEVENT(evt , dele) UReichGameInstance::getRootObject()->On##evt().RemoveAll(dele); 


/**
 * 
 */
UCLASS()
class REICHTHREE_API URootEventObject : public UObject
{
	GENERATED_BODY()
	
};
