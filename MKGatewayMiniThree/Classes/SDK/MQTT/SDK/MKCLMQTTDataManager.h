//
//  MKCLMQTTDataManager.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MKCLServerConfigDefines.h"

#import "MKCLMQTTTaskID.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const MKCLMQTTSessionManagerStateChangedNotification;

extern NSString *const MKCLReceiveDeviceOnlineNotification;

extern NSString *const MKCLReceiveDeviceOTAResultNotification;

extern NSString *const MKCLReceiveDeviceNpcOTAResultNotification;

extern NSString *const MKCLReceiveDeviceResetByButtonNotification;

extern NSString *const MKCLReceiveDeviceUpdateMqttCertsResultNotification;

extern NSString *const MKCLReceiveDeviceNetStateNotification;

extern NSString *const MKCLReceiveDeviceDatasNotification;

extern NSString *const MKCLReceiveGatewayDisconnectBXPButtonNotification;

extern NSString *const MKCLReceiveGatewayDisconnectDeviceNotification;

extern NSString *const MKCLReceiveGatewayConnectedDeviceDatasNotification;

extern NSString *const MKCLReceiveBxpButtonDfuProgressNotification;

extern NSString *const MKCLReceiveBxpButtonDfuResultNotification;


extern NSString *const MKCLReceiveDeviceOfflineNotification;

@protocol MKCLReceiveDeviceDatasDelegate <NSObject>

- (void)mk_cl_receiveDeviceDatas:(NSDictionary *)data;

@end

@interface MKCLMQTTDataManager : NSObject<MKCLServerManagerProtocol>

@property (nonatomic, weak)id <MKCLReceiveDeviceDatasDelegate>dataDelegate;

@property (nonatomic, assign, readonly)MKCLMQTTSessionManagerState state;

+ (MKCLMQTTDataManager *)shared;

+ (void)singleDealloc;

/// 当前app连接服务器参数
@property (nonatomic, strong, readonly, getter=currentServerParams)id <MKCLServerParamsProtocol>serverParams;

/// 当前用户有没有设置MQTT的订阅topic，如果设置了，则只能定于这个topic，如果没有设置，则订阅添加的设备的topic
@property (nonatomic, copy, readonly, getter=currentSubscribeTopic)NSString *subscribeTopic;

/// 当前用户有没有设置MQTT的订阅topic，如果设置了，则只能定于这个topic，如果没有设置，则订阅添加的设备的topic
@property (nonatomic, copy, readonly, getter=currentPublishedTopic)NSString *publishedTopic;

/// 将参数保存到本地，下次启动通过该参数连接服务器
/// @param protocol protocol
- (BOOL)saveServerParams:(id <MKCLServerParamsProtocol>)protocol;

/**
 清除本地记录的设置信息
 */
- (BOOL)clearLocalData;

#pragma mark - *****************************服务器交互部分******************************

/// 开始连接服务器，前提是必须服务器参数不能为空
- (BOOL)connect;

- (void)disconnect;

/**
 Subscribe the topic

 @param topicList topicList
 */
- (void)subscriptions:(NSArray <NSString *>*)topicList;

/**
 Unsubscribe the topic
 
 @param topicList topicList
 */
- (void)unsubscriptions:(NSArray <NSString *>*)topicList;

- (void)clearAllSubscriptions;

/// Send Data
/// @param data json
/// @param topic topic,1-128 Characters
/// @param macAddress macAddress,6字节16进制，不包含任何符号AABBCCDDEEFF
/// @param taskID taskID
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
- (void)sendData:(NSDictionary *)data
           topic:(NSString *)topic
      macAddress:(NSString *)macAddress
          taskID:(mk_cl_serverOperationID)taskID
        sucBlock:(void (^)(id returnData))sucBlock
     failedBlock:(void (^)(NSError *error))failedBlock;

/// Send Data
/// @param data json
/// @param topic topic,1-128 Characters
/// @param macAddress macAddress,6字节16进制，不包含任何符号AABBCCDDEEFF
/// @param taskID taskID
/// @param timeout 任务超时时间
/// @param sucBlock Success callback
/// @param failedBlock Failed callback
- (void)sendData:(NSDictionary *)data
           topic:(NSString *)topic
      macAddress:(NSString *)macAddress
          taskID:(mk_cl_serverOperationID)taskID
         timeout:(NSInteger)timeout
        sucBlock:(void (^)(id returnData))sucBlock
     failedBlock:(void (^)(NSError *error))failedBlock;

@end

NS_ASSUME_NONNULL_END
