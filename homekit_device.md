
# 设备

| TYPE | 类别 | 必须特征 |可选特征 |
| :-- | :--: | --:|--:|
|`homekit_accessory_category_other` | 其它 |  【未知】
|`homekit_accessory_category_bridge`|  桥|【可将多个设备集成到一块】
|`homekit_accessory_category_fan`| 风扇| `ON`【开关状态】 | `NAME`【名称】<br />`ROTATION_DIRECTION`【摇头】<br />`ROTATION_SPEED`【转速】
|`homekit_accessory_category_fan`| 风扇02| `ACTIVE`【状态】 | `NAME`【名称】<br />`CURRENT_FAN_STATE`【当前风扇状态】<br />`TARGET_FAN_STATE`【目标风扇状态】<br />`LOCK_PHYSICAL_CONTROLS`【锁定物理控件】<br />`ROTATION_DIRECTION`【旋转_方向】<br />`ROTATION_SPEED`【转速】<br />`SWING_MODE`【模式】
|`homekit_accessory_category_garage`| 车库|`CURRENT_DOOR_STATE`【车库门当前状态】<br/>`TARGET_DOOR_STATE`【车库门目标状态】<br/>`OBSTRUCTION_DETECTED`【障碍物检测】|`NAME`【名称】<br />`LOCK_CURRENT_STATE`【锁定当前状态】<br/>`LOCK_TARGET_STATE`【锁定目标状态】
|`homekit_accessory_category_lightbulb`| 灯泡|`ON`【开关状态】|`NAME`【名称】<br />`BRIGHTNESS`【亮度】<br/>`HUE`【色调】<br/>`SATURATION`【饱和度】<br/>`COLOR_TEMPERATURE`【颜色值】
|`homekit_accessory_category_door_lock`| 门锁| 【需要配合`附件`】
|`homekit_accessory_category_outlet`| 插座|`ON`【开关状态】<br/>`OUTLET_IN_USE`【正在使用中】|`NAME`【名称】
|`homekit_accessory_category_switch`| 开关|`ON`【开关状态】 | `NAME`【名称】
|`homekit_accessory_category_thermostat`| 恒温器|`CURRENT_HEATING_COOLING_STATE`【恒温器当前状态】<br/>`TARGET_HEATING_COOLING_STATE`【恒温器目标状态】<br/>`CURRENT_TEMPERATURE`【当前状态】<br/>`TARGET_TEMPERATURE`【目标状态】<br/>`TEMPERATURE_DISPLAY_UNITS`【显示温度单位】<br/>|`NAME`【名称】<br/>`CURRENT_RELATIVE_HUMIDITY`【当前相对温度】<br/>`TARGET_RELATIVE_HUMIDITY`【目标相对温度】<br/>`COOLING_THRESHOLD_TEMPERATURE`【冷却阀值温度】<br/>`HEATING_THRESHOLD_TEMPERATURE`【加热阀值温度】
|`homekit_accessory_category_sensor`| 传感器|【多个、详情看`附件`】
|`homekit_accessory_category_security_system`| 安全系统|`SECURITY_SYSTEM_CURRENT_STATE`【安全系统当前状态】<br/>`SECURITY_SYSTEM_TARGET_STATE`【安全系统目标状态】|`NAME`【名称】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`SECURITY_SYSTEM_ALARM_TYPE`【安全系统警报类型】
|`homekit_accessory_category_door`| 门|`CURRENT_POSITION`【当前位置】<br/>`TARGET_POSITION`【目标位置】<br/>`POSITION_STATE`【位置_状态】|`NAME`【名称】<br/>`HOLD_POSITION`【保持_位置】<br/>`OBSTRUCTION_DETECTED`【障碍物监测】
|`homekit_accessory_category_window`| 窗|`CURRENT_POSITION`【当前位置】<br/>`TARGET_POSITION`【目标位置】<br/>`POSITION_STATE`【位置_状态】|`NAME`【名称】<br/>`HOLD_POSITION`【保持_位置】<br/>`OBSTRUCTION_DETECTED`【障碍物监测】
|`homekit_accessory_category_window_covering`| 窗帘或百叶窗|`CURRENT_POSITION`【当前位置】<br/>`TARGET_POSITION`【目标位置】<br/>`POSITION_STATE`【位置_状态】|`NAME`【名称】<br/>`HOLD_POSITION`【保持_位置】<br/> `TARGET_HORIZONTAL_TILT_ANGLE`【目标水平倾斜角度】<br/>`TARGET_VERTICAL_TILT_ANGLE`【目标垂直倾斜角度】<br/>`CURRENT_HORIZONTAL_TILT_ANGLE`【当前水平倾斜角度】<br/>`CURRENT_VERTICAL_TILT_ANGLE`【当前垂直倾斜角度】<br/>`OBSTRUCTION_DETECTED`【障碍物监测】
|`homekit_accessory_category_programmable_switch`| 可编程开关|`PROGRAMMABLE_SWITCH_EVENT`【可编程开关事件】|`NAME`【名称】<br />`SERVICE_LABEL_INDEX`【服务标签索引】
|`homekit_accessory_category_range_extender`|  范围扩展器|
|`homekit_accessory_category_ip_camera`| 摄像头|
|`homekit_accessory_category_video_door_bell`| 视频门铃|【需要配合`附件`】
|`homekit_accessory_category_air_purifier`| 空气净化器|`ACTIVE`【状态】<br/>`CURRENT_AIR_PURIFIER_STATE`【空气净化器当前状态】<br/>`TARGET_AIR_PURIFIER_STATE`【空气净化器目标状态】|`NAME`【名称】<br/>`SWING_MODE`【模式】<br/>`LOCK_PHYSICAL_CONTROLS`【锁定物理控件】<br/>`ROTATION_SPEED`【转速】
|`homekit_accessory_category_heater`<br/>`homekit_accessory_category_air_conditioner`| 20.加热器 <br/>21.空调器|`ACTIVE`【状态】<br/>`CURRENT_TEMPERATURE`【当前温度】<br/>`CURRENT_HEATER_COOLER_STATE`【当前加热器冷却器状态】<br/>`TARGET_HEATER_COOLER_STATE`【目标加热器冷却器状态】|`NAME`【名称】<br/>`ROTATION_SPEED`【转速】<br/>`TEMPERATURE_DISPLAY_UNITS`【显示温度单位】<br/>`SWING_MODE`【模式】<br/>`COOLING_THRESHOLD_TEMPERATURE`【冷却阈值温度】<br/>`HEATING_THRESHOLD_TEMPERATURE`【加热阈值温度】<br/>`LOCK_PHYSICAL_CONTROLS`【锁定物理控件】
|`homekit_accessory_category_humidifier`<br/>`homekit_accessory_category_dehumidifier`| 22.加湿器<br/> 23.除湿器|`ACTIVE`【状态】<br/>`CURRENT_RELATIVE_HUMIDITY`【当前相对湿度】<br/>`CURRENT_HUMIDIFIER_DEHUMIDIFIER_STATE`【当前加湿器状态】<br/>`TARGET_HUMIDIFIER_DEHUMIDIFIER_STATE`【目标加湿器状态】|`NAME`【名称】<br/>`RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD`【相对湿度除湿阈值】<br/>`RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD`【相对湿度加湿器阈值】<br/>`ROTATION_SPEED`【转速】<br/>`SWING_MODE`【模式】<br/>`WATER_LEVEL`【水位】<br/>`LOCK_PHYSICAL_CONTROLS`【锁定物理控件】
|`homekit_accessory_category_speaker`| 扬声器|【属于附件】
|`homekit_accessory_category_sprinkler`| 洒水器|`ACTIVE`【状态】<br/>`PROGRAM_MODE`【模式】<br/>`IN_USE`【使用状态】|`NAME`【名称】<br/>`REMAINING_DURATION`【剩余时间】<br/>`STATUS_FAULT`【故障状态】
|`homekit_accessory_category_faucet`| 水龙头|`ACTIVE`【状态】|`NAME`【名称】<br/>`STATUS_FAULT`【故障状态】
|`homekit_accessory_category_shower_head`| 淋浴头|
|`homekit_accessory_category_television`| 电视机|`ACTIVE`【状态】<br/>`ACTIVE_IDENTIFIER`【活动标识符】<br/>`CONFIGURED_NAME`【配置的名称】<br/>`SLEEP_DISCOVERY_MODE`【睡眠发现模式】|`BRIGHTNESS`【亮度】<br/>`CLOSED_CAPTIONS`【闭路字幕】<br/>`DISPLAY_ORDER`【显示_顺序】<br/>`CURRENT_MEDIA_STATE`【当前媒体状态】<br/>` TARGET_MEDIA_STATE`【目标媒体状态】<br/>`PICTURE_MODE`【图片模式】<br/>`POWER_MODE_SELECTION`【电源模式选择】<br/>`REMOTE_KEY`【遥控钥匙】
|`homekit_accessory_category_target_controller`| 目标控制器|


# 附件


| 附件 | 类别 | 必须特征 |可选特征 |
| :-- | :--: | --:|--:|
|`HOMEKIT_SERVICE_BATTERY_SERVICE`|可监控的电池|`BATTERY_LEVEL`【电池电量】<br/>`CHARGING_STATE`【充电状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足】|`NAME`【名称】
|`HOMEKIT_SERVICE_LOCK_MANAGEMENT`|锁的许多附加设置<br/>规则和信息|`LOCK_CONTROL_POINT`【锁定控制点】<be/>`VERSION`【版本】|`NAME`【名称】<br>`LOGS`【日志】<br>`AUDIO_FEEDBACK`【音频反馈】<br>`LOCK_MANAGEMENT_AUTO_SECURITY_TIMEOUT`【锁定管理自动安全超时】<br>`ADMINISTRATOR_ONLY_ACCESS`【管理员唯一访问权限】<br>`LOCK_LAST_KNOWN_ACTION`【锁定最后一个已知动作】<br>` CURRENT_DOOR_STATE`【当前车门状态】<br>`MOTION_DETECTED`【运动检测】
|`HOMEKIT_SERVICE_LOCK_MECHANISM`|控制锁|`LOCK_CURRENT_STATE`【锁定当前状态】<br/>`LOCK_TARGET_STATE`【锁定目标状态】|`NAME`【名称
|`HOMEKIT_SERVICE_CARBON_MONOXIDE_SENSOR`|一氧化碳（CO）传感器|`CARBON_MONOXIDE_DETECTED`【检测到一氧化碳】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`CARBON_MONOXIDE_LEVEL`【一氧化碳水平】<br/>`CARBON_MONOXIDE_PEAK_LEVEL`【一氧化碳峰值水平】
|`HOMEKIT_SERVICE_CONTACT_SENSOR`|触点式传感器|`CONTACT_SENSOR_STATE`【触点传感器状态】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_HUMIDITY_SENSOR`|温湿度传感器|`CURRENT_RELATIVE_HUMIDITY`【当前相对湿度】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_LEAK_SENSOR`|(水)泄漏传感器|`LEAK_DETECTED`【泄漏检测】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_LIGHT_SENSOR`|光传感器|`CURRENT_AMBIENT_LIGHT_LEVEL`【当前环境亮度级别】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_MOTION_SENSOR`|运动传感器|`MOTION_DETECTED`【运动检测】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_OCCUPANCY_SENSOR`|占用传感器|`OCCUPANCY_DETECTED`【检测到占用】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_SMOKE_SENSOR`|烟雾传感器|`SMOKE_DETECTED`【烟雾检测】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_TEMPERATURE_SENSOR`|温度传感器|`CURRENT_TEMPERATURE`【当前温度】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】
|`HOMEKIT_SERVICE_CARBON_DIOXIDE_SENSOR`|二氧化碳（CO2）传感器|`CARBON_DIOXIDE_DETECTED`【检测到二氧化碳】|`NAME`【名称】<br/>`STATUS_ACTIVE`【活动状态】<br/>`STATUS_FAULT`【故障状态】<br/>`STATUS_TAMPERED`【篡改状态】<br/>`STATUS_LOW_BATTERY`【电池电量不足状态】<br/>`CARBON_DIOXIDE_LEVEL`【二氧化碳水平】<br/>`CARBON_DIOXIDE_PEAK_LEVEL`【二氧化碳峰值水平】
|`HOMEKIT_SERVICE_CAMERA_RTP_STREAM_MANAGEMENT`|管理RTP（视频）流、主要用于视频门铃和摄像机|`SUPPORTED_VIDEO_STREAM_CONFIGURATION`【支持的视频流配置】<br/>`SUPPORTED_AUDIO_STREAM_CONFIGURATION`【支持的音频流配置】<br/>`SUPPORTED_RTP_CONFIGURATION`【支持的RTP_配置】<br/>`SELECTED_RTPS_CONFIGURATION`【SELECTED_RTPS_配置】<br/>`STREAMING_STATUS`【流式处理状态】<br/>`SETUP_ENDPOINTS`【设置端点】|`NAME`【名称】<br>`VOLUME`【音量】
|`HOMEKIT_SERVICE_MICROPHONE`|麦克风、主要用于视频门铃和摄像机|`MUTE`【静音】|`NAME`【名称】<br>`VOLUME`【音量】
|`HOMEKIT_SERVICE_SPEAKER`|扬声器、主要用于视频门铃和摄像机|`MUTE`【静音】|`NAME`【名称】<br>`VOLUME`【音量】
|`HOMEKIT_SERVICE_DOORBELL`|门铃、主要用于视频门铃|`PROGRAMMABLE_SWITCH_EVENT`【可编程开关事件】|`NAME`【名称】<br>`BRIGHTNESS`【亮度】<br/>`VOLUME`【音量】
|`HOMEKIT_SERVICE_SLAT`|水平或垂直倾斜的板条|`SLAT_TYPE`【板条类型】<br/>`CURRENT_SLAT_STATE`【当前平台状态】|`NAME`【名称】<br/>`CURRENT_TILT_ANGLE`【当前倾斜角度】<br/>`TARGET_TILT_ANGLE`【目标倾斜角度】<br/>`SWING_MODE`【模式】
|`HOMEKIT_SERVICE_FILTER_MAINTENANCE`|通知用户需要维护的过滤器|`FILTER_CHANGE_INDICATION`【过滤器更改指示】|`NAME`【名称】<br>`FILTER_LIFE_LEVEL`【过滤器生活水平】<br/>`RESET_FILTER_INDICATION`【重置过滤器指示】
|`HOMEKIT_SERVICE_INPUT_SOURCE`|控制电视输入源|`NAME`【姓名】<br/>`CONFIGURED_NAME`【配置的名称】<br/>`INPUT_SOURCE_TYPE`【输入源类型】<br/>`IS_CONFIGURED`【已配置】<br/>`CURRENT_VISIBILITY_STATE`【当前可见性状态】|`IDENTIFIER`【标识符】<br/>`INPUT_DEVICE_TYPE`【输入设备类型】<br/>`TARGET_VISIBILITY_STATE`【目标可见性状态】
|`HOMEKIT_SERVICE_TELEVISION_SPEAKER`|控制电视扬声器|`MUTE`【静音】|`ACTIVE`【状态】<br/>`VOLUME`【音量】<br/>`VOLUME_CONTROL_TYPE`【音量控制类型】<br/>`VOLUME_SELECTOR`【音量选择器】<br/>`NAME`【姓名】