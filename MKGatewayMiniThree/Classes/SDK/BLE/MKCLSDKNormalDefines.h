
typedef NS_ENUM(NSInteger, mk_cl_centralConnectStatus) {
    mk_cl_centralConnectStatusUnknow,                                           //未知状态
    mk_cl_centralConnectStatusConnecting,                                       //正在连接
    mk_cl_centralConnectStatusConnected,                                        //连接成功
    mk_cl_centralConnectStatusConnectedFailed,                                  //连接失败
    mk_cl_centralConnectStatusDisconnect,
};

typedef NS_ENUM(NSInteger, mk_cl_centralManagerStatus) {
    mk_cl_centralManagerStatusUnable,                           //不可用
    mk_cl_centralManagerStatusEnable,                           //可用状态
};



typedef NS_ENUM(NSInteger, mk_cl_connectMode) {
    mk_cl_connectMode_TCP,                                          //TCP
    mk_cl_connectMode_CASignedServerCertificate,                    //SSL.Do not verify the server certificate.
    mk_cl_connectMode_CACertificate,                                //SSL.Verify the server's certificate
    mk_cl_connectMode_SelfSignedCertificates,                       //SSL.Two-way authentication
};

//Quality of MQQT service
typedef NS_ENUM(NSInteger, mk_cl_mqttServerQosMode) {
    mk_cl_mqttQosLevelAtMostOnce,      //At most once. The message sender to find ways to send messages, but an accident and will not try again.
    mk_cl_mqttQosLevelAtLeastOnce,     //At least once.If the message receiver does not know or the message itself is lost, the message sender sends it again to ensure that the message receiver will receive at least one, and of course, duplicate the message.
    mk_cl_mqttQosLevelExactlyOnce,     //Exactly once.Ensuring this semantics will reduce concurrency or increase latency, but level 2 is most appropriate when losing or duplicating messages is unacceptable.
};

typedef NS_ENUM(NSInteger, mk_cl_filterRelationship) {
    mk_cl_filterRelationship_null,
    mk_cl_filterRelationship_mac,
    mk_cl_filterRelationship_advName,
    mk_cl_filterRelationship_rawData,
    mk_cl_filterRelationship_advNameAndRawData,
    mk_cl_filterRelationship_macAndadvNameAndRawData,
    mk_cl_filterRelationship_advNameOrRawData,
    mk_cl_filterRelationship_advNameAndMacData,
};


@protocol mk_cl_centralManagerScanDelegate <NSObject>

/// Scan to new device.
/// @param deviceModel device
- (void)mk_cl_receiveDevice:(NSDictionary *)deviceModel;

@optional

/// Starts scanning equipment.
- (void)mk_cl_startScan;

/// Stops scanning equipment.
- (void)mk_cl_stopScan;

@end
