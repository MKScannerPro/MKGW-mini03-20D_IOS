//
//  MKCLSystemTimeCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLSystemTimeCellModel : NSObject

@property (nonatomic, assign)NSInteger index;

@property (nonatomic, copy)NSString *msg;

@property (nonatomic, copy)NSString *buttonTitle;

@end

@protocol MKCLSystemTimeCellDelegate <NSObject>

- (void)cl_systemTimeButtonPressed:(NSInteger)index;

@end

@interface MKCLSystemTimeCell : MKBaseCell

@property (nonatomic, strong)MKCLSystemTimeCellModel *dataModel;

@property (nonatomic, weak)id <MKCLSystemTimeCellDelegate>delegate;

+ (MKCLSystemTimeCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
