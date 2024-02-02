//
//  MKCLTestController.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 lovexiaoxia. All rights reserved.
//

#import "MKCLTestController.h"

#import "Masonry.h"

#import "MKCustomUIAdopter.h"

#import "MKCLDeviceListController.h"

@interface MKCLTestController ()

@end

@implementation MKCLTestController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.defaultTitle = @"Remote gateway";
    self.leftButton.hidden = YES;
    UIButton *button = [MKCustomUIAdopter customButtonWithTitle:@"MKGW-mini03-20D"
                                                         target:self
                                                         action:@selector(pushRemoteGatewayPage)];
    [self.view addSubview:button];
    [button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.mas_equalTo(self.view.mas_centerX);
        make.width.mas_equalTo(180.f);
        make.centerY.mas_equalTo(self.view.mas_centerY);
        make.height.mas_equalTo(40.f);
    }];
}

- (void)pushRemoteGatewayPage {
    MKCLDeviceListController *vc = [[MKCLDeviceListController alloc] init];
    vc.connectServer = YES;
    [self.navigationController pushViewController:vc animated:YES];
}

@end
