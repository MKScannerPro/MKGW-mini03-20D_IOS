//
//  MKCLBleWifiSettingsBandCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2023/6/15.
//  Copyright © 2023 aadyx2007@163.com. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLBleWifiSettingsBandCellModel : NSObject

@property (nonatomic, assign)NSInteger country;

@end

@protocol MKCLBleWifiSettingsBandCellDelegate <NSObject>

- (void)cl_bleWifiSettingsBandCell_countryChanged:(NSInteger)country;

@end

@interface MKCLBleWifiSettingsBandCell : MKBaseCell

@property (nonatomic, strong)MKCLBleWifiSettingsBandCellModel *dataModel;

@property (nonatomic, weak)id <MKCLBleWifiSettingsBandCellDelegate>delegate;

+ (MKCLBleWifiSettingsBandCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
