// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWindow.generated.h"

/**
 * 
 */
UCLASS()
class REICHTHREE_API UUIWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUIType(int nUIType) { n_UIType = nUIType; }
	int  GetUIType() const { return n_UIType; }
private:
	int  n_UIType{ 0 };
};
