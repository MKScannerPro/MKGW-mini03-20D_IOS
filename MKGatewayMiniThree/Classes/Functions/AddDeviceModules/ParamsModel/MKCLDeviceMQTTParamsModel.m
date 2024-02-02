//
//  MKCLDeviceMQTTParamsModel.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLDeviceMQTTParamsModel.h"

#import "MKCLDeviceModel.h"

static MKCLDeviceMQTTParamsModel *paramsModel = nil;
static dispatch_once_t onceToken;

@implementation MKCLDeviceMQTTParamsModel

+ (MKCLDeviceMQTTParamsModel *)shared {
    dispatch_once(&onceToken, ^{
        if (!paramsModel) {
            paramsModel = [MKCLDeviceMQTTParamsModel new];
        }
    });
    return paramsModel;
}

+ (void)sharedDealloc {
    paramsModel = nil;
    onceToken = 0;
}

#pragma mark - getter
- (MKCLDeviceModel *)deviceModel {
    if (!_deviceModel) {
        _deviceModel = [[MKCLDeviceModel alloc] init];
    }
    return _deviceModel;
}

@end
