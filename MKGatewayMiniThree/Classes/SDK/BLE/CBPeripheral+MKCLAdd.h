//
//  CBPeripheral+MKCLAdd.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface CBPeripheral (MKCLAdd)

/// R
@property (nonatomic, strong, readonly)CBCharacteristic *cl_manufacturer;

/// R
@property (nonatomic, strong, readonly)CBCharacteristic *cl_deviceModel;

/// R
@property (nonatomic, strong, readonly)CBCharacteristic *cl_hardware;

/// R
@property (nonatomic, strong, readonly)CBCharacteristic *cl_software;

/// R
@property (nonatomic, strong, readonly)CBCharacteristic *cl_firmware;

#pragma mark - custom

/// W/N
@property (nonatomic, strong, readonly)CBCharacteristic *cl_password;

/// N
@property (nonatomic, strong, readonly)CBCharacteristic *cl_disconnectType;

/// W/N
@property (nonatomic, strong, readonly)CBCharacteristic *cl_custom;

- (void)cl_updateCharacterWithService:(CBService *)service;

- (void)cl_updateCurrentNotifySuccess:(CBCharacteristic *)characteristic;

- (BOOL)cl_connectSuccess;

- (void)cl_setNil;

@end

NS_ASSUME_NONNULL_END
