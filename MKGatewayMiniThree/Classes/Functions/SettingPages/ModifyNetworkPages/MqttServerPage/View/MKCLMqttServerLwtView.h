//
//  MKCLMqttServerLwtView.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMqttServerLwtViewModel : NSObject

@property (nonatomic, assign)BOOL lwtStatus;

@property (nonatomic, assign)BOOL lwtRetain;

@property (nonatomic, assign)NSInteger lwtQos;

@property (nonatomic, copy)NSString *lwtTopic;

@property (nonatomic, copy)NSString *lwtPayload;

@end

@protocol MKCLMqttServerLwtViewDelegate <NSObject>

- (void)cl_lwt_statusChanged:(BOOL)isOn;

- (void)cl_lwt_retainChanged:(BOOL)isOn;

- (void)cl_lwt_qosChanged:(NSInteger)qos;

- (void)cl_lwt_topicChanged:(NSString *)text;

- (void)cl_lwt_payloadChanged:(NSString *)text;

@end

@interface MKCLMqttServerLwtView : UIView

@property (nonatomic, strong)MKCLMqttServerLwtViewModel *dataModel;

@property (nonatomic, weak)id <MKCLMqttServerLwtViewDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
