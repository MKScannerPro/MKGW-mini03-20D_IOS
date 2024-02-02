//
//  MKCLMqttServerSSLTextField.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MKCustomUIModule/MKTextField.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMqttServerSSLTextFieldModel : NSObject

@property (nonatomic, assign)NSInteger index;

@property (nonatomic, copy)NSString *msg;

/// 当前textField的值
@property (nonatomic, copy)NSString *textFieldValue;

/// textField的占位符
@property (nonatomic, copy)NSString *textPlaceholder;

/// 当前textField的输入类型
@property (nonatomic, assign)mk_textFieldType textFieldType;

@property (nonatomic, assign)NSInteger maxLength;

@end

@protocol MKCLMqttServerSSLTextFieldDelegate <NSObject>

/// textField内容发送改变时的回调事件
/// @param index 当前cell所在的index
/// @param value 当前textField的值
- (void)cl_modifyServerSSLTextFieldValueChanged:(NSInteger)index textValue:(NSString *)value;

@end

@interface MKCLMqttServerSSLTextField : UIView

@property (nonatomic, strong)MKCLMqttServerSSLTextFieldModel *dataModel;

@property (nonatomic, weak)id <MKCLMqttServerSSLTextFieldDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
