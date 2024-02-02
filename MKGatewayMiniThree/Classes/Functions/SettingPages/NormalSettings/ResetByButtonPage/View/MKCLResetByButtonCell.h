//
//  MKCLResetByButtonCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLResetByButtonCellModel : NSObject

@property (nonatomic, assign)NSInteger index;

@property (nonatomic, copy)NSString *msg;

@property (nonatomic, assign)BOOL selected;

@end

@protocol MKCLResetByButtonCellDelegate <NSObject>

- (void)cl_resetByButtonCellAction:(NSInteger)index;

@end

@interface MKCLResetByButtonCell : MKBaseCell

@property (nonatomic, weak)id <MKCLResetByButtonCellDelegate>delegate;

@property (nonatomic, strong)MKCLResetByButtonCellModel *dataModel;

+ (MKCLResetByButtonCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
