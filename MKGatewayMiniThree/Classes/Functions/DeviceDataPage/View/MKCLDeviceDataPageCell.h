//
//  MKCLDeviceDataPageCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLDeviceDataPageCellModel : NSObject

@property (nonatomic, copy)NSString *msg;

- (CGFloat)fetchCellHeight;

@end

@interface MKCLDeviceDataPageCell : MKBaseCell

+ (MKCLDeviceDataPageCell *)initCellWithTableView:(UITableView *)tableView;

@property (nonatomic, strong)MKCLDeviceDataPageCellModel *dataModel;

@end

NS_ASSUME_NONNULL_END
