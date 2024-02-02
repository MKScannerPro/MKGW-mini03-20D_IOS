//
//  MKCLUserCredentialsView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLUserCredentialsViewModel : NSObject

@property (nonatomic, copy)NSString *userName;

@property (nonatomic, copy)NSString *password;

@end

@protocol MKCLUserCredentialsViewDelegate <NSObject>

- (void)cl_mqtt_userCredentials_userNameChanged:(NSString *)userName;

- (void)cl_mqtt_userCredentials_passwordChanged:(NSString *)password;

@end

@interface MKCLUserCredentialsView : UIView

@property (nonatomic, strong)MKCLUserCredentialsViewModel *dataModel;

@property (nonatomic, weak)id <MKCLUserCredentialsViewDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
