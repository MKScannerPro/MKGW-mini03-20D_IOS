//
//  MKCLMQTTInterface.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MKCLMQTTConfigDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMQTTInterface : NSObject

#pragma mark *********************Config************************

/// Reboot.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_rebootDeviceWithMacAddress:(NSString *)macAddress
                                topic:(NSString *)topic
                             sucBlock:(void (^)(id returnData))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Reset device by button.
/// @param type type
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configKeyResetType:(mk_cl_keyResetType)type
                   macAddress:(NSString *)macAddress
                        topic:(NSString *)topic
                     sucBlock:(void (^)(id returnData))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// The reporting interval of the device's network status.
/// @param interval 0s or 30s ~ 86400s
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configNetworkStatusReportInterval:(NSInteger)interval
                                  macAddress:(NSString *)macAddress
                                       topic:(NSString *)topic
                                    sucBlock:(void (^)(id returnData))sucBlock
                                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Reconnect timeout.
/// @param timeout 0~1440 Mins.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configReconnectTimeout:(NSInteger)timeout
                       macAddress:(NSString *)macAddress
                            topic:(NSString *)topic
                         sucBlock:(void (^)(id returnData))sucBlock
                      failedBlock:(void (^)(NSError *error))failedBlock;

/// WIFI OTA.
/// @param filePath 1-256 Characters
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configOTAWithFilePath:(NSString *)filePath
                      macAddress:(NSString *)macAddress
                           topic:(NSString *)topic
                        sucBlock:(void (^)(id returnData))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the NTP server.
/// @param isOn isOn
/// @param host 0-64 Characters
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configNTPServer:(BOOL)isOn
                      host:(NSString *)host
                macAddress:(NSString *)macAddress
                     topic:(NSString *)topic
                  sucBlock:(void (^)(id returnData))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the UTC time zone of the device, and the device will reset the time according to the time zone.
/// @param timeZone Time Zone(-24~28,Unit:0.5)
/// @param timestamp timestamp
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configDeviceTimeZone:(NSInteger)timeZone
                      timestamp:(NSTimeInterval)timestamp
                     macAddress:(NSString *)macAddress
                          topic:(NSString *)topic
                       sucBlock:(void (^)(id returnData))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Communication timeout.
/// @param timeout 0~60 Mins.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configCommunicationTimeout:(NSInteger)timeout
                           macAddress:(NSString *)macAddress
                                topic:(NSString *)topic
                             sucBlock:(void (^)(id returnData))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure indicator status.
/// @param protocol protocol.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configIndicatorLightStatus:(id <cl_indicatorLightStatusProtocol>)protocol
                           macAddress:(NSString *)macAddress
                                topic:(NSString *)topic
                             sucBlock:(void (^)(id returnData))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Reset.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_resetDeviceWithMacAddress:(NSString *)macAddress
                               topic:(NSString *)topic
                            sucBlock:(void (^)(id returnData))sucBlock
                         failedBlock:(void (^)(NSError *error))failedBlock;

/// NPC OTA.
/// @param filePath 1-256 Characters
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configNpcOTAWithFilePath:(NSString *)filePath
                         macAddress:(NSString *)macAddress
                              topic:(NSString *)topic
                           sucBlock:(void (^)(id returnData))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Modify Wifi.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_modifyWifiInfos:(id <mk_cl_mqttModifyWifiProtocol>)protocol
                macAddress:(NSString *)macAddress
                     topic:(NSString *)topic
                  sucBlock:(void (^)(id returnData))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Network Settings.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_modifyNetworkInfos:(id <mk_cl_mqttModifyNetworkProtocol>)protocol
                   macAddress:(NSString *)macAddress
                        topic:(NSString *)topic
                     sucBlock:(void (^)(id returnData))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// MQTT Settings.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_modifyMqttInfos:(id <mk_cl_modifyMqttServerProtocol>)protocol
                macAddress:(NSString *)macAddress
                     topic:(NSString *)topic
                  sucBlock:(void (^)(id returnData))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// MQTT certificate update.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_modifyMqttCerts:(id <mk_cl_modifyMqttServerCertsProtocol>)protocol
                macAddress:(NSString *)macAddress
                     topic:(NSString *)topic
                  sucBlock:(void (^)(id returnData))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Config scan status.
/// @param isOn isOn
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configScanSwitchStatus:(BOOL)isOn
                       macAddress:(NSString *)macAddress
                            topic:(NSString *)topic
                         sucBlock:(void (^)(id returnData))sucBlock
                      failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the filter relationship.
/// @param relationship relationship
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterRelationship:(mk_cl_filterRelationship)relationship
                         macAddress:(NSString *)macAddress
                              topic:(NSString *)topic
                           sucBlock:(void (^)(id returnData))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by RSSI
/// @param rssi -127dBm~0dBm
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByRSSI:(NSInteger)rssi
                   macAddress:(NSString *)macAddress
                        topic:(NSString *)topic
                     sucBlock:(void (^)(id returnData))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by MAC Address.
/// @param macList The filtered mac address list contains up to 10 filtering options, and the length of each option should be 1 to 6 bytes of hexadecimal data.If the number is 0, it means that the historical configuration data is cleared.
/// @param preciseMatch Precise Match is On.
/// @param reverseFilter Reverse Filter is On.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByMacAddress:(nonnull NSArray <NSString *>*)macList
                       preciseMatch:(BOOL)preciseMatch
                      reverseFilter:(BOOL)reverseFilter
                         macAddress:(NSString *)macAddress
                              topic:(NSString *)topic
                           sucBlock:(void (^)(id returnData))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by ADV Name.
/// @param nameList The list of filtered device broadcast names contains up to 10 filtering options, and each option should be 1-20 characters in length. If the incoming number is zero, it means that the filter options are cleared.
/// @param preciseMatch Precise Match is On.
/// @param reverseFilter Reverse Filter is On.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByADVName:(nonnull NSArray <NSString *>*)nameList
                    preciseMatch:(BOOL)preciseMatch
                   reverseFilter:(BOOL)reverseFilter
                      macAddress:(NSString *)macAddress
                           topic:(NSString *)topic
                        sucBlock:(void (^)(id returnData))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by iBeacon.
/// @param isOn isOn
/// @param minMinor 0~65535
/// @param maxMinor minMinor <= maxMinor < 65535
/// @param minMajor 0~65535
/// @param maxMajor minMajor <= maxMajor < 65535
/// @param uuid 0~16 Bytes.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByBeacon:(BOOL)isOn
                       minMinor:(NSInteger)minMinor
                       maxMinor:(NSInteger)maxMinor
                       minMajor:(NSInteger)minMajor
                       maxMajor:(NSInteger)maxMajor
                           uuid:(NSString *)uuid
                     macAddress:(NSString *)macAddress
                          topic:(NSString *)topic
                       sucBlock:(void (^)(id returnData))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by UID Data.
/// @param isOn isOn
/// @param namespaceID 0~10 Bytes.
/// @param instanceID 0~6 Bytes.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByUID:(BOOL)isOn
                 namespaceID:(NSString *)namespaceID
                  instanceID:(NSString *)instanceID
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by URL Data.
/// @param isOn isOn
/// @param url 0-37 Characters
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByURL:(BOOL)isOn
                         url:(NSString *)url
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by TLM Data.
/// @param isOn isOn
/// @param tlm tlm
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByTLM:(BOOL)isOn
                         tlm:(mk_cl_filterByTLM)tlm
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-DeviceInfo.
/// @param isOn isOn
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterFilterBXPDeviceInfo:(BOOL)isOn
                                macAddress:(NSString *)macAddress
                                     topic:(NSString *)topic
                                  sucBlock:(void (^)(id returnData))sucBlock
                               failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-ACC.
/// @param isOn isOn
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterBXPAcc:(BOOL)isOn
                   macAddress:(NSString *)macAddress
                        topic:(NSString *)topic
                     sucBlock:(void (^)(id returnData))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-TH.
/// @param isOn isOn
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterBXPTH:(BOOL)isOn
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter By BXP-Button.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterBXPButton:(id <mk_cl_BLEFilterBXPButtonProtocol>)protocol
                      macAddress:(NSString *)macAddress
                           topic:(NSString *)topic
                        sucBlock:(void (^)(id returnData))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by BXP-Tag.
/// @param isOn isOn
/// @param preciseMatch Precise Match is On.
/// @param reverseFilter Reverse Filter is On.
/// @param tagIDList The filtered tag ID list contains up to 10 filtering options, and the length of each option should be 1 to 6 bytes of hexadecimal data.If the number is 0, it means that the historical configuration data is cleared.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByTag:(BOOL)isOn
                preciseMatch:(BOOL)preciseMatch
               reverseFilter:(BOOL)reverseFilter
                   tagIDList:(NSArray <NSString *>*)tagIDList
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter By PIR Presence.
/// @param protocol protocol
/// @param minMinor 0~65535
/// @param maxMinor minMinor <= maxMinor < 65535
/// @param minMajor 0~65535
/// @param maxMajor minMajor <= maxMajor < 65535
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByPir:(id <mk_cl_BLEFilterPirProtocol>)protocol
                    minMinor:(NSInteger)minMinor
                    maxMinor:(NSInteger)maxMinor
                    minMajor:(NSInteger)minMajor
                    maxMajor:(NSInteger)maxMajor
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by Other Raw Data.
/// @param isOn isOn
/// @param relationship The relationship changes with the original filter condition. If the original filter condition is empty, the relationship does not take effect; if the filter condition is 1, the relationship can only fill in mk_cl_filterByOther_A; if the filter condition is 2, you can choose mk_cl_filterByOther_AB/mk_cl_filterByOther_AOrB; If there are 3, select mk_cl_filterByOther_ABC/mk_cl_filterByOther_ABOrC/mk_cl_filterByOther_AOrBOrC.
/// @param rawDataList rawDataList
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByOtherDatas:(BOOL)isOn
                       relationship:(mk_cl_filterByOther)relationship
                        rawDataList:(NSArray <mk_cl_BLEFilterRawDataProtocol>*)rawDataList
                         macAddress:(NSString *)macAddress
                              topic:(NSString *)topic
                           sucBlock:(void (^)(id returnData))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure scan duplicate data parameters.
/// @param filter filter
/// @param period 1s~86400s
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configDuplicateDataFilter:(mk_cl_duplicateDataFilter)filter
                              period:(long long)period
                          macAddress:(NSString *)macAddress
                               topic:(NSString *)topic
                            sucBlock:(void (^)(id returnData))sucBlock
                         failedBlock:(void (^)(NSError *error))failedBlock;

/// Data report timeout.
/// @param timeout 100ms ~ 3000ms
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configDataReportTimeout:(NSInteger)timeout
                        macAddress:(NSString *)macAddress
                             topic:(NSString *)topic
                          sucBlock:(void (^)(id returnData))sucBlock
                       failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure scan data report content options.
/// @param protocol protocol
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configUploadDataOption:(id <cl_uploadDataOptionProtocol>)protocol
                       macAddress:(NSString *)macAddress
                            topic:(NSString *)topic
                         sucBlock:(void (^)(id returnData))sucBlock
                      failedBlock:(void (^)(NSError *error))failedBlock;

/// The gateway connects to the BXP-Button with the specified MAC address.
/// @param password 0-16 Characters
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_connectBXPButtonWithPassword:(NSString *)password
                                 bleMac:(NSString *)bleMacAddress
                             macAddress:(NSString *)macAddress
                                  topic:(NSString *)topic
                               sucBlock:(void (^)(id returnData))sucBlock
                            failedBlock:(void (^)(NSError *error))failedBlock;

/// The gateway disconnect the Bluetooth device with the specified MAC address.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_disconnectNormalBleDeviceWithBleMac:(NSString *)bleMacAddress
                                    macAddress:(NSString *)macAddress
                                         topic:(NSString *)topic
                                      sucBlock:(void (^)(id returnData))sucBlock
                                   failedBlock:(void (^)(NSError *error))failedBlock;

/// BXP-Button DFU.
/// @param firmwareUrl Firmware file URL.1- 256 Characters.
/// @param dataUrl Init data file URL.1- 256 Characters.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_startBXPButtonDfuWithFirmwareUrl:(NSString *)firmwareUrl
                                    dataUrl:(NSString *)dataUrl
                                     bleMac:(NSString *)bleMacAddress
                                 macAddress:(NSString *)macAddress
                                      topic:(NSString *)topic
                                   sucBlock:(void (^)(id returnData))sucBlock
                                failedBlock:(void (^)(NSError *error))failedBlock;


/// The gateway connects to the Bluetooth device with the specified MAC address.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_connectNormalBleDeviceWithBleMac:(NSString *)bleMacAddress
                                 macAddress:(NSString *)macAddress
                                      topic:(NSString *)topic
                                   sucBlock:(void (^)(id returnData))sucBlock
                                failedBlock:(void (^)(NSError *error))failedBlock;


#pragma mark *********************Read************************

/// Reset device by button.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readKeyResetTypeWithMacAddress:(NSString *)macAddress
                                    topic:(NSString *)topic
                                 sucBlock:(void (^)(id returnData))sucBlock
                              failedBlock:(void (^)(NSError *error))failedBlock;

/// Reset device Infomation.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readDeviceInfoWithMacAddress:(NSString *)macAddress
                                  topic:(NSString *)topic
                               sucBlock:(void (^)(id returnData))sucBlock
                            failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the reporting interval of the device's network status.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readNetworkStatusReportIntervalWithMacAddress:(NSString *)macAddress
                                                   topic:(NSString *)topic
                                                sucBlock:(void (^)(id returnData))sucBlock
                                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Reconnect Timeout.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readNetworkReconnectTimeoutWithMacAddress:(NSString *)macAddress
                                               topic:(NSString *)topic
                                            sucBlock:(void (^)(id returnData))sucBlock
                                         failedBlock:(void (^)(NSError *error))failedBlock;
/// NTP Server.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readNTPServerWithMacAddress:(NSString *)macAddress
                                 topic:(NSString *)topic
                              sucBlock:(void (^)(id returnData))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock;

/// UTC Time.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readDeviceUTCTimeWithMacAddress:(NSString *)macAddress
                                     topic:(NSString *)topic
                                  sucBlock:(void (^)(id returnData))sucBlock
                               failedBlock:(void (^)(NSError *error))failedBlock;

/// Communicate Timeout.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readCommunicateTimeoutWithMacAddress:(NSString *)macAddress
                                          topic:(NSString *)topic
                                       sucBlock:(void (^)(id returnData))sucBlock
                                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Indicator Status
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readIndicatorLightStatusWithMacAddress:(NSString *)macAddress
                                            topic:(NSString *)topic
                                         sucBlock:(void (^)(id returnData))sucBlock
                                      failedBlock:(void (^)(NSError *error))failedBlock;

/// Query whether the device can perform OTA upgrade.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readOtaStatusWithMacAddress:(NSString *)macAddress
                                 topic:(NSString *)topic
                              sucBlock:(void (^)(id returnData))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the wifi information that the device is currently connected to.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readWifiInfosWithMacAddress:(NSString *)macAddress
                                 topic:(NSString *)topic
                              sucBlock:(void (^)(id returnData))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the network information that the device is currently connected to.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readNetworkInfosWithMacAddress:(NSString *)macAddress
                                    topic:(NSString *)topic
                                 sucBlock:(void (^)(id returnData))sucBlock
                              failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the MQTT Params.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readMQTTParamsWithMacAddress:(NSString *)macAddress
                                  topic:(NSString *)topic
                               sucBlock:(void (^)(id returnData))sucBlock
                            failedBlock:(void (^)(NSError *error))failedBlock;

/// Read scan status.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readScanSwitchStatusWithMacAddress:(NSString *)macAddress
                                        topic:(NSString *)topic
                                     sucBlock:(void (^)(id returnData))sucBlock
                                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter Relationship.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterRelationshipWithMacAddress:(NSString *)macAddress
                                          topic:(NSString *)topic
                                       sucBlock:(void (^)(id returnData))sucBlock
                                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by Mac.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByRSSIWithMacAddress:(NSString *)macAddress
                                    topic:(NSString *)topic
                                 sucBlock:(void (^)(id returnData))sucBlock
                              failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by MAC Address.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByMacWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by ADV Name.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByADVNameWithMacAddress:(NSString *)macAddress
                                       topic:(NSString *)topic
                                    sucBlock:(void (^)(id returnData))sucBlock
                                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by Raw Data Status.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByRawDataStatusWithMacAddress:(NSString *)macAddress
                                             topic:(NSString *)topic
                                          sucBlock:(void (^)(id returnData))sucBlock
                                       failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by iBeacon.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByBeaconWithMacAddress:(NSString *)macAddress
                                      topic:(NSString *)topic
                                   sucBlock:(void (^)(id returnData))sucBlock
                                failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by UID.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByUIDWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by Url.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByUrlWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by TLM.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByTLMWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-DeviceInfo.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterBXPDeviceInfoStatusWithMacAddress:(NSString *)macAddress
                                                 topic:(NSString *)topic
                                              sucBlock:(void (^)(id returnData))sucBlock
                                           failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-Acc.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterBXPAccStatusWithMacAddress:(NSString *)macAddress
                                          topic:(NSString *)topic
                                       sucBlock:(void (^)(id returnData))sucBlock
                                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter switch status of BXP-TH.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterBXPTHStatusWithMacAddress:(NSString *)macAddress
                                         topic:(NSString *)topic
                                      sucBlock:(void (^)(id returnData))sucBlock
                                   failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter By BXP-Button.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterBXPButtonWithMacAddress:(NSString *)macAddress
                                       topic:(NSString *)topic
                                    sucBlock:(void (^)(id returnData))sucBlock
                                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter By BXP-Tag.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterBXPTagWithMacAddress:(NSString *)macAddress
                                    topic:(NSString *)topic
                                 sucBlock:(void (^)(id returnData))sucBlock
                              failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter By PIR Presence.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByPirWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by Other Raw Data.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterOtherDatasWithMacAddress:(NSString *)macAddress
                                        topic:(NSString *)topic
                                     sucBlock:(void (^)(id returnData))sucBlock
                                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Read scan duplicate data parameters.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readDuplicateDataFilterDatasWithMacAddress:(NSString *)macAddress
                                                topic:(NSString *)topic
                                             sucBlock:(void (^)(id returnData))sucBlock
                                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Data report timeout.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readDataReportTimeoutWithMacAddress:(NSString *)macAddress
                                         topic:(NSString *)topic
                                      sucBlock:(void (^)(id returnData))sucBlock
                                   failedBlock:(void (^)(NSError *error))failedBlock;

/// Read scan data report content option.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readUploadDataOptionWithMacAddress:(NSString *)macAddress
                                        topic:(NSString *)topic
                                     sucBlock:(void (^)(id returnData))sucBlock
                                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the service and feature information of the specified BXP-Button connected to the current gateway.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readBXPButtonConnectedDeviceInfoWithBleMacAddress:(NSString *)bleMacAddress
                                                  macAddress:(NSString *)macAddress
                                                       topic:(NSString *)topic
                                                    sucBlock:(void (^)(id returnData))sucBlock
                                                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the  BXP-Button's status that connected to the current gateway.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readBXPButtonConnectedStatusWithBleMacAddress:(NSString *)bleMacAddress
                                              macAddress:(NSString *)macAddress
                                                   topic:(NSString *)topic
                                                sucBlock:(void (^)(id returnData))sucBlock
                                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Dismiss Alarm Status.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_dismissBXPButtonAlarmStatusWithBleMacAddress:(NSString *)bleMacAddress
                                             macAddress:(NSString *)macAddress
                                                  topic:(NSString *)topic
                                               sucBlock:(void (^)(id returnData))sucBlock
                                            failedBlock:(void (^)(NSError *error))failedBlock;

/// LED Reminder.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param color LED Color.
/// @param interval flash interval.0-100(Unit:0.1s)
/// @param duration flash time.1-6000(Unit:0.1s).
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configDeviceLedReminderWithBleMac:(NSString *)bleMacAddress
                                    interval:(NSInteger)interval
                                    duration:(NSInteger)duration
                                  macAddress:(NSString *)macAddress
                                       topic:(NSString *)topic
                                    sucBlock:(void (^)(id returnData))sucBlock
                                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Buzzer Reminder.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param interval ring interval.0-100(Unit:0.1s).
/// @param duration ring time.1-6000(Unit:0.1s).
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configDeviceBuzzerReminderWithBleMac:(NSString *)bleMacAddress
                                       interval:(NSInteger)interval
                                       duration:(NSInteger)duration
                                     macAddress:(NSString *)macAddress
                                          topic:(NSString *)topic
                                       sucBlock:(void (^)(id returnData))sucBlock
                                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Query whether the Bluetooth gateway is connected to the device.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readGatewayBleConnectStatusWithMacAddress:(NSString *)macAddress
                                               topic:(NSString *)topic
                                            sucBlock:(void (^)(id returnData))sucBlock
                                         failedBlock:(void (^)(NSError *error))failedBlock;

/// Read the service and feature information of the specified device connected to the current gateway.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readNormalConnectedDeviceInfoWithBleMacAddress:(NSString *)bleMacAddress
                                               macAddress:(NSString *)macAddress
                                                    topic:(NSString *)topic
                                                 sucBlock:(void (^)(id returnData))sucBlock
                                              failedBlock:(void (^)(NSError *error))failedBlock;
/// Whether to open the characteristic's monitoring.
/// @param notify notify
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param serviceUUID serviceUUID
/// @param characteristicUUID characteristicUUID
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_notifyCharacteristic:(BOOL)notify
                  bleMacAddress:(NSString *)bleMacAddress
                    serviceUUID:(NSString *)serviceUUID
             characteristicUUID:(NSString *)characteristicUUID
                     macAddress:(NSString *)macAddress
                          topic:(NSString *)topic
                       sucBlock:(void (^)(id returnData))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;


/// Read the characteristic value of the connected device with the specified mac address.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param serviceUUID serviceUUID
/// @param characteristicUUID characteristicUUID
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readCharacteristicValueWithBleMacAddress:(NSString *)bleMacAddress
                                        serviceUUID:(NSString *)serviceUUID
                                 characteristicUUID:(NSString *)characteristicUUID
                                         macAddress:(NSString *)macAddress
                                              topic:(NSString *)topic
                                           sucBlock:(void (^)(id returnData))sucBlock
                                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Writes a value to the characteristic of the connected device for the specified mac address.
/// @param bleMacAddress The mac address of the target bluetooth device.(e.g.AABBCCDDEEFF)
/// @param value value(Byte)
/// @param serviceUUID serviceUUID
/// @param characteristicUUID characteristicUUID
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_writeValueToDeviceWithBleMacAddress:(NSString *)bleMacAddress
                                         value:(NSString *)value
                                   serviceUUID:(NSString *)serviceUUID
                            characteristicUUID:(NSString *)characteristicUUID
                                    macAddress:(NSString *)macAddress
                                         topic:(NSString *)topic
                                      sucBlock:(void (^)(id returnData))sucBlock
                                   failedBlock:(void (^)(NSError *error))failedBlock;

/// Advertise iBeacon.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readAdvertiseBeaconParamsWithMacAddress:(NSString *)macAddress
                                             topic:(NSString *)topic
                                          sucBlock:(void (^)(id returnData))sucBlock
                                       failedBlock:(void (^)(NSError *error))failedBlock;

/// Advertise iBeacon.
/// @param protocol protocol.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configAdvertiseBeaconParams:(id <cl_advertiseBeaconProtocol>)protocol
                            macAddress:(NSString *)macAddress
                                 topic:(NSString *)topic
                              sucBlock:(void (^)(id returnData))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by MK-TOF.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByTofWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filtered list of TOF List.
/// @param codeList You can set up to 10 filters.2 Bytes.
/// @param isOn Filter Status.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByTofList:(NSArray <NSString *>*)codeList
                            isOn:(BOOL)isOn
                      macAddress:(NSString *)macAddress
                           topic:(NSString *)topic
                        sucBlock:(void (^)(id returnData))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by PHY.
/// @param macAddress WIFI_STA Mac address of the device.(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_readFilterByPhyWithMacAddress:(NSString *)macAddress
                                   topic:(NSString *)topic
                                sucBlock:(void (^)(id returnData))sucBlock
                             failedBlock:(void (^)(NSError *error))failedBlock;

/// Filter by PHY.
/// @param phy phy.
/// @param macAddress WIFI_STA Mac address of the device(e.g.AABBCCDDEEFF)
/// @param topic topic 1-128 Characters
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
+ (void)cl_configFilterByPhy:(mk_cl_PHYMode)phy
                  macAddress:(NSString *)macAddress
                       topic:(NSString *)topic
                    sucBlock:(void (^)(id returnData))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

@end

NS_ASSUME_NONNULL_END
