//
//  MKCLInterface+MKCLConfig.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLInterface.h"

#import "MKCLSDKNormalDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLInterface (MKCLConfig)

#pragma mark ******************Custom parameter configuration*********************

#pragma mark *********************System Params************************

/// The device enter STA mode.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_enterSTAModeWithSucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure NTP server domain name.
/// @param host 0~64 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configNTPServerHost:(NSString *)host
                      sucBlock:(void (^)(void))sucBlock
                   failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the current time zone to the device.(MK107)
/// @param timeZone Time Zone(-12~12)
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configTimeZone:(NSInteger)timeZone
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock;

#pragma mark *********************MQTT Params************************
/// Configure the domain name of the MQTT server.
/// @param host 1~64 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerHost:(NSString *)host
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the port number of the MQTT server.
/// @param port 0~65535
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerPort:(NSInteger)port
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure Client ID of the MQTT server.
/// @param clientID 1~64 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configClientID:(NSString *)clientID
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the user name for the device to connect to the server. If the server passes the certificate or does not require any authentication, you do not need to fill in.
/// @param userName 0~256 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerUserName:(NSString *)userName
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the password for the device to connect to the server. If the server passes the certificate or does not require any authentication, you do not need to fill in.
/// @param password 0~256 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerPassword:(NSString *)password
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure clean session of the  MQTT server.
/// @param clean clean
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerCleanSession:(BOOL)clean
                           sucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure Keep Alive of the MQTT server.
/// @param interval 10s~120s.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerKeepAlive:(NSInteger)interval
                        sucBlock:(void (^)(void))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure Qos of the MQTT server.
/// @param mode mode
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configServerQos:(mk_cl_mqttServerQosMode)mode
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the subscription topic of the device.
/// @param subscibeTopic 1~128 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configSubscibeTopic:(NSString *)subscibeTopic
                      sucBlock:(void (^)(void))sucBlock
                   failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the publishing theme of the device.
/// @param publishTopic 1~128 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configPublishTopic:(NSString *)publishTopic
                     sucBlock:(void (^)(void))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the switch state of MQTT LWT.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLWTStatus:(BOOL)isOn
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure Qos of the MQTT LWT.
/// @param mode mode
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLWTQos:(mk_cl_mqttServerQosMode)mode
               sucBlock:(void (^)(void))sucBlock
            failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the retain state of MQTT LWT.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLWTRetain:(BOOL)isOn
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the topic of MQTT LWT.
/// @param topic 1~128 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLWTTopic:(NSString *)topic
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the message of MQTT LWT.
/// @param payload 1~128 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLWTPayload:(NSString *)payload
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the device tcp communication encryption method.
/// @param mode mode
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configConnectMode:(mk_cl_connectMode)mode
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure the root certificate of the MQTT server.
/// @param caFile caFile
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configCAFile:(NSData *)caFile
               sucBlock:(void (^)(void))sucBlock
            failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure client certificate.
/// @param cert cert
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configClientCert:(NSData *)cert
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure client private key.
/// @param privateKey privateKey
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configClientPrivateKey:(NSData *)privateKey
                         sucBlock:(void (^)(void))sucBlock
                      failedBlock:(void (^)(NSError *error))failedBlock;


#pragma mark *********************WIFI Params************************

/// Configure SSID of WIFI.
/// @param ssid 1~32 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configWIFISSID:(NSString *)ssid
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock;

/// Configure password of WIFI.(WIFI Security is persional.)
/// @param password 0~64 character ascii code.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configWIFIPassword:(NSString *)password
                     sucBlock:(void (^)(void))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock;

/// DHCP Status.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configDHCPStatus:(BOOL)isOn
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// IP Information.
/// @param ip e.g.(@"47.104.81.55")
/// @param mask e.g.(@"255.255.255.255")
/// @param gateway e.g.(@"255.255.255.1")
/// @param dns e.g.(@"47.104.81.55")
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configIpAddress:(NSString *)ip
                      mask:(NSString *)mask
                   gateway:(NSString *)gateway
                       dns:(NSString *)dns
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock;

/// Please note the country&Band is a configuration for 5GHZ WiFi,if using 2.4GHz WiFi, there is no need to choose the band.
/// @param parameter country&Band
/*
 parameter:
 0:Argentina、Mexico
 1:Australia、New Zealand
 2:Bahrain、Egypt、Israel、India
 3:Bolivia、Chile、China、El Salvador
 4:Canada
 5:Europe
 6:Indonesia
 7:Japan
 8:Jordan
 9:Korea、US
 10:Latin America-1
 11:Latin America-2
 12:Latin America-3
 13:Lebanon
 14:Malaysia
 15:Qatar
 16:Russia
 17:Singapore
 18:Taiwan
 19:Tunisia
 20:Venezuela
 21:Worldwide
 */
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configCountryBand:(NSInteger)parameter
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

#pragma mark *********************Filter Params************************

/// The device will uplink valid ADV data with RSSI no less than rssi dBm.
/// @param rssi -127 dBm ~ 0 dBm.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configRssiFilterValue:(NSInteger)rssi
                        sucBlock:(void (^)(void))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock;

/// Broadcast content filtering logic.
/// @param relationship relationship
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configFilterRelationship:(mk_cl_filterRelationship)relationship
                           sucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock;

/// Filtered list of mac addresses.
/// @param macList You can set up to 10 filters.1-6 Bytes.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configFilterMACAddressList:(NSArray <NSString *>*)macList
                             sucBlock:(void (^)(void))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Filtered list of Adv Name.
/// @param nameList You can set up to 10 filters.1-20 Characters.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configFilterAdvNameList:(NSArray <NSString *>*)nameList
                          sucBlock:(void (^)(void))sucBlock
                       failedBlock:(void (^)(NSError *error))failedBlock;

#pragma mark *********************BLE Adv Params************************

/// The advertise status of iBeacon.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configAdvertiseBeaconStatus:(BOOL)isOn
                              sucBlock:(void (^)(void))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock;

/// Major.
/// @param major 0-65535.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configBeaconMajor:(NSInteger)major
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Minor.
/// @param minor 0-65535.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configBeaconMinor:(NSInteger)minor
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// UUID.
/// @param uuid 16 Bytes.
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configBeaconUUID:(NSString *)uuid
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock;

/// ADV interval.
/// @param interval 1 x 100ms ~ 100 x 100ms
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configAdvInterval:(NSInteger)interval
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock;

/// Tx Power.
/// @param txPower 0~15
/*
    Tx Power:
 0：-24dbm
 1：-21dbm
 2：-18dbm
 3：-15dbm
 4：-12dbm
 5：-9dbm
 6：-6dbm
 7：-3dbm
 8：0dbm
 9：3dbm
 10：6dbm
 11：9dbm
 12：12dbm
 13：15dbm
 14：18dbm
 15：21dbm
 */
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configTxPower:(NSInteger)txPower
                sucBlock:(void (^)(void))sucBlock
             failedBlock:(void (^)(NSError *error))failedBlock;

#pragma mark *********************Metering Params************************

/// Switch of the metering.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configMeteringSwitch:(BOOL)isOn
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock;

/// Power reporting interval.
/// @param interval 1s-86400s
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configPowerReportInterval:(NSInteger)interval
                            sucBlock:(void (^)(void))sucBlock
                         failedBlock:(void (^)(NSError *error))failedBlock;

/// Energy reporting interval.
/// @param interval 1min-1440mins
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configEnergyReportInterval:(NSInteger)interval
                             sucBlock:(void (^)(void))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock;

/// Load detection notification.
/// @param isOn isOn
/// @param sucBlock Success callback
/// @param failedBlock Failure callback
+ (void)cl_configLoadDetectionNotificationStatus:(BOOL)isOn
                                        sucBlock:(void (^)(void))sucBlock
                                     failedBlock:(void (^)(NSError *error))failedBlock;

@end

NS_ASSUME_NONNULL_END
