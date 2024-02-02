//
//  MKCLFilterByBeaconModel.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12..
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MKCLFilterByBeaconDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLFilterByBeaconModel : NSObject

- (instancetype)initWithPageType:(mk_cl_filterByBeaconPageType)pageType;

@property (nonatomic, assign)BOOL isOn;

@property (nonatomic, copy)NSString *uuid;

@property (nonatomic, copy)NSString *minMajor;

@property (nonatomic, copy)NSString *maxMajor;

@property (nonatomic, copy)NSString *minMinor;

@property (nonatomic, copy)NSString *maxMinor;

- (void)readDataWithSucBlock:(void (^)(void))sucBlock failedBlock:(void (^)(NSError *error))failedBlock;

- (void)configDataWithSucBlock:(void (^)(void))sucBlock failedBlock:(void (^)(NSError *error))failedBlock;

@end

NS_ASSUME_NONNULL_END
