//
//  MKCLInterface+MKCLConfig.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLInterface+MKCLConfig.h"

#import "MKBLEBaseCentralManager.h"
#import "MKBLEBaseSDKDefines.h"
#import "MKBLEBaseSDKAdopter.h"

#import "MKCLCentralManager.h"
#import "MKCLOperationID.h"
#import "CBPeripheral+MKCLAdd.h"
#import "MKCLOperation.h"
#import "MKCLSDKDataAdopter.h"

static const NSInteger packDataMaxLen = 150;

#define centralManager [MKCLCentralManager shared]
#define peripheral ([MKCLCentralManager shared].peripheral)

@implementation MKCLInterface (MKCLConfig)

#pragma mark ********************自定义参数配置************************

#pragma mark *********************System Params************************
+ (void)cl_enterSTAModeWithSucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = @"ed010200";
    [self configDataWithTaskID:mk_cl_taskEnterSTAModeOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configNTPServerHost:(NSString *)host
                      sucBlock:(void (^)(void))sucBlock
                   failedBlock:(void (^)(NSError *error))failedBlock {
    if (host.length > 64) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:host];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:host.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0111",lenString,tempString];
    
    [self configDataWithTaskID:mk_cl_taskConfigNTPServerHostOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configTimeZone:(NSInteger)timeZone
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock {
    if (timeZone < -24 || timeZone > 28) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *zoneValue = [MKBLEBaseSDKAdopter hexStringFromSignedNumber:timeZone];
    NSString *commandString = [@"ed011201" stringByAppendingString:zoneValue];
    [self configDataWithTaskID:mk_cl_taskConfigTimeZoneOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

#pragma mark *********************MQTT Params************************

+ (void)cl_configServerHost:(NSString *)host
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(host) || host.length > 64) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:host];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:host.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0120",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigServerHostOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configServerPort:(NSInteger)port
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    if (port < 0 || port > 65535) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:port byteLen:2];
    NSString *commandString = [@"ed012102" stringByAppendingString:value];
    [self configDataWithTaskID:mk_cl_taskConfigServerPortOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configClientID:(NSString *)clientID
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(clientID) || clientID.length > 64) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:clientID];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:clientID.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0122",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigClientIDOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configServerUserName:(NSString *)userName
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock {
    if (userName.length > 256) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    if (!MKValidStr(userName)) {
        //空的
        NSString *commandString = @"ee0123010000";
        [self configDataWithTaskID:mk_cl_taskConfigServerUserNameOperation
                              data:commandString
                          sucBlock:sucBlock
                       failedBlock:failedBlock];
        return;
    }
    NSInteger totalNum = userName.length / packDataMaxLen;
    NSInteger packRemain = userName.length % packDataMaxLen;
    if (packRemain > 0) {
        totalNum ++;
    }
    NSString *totalNumString = [MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1];
    NSString *commandHeader = @"ee0123";
    dispatch_queue_t queue = dispatch_queue_create("configUserNameQueue", 0);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    dispatch_async(queue, ^{
        for (NSInteger i = 0; i < totalNum; i ++) {
            NSString *index = [MKBLEBaseSDKAdopter fetchHexValue:i byteLen:1];
            NSInteger len = packDataMaxLen;
            if ((i == totalNum - 1) && (packRemain > 0)) {
                //最后一帧
                len = packRemain;
            }
            NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:len byteLen:1];
            NSString *asciiChar = [MKCLSDKDataAdopter fetchAsciiCode:[userName substringWithRange:NSMakeRange(i * packDataMaxLen, len)]];
            NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@%@",commandHeader,totalNumString,index,lenString,asciiChar];
            BOOL success = [self sendDataToPeripheral:commandString
                                               taskID:mk_cl_taskConfigServerUserNameOperation
                                            semaphore:semaphore];
            if (!success) {
                [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                return;
            }
        }
        MKBLEBase_main_safe(^{
            if (sucBlock) {
                sucBlock();
            }
        });
    });
}

+ (void)cl_configServerPassword:(NSString *)password
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock {
    if (password.length > 256) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    if (!MKValidStr(password)) {
        //空的
        NSString *commandString = @"ee0124010000";
        [self configDataWithTaskID:mk_cl_taskConfigServerPasswordOperation
                              data:commandString
                          sucBlock:sucBlock
                       failedBlock:failedBlock];
        return;
    }
    NSInteger totalNum = password.length / packDataMaxLen;
    NSInteger packRemain = password.length % packDataMaxLen;
    if (packRemain > 0) {
        totalNum ++;
    }
    NSString *totalNumString = [MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1];
    NSString *commandHeader = @"ee0124";
    dispatch_queue_t queue = dispatch_queue_create("configUserPasswordQueue", 0);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    dispatch_async(queue, ^{
        for (NSInteger i = 0; i < totalNum; i ++) {
            NSString *index = [MKBLEBaseSDKAdopter fetchHexValue:i byteLen:1];
            NSInteger len = packDataMaxLen;
            if ((i == totalNum - 1) && (packRemain > 0)) {
                //最后一帧
                len = packRemain;
            }
            NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:len byteLen:1];
            NSString *asciiChar = [MKCLSDKDataAdopter fetchAsciiCode:[password substringWithRange:NSMakeRange(i * packDataMaxLen, len)]];
            NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@%@",commandHeader,totalNumString,index,lenString,asciiChar];
            BOOL success = [self sendDataToPeripheral:commandString
                                               taskID:mk_cl_taskConfigServerPasswordOperation
                                            semaphore:semaphore];
            if (!success) {
                [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                return;
            }
        }
        MKBLEBase_main_safe(^{
            if (sucBlock) {
                sucBlock();
            }
        });
    });
}

+ (void)cl_configServerCleanSession:(BOOL)clean
                           sucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (clean ? @"ed01250101" : @"ed01250100");
    [self configDataWithTaskID:mk_cl_taskConfigServerCleanSessionOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configServerKeepAlive:(NSInteger)interval
                        sucBlock:(void (^)(void))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock {
    if (interval < 10 || interval > 120) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:interval byteLen:1];
    NSString *commandString = [@"ed012601" stringByAppendingString:value];
    [self configDataWithTaskID:mk_cl_taskConfigServerKeepAliveOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configServerQos:(mk_cl_mqttServerQosMode)mode
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *qosString = [MKCLSDKDataAdopter fetchMqttServerQosMode:mode];
    NSString *commandString = [@"ed012701" stringByAppendingString:qosString];
    [self configDataWithTaskID:mk_cl_taskConfigServerQosOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configSubscibeTopic:(NSString *)subscibeTopic
                      sucBlock:(void (^)(void))sucBlock
                   failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(subscibeTopic) || subscibeTopic.length > 128) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:subscibeTopic];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:subscibeTopic.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0128",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigSubscibeTopicOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configPublishTopic:(NSString *)publishTopic
                     sucBlock:(void (^)(void))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(publishTopic) || publishTopic.length > 128) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:publishTopic];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:publishTopic.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0129",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigPublishTopicOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLWTStatus:(BOOL)isOn
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed012a0101" : @"ed012a0100");
    [self configDataWithTaskID:mk_cl_taskConfigLWTStatusOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLWTQos:(mk_cl_mqttServerQosMode)mode
                sucBlock:(void (^)(void))sucBlock
             failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *qosString = [MKCLSDKDataAdopter fetchMqttServerQosMode:mode];
    NSString *commandString = [@"ed012b01" stringByAppendingString:qosString];
    [self configDataWithTaskID:mk_cl_taskConfigLWTQosOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLWTRetain:(BOOL)isOn
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed012c0101" : @"ed012c0100");
    [self configDataWithTaskID:mk_cl_taskConfigLWTRetainOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLWTTopic:(NSString *)topic
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(topic) || topic.length > 128) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:topic];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:topic.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed012d",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigLWTTopicOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLWTPayload:(NSString *)payload
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(payload) || payload.length > 128) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:payload];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:payload.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed012e",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigLWTPayloadOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configConnectMode:(mk_cl_connectMode)mode
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *modeString = [MKCLSDKDataAdopter fetchConnectModeString:mode];
    NSString *commandString = [@"ed012f01" stringByAppendingString:modeString];
    [self configDataWithTaskID:mk_cl_taskConfigConnectModeOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configCAFile:(NSData *)caFile
               sucBlock:(void (^)(void))sucBlock
            failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidData(caFile)) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *caStrings = [MKBLEBaseSDKAdopter hexStringFromData:caFile];
    NSInteger totalNum = (caStrings.length / 2) / packDataMaxLen;
    NSInteger packRemain = (caStrings.length / 2) % packDataMaxLen;
    if (packRemain > 0) {
        totalNum ++;
    }
    NSString *commandHeader = [NSString stringWithFormat:@"%@%@",@"ee0130",[MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1]];
    dispatch_queue_t queue = dispatch_queue_create("configCAFileQueue", 0);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    dispatch_async(queue, ^{
        for (NSInteger i = 0; i < totalNum; i ++) {
            NSString *index = [MKBLEBaseSDKAdopter fetchHexValue:i byteLen:1];
            NSInteger len = packDataMaxLen;
            if ((i == totalNum - 1) && (packRemain > 0)) {
                //最后一帧
                len = packRemain;
            }
            NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:len byteLen:1];
            NSString *subChar = [caStrings substringWithRange:NSMakeRange(i * 2 * packDataMaxLen, 2 * len)];
            NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@",commandHeader,index,lenString,subChar];
            BOOL success = [self sendDataToPeripheral:commandString
                                               taskID:mk_cl_taskConfigCAFileOperation
                                            semaphore:semaphore];
            if (!success) {
                [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                return;
            }
        }
        MKBLEBase_main_safe(^{
            if (sucBlock) {
                sucBlock();
            }
        });
    });
}

+ (void)cl_configClientCert:(NSData *)cert
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidData(cert)) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *certStrings = [MKBLEBaseSDKAdopter hexStringFromData:cert];
    NSInteger totalNum = (certStrings.length / 2) / packDataMaxLen;
    NSInteger packRemain = (certStrings.length / 2) % packDataMaxLen;
    if (packRemain > 0) {
        totalNum ++;
    }
    NSString *commandHeader = [NSString stringWithFormat:@"%@%@",@"ee0131",[MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1]];
    dispatch_queue_t queue = dispatch_queue_create("configCertQueue", 0);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    dispatch_async(queue, ^{
        for (NSInteger i = 0; i < totalNum; i ++) {
            NSString *index = [MKBLEBaseSDKAdopter fetchHexValue:i byteLen:1];
            NSInteger len = packDataMaxLen;
            if ((i == totalNum - 1) && (packRemain > 0)) {
                //最后一帧
                len = packRemain;
            }
            NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:len byteLen:1];
            NSString *subChar = [certStrings substringWithRange:NSMakeRange(i * 2 * packDataMaxLen, 2 * len)];
            NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@",commandHeader,index,lenString,subChar];
            BOOL success = [self sendDataToPeripheral:commandString
                                               taskID:mk_cl_taskConfigClientCertOperation
                                            semaphore:semaphore];
            if (!success) {
                [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                return;
            }
        }
        MKBLEBase_main_safe(^{
            if (sucBlock) {
                sucBlock();
            }
        });
    });
}

+ (void)cl_configClientPrivateKey:(NSData *)privateKey
                         sucBlock:(void (^)(void))sucBlock
                      failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidData(privateKey)) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *privateKeyStrings = [MKBLEBaseSDKAdopter hexStringFromData:privateKey];
    NSInteger totalNum = (privateKeyStrings.length / 2) / packDataMaxLen;
    NSInteger packRemain = (privateKeyStrings.length / 2) % packDataMaxLen;
    if (packRemain > 0) {
        totalNum ++;
    }
    NSString *commandHeader = [NSString stringWithFormat:@"%@%@",@"ee0132",[MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1]];
    dispatch_queue_t queue = dispatch_queue_create("configPrivateKeyQueue", 0);
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    dispatch_async(queue, ^{
        for (NSInteger i = 0; i < totalNum; i ++) {
            NSString *index = [MKBLEBaseSDKAdopter fetchHexValue:i byteLen:1];
            NSInteger len = packDataMaxLen;
            if ((i == totalNum - 1) && (packRemain > 0)) {
                //最后一帧
                len = packRemain;
            }
            NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:len byteLen:1];
            NSString *subChar = [privateKeyStrings substringWithRange:NSMakeRange(i * 2 * packDataMaxLen, 2 * len)];
            NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@",commandHeader,index,lenString,subChar];
            BOOL success = [self sendDataToPeripheral:commandString
                                               taskID:mk_cl_taskConfigClientPrivateKeyOperation
                                            semaphore:semaphore];
            if (!success) {
                [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                return;
            }
        }
        MKBLEBase_main_safe(^{
            if (sucBlock) {
                sucBlock();
            }
        });
    });
}


#pragma mark *********************WIFI Params************************

+ (void)cl_configWIFISSID:(NSString *)ssid
                 sucBlock:(void (^)(void))sucBlock
              failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(ssid) || ssid.length > 32) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:ssid];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:ssid.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0140",lenString,tempString];
    [self configDataWithTaskID:mk_cl_taskConfigWIFISSIDOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configWIFIPassword:(NSString *)password
                     sucBlock:(void (^)(void))sucBlock
                  failedBlock:(void (^)(NSError *error))failedBlock {
    if (password.length > 64) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *tempString = [MKCLSDKDataAdopter fetchAsciiCode:password];
    NSString *lenString = [MKBLEBaseSDKAdopter fetchHexValue:password.length byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@",@"ed0141",lenString,tempString];
    
    [self configDataWithTaskID:mk_cl_taskConfigWIFIPasswordOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configDHCPStatus:(BOOL)isOn
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed01420101" : @"ed01420100");
    [self configDataWithTaskID:mk_cl_taskConfigDHCPStatusOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configIpAddress:(NSString *)ip
                      mask:(NSString *)mask
                   gateway:(NSString *)gateway
                       dns:(NSString *)dns
                  sucBlock:(void (^)(void))sucBlock
               failedBlock:(void (^)(NSError *error))failedBlock {
    if (![MKCLSDKDataAdopter isIpAddress:ip] || ![MKCLSDKDataAdopter isIpAddress:mask]
        || ![MKCLSDKDataAdopter isIpAddress:gateway] || ![MKCLSDKDataAdopter isIpAddress:dns]) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *ipValue = [MKCLSDKDataAdopter ipAddressToHex:ip];
    NSString *maskValue = [MKCLSDKDataAdopter ipAddressToHex:mask];
    NSString *gatewayValue = [MKCLSDKDataAdopter ipAddressToHex:gateway];
    NSString *dnsValue = [MKCLSDKDataAdopter ipAddressToHex:dns];
    NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@%@",@"ed014310",ipValue,maskValue,gatewayValue,dnsValue];
    [self configDataWithTaskID:mk_cl_taskConfigIpInfoOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configCountryBand:(NSInteger)parameter
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    if (parameter < 0 || parameter > 21) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *type = [MKBLEBaseSDKAdopter fetchHexValue:parameter byteLen:1];
    NSString *commandString = [@"ed014401" stringByAppendingString:type];
    [self configDataWithTaskID:mk_cl_taskConfigCountryBandOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

#pragma mark *********************Filter Params************************

+ (void)cl_configRssiFilterValue:(NSInteger)rssi
                        sucBlock:(void (^)(void))sucBlock
                     failedBlock:(void (^)(NSError *error))failedBlock {
    if (rssi < -127 || rssi > 0) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *rssiValue = [MKBLEBaseSDKAdopter hexStringFromSignedNumber:rssi];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed016001",rssiValue];
    [self configDataWithTaskID:mk_cl_taskConfigRssiFilterValueOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configFilterRelationship:(mk_cl_filterRelationship)relationship
                           sucBlock:(void (^)(void))sucBlock
                        failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:relationship byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed016101",value];
    [self configDataWithTaskID:mk_cl_taskConfigFilterRelationshipOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configFilterMACAddressList:(NSArray <NSString *>*)macList
                             sucBlock:(void (^)(void))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock {
    if (macList.count > 10) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *macString = @"";
    if (MKValidArray(macList)) {
        for (NSString *mac in macList) {
            if ((mac.length % 2 != 0) || !MKValidStr(mac) || mac.length > 12 || ![MKBLEBaseSDKAdopter checkHexCharacter:mac]) {
                [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
                return;
            }
            NSString *tempLen = [MKBLEBaseSDKAdopter fetchHexValue:(mac.length / 2) byteLen:1];
            NSString *string = [tempLen stringByAppendingString:mac];
            macString = [macString stringByAppendingString:string];
        }
    }
    NSString *dataLen = [MKBLEBaseSDKAdopter fetchHexValue:(macString.length / 2) byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"ed0164%@%@",dataLen,macString];
    [self configDataWithTaskID:mk_cl_taskConfigFilterMACAddressListOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configFilterAdvNameList:(NSArray <NSString *>*)nameList
                          sucBlock:(void (^)(void))sucBlock
                       failedBlock:(void (^)(NSError *error))failedBlock {
    if (nameList.count > 10) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    if (!MKValidArray(nameList)) {
        //无列表
        NSString *commandString = @"ee0167010000";
        [self configDataWithTaskID:mk_cl_taskConfigFilterAdvNameListOperation
                              data:commandString
                          sucBlock:sucBlock
                       failedBlock:failedBlock];
        return;
    }
    NSString *nameString = @"";
    if (MKValidArray(nameList)) {
        for (NSString *name in nameList) {
            if (!MKValidStr(name) || name.length > 20 || ![MKBLEBaseSDKAdopter asciiString:name]) {
                [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
                return;
            }
            NSString *nameAscii = @"";
            for (NSInteger i = 0; i < name.length; i ++) {
                int asciiCode = [name characterAtIndex:i];
                nameAscii = [nameAscii stringByAppendingString:[NSString stringWithFormat:@"%1lx",(unsigned long)asciiCode]];
            }
            NSString *tempLen = [MKBLEBaseSDKAdopter fetchHexValue:(nameAscii.length / 2) byteLen:1];
            NSString *string = [tempLen stringByAppendingString:nameAscii];
            nameString = [nameString stringByAppendingString:string];
        }
    }
    NSInteger totalLen = nameString.length / 2;
    NSInteger totalNum = (totalLen / packDataMaxLen);
    if (totalLen % packDataMaxLen != 0) {
        totalNum ++;
    }
    NSMutableArray *commandList = [NSMutableArray array];
    for (NSInteger i = 0; i < totalNum; i ++) {
        NSString *tempString = @"";
        if (i == totalNum - 1) {
            //最后一帧
            tempString = [nameString substringFromIndex:(i * 2 * packDataMaxLen)];
        }else {
            tempString = [nameString substringWithRange:NSMakeRange(i * 2 * packDataMaxLen, 2 * packDataMaxLen)];
        }
        [commandList addObject:tempString];
    }
    NSString *totalNumberHex = [MKBLEBaseSDKAdopter fetchHexValue:totalNum byteLen:1];
    
    __block NSInteger commandIndex = 0;
    dispatch_queue_t dataQueue = dispatch_queue_create("filterNameListQueue", DISPATCH_QUEUE_SERIAL);
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dataQueue);
    //当2s内没有接收到新的数据的时候，也认为是接受超时
    dispatch_source_set_timer(timer, dispatch_walltime(NULL, 0), 0.05 * NSEC_PER_SEC, 0);
    dispatch_source_set_event_handler(timer, ^{
        if (commandIndex >= commandList.count) {
            //停止
            dispatch_cancel(timer);
            MKCLOperation *operation = [[MKCLOperation alloc] initOperationWithID:mk_cl_taskConfigFilterAdvNameListOperation commandBlock:^{
                
            } completeBlock:^(NSError * _Nullable error, id  _Nullable returnData) {
                BOOL success = [returnData[@"success"] boolValue];
                if (!success) {
                    [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
                    return ;
                }
                if (sucBlock) {
                    sucBlock();
                }
            }];
            [[MKCLCentralManager shared] addOperation:operation];
            return;
        }
        NSString *tempCommandString = commandList[commandIndex];
        NSString *indexHex = [MKBLEBaseSDKAdopter fetchHexValue:commandIndex byteLen:1];
        NSString *totalLenHex = [MKBLEBaseSDKAdopter fetchHexValue:(tempCommandString.length / 2) byteLen:1];
        NSString *commandString = [NSString stringWithFormat:@"%@%@%@%@%@",@"ee0167",totalNumberHex,indexHex,totalLenHex,tempCommandString];
        [[MKBLEBaseCentralManager shared] sendDataToPeripheral:commandString characteristic:peripheral.cl_custom type:CBCharacteristicWriteWithResponse];
        commandIndex ++;
    });
    dispatch_resume(timer);
}

#pragma mark *********************BLE Adv Params************************

+ (void)cl_configAdvertiseBeaconStatus:(BOOL)isOn
                              sucBlock:(void (^)(void))sucBlock
                           failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed01700101" : @"ed01700100");
    [self configDataWithTaskID:mk_cl_taskConfigAdvertiseBeaconStatusOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configBeaconMajor:(NSInteger)major
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    if (major < 0 || major > 65535) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:major byteLen:2];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed017102",value];
    [self configDataWithTaskID:mk_cl_taskConfigBeaconMajorOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configBeaconMinor:(NSInteger)minor
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    if (minor < 0 || minor > 65535) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:minor byteLen:2];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed017202",value];
    [self configDataWithTaskID:mk_cl_taskConfigBeaconMinorOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configBeaconUUID:(NSString *)uuid
                   sucBlock:(void (^)(void))sucBlock
                failedBlock:(void (^)(NSError *error))failedBlock {
    if (!MKValidStr(uuid) || uuid.length != 32 || ![MKBLEBaseSDKAdopter checkHexCharacter:uuid]) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed017310",uuid];
    [self configDataWithTaskID:mk_cl_taskConfigBeaconUUIDOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configAdvInterval:(NSInteger)interval
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    if (interval < 1 || interval > 100) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:interval byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed017401",value];
    [self configDataWithTaskID:mk_cl_taskConfigAdvIntervalOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configTxPower:(NSInteger)txPower
                sucBlock:(void (^)(void))sucBlock
             failedBlock:(void (^)(NSError *error))failedBlock {
    if (txPower < 0 || txPower > 15) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:txPower byteLen:1];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed017501",value];
    [self configDataWithTaskID:mk_cl_taskConfigTxPowerOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

#pragma mark *********************Metering Params************************

+ (void)cl_configMeteringSwitch:(BOOL)isOn
                       sucBlock:(void (^)(void))sucBlock
                    failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed01800101" : @"ed01800100");
    [self configDataWithTaskID:mk_cl_taskConfigMeteringSwitchOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configPowerReportInterval:(NSInteger)interval
                            sucBlock:(void (^)(void))sucBlock
                         failedBlock:(void (^)(NSError *error))failedBlock {
    if (interval < 1 || interval > 86400) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:interval byteLen:4];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed018104",value];
    [self configDataWithTaskID:mk_cl_taskConfigPowerReportIntervalOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configEnergyReportInterval:(NSInteger)interval
                             sucBlock:(void (^)(void))sucBlock
                          failedBlock:(void (^)(NSError *error))failedBlock {
    if (interval < 1 || interval > 1440) {
        [MKBLEBaseSDKAdopter operationParamsErrorBlock:failedBlock];
        return;
    }
    NSString *value = [MKBLEBaseSDKAdopter fetchHexValue:interval byteLen:2];
    NSString *commandString = [NSString stringWithFormat:@"%@%@",@"ed018202",value];
    [self configDataWithTaskID:mk_cl_taskConfigEnergyReportIntervalOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

+ (void)cl_configLoadDetectionNotificationStatus:(BOOL)isOn
                                        sucBlock:(void (^)(void))sucBlock
                                     failedBlock:(void (^)(NSError *error))failedBlock {
    NSString *commandString = (isOn ? @"ed01830101" : @"ed01830100");
    [self configDataWithTaskID:mk_cl_taskConfigLoadDetectionNotificationStatusOperation
                          data:commandString
                      sucBlock:sucBlock
                   failedBlock:failedBlock];
}

#pragma mark - Private method

+ (void)configDataWithTaskID:(mk_cl_taskOperationID)taskID
                        data:(NSString *)data
                    sucBlock:(void (^)(void))sucBlock
                 failedBlock:(void (^)(NSError *error))failedBlock {
    [centralManager addTaskWithTaskID:taskID characteristic:peripheral.cl_custom commandData:data successBlock:^(id  _Nonnull returnData) {
        BOOL success = [returnData[@"result"][@"success"] boolValue];
        if (!success) {
            [MKBLEBaseSDKAdopter operationSetParamsErrorBlock:failedBlock];
            return ;
        }
        if (sucBlock) {
            sucBlock();
        }
    } failureBlock:failedBlock];
}

+ (BOOL)sendDataToPeripheral:(NSString *)commandString
                      taskID:(mk_cl_taskOperationID)taskID
                   semaphore:(dispatch_semaphore_t)semaphore {
    __block BOOL success = NO;
    [self configDataWithTaskID:taskID data:commandString sucBlock:^{
        success = YES;
        dispatch_semaphore_signal(semaphore);
    } failedBlock:^(NSError *error) {
        dispatch_semaphore_signal(semaphore);
    }];
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    return success;
}


@end
