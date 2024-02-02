//
//  MKCLMQTTLWTForDeviceView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMQTTLWTForDeviceViewModel : NSObject

@property (nonatomic, assign)BOOL lwtStatus;

@property (nonatomic, assign)BOOL lwtRetain;

@property (nonatomic, assign)NSInteger lwtQos;

@property (nonatomic, copy)NSString *lwtTopic;

@property (nonatomic, copy)NSString *lwtPayload;

@end

@protocol MKCLMQTTLWTForDeviceViewDelegate <NSObject>

- (void)cl_lwt_statusChanged:(BOOL)isOn;

- (void)cl_lwt_retainChanged:(BOOL)isOn;

- (void)cl_lwt_qosChanged:(NSInteger)qos;

- (void)cl_lwt_topicChanged:(NSString *)text;

- (void)cl_lwt_payloadChanged:(NSString *)text;

@end

@interface MKCLMQTTLWTForDeviceView : UIView

@property (nonatomic, strong)MKCLMQTTLWTForDeviceViewModel *dataModel;

@property (nonatomic, weak)id <MKCLMQTTLWTForDeviceViewDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
