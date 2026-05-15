LOCAL_PATH := $(call my-dir)/../../../../static/static_msg/msg
include $(CLEAR_VARS)

LOCAL_MODULE := libmsg

LOCAL_MODULE_FILENAME := libmsg

LOCAL_SRC_FILES := \
MsgAchieve.pb.cc \
MsgAI.pb.cc \
MsgBuff.pb.cc \
MsgBuild.pb.cc \
MsgBuildTower.pb.cc \
MsgCooldown.pb.cc \
MsgCraft.pb.cc \
MsgDB.pb.cc \
MsgDBAction.pb.cc \
MsgDBLog.pb.cc \
MsgDungeon.pb.cc \
MsgGameDef.pb.cc \
MsgGM.pb.cc \
MsgHouse.pb.cc \
MsgInteraction.pb.cc \
MsgInteractive.pb.cc \
MsgItem.pb.cc \
MsgLogin.pb.cc \
MsgLottery.pb.cc \
MsgMail.pb.cc \
MsgMailServer.pb.cc \
MsgMapMgrServer.pb.cc \
MsgMapServer.pb.cc \
MsgMatchServer.pb.cc \
MsgMob.pb.cc \
MsgMove.pb.cc \
MsgNpc.pb.cc \
MsgNpcAutoIncome.pb.cc \
MsgNpcDak.pb.cc \
MsgNpcDakRepo.pb.cc \
MsgPacketDrop.pb.cc \
MsgPing.pb.cc \
MsgPlant.pb.cc \
MsgPlayer.pb.cc \
MsgPlayerDataSync.pb.cc \
MsgPlayerEvent.pb.cc \
MsgProtector.pb.cc \
MsgPublicMap.pb.cc \
MsgPVP.pb.cc \
MsgPvPRandItem.pb.cc \
MsgPvPRandMap.pb.cc \
MsgSkill.pb.cc \
MsgStore.pb.cc \
MsgSurvival.pb.cc \
MsgSyncToUserServer.pb.cc \
MsgTeam.pb.cc \
MsgTest.pb.cc \
MsgTowerPVPTombstone.pb.cc \
MsgTroops.pb.cc \
MsgType.pb.cc \
RegServer.pb.cc

# 赋值给NDK编译系统
LOCAL_C_INCLUDES := $(MY_ALL_DIRS) \
$(LOCAL_PATH)/../../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../../external/libprotobuf/source \

LOCAL_WHOLE_STATIC_LIBRARIES := libprotobuf
LOCAL_WHOLE_STATIC_LIBRARIES += libbaseutil

LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH)
LOCAL_SHORT_COMMANDS := true
include $(BUILD_STATIC_LIBRARY)
