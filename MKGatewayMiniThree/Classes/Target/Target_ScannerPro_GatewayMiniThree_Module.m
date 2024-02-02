//
//  Target_ScannerPro_GatewayMiniThree_Module.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "Target_ScannerPro_GatewayMiniThree_Module.h"

#import "MKCLDeviceListController.h"

@implementation Target_ScannerPro_GatewayMiniThree_Module

- (UIViewController *)Action_MKScannerPro_GatewayMiniThree_DeviceListPage:(NSDictionary *)params {
    MKCLDeviceListController *vc = [[MKCLDeviceListController alloc] init];
    vc.connectServer = YES;
    return vc;
}

@end
