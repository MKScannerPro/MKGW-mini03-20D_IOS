//
//  MKCLDeviceListController.m
//  MKGatewayMiniThree_Example
//
//  Created by aa on 2024/1/12.
//  Copyright © 2024 aadyx2007@163.com. All rights reserved.
//

#import "MKCLDeviceListController.h"

#import "Masonry.h"

#import "MKMacroDefines.h"
#import "MKBaseTableView.h"
#import "UIView+MKAdd.h"
#import "UITableView+MKAdd.h"

#import "MKHudManager.h"
#import "MKCustomUIAdopter.h"
#import "MKAlertView.h"

#import "MKIoTCloudAccountLoginAlertView.h"
#import "MKNormalService.h"

#import "MKNetworkManager.h"

#import "MKCLDeviceModeManager.h"
#import "MKCLDeviceModel.h"

#import "MKCLMQTTServerManager.h"

#import "MKCLMQTTDataManager.h"

#import "MKCLDeviceDatabaseManager.h"

#import "CTMediator+MKCLAdd.h"

#import "MKCLUserLoginManager.h"

#import "MKCLDeviceListModel.h"

#import "MKCLAddDeviceView.h"
#import "MKCLDeviceListCell.h"
#import "MKCLEasyShowView.h"

#import "MKCLServerForAppController.h"
#import "MKCLScanPageController.h"
#import "MKCLDeviceDataController.h"
#import "MKCLSyncDeviceController.h"

static NSTimeInterval const kRefreshInterval = 0.5f;

@interface MKCLDeviceListController ()<UITableViewDelegate,
UITableViewDataSource,
MKCLDeviceListCellDelegate,
MKCLDeviceModelDelegate>

/// 没有添加设备的时候显示
@property (nonatomic, strong)MKCLAddDeviceView *addView;

/// 本地有设备的时候显示
@property (nonatomic, strong)MKBaseTableView *tableView;

@property (nonatomic, strong)UIView *footerView;

@property (nonatomic, strong)MKCLEasyShowView *loadingView;

@property (nonatomic, strong)NSMutableArray *dataList;

/// 定时刷新
@property (nonatomic, assign)CFRunLoopObserverRef observerRef;
//不能立即刷新列表，降低刷新频率
@property (nonatomic, assign)BOOL isNeedRefresh;

@end

@implementation MKCLDeviceListController

- (void)dealloc {
    NSLog(@"MKCLDeviceListController销毁");
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    //移除runloop的监听
    CFRunLoopRemoveObserver(CFRunLoopGetCurrent(), self.observerRef, kCFRunLoopCommonModes);
    [[MKCLMQTTDataManager shared] clearAllSubscriptions];
    [[MKCLMQTTDataManager shared] disconnect];
    [MKCLMQTTDataManager singleDealloc];
    [MKCLMQTTServerManager singleDealloc];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self loadSubViews];
    if (self.connectServer) {
        //对于从壳工程进来的时候，需要走本地联网流程
        [[MKCLMQTTServerManager shared] startWork];
    }
    
    [self readDataFromDatabase];
    [self runloopObserver];
    [self addNotifications];
}

#pragma mark - super method

- (void)rightButtonMethod {
    MKCLServerForAppController *vc = [[MKCLServerForAppController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark - UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60.f;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    MKCLDeviceListModel *deviceModel = self.dataList[indexPath.row];
    if (deviceModel.onLineState != MKCLDeviceModelStateOnline) {
        [self.view showCentralToast:@"Device is off-line!"];
        return;
    }
    [[MKCLDeviceModeManager shared] addDeviceModel:deviceModel];
    MKCLDeviceDataController *vc = [[MKCLDeviceDataController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    MKCLDeviceListCell *cell = [MKCLDeviceListCell initCellWithTableView:tableView];
    cell.indexPath = indexPath;
    cell.dataModel = self.dataList[indexPath.row];
    cell.delegate = self;
    return cell;
}

#pragma mark - MKCLDeviceListCellDelegate
/**
 删除
 
 @param index 所在index
 */
- (void)cl_cellDeleteButtonPressed:(NSInteger)index {
    if (index >= self.dataList.count) {
        return;
    }
    
    @weakify(self);
    MKAlertViewAction *cancelAction = [[MKAlertViewAction alloc] initWithTitle:@"Cancel" handler:^{
        
    }];
    
    MKAlertViewAction *confirmAction = [[MKAlertViewAction alloc] initWithTitle:@"Confirm" handler:^{
        @strongify(self);
        [self removeDeviceFromLocal:index];
    }];
    NSString *msg = @"Please confirm again whether to remove the device.";
    MKAlertView *alertView = [[MKAlertView alloc] init];
    [alertView addAction:cancelAction];
    [alertView addAction:confirmAction];
    [alertView showAlertWithTitle:@"Remove Device" message:msg notificationName:@"mk_cl_needDismissAlert"];
}

#pragma mark - MKCLDeviceModelDelegate
/// 当前设备离线
/// @param deviceID 当前设备的deviceID
- (void)cl_deviceOfflineWithMacAddress:(NSString *)macAddress {
    [self deviceModelOnlineStateChanged:MKCLDeviceModelStateOffline macAddress:macAddress];
}

#pragma mark - note
- (void)receiveNewDevice:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user)) {
        return;
    }
    MKCLDeviceModel *receiveModel = user[@"deviceModel"];
    MKCLDeviceListModel *deviceModel = [[MKCLDeviceListModel alloc] init];
    deviceModel.deviceType = receiveModel.deviceType;
    deviceModel.clientID = receiveModel.clientID;
    deviceModel.deviceName = receiveModel.deviceName;
    deviceModel.subscribedTopic = receiveModel.subscribedTopic;
    deviceModel.publishedTopic = receiveModel.publishedTopic;
    deviceModel.macAddress = receiveModel.macAddress;
    deviceModel.lwtStatus = receiveModel.lwtStatus;
    deviceModel.lwtTopic = receiveModel.lwtTopic;
    deviceModel.onLineState = receiveModel.onLineState;
    deviceModel.wifiLevel = 2;
    deviceModel.delegate = self;
    [deviceModel startStateMonitoringTimer];
    
    NSInteger index = 0;
    BOOL contain = NO;
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *model = self.dataList[i];
        if ([model.macAddress isEqualToString:deviceModel.macAddress]) {
            index = i;
            contain = YES;
            break;
        }
    }
    if (contain) {
        //当前设备列表存在deviceID相同的设备，替换，本地数据库已经替换过了
        [self.dataList replaceObjectAtIndex:index withObject:deviceModel];
    }else {
        //不存在，则添加到设备列表
        if (self.dataList.count > 0) {
            [self.dataList insertObject:deviceModel atIndex:0];
        }else {
            [self.dataList addObject:deviceModel];
        }
    }
    
    [self loadMainViews];
    NSMutableArray *topicList = [NSMutableArray array];
    [topicList addObject:[deviceModel currentPublishedTopic]];
    if (deviceModel.lwtStatus) {
        [topicList addObject:deviceModel.lwtTopic];
    }
    [[MKCLMQTTDataManager shared] subscriptions:topicList];
}

- (void)receiveDeviceOnlineState:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || !ValidStr(user[@"macAddress"]) || self.dataList.count == 0) {
        return;
    }
    [self deviceModelOnlineStateChanged:MKCLDeviceModelStateOnline macAddress:user[@"macAddress"]];
}

- (void)receiveDeviceNetworkState:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || !ValidStr(user[@"macAddress"]) || self.dataList.count == 0) {
        return;
    }
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *deviceModel = self.dataList[i];
        if ([deviceModel.macAddress isEqualToString:user[@"macAddress"]]) {
            deviceModel.onLineState = MKCLDeviceModelStateOnline;
            [deviceModel startStateMonitoringTimer];
            deviceModel.wifiLevel = [user[@"data"][@"wifi_rssi"] integerValue];
            break;
        }
    }
    [self needRefreshList];
}

- (void)receiveDeviceNameChanged:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || !ValidStr(user[@"macAddress"]) || self.dataList.count == 0) {
        return;
    }
    NSInteger index = 0;
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *deviceModel = self.dataList[i];
        if ([deviceModel.macAddress isEqualToString:user[@"macAddress"]]) {
            deviceModel.deviceName = user[@"deviceName"];
            index = i;
            break;
        }
    }
    [self.tableView mk_reloadRow:index inSection:0 withRowAnimation:UITableViewRowAnimationNone];
}

- (void)receiveDeleteDevice:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || !ValidStr(user[@"macAddress"]) || self.dataList.count == 0) {
        return;
    }
    MKCLDeviceListModel *deviceModel = nil;
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *model = self.dataList[i];
        if ([model.macAddress isEqualToString:user[@"macAddress"]]) {
            deviceModel = model;
            break;
        }
    }
    
    if (!deviceModel) {
        return;
    }
    NSMutableArray *unSubTopicList = [NSMutableArray array];
    [unSubTopicList addObject:[deviceModel currentPublishedTopic]];
    if (deviceModel.lwtStatus) {
        [unSubTopicList addObject:deviceModel.lwtTopic];
    }
    [[MKCLMQTTDataManager shared] unsubscriptions:unSubTopicList];
    [self.dataList removeObject:deviceModel];
    
    [self loadMainViews];
}

- (void)receiveDeviceModifyMQTTServer:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user)) {
        return;
    }
    
    BOOL contain = NO;
    NSMutableArray *unsubTopicList = [NSMutableArray array];
    NSMutableArray *subTopicList = [NSMutableArray array];
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceModel *model = self.dataList[i];
        if ([model.macAddress isEqualToString:user[@"macAddress"]]) {
            if (!ValidStr([MKCLMQTTDataManager shared].serverParams.subscribeTopic)) {
                //app端MQTT订阅了指定的topic，不能取消订阅
                //如果是app端MQTT订阅每一个设备的topic，则切网成功之后需要选取消原来的订阅，增加新的订阅
                [unsubTopicList addObject:[model currentPublishedTopic]];
            }
            if (model.lwtStatus) {
                //如果设备打开了遗嘱功能
                [unsubTopicList addObject:model.lwtTopic];
            }
            model.clientID = user[@"clientID"];
            model.subscribedTopic = user[@"subscribedTopic"];
            model.publishedTopic = user[@"publishedTopic"];
            model.lwtStatus = [user[@"lwtStatus"] boolValue];
            model.lwtTopic = user[@"lwtTopic"];
            model.onLineState = MKCLDeviceModelStateOffline;
            [subTopicList addObject:[model currentPublishedTopic]];
            if (model.lwtStatus) {
                //如果用户打开了遗嘱功能，则订阅topic
                [subTopicList addObject:model.lwtTopic];
            }
            contain = YES;
            break;
        }
    }
    if (!contain) {
        return;
    }
    [[MKCLMQTTDataManager shared] unsubscriptions:unsubTopicList];
    [self performSelector:@selector(resubTopics:) withObject:subTopicList afterDelay:1.f];
}

- (void)resubTopics:(NSArray *)subTopicList {
    [self loadMainViews];
    [[MKCLMQTTDataManager shared] subscriptions:subTopicList];
}

/// 当前MQTT服务器连接状态发生改变
- (void)serverManagerStateChanged {
    if ([MKCLMQTTDataManager shared].state == MKCLMQTTSessionManagerStateConnecting) {
        [self.loadingView showText:@"Connecting..." superView:self.titleLabel animated:YES];
        return;
    }
    if ([MKCLMQTTDataManager shared].state == MKCLMQTTSessionManagerStateConnected) {
        [self.loadingView hidden];
        self.defaultTitle = @"MKScannerPro";
        return;
    }
    if ([MKCLMQTTDataManager shared].state == MKCLMQTTSessionManagerStateError) {
        [self.loadingView hidden];
        self.defaultTitle = @"Connect Failed";
        return;
    }
}

- (void)networkStatusChanged {
    if (![[MKNetworkManager sharedInstance] currentNetworkAvailable]) {
        self.defaultTitle = @"Network Unreachable";
        return;
    }
}

- (void)receiveDeviceLwtMessage:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || self.dataList.count == 0) {
        return;
    }
    NSString *macAddress = user[@"device_info"][@"mac"];
    if (!ValidStr(macAddress)) {
        return;
    }
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *deviceModel = self.dataList[i];
        if ([deviceModel.macAddress isEqualToString:macAddress]) {
            deviceModel.onLineState = MKCLDeviceModelStateOffline;
            break;
        }
    }
    [self needRefreshList];
}

- (void)deviceResetByButton:(NSNotification *)note {
    NSDictionary *user = note.userInfo;
    if (!ValidDict(user) || self.dataList.count == 0) {
        return;
    }
    NSString *macAddress = user[@"device_info"][@"mac"];
    if (!ValidStr(macAddress)) {
        return;
    }
    NSMutableArray *unSubTopicList = [NSMutableArray array];
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *deviceModel = self.dataList[i];
        if ([deviceModel.macAddress isEqualToString:macAddress]) {
            deviceModel.onLineState = MKCLDeviceModelStateOffline;
            [unSubTopicList addObject:[deviceModel currentPublishedTopic]];
            if (deviceModel.lwtStatus) {
                [unSubTopicList addObject:deviceModel.lwtTopic];
            }
            break;
        }
    }
    [[MKCLMQTTDataManager shared] unsubscriptions:unSubTopicList];
    [self needRefreshList];
}

- (void)reloadDeviceTopics {
    //切网之后需要重新加载topic
    //先取消当前所有订阅
    [[MKCLMQTTDataManager shared] clearAllSubscriptions];
    //重新加载需要订阅的topic
    NSMutableArray *topicList = [NSMutableArray array];
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceModel *deviceModel = self.dataList[i];
        [topicList addObject:[deviceModel currentPublishedTopic]];
    }
    [[MKCLMQTTDataManager shared] subscriptions:topicList];
}

#pragma mark - event method
- (void)addButtonPressed {
    if (!ValidStr([MKCLMQTTDataManager shared].serverParams.host)) {
        //如果MQTT服务器参数不存在，则去引导用户添加服务器参数，让app连接MQTT服务器
        [self rightButtonMethod];
        return;
    }
    //MQTT服务器参数存在，则添加设备
    MKCLScanPageController *vc = [[MKCLScanPageController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)syncButtonPressed {
    if (self.dataList.count == 0) {
        [self.view showCentralToast:@"Add devices first"];
        return;
    }
    if (ValidStr([MKCLUserLoginManager shared].password)) {
        //已经登陆过
        [self login:[MKCLUserLoginManager shared].isHome username:[MKCLUserLoginManager shared].username password:[MKCLUserLoginManager shared].password];
        return;
    }
    MKIoTCloudAccountLoginAlertViewModel *viewModel = [[MKIoTCloudAccountLoginAlertViewModel alloc] init];
    viewModel.account = [MKCLUserLoginManager shared].username;
    viewModel.isHome = [MKCLUserLoginManager shared].isHome;
    viewModel.password = [MKCLUserLoginManager shared].password;
    MKIoTCloudAccountLoginAlertView *alertView = [[MKIoTCloudAccountLoginAlertView alloc] init];
    [alertView showViewWithModel:viewModel completeBlock:^(NSString * _Nonnull account, NSString * _Nonnull password, BOOL isHome) {
        [self login:isHome username:account password:password];
    }];
}

#pragma mark - private method
- (void)loadMainViews {
    if (self.tableView.superview) {
        [self.tableView removeFromSuperview];
    }
    if (self.addView.superview) {
        [self.addView removeFromSuperview];
    }
    if (!ValidArray(self.dataList)) {
        //没有设备的情况下，隐藏设备列表，显示添加设备页面
        [self.view addSubview:self.addView];
        [self.addView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(0);
            make.right.mas_equalTo(0);
            make.top.mas_equalTo(self.view.mas_safeAreaLayoutGuideTop);
            make.bottom.mas_equalTo(self.footerView.mas_top);
        }];
        return;
    }
    //有设备了，显示设备列表
    [self.view addSubview:self.tableView];
    [self.tableView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.right.mas_equalTo(0);
        make.top.mas_equalTo(self.view.mas_safeAreaLayoutGuideTop);
        make.bottom.mas_equalTo(self.footerView.mas_top);
    }];
    [self.tableView reloadData];
}

- (void)readDataFromDatabase {
    [[MKHudManager share] showHUDWithTitle:@"Reading..." inView:self.view isPenetration:NO];
    [MKCLDeviceDatabaseManager readLocalDeviceWithSucBlock:^(NSArray<MKCLDeviceModel *> * _Nonnull deviceList) {
        [[MKHudManager share] hide];
        [self loadTopics:deviceList];
    } failedBlock:^(NSError * _Nonnull error) {
        [[MKHudManager share] hide];
        [self.view showCentralToast:error.userInfo[@"errorInfo"]];
    }];
}

- (void)loadTopics:(NSArray <MKCLDeviceModel *>*)deviceList {
    NSMutableArray *topicList = [NSMutableArray array];
    for (NSInteger i = 0; i < deviceList.count; i ++) {
        MKCLDeviceModel *tempModel = deviceList[i];
        MKCLDeviceListModel *deviceModel = [[MKCLDeviceListModel alloc] init];
        deviceModel.deviceType = tempModel.deviceType;
        deviceModel.clientID = tempModel.clientID;
        deviceModel.deviceName = tempModel.deviceName;
        deviceModel.subscribedTopic = tempModel.subscribedTopic;
        deviceModel.publishedTopic = tempModel.publishedTopic;
        deviceModel.macAddress = tempModel.macAddress;
        deviceModel.lwtStatus = tempModel.lwtStatus;
        deviceModel.lwtTopic = tempModel.lwtTopic;
        deviceModel.delegate = self;
        if (i == 0) {
            [self.dataList addObject:deviceModel];
        }else {
            [self.dataList insertObject:deviceModel atIndex:0];
        }
        [topicList addObject:[deviceModel currentPublishedTopic]];
        if (deviceModel.lwtStatus) {
            //如果用户打开了遗嘱功能，则订阅topic
            [topicList addObject:deviceModel.lwtTopic];
        }
    }
    [self loadMainViews];
    [[MKCLMQTTDataManager shared] subscriptions:topicList];
}

- (void)deviceModelOnlineStateChanged:(MKCLDeviceModelState)state macAddress:(NSString *)macAddress {
    for (NSInteger i = 0; i < self.dataList.count; i ++) {
        MKCLDeviceListModel *deviceModel = self.dataList[i];
        if ([deviceModel.macAddress isEqualToString:macAddress]) {
            deviceModel.onLineState = state;
            if (state == MKCLDeviceModelStateOnline) {
                //在线状态开启监听
                [deviceModel startStateMonitoringTimer];
            }
            break;
        }
    }
    [self needRefreshList];
}

- (void)removeDeviceFromLocal:(NSInteger)index {
    MKCLDeviceListModel *deviceModel = self.dataList[index];
    [[MKHudManager share] showHUDWithTitle:@"Delete..." inView:self.view isPenetration:NO];
    [MKCLDeviceDatabaseManager deleteDeviceWithMacAddress:deviceModel.macAddress sucBlock:^{
        [[MKHudManager share] hide];
        [self.dataList removeObject:deviceModel];
        [[MKCLMQTTDataManager shared] unsubscriptions:@[[deviceModel currentPublishedTopic]]];
        [self loadMainViews];
    } failedBlock:^(NSError * _Nonnull error) {
        [[MKHudManager share] hide];
        [self.view showCentralToast:error.userInfo[@"errorInfo"]];
    }];
}

- (void)addNotifications {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveNewDevice:)
                                                 name:@"mk_cl_addNewDeviceSuccessNotification"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeviceOnlineState:)
                                                 name:MKCLReceiveDeviceOnlineNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeviceNameChanged:)
                                                 name:@"mk_cl_deviceNameChangedNotification"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeleteDevice:)
                                                 name:@"mk_cl_deleteDeviceNotification"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeviceModifyMQTTServer:)
                                                 name:@"mk_cl_deviceModifyMQTTServerSuccessNotification"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(serverManagerStateChanged)
                                                 name:MKCLMQTTSessionManagerStateChangedNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(networkStatusChanged)
                                                 name:MKNetworkStatusChangedNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeviceNetworkState:)
                                                 name:MKCLReceiveDeviceNetStateNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveDeviceLwtMessage:)
                                                 name:MKCLReceiveDeviceOfflineNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceResetByButton:)
                                                 name:MKCLReceiveDeviceResetByButtonNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reloadDeviceTopics)
                                                 name:@"mk_cl_needReloadTopicsNotification"
                                               object:nil];
}

- (void)login:(BOOL)isHome username:(NSString *)username password:(NSString *)password {
    [[MKHudManager share] showHUDWithTitle:@"Login..." inView:self.view isPenetration:NO];
    [[MKNormalService share] loginWithUsername:username password:password isHome:isHome sucBlock:^(id returnData) {
        [[MKHudManager share] hide];
        [[MKCLUserLoginManager shared] syncLoginDataWithHome:isHome username:username password:password];
        MKCLSyncDeviceController *vc = [[MKCLSyncDeviceController alloc] init];
        vc.deviceList = self.dataList;
        vc.token = SafeStr(returnData[@"data"][@"access_token"]);
        [self.navigationController pushViewController:vc animated:YES];
    } failBlock:^(NSError *error) {
        [[MKHudManager share] hide];
        [self.view showCentralToast:error.userInfo[@"errorInfo"]];
    }];
}

#pragma mark - 定时刷新

- (void)needRefreshList {
    //标记需要刷新
    self.isNeedRefresh = YES;
    //唤醒runloop
    CFRunLoopWakeUp(CFRunLoopGetMain());
}

- (void)runloopObserver {
    @weakify(self);
    __block NSTimeInterval timeInterval = [[NSDate date] timeIntervalSince1970];
    self.observerRef = CFRunLoopObserverCreateWithHandler(CFAllocatorGetDefault(), kCFRunLoopAllActivities, YES, 0, ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
        @strongify(self);
        if (activity == kCFRunLoopBeforeWaiting) {
            //runloop空闲的时候刷新需要处理的列表,但是需要控制刷新频率
            NSTimeInterval currentInterval = [[NSDate date] timeIntervalSince1970];
            if (currentInterval - timeInterval < kRefreshInterval) {
                return;
            }
            timeInterval = currentInterval;
            if (self.isNeedRefresh) {
                [self.tableView reloadData];
                self.isNeedRefresh = NO;
            }
        }
    });
    //添加监听，模式为kCFRunLoopCommonModes
    CFRunLoopAddObserver(CFRunLoopGetCurrent(), self.observerRef, kCFRunLoopCommonModes);
}

#pragma mark - UI
- (void)loadSubViews {
    self.defaultTitle = @"MKScannerPro";
    [self.rightButton setImage:LOADICON(@"MKGatewayMiniThree", @"MKCLDeviceListController", @"cl_menuIcon.png") forState:UIControlStateNormal];
    [self.view addSubview:self.footerView];
    [self.footerView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.right.mas_equalTo(0);
        make.bottom.mas_equalTo(self.view.mas_safeAreaLayoutGuideBottom);
        make.height.mas_equalTo(60.f);
    }];
    UIButton *addButton = [MKCustomUIAdopter customButtonWithTitle:@"Add Devices"
                                                            target:self
                                                            action:@selector(addButtonPressed)];
    [self.footerView addSubview:addButton];
    [addButton mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(30.f);
        make.right.mas_equalTo(self.footerView.mas_centerX).mas_offset(-10.f);
        make.centerY.mas_equalTo(self.footerView.mas_centerY);
        make.height.mas_equalTo(40.f);
    }];
    
    UIButton *syncButton = [MKCustomUIAdopter customButtonWithTitle:@"Sync Devices"
                                                             target:self
                                                             action:@selector(syncButtonPressed)];
    [self.footerView addSubview:syncButton];
    [syncButton mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(self.footerView.mas_centerX).mas_offset(10.f);
        make.right.mas_equalTo(-30.f);
        make.centerY.mas_equalTo(self.footerView.mas_centerY);
        make.height.mas_equalTo(40.f);
    }];
}

#pragma mark - getter
- (MKBaseTableView *)tableView {
    if (!_tableView) {
        _tableView = [[MKBaseTableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        _tableView.backgroundColor = RGBCOLOR(242, 242, 242);
    }
    return _tableView;
}

- (MKCLAddDeviceView *)addView {
    if (!_addView) {
        _addView = [[MKCLAddDeviceView alloc] init];
    }
    return _addView;
}

- (MKCLEasyShowView *)loadingView {
    if (!_loadingView) {
        _loadingView = [[MKCLEasyShowView alloc] init];
    }
    return _loadingView;
}

- (NSMutableArray *)dataList {
    if (!_dataList) {
        _dataList = [NSMutableArray array];
    }
    return _dataList;
}

- (UIView *)footerView {
    if (!_footerView) {
        _footerView = [[UIView alloc] init];
        _footerView.backgroundColor = COLOR_WHITE_MACROS;
    }
    return _footerView;
}

@end
