//
//  MKCLDeviceListModel.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLDeviceModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLDeviceListModel : MKCLDeviceModel

/// 0:Good 1:Medium 2:Poor
@property (nonatomic, assign)NSInteger wifiLevel;

@end

NS_ASSUME_NONNULL_END
