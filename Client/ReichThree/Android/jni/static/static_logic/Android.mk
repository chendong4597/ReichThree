LOCAL_PATH := $(call my-dir)/../../../../static/static_logic
include $(CLEAR_VARS)
LOCAL_MODULE := liblogic

LOCAL_MODULE_FILENAME := liblogic


LOCAL_SRC_FILES := DataHandler.cpp \
GameAppExtern.cpp \
common/BlockManager.cpp \
common/CacheQueue.cpp \
common/ConfigInitializer.cpp \
common/MessageQueue.cpp \
common/MsgMgr.cpp \
common/MyLocalization.cpp \
common/SyncCache.cpp \
GameModule/GameAppModule.cpp \
gm/GmCfg.cpp \
gm/GmLine.cpp \
handler/HandlerAchieve.cpp \
handler/HandlerBuilding.cpp \
handler/HandlerCraft.cpp \
handler/HandlerDrop.cpp \
handler/HandlerDungeon.cpp \
handler/HandlerFriend.cpp \
handler/HandlerHouse.cpp \
handler/HandlerInteraction.cpp \
handler/HandlerItem.cpp \
handler/HandlerKeepAlive.cpp \
handler/HandlerLogin.cpp \
handler/HandlerMgr.cpp \
handler/HandlerMonster.cpp \
handler/HandlerMsg.cpp \
handler/HandlerNpc.cpp \
handler/HandlerPlant.cpp \
handler/HandlerPublicMap.cpp \
handler/HandlerRole.cpp \
handler/HandlerStore.cpp \
handler/HandlerSurvival.cpp \
handler/HandlerTeam.cpp \
handler/HandlerTowerBuild.cpp \
localserver/BattleCalc.cpp \
localserver/LocalServer.cpp \
localserver/LocalServer_Action.cpp \
localserver/LocalServer_Battle.cpp \
localserver/LocalServer_Buff.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../external/libzlib/source \
$(LOCAL_PATH)/../../external/libprotobuf/source \
$(LOCAL_PATH)/../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../bzbee/libframework/source \
$(LOCAL_PATH)/../../bzbee/libnetwork/source \
$(LOCAL_PATH)/../../static/static_msg \
$(LOCAL_PATH)/../../static/static_data \

LOCAL_WHOLE_STATIC_LIBRARIES := libdata

LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../external/libzlib/source \
$(LOCAL_PATH)/../../external/libprotobuf/source \
$(LOCAL_PATH)/../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../bzbee/libframework/source \
$(LOCAL_PATH)/../../bzbee/libnetwork/source \
$(LOCAL_PATH)/../../static/static_msg \
$(LOCAL_PATH)/../../static/static_data \

LOCAL_SHORT_COMMANDS := true
include $(BUILD_STATIC_LIBRARY)
