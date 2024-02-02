//
//  MKCLReminderAlertView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2023/9/19.
//  Copyright © 2023 lovexiaoxia. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLReminderAlertViewModel : NSObject

@property (nonatomic, assign)BOOL needColor;

@property (nonatomic, copy)NSString *title;

@property (nonatomic, copy)NSString *intervalMsg;

@property (nonatomic, copy)NSString *durationMsg;

@end

@interface MKCLReminderAlertView : UIView

- (void)showAlertWithModel:(MKCLReminderAlertViewModel *)dataModel
             confirmAction:(void (^)(NSString *interval, NSString *duration, NSInteger color))confirmAction;

@end

NS_ASSUME_NONNULL_END
