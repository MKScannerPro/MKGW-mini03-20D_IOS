//
//  MKCLImportServerController.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseViewController.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MKCLImportServerControllerDelegate <NSObject>

- (void)cl_selectedServerParams:(NSString *)fileName;

@end

@interface MKCLImportServerController : MKBaseViewController

@property (nonatomic, weak)id <MKCLImportServerControllerDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
