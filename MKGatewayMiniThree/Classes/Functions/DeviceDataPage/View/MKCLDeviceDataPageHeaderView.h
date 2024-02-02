//
//  MKCLDeviceDataPageHeaderView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLDeviceDataPageHeaderViewModel : NSObject

@property (nonatomic, assign)BOOL isOn;

@end

@protocol MKCLDeviceDataPageHeaderViewDelegate <NSObject>

- (void)cl_updateLoadButtonAction;

- (void)cl_powerButtonAction;

- (void)cl_scannerStatusChanged:(BOOL)isOn;

- (void)cl_manageBleDeviceAction;

@end

@interface MKCLDeviceDataPageHeaderView : UIView

@property (nonatomic, strong)MKCLDeviceDataPageHeaderViewModel *dataModel;

@property (nonatomic, weak)id <MKCLDeviceDataPageHeaderViewDelegate>delegate;

- (void)updateTotalNumbers:(NSInteger)numbers;

@end

NS_ASSUME_NONNULL_END
