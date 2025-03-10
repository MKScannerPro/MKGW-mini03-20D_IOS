//
//  MKCLSyncDeviceCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2025/3/7.
//  Copyright © 2025 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

#import "MKCLDeviceModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface MKCLSyncDeviceCellModel : MKCLDeviceModel

@property (nonatomic, assign)NSInteger index;

@property (nonatomic, assign)BOOL selected;

@end

@protocol MKCLSyncDeviceCellDelegate <NSObject>

- (void)cl_syncDeviceCell_selected:(BOOL)selected index:(NSInteger)index;

@end

@interface MKCLSyncDeviceCell : MKBaseCell

@property (nonatomic, strong)MKCLSyncDeviceCellModel *dataModel;

@property (nonatomic, weak)id <MKCLSyncDeviceCellDelegate>delegate;

+ (MKCLSyncDeviceCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
