LOCAL_PATH := $(call my-dir)/../../../../static/static_data
include $(CLEAR_VARS)
LOCAL_MODULE := libdata

LOCAL_MODULE_FILENAME := libdata

LOCAL_SRC_FILES := common/calculate.cpp \
common/CommonDataTypeDef.cpp \
common/ComSkillBuff.cpp \
common/EncryptUtil.cpp \
common/EffectCalculation.cpp \
common/Heartbeat.cpp \
common/PlayerPrefs.cpp \
common/RandomData.cpp \
common/SkillBuffContainer.cpp \
common/SkillBuffInfo.cpp \
common/Timer.cpp \
config/AchieveCfg.cpp \
config/ArmorCfg.cpp \
config/BehaviorTreeTypeCfg.cpp \
config/BuffCfg.cpp \
config/BuffGroupRuleCfg.cpp \
config/BuffTypeCfg.cpp \
config/BuildingCfg.cpp \
config/BuildRoomCfg.cpp \
config/CraftCfg.cpp \
config/DefenceInfoTypeCfg.cpp \
config/DefencePosTpyCfg.cpp \
config/DropCfg.cpp \
config/EquipTypeCfg.cpp \
config/FieldAdventureCfg.cpp \
config/GlobalCfg.cpp \
config/HelpCfg.cpp \
config/HouseCfg.cpp \
config/ItemCfg.cpp \
config/LocalizationCfg.cpp \
config/MapSettingCfg.cpp \
config/MedicamentCfg.cpp \
config/MonsterCfg.cpp \
config/NpcActiveCfg.cpp \
config/NpcBadgeCfg.cpp \
config/NpcTypeCfg.cpp \
config/PlantCfg.cpp \
config/PlayerAttrCfg.cpp \
config/PlayerAttrNameCfg.cpp \
config/RoleCreateCfg.cpp \
config/SkillCfg.cpp \
config/SkillFrontEffectCfg.cpp \
config/SkillTypeCfg.cpp \
config/StoreCfg.cpp \
config/SurvivalEventCfg.cpp \
config/TowerBuildingCfg.cpp \
config/TroopsCfg.cpp \
config/WalkNpcCfg.cpp \
config/WeaponAniEffectCfg.cpp \
config/WeaponInfoTypeCfg.cpp \
config/WeaponTypeCfg.cpp \
data/AchieveData.cpp \
data/CraftData.cpp \
data/DropData.cpp \
data/HouseData.cpp \
data/ItemData.cpp \
data/MapData.cpp \
data/MapDataMgr.cpp \
data/MapObj.cpp \
data/NotesData.cpp \
data/NpcProtectorData.cpp \
data/PlantData.cpp \
data/SkillData.cpp \
data/StoreData.cpp \
data/SurvivalData.cpp \
data/TeamMemberData.cpp \
data/TowerBuildData.cpp \
data/role/Monsters.cpp \
data/role/Npc.cpp \
data/role/Player.cpp \
data/role/Role.cpp \
data/role/skill/PassiveSkillMgr.cpp \
data/role/skill/PassiveTrigger.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../external/libprotobuf/source \
$(LOCAL_PATH)/../../external/libcryptopp/source \
$(LOCAL_PATH)/../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../bzbee/libframework/source \
$(LOCAL_PATH)/../../bzbee/libnetwork/source \
$(LOCAL_PATH)/../../static/static_msg \
$(LOCAL_PATH)/../../static/static_logic \

LOCAL_WHOLE_STATIC_LIBRARIES := libmsg

LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../external/libprotobuf/source \
$(LOCAL_PATH)/../../external/libcryptopp/source \
$(LOCAL_PATH)/../../bzbee/libbaseutil/source \
$(LOCAL_PATH)/../../bzbee/libframework/source \
$(LOCAL_PATH)/../../bzbee/libnetwork/source \
$(LOCAL_PATH)/../../static/static_msg \
$(LOCAL_PATH)/../../static/static_logic \

LOCAL_SHORT_COMMANDS := true
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
