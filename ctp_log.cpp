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
    os<<"," << dt.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd").toStdString();
    os<< "," << pDepthMarketData->InstrumentID;
    os<< "," << pDepthMarketData->BidPrice1;
    os<< "," << pDepthMarketData->AskPrice1;
    os<< "," << pDepthMarketData->BidVolume1;
    os<< "," << pDepthMarketData->AskVolume1;
    os<< "," << pDepthMarketData->LastPrice;
    os<< "," << pDepthMarketData->HighestPrice;
    os<< "," << pDepthMarketData->LowestPrice;
    os<< "," << pDepthMarketData->Turnover;
    os<< "," << pDepthMarketData->AveragePrice;
    os<< "," << pDepthMarketData->PreSettlementPrice;
    // SettlementPrice 是无效数据
    //os<< "," << pDepthMarketData->SettlementPrice;
    os<< endl;
    outlog<<os.str();
    emit broadcast_quote(os.str());
}
