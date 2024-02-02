//
//  MKCLMqttServerSettingView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MKCLMqttServerSettingViewDelegate <NSObject>

/// 底部按钮
/// @param index 0:Export Demo File   1:Import Config File  2:Clear All Configurations
- (void)cl_mqtt_deviecSetting_fileButtonPressed:(NSInteger)index;

@end

@interface MKCLMqttServerSettingView : UIView

@property (nonatomic, weak)id <MKCLMqttServerSettingViewDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
