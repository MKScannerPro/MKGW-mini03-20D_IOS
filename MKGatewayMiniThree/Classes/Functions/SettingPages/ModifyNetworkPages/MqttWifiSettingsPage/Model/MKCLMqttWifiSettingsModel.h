//
//  MKCLMqttWifiSettingsModel.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MKCLMQTTConfigDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMqttWifiSettingsModel : NSObject<mk_cl_mqttModifyWifiProtocol,mk_cl_mqttModifyNetworkProtocol>

/// 1-32 Characters.
@property (nonatomic, copy)NSString *ssid;

/// 0-64 Characters.security为personal的时候才有效
@property (nonatomic, copy)NSString *wifiPassword;

/*
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
@property (nonatomic, assign)NSInteger country;

@property (nonatomic, assign)BOOL dhcp;

@property (nonatomic, copy)NSString *ip;

@property (nonatomic, copy)NSString *mask;

@property (nonatomic, copy)NSString *gateway;

@property (nonatomic, copy)NSString *dns;

- (void)readDataWithSucBlock:(void (^)(void))sucBlock failedBlock:(void (^)(NSError *error))failedBlock;

- (void)configDataWithSucBlock:(void (^)(void))sucBlock failedBlock:(void (^)(NSError *error))failedBlock;

@end

NS_ASSUME_NONNULL_END
