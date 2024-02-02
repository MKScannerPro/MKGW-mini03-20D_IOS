//
//  MKCLDeviceListCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MKCLDeviceListCellDelegate <NSObject>

/**
 删除
 
 @param index 所在index
 */
- (void)cl_cellDeleteButtonPressed:(NSInteger)index;

@end

@class MKCLDeviceListModel;
@interface MKCLDeviceListCell : MKBaseCell

@property (nonatomic, weak)id <MKCLDeviceListCellDelegate>delegate;

@property (nonatomic, strong)MKCLDeviceListModel *dataModel;

+ (MKCLDeviceListCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
