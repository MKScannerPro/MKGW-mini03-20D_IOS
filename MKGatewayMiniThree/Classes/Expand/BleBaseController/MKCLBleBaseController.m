//
//  MKCLBleBaseController.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLBleBaseController.h"

#import "MKMacroDefines.h"
#import "UIView+MKAdd.h"

#import "MKCLCentralManager.h"

@interface MKCLBleBaseController ()

@end

@implementation MKCLBleBaseController

- (void)dealloc {
    NSLog(@"MKCLBleBaseController销毁");
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceConnectStateChanged)
                                                 name:mk_cl_peripheralConnectStateChangedNotification
                                               object:nil];
}

#pragma mark - note
- (void)deviceConnectStateChanged {
    if ([MKCLCentralManager shared].connectStatus == mk_cl_centralConnectStatusConnected) {
        return;
    }
    if (![MKBaseViewController isCurrentViewControllerVisible:self]) {
        return;
    }
    [self.view showCentralToast:@"Device disconnect!"];
    [self performSelector:@selector(gotoScanPage) withObject:nil afterDelay:0.5f];
}

#pragma mark - private method
- (void)gotoScanPage {
    [self popToViewControllerWithClassName:@"MKCLScanPageController"];
}

@end
