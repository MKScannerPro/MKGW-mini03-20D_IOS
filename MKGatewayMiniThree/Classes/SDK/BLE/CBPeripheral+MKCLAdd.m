//
//  CBPeripheral+MKCLAdd.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "CBPeripheral+MKCLAdd.h"

#import <objc/runtime.h>

static const char *cl_manufacturerKey = "cl_manufacturerKey";
static const char *cl_deviceModelKey = "cl_deviceModelKey";
static const char *cl_hardwareKey = "cl_hardwareKey";
static const char *cl_softwareKey = "cl_softwareKey";
static const char *cl_firmwareKey = "cl_firmwareKey";

static const char *cl_passwordKey = "cl_passwordKey";
static const char *cl_disconnectTypeKey = "cl_disconnectTypeKey";
static const char *cl_customKey = "cl_customKey";

static const char *cl_passwordNotifySuccessKey = "cl_passwordNotifySuccessKey";
static const char *cl_disconnectTypeNotifySuccessKey = "cl_disconnectTypeNotifySuccessKey";
static const char *cl_customNotifySuccessKey = "cl_customNotifySuccessKey";

@implementation CBPeripheral (MKCLAdd)

- (void)cl_updateCharacterWithService:(CBService *)service {
    NSArray *characteristicList = service.characteristics;
    if ([service.UUID isEqual:[CBUUID UUIDWithString:@"180A"]]) {
        //设备信息
        for (CBCharacteristic *characteristic in characteristicList) {
            if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"2A24"]]) {
                objc_setAssociatedObject(self, &cl_deviceModelKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"2A26"]]) {
                objc_setAssociatedObject(self, &cl_firmwareKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"2A27"]]) {
                objc_setAssociatedObject(self, &cl_hardwareKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"2A28"]]) {
                objc_setAssociatedObject(self, &cl_softwareKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"2A29"]]) {
                objc_setAssociatedObject(self, &cl_manufacturerKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }
        }
        return;
    }
    if ([service.UUID isEqual:[CBUUID UUIDWithString:@"AA00"]]) {
        //自定义
        for (CBCharacteristic *characteristic in characteristicList) {
            if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA00"]]) {
                objc_setAssociatedObject(self, &cl_passwordKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA01"]]) {
                objc_setAssociatedObject(self, &cl_disconnectTypeKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }else if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA03"]]) {
                objc_setAssociatedObject(self, &cl_customKey, characteristic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            }
            [self setNotifyValue:YES forCharacteristic:characteristic];
        }
        return;
    }
}

- (void)cl_updateCurrentNotifySuccess:(CBCharacteristic *)characteristic {
    if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA00"]]) {
        objc_setAssociatedObject(self, &cl_passwordNotifySuccessKey, @(YES), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        return;
    }
    if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA01"]]) {
        objc_setAssociatedObject(self, &cl_disconnectTypeNotifySuccessKey, @(YES), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        return;
    }
    if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:@"AA03"]]) {
        objc_setAssociatedObject(self, &cl_customNotifySuccessKey, @(YES), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        return;
    }
}

- (BOOL)cl_connectSuccess {
    if (![objc_getAssociatedObject(self, &cl_customNotifySuccessKey) boolValue] || ![objc_getAssociatedObject(self, &cl_passwordNotifySuccessKey) boolValue] || ![objc_getAssociatedObject(self, &cl_disconnectTypeNotifySuccessKey) boolValue]) {
        return NO;
    }
    if (!self.cl_hardware || !self.cl_firmware) {
        return NO;
    }
    if (!self.cl_password || !self.cl_disconnectType || !self.cl_custom) {
        return NO;
    }
    return YES;
}

- (void)cl_setNil {
    objc_setAssociatedObject(self, &cl_manufacturerKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_deviceModelKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_hardwareKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_softwareKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_firmwareKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    
    objc_setAssociatedObject(self, &cl_passwordKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_disconnectTypeKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_customKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    
    objc_setAssociatedObject(self, &cl_passwordNotifySuccessKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_disconnectTypeNotifySuccessKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(self, &cl_customNotifySuccessKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

#pragma mark - getter

- (CBCharacteristic *)cl_manufacturer {
    return objc_getAssociatedObject(self, &cl_manufacturerKey);
}

- (CBCharacteristic *)cl_deviceModel {
    return objc_getAssociatedObject(self, &cl_deviceModelKey);
}

- (CBCharacteristic *)cl_hardware {
    return objc_getAssociatedObject(self, &cl_hardwareKey);
}

- (CBCharacteristic *)cl_software {
    return objc_getAssociatedObject(self, &cl_softwareKey);
}

- (CBCharacteristic *)cl_firmware {
    return objc_getAssociatedObject(self, &cl_firmwareKey);
}

- (CBCharacteristic *)cl_password {
    return objc_getAssociatedObject(self, &cl_passwordKey);
}

- (CBCharacteristic *)cl_disconnectType {
    return objc_getAssociatedObject(self, &cl_disconnectTypeKey);
}

- (CBCharacteristic *)cl_custom {
    return objc_getAssociatedObject(self, &cl_customKey);
}

@end
