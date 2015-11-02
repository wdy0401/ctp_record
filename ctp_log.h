#ifndef CTP_LOG_H
#define CTP_LOG_H

#include"../libs/ctp/ThostFtdcMdApi.h"
#include"../gpp_qt/log_info/log_info.h"

#include<QObject>
#include<string>
class ctp_log :public QObject , public log_info
{
    Q_OBJECT
public:
    ctp_log();
signals:
    void broadcast_quote(const std::string &);
public slots:
    void writeinfo(CThostFtdcDepthMarketDataField *pDepthMarketData);
private:
    std::ostringstream os;
};

#endif // CTP_LOG_H
