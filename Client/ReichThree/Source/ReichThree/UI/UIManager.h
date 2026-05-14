// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HAL/Platform.h"

#include "../Common/UIEvents.h"

enum {
	UI_Z_ORDER_UNDER = -1,
	UI_Z_ORDER_NOPRMAL = 0,
	UI_Z_ORDER_MSGBOX = 900,
	UI_Z_ORDER_MSGTIPS = 901,
	UI_Z_ORDER_MSG_DUN_READY = 910,
	UI_Z_ORDER_MSG_DEATH = 980,
	UI_Z_ORDER_MSG_LOADING = 990,
	UI_Z_ORDER_MSG_OUT = 1000,
};

#define REGISTER_BTN_CLICK(BTNName , FUN_NAME) \
{\
UButton* btn = Cast<UButton>(GetWidgetFromName(FName(BTNName))); \
if (btn)\
{\
	FScriptDelegate sgbDelegate;  \
	sgbDelegate.BindUFunction(this, #FUN_NAME );  \
	btn->OnClicked.Add(sgbDelegate);  \
}\
}\

#define REGISTER_BTN_CLICK_M(btn, BTNName , FUN_NAME) \
{\
btn = Cast<UButton>(GetWidgetFromName(FName(BTNName))); \
if (btn)\
{\
	FScriptDelegate sgbDelegate;  \
	sgbDelegate.BindUFunction(this, #FUN_NAME );  \
	btn->OnClicked.Add(sgbDelegate);  \
}\
}\

#define REGISTER_BTN_PRESSED(BTNName , FUN_NAME) \
{\
UButton* btn = Cast<UButton>(GetWidgetFromName(FName(BTNName))); \
if (btn)\
{\
	FScriptDelegate sgbDelegate;  \
	sgbDelegate.BindUFunction(this, #FUN_NAME );  \
	if(UIManager::getInstance().IsPlatformWindow()) { \
		btn->OnPressed.Add(sgbDelegate);  \
	} \
	else { \
		btn->OnHovered.Add(sgbDelegate);  \
	} \
}\
}\

#define REGISTER_BTN_RELEASED(BTNName , FUN_NAME) \
{\
UButton* btn = Cast<UButton>(GetWidgetFromName(FName(BTNName))); \
if (btn)\
{\
	FScriptDelegate sgbDelegate;  \
	sgbDelegate.BindUFunction(this, #FUN_NAME );  \
	if(UIManager::getInstance().IsPlatformWindow()) { \
		btn->OnReleased.Add(sgbDelegate);  \
	} \
	else { \
		btn->OnUnhovered.Add(sgbDelegate);  \
	} \
}\
}\


//*************************************************************************************************************************
//×Ô¶¨Òåºê
//*************************************************************************************************************************
enum UI_TPY {
	UI_TPY_None = 0,    //
	UI_TPY_Login,    //
	UI_TPY_CreateRole,    //
	UI_TPY_Lobby,    //
};


class UIManager
{
	//DECLARE_EVENT_HOST();
public:
	static UIManager& getInstance();

	void initialize();
	void terminate();
	void update(float dt);
	void reset();

	void addWidget(UUserWidget* pWidget);
	void RemoveWidget(UUserWidget* pWidget);

	void CloseWidget(UUserWidget* pWidget);
	void CloseWindow(int uiType);

	UUserWidget* GetWidget(UI_TPY);
	UUserWidget* CreateNewWidget(const char* pszBPPath, UObject* InOuter);

	UUserWidget* ShowUI(const TCHAR* path, int nUIType, bool bAddShow = true);
	//void ShowLobby(bool bShow);

	bool IsPlatformWindow();

	void onWindowEvent(const WindowEvent& evt);

	bool IsShowUI() const { return m_bShowUI; }
	void ResetShowUI();
	bool IsUIShowByType(WindowEvent::EventType uiType);
	bool CloseWindowByType(WindowEvent::EventType uiType);
private:
	TArray<UUserWidget*> m_vecWidgets;
	bool m_bShowUI{ false };
};
