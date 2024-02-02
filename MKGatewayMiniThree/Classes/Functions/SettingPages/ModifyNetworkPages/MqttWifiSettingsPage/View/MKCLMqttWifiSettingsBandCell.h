//
//  MKCLMqttWifiSettingsBandCell.h
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/2/2.
//  Copyright © 2024 lovexiaoxia. All rights reserved.
//

#import <MKBaseModuleLibrary/MKBaseCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface MKCLMqttWifiSettingsBandCellModel : NSObject

@property (nonatomic, assign)NSInteger country;

@end

@protocol MKCLMqttWifiSettingsBandCellDelegate <NSObject>

- (void)cl_mqttWifiSettingsBandCell_countryChanged:(NSInteger)country;

@end

@interface MKCLMqttWifiSettingsBandCell : MKBaseCell

@property (nonatomic, strong)MKCLMqttWifiSettingsBandCellModel *dataModel;

@property (nonatomic, weak)id <MKCLMqttWifiSettingsBandCellDelegate>delegate;

+ (MKCLMqttWifiSettingsBandCell *)initCellWithTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
