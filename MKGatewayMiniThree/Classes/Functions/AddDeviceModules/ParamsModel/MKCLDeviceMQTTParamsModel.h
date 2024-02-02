//
//  MKCLDeviceMQTTParamsModel.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKCLDeviceModel;
@interface MKCLDeviceMQTTParamsModel : NSObject

@property (nonatomic, assign)BOOL wifiConfig;

@property (nonatomic, assign)BOOL mqttConfig;

@property (nonatomic, strong)MKCLDeviceModel *deviceModel;

+ (MKCLDeviceMQTTParamsModel *)shared;

+ (void)sharedDealloc;

@end

NS_ASSUME_NONNULL_END
