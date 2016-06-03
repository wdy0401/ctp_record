#include "ctp_log.h"

#include<iostream>
#include<iomanip>


#include"../libs/ctp/ThostFtdcMdApi.h"

using namespace std;
ctp_log::ctp_log()
{
    os<<setprecision(10);
}
void ctp_log::writeinfo(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    os.str("");
    os<< pDepthMarketData->TradingDay;
    os<< "," << pDepthMarketData->UpdateTime;
    os<< ":" << pDepthMarketData->UpdateMillisec;
    os<<"," << dt.currentDateTime().toString("hh:mm:ss:zzz").toStdString();
    os<< "," << pDepthMarketData->InstrumentID;
    os<< "," << pDepthMarketData->BidPrice1;
    os<< "," << pDepthMarketData->AskPrice1;
    os<< "," << pDepthMarketData->BidVolume1;
    os<< "," << pDepthMarketData->AskVolume1;
    os<< "," << pDepthMarketData->LastPrice;
    os<< "," << pDepthMarketData->AveragePrice;//当日均价
    os<< "," << pDepthMarketData->Turnover;//成交金额
    os<< "," << pDepthMarketData->Volume;//数量
    os<< "," << pDepthMarketData->OpenInterest;//持仓量
    os<< "," << pDepthMarketData->OpenPrice;//今开
    os<< "," << pDepthMarketData->HighestPrice;//今高
    os<< "," << pDepthMarketData->LowestPrice;//今低
    os<< "," << pDepthMarketData->UpperLimitPrice;//涨停板价格
    os<< "," << pDepthMarketData->LowerLimitPrice;//跌停板价格
    os<< "," << pDepthMarketData->PreSettlementPrice;//昨结算
    os<< "," << pDepthMarketData->PreClosePrice;//昨收盘
    os<< "," << pDepthMarketData->PreOpenInterest;//昨持仓
    os<< endl;
    outlog<<os.str();
    outlog.flush();
    emit broadcast_quote(os.str());
}
