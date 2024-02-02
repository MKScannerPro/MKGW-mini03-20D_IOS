//
//  MKCLButtonFirmwareCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLButtonFirmwareCellModel : NSObject

/// cell唯一识别号
@property (nonatomic, assign)NSInteger index;

@property (nonatomic, copy)NSString *leftMsg;

@property (nonatomic, copy)NSString *rightMsg;

@property (nonatomic, copy)NSString *rightButtonTitle;

@end

@protocol MKCLButtonFirmwareCellDelegate <NSObject>

- (void)cl_buttonFirmwareCell_buttonAction:(NSInteger)index;

@end

@interface MKCLButtonFirmwareCell : MKBaseCell

@property (nonatomic, strong)MKCLButtonFirmwareCellModel *dataModel;

@property (nonatomic, weak)id <MKCLButtonFirmwareCellDelegate>delegate;

+ (MKCLButtonFirmwareCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
