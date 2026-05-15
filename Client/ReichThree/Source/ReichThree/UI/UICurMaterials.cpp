// Fill out your copyright notice in the Description page of Project Settings.


#include "UICurMaterials.h"
#include "UIWindow.h"

#include "config/ItemCfg.h"

bool UUICurMaterials::Initialize()
{
	if (!Super::Initialize())return false;

	RefreshMatItems();
	return true;
}

void UUICurMaterials::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}


void UUICurMaterials::RefreshMatItems()
{
	
}

