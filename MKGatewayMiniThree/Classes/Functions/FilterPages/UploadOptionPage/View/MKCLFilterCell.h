//
//  MKCLFilterCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLFilterCellModel : NSObject

/// cell标识符
@property (nonatomic, assign)NSInteger index;

@property (nonatomic, copy)NSString *msg;

@property (nonatomic, assign)NSInteger dataListIndex;

@property (nonatomic, strong)NSArray <NSString *>*dataList;

@end

@protocol MKCLFilterCellDelegate <NSObject>

- (void)cl_filterValueChanged:(NSInteger)dataListIndex index:(NSInteger)index;

@end

@interface MKCLFilterCell : MKBaseCell

@property (nonatomic, strong)MKCLFilterCellModel *dataModel;

@property (nonatomic, weak)id <MKCLFilterCellDelegate>delegate;

+ (MKCLFilterCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
