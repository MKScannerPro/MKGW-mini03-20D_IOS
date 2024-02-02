//
//  MKCLScanPageCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@class MKCLScanPageModel;
@interface MKCLScanPageCell : MKBaseCell

@property (nonatomic, strong)MKCLScanPageModel *dataModel;

+ (MKCLScanPageCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
