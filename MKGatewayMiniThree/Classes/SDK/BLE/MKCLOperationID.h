

typedef NS_ENUM(NSInteger, mk_cl_taskOperationID) {
    mk_cl_defaultTaskOperationID,
    
#pragma mark - Read
    mk_cl_taskReadDeviceModelOperation,        //读取产品型号
    mk_cl_taskReadFirmwareOperation,           //读取固件版本
    mk_cl_taskReadHardwareOperation,           //读取硬件类型
    mk_cl_taskReadSoftwareOperation,           //读取软件版本
    mk_cl_taskReadManufacturerOperation,       //读取厂商信息
    
#pragma mark - 自定义协议读取
    mk_cl_taskReadDeviceNameOperation,         //读取设备名称
    mk_cl_taskReadDeviceMacAddressOperation,    //读取MAC地址
    mk_cl_taskReadDeviceWifiSTAMacAddressOperation, //读取WIFI STA MAC地址
    mk_cl_taskReadNTPServerHostOperation,       //读取NTP服务器域名
    mk_cl_taskReadTimeZoneOperation,            //读取时区
    
#pragma mark - Wifi Params
    mk_cl_taskReadWIFISSIDOperation,            //读取设备当前的wifi ssid
    mk_cl_taskReadWIFIPasswordOperation,        //读取设备当前的wifi密码
    mk_cl_taskReadDHCPStatusOperation,              //读取DHCP开关
    mk_cl_taskReadNetworkIpInfosOperation,          //读取IP信息
    mk_cl_taskReadCountryBandOperation,             //读取国家地区参数
    
#pragma mark - MQTT Params
    mk_cl_taskReadServerHostOperation,          //读取MQTT服务器域名
    mk_cl_taskReadServerPortOperation,          //读取MQTT服务器端口
    mk_cl_taskReadClientIDOperation,            //读取Client ID
    mk_cl_taskReadServerUserNameOperation,      //读取服务器登录用户名
    mk_cl_taskReadServerPasswordOperation,      //读取服务器登录密码
    mk_cl_taskReadServerCleanSessionOperation,  //读取MQTT Clean Session
    mk_cl_taskReadServerKeepAliveOperation,     //读取MQTT KeepAlive
    mk_cl_taskReadServerQosOperation,           //读取MQTT Qos
    mk_cl_taskReadSubscibeTopicOperation,       //读取Subscribe topic
    mk_cl_taskReadPublishTopicOperation,        //读取Publish topic
    mk_cl_taskReadLWTStatusOperation,           //读取LWT开关状态
    mk_cl_taskReadLWTQosOperation,              //读取LWT Qos
    mk_cl_taskReadLWTRetainOperation,           //读取LWT Retain
    mk_cl_taskReadLWTTopicOperation,            //读取LWT topic
    mk_cl_taskReadLWTPayloadOperation,          //读取LWT Payload
    mk_cl_taskReadConnectModeOperation,         //读取MTQQ服务器通信加密方式
    
#pragma mark - Filter Params
    mk_cl_taskReadRssiFilterValueOperation,             //读取扫描RSSI过滤
    mk_cl_taskReadFilterRelationshipOperation,          //读取扫描过滤逻辑
    mk_cl_taskReadFilterMACAddressListOperation,        //读取MAC过滤列表
    mk_cl_taskReadFilterAdvNameListOperation,           //读取ADV Name过滤列表
    
#pragma mark - iBeacon Params
    mk_cl_taskReadAdvertiseBeaconStatusOperation,       //读取iBeacon开关
    mk_cl_taskReadBeaconMajorOperation,                 //读取iBeacon major
    mk_cl_taskReadBeaconMinorOperation,                 //读取iBeacon minor
    mk_cl_taskReadBeaconUUIDOperation,                  //读取iBeacon UUID
    mk_cl_taskReadBeaconAdvIntervalOperation,           //读取Adv interval
    mk_cl_taskReadBeaconTxPowerOperation,               //读取Tx Power
    
#pragma mark - 计电量参数
    mk_cl_taskReadMeteringSwitchOperation,              //读取计量数据上报开关
    mk_cl_taskReadPowerReportIntervalOperation,         //读取电量数据上报间隔
    mk_cl_taskReadEnergyReportIntervalOperation,        //读取电能数据上报间隔
    mk_cl_taskReadLoadDetectionNotificationStatusOperation, //读取负载检测通知开关
    
    
#pragma mark - 密码特征
    mk_cl_connectPasswordOperation,             //连接设备时候发送密码
    
#pragma mark - 配置
    mk_cl_taskEnterSTAModeOperation,                //设备重启进入STA模式
    mk_cl_taskConfigNTPServerHostOperation,         //配置NTP服务器域名
    mk_cl_taskConfigTimeZoneOperation,              //配置时区
    
#pragma mark - Wifi Params
    
    mk_cl_taskConfigWIFISSIDOperation,          //配置wifi的ssid
    mk_cl_taskConfigWIFIPasswordOperation,      //配置wifi的密码
    mk_cl_taskConfigDHCPStatusOperation,                //配置DHCP开关
    mk_cl_taskConfigIpInfoOperation,                    //配置IP地址相关信息
    mk_cl_taskConfigCountryBandOperation,               //配置国家地区参数
    
#pragma mark - MQTT Params
    mk_cl_taskConfigServerHostOperation,        //配置MQTT服务器域名
    mk_cl_taskConfigServerPortOperation,        //配置MQTT服务器端口
    mk_cl_taskConfigClientIDOperation,              //配置ClientID
    mk_cl_taskConfigServerUserNameOperation,        //配置服务器的登录用户名
    mk_cl_taskConfigServerPasswordOperation,        //配置服务器的登录密码
    mk_cl_taskConfigServerCleanSessionOperation,    //配置MQTT Clean Session
    mk_cl_taskConfigServerKeepAliveOperation,       //配置MQTT KeepAlive
    mk_cl_taskConfigServerQosOperation,             //配置MQTT Qos
    mk_cl_taskConfigSubscibeTopicOperation,         //配置Subscribe topic
    mk_cl_taskConfigPublishTopicOperation,          //配置Publish topic
    mk_cl_taskConfigLWTStatusOperation,             //配置LWT开关
    mk_cl_taskConfigLWTQosOperation,                //配置LWT Qos
    mk_cl_taskConfigLWTRetainOperation,             //配置LWT Retain
    mk_cl_taskConfigLWTTopicOperation,              //配置LWT topic
    mk_cl_taskConfigLWTPayloadOperation,            //配置LWT payload
    mk_cl_taskConfigConnectModeOperation,           //配置MTQQ服务器通信加密方式
    mk_cl_taskConfigCAFileOperation,                //配置CA证书
    mk_cl_taskConfigClientCertOperation,            //配置设备证书
    mk_cl_taskConfigClientPrivateKeyOperation,      //配置私钥
        
#pragma mark - 过滤参数
    mk_cl_taskConfigRssiFilterValueOperation,                   //配置扫描RSSI过滤
    mk_cl_taskConfigFilterRelationshipOperation,                //配置扫描过滤逻辑
    mk_cl_taskConfigFilterMACAddressListOperation,           //配置MAC过滤规则
    mk_cl_taskConfigFilterAdvNameListOperation,             //配置Adv Name过滤规则
    
#pragma mark - 蓝牙广播参数
    mk_cl_taskConfigAdvertiseBeaconStatusOperation,         //配置iBeacon开关
    mk_cl_taskConfigBeaconMajorOperation,                   //配置iBeacon major
    mk_cl_taskConfigBeaconMinorOperation,                   //配置iBeacon minor
    mk_cl_taskConfigBeaconUUIDOperation,                    //配置iBeacon UUID
    mk_cl_taskConfigAdvIntervalOperation,                   //配置广播频率
    mk_cl_taskConfigTxPowerOperation,                       //配置Tx Power
    
#pragma mark - 计电量参数
    mk_cl_taskConfigMeteringSwitchOperation,                //配置计量数据上报开关
    mk_cl_taskConfigPowerReportIntervalOperation,           //配置电量数据上报间隔
    mk_cl_taskConfigEnergyReportIntervalOperation,          //配置电能数据上报间隔
    mk_cl_taskConfigLoadDetectionNotificationStatusOperation,   //配置负载检测通知开关
};

