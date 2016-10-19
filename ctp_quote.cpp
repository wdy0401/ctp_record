#include"ctp_quote.h"

#include<iostream>
#include<cstring>
#include<list>
#include<windows.h>

#include <QCoreApplication>

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/log_info/log_info.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/wfunction/wfunction.h"

#include"../libs/ctp/ThostFtdcMdApi.h"

#include"ctp_quote_qthread.h"
extern cfg cfg_info;
extern wtimer wtm;


using namespace std;


void ctp_quote::init(ctp_quote_qthread * father)
{
    pqfather=father;
    init();
}
void ctp_quote::init()
{
    pUserApi=CThostFtdcMdApi::CreateFtdcMdApi();
    nRequestID=0;
    nppInstrumentID=0;
    ctp_time_length=sizeof(TThostFtdcTimeType);

    req=new CThostFtdcReqUserLoginField;
    memset(req, 0, sizeof(*req));
    strncpy(req->BrokerID,const_cast<char*>(cfg_info.get_para("BROKER_ID").c_str()),sizeof(req->BrokerID));
    strncpy(req->UserID,const_cast<char*>(cfg_info.get_para("INVESTOR_ID").c_str()),sizeof(req->UserID));
    strncpy(req->Password,const_cast<char*>(cfg_info.get_para("PASSWORD").c_str()),sizeof(req->Password));


    ppInstrumentID=new char * [MAX_CONTRACT_NUMBER];
    list<string> contracts=wfunction::splitstring(cfg_info.get_para("INSTRUMENT_ID"));
    for(list<string>::iterator iter=contracts.begin();iter!=contracts.end();iter++)
    {
        ppInstrumentID[nppInstrumentID]=new char [MAX_CONTRACT_NAME];
        memset(ppInstrumentID[nppInstrumentID],'\0',MAX_CONTRACT_NAME);
        strncpy(ppInstrumentID[nppInstrumentID],iter->c_str(),iter->size());
        nppInstrumentID++;
        cout<<"INFO: quote contract   "<<iter->c_str()<<endl;
    }
    cout << "INFO: BrokerID: "<<req->BrokerID<<endl;
    cout << "INFO: UserID: "<<req->UserID<<endl;
    login();
}

void ctp_quote::login()
{
    pUserApi->RegisterSpi(this);
    pUserApi->RegisterFront(const_cast<char*>(cfg_info.get_para("QUOTE_FRONT_ADDR").c_str()));
    pUserApi->Init();
    pUserApi->Join();
}
void ctp_quote::ReqUserLogin()
{
    int iResult = pUserApi->ReqUserLogin(req, ++nRequestID);
    cout << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void ctp_quote::OnRspError(CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
    //�в�����ھ�����������»ᴥ���˻ص�
    cout<< "--->>> "<< "OnRspError\t RequeseID="<<nRequestID<< endl;
    IsErrorRspInfo(pRspInfo);
}
void ctp_quote::OnFrontDisconnected(int nReason)
{
    cout << "--->>> " << "OnFrontDisconnected" << endl;
    cout << "Reasons\n\t0x1001 �����ʧ��\n\t0x1002 ����дʧ��\n\t0x2001 ����������ʱ\n\t0x2002 ��������ʧ��\n\t0x2003 �յ�������"<<endl;
    cout << "\tReason = " << nReason << endl;
}

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void ctp_quote::OnFrontConnected()
{
    cout << "--->>> " << "OnFrontConnected" << endl;
    ReqUserLogin();
}

///��¼������Ӧ
void ctp_quote::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cout << "--->>> " << "OnRspUserLogin" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        ///��ȡ��ǰ������
        cout << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay()<< endl;
        // ����������
        SubscribeMarketData();
    }
}
void ctp_quote::SubscribeMarketData()
{
    int iResult;
    if(nppInstrumentID>0)
    {
       iResult = pUserApi->SubscribeMarketData(ppInstrumentID, nppInstrumentID);
    }
    else
    {
        iResult = pUserApi->SubscribeMarketData(nullptr,0);
    }
    cout << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

///��������Ӧ��
void ctp_quote::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cout << "OnRspSubMarketData" << endl;
}

///ȡ����������Ӧ��
void ctp_quote::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cout << "OnRspUnSubMarketData" << endl;
}

///�������֪ͨ
void ctp_quote::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *p)
{
    char *tp=wfunction::ctp_time_char_convert(p->UpdateTime,sizeof(TThostFtdcTimeType));
    wtm.settic(atof(tp));
    delete tp;
    CThostFtdcDepthMarketDataField * pemit=new CThostFtdcDepthMarketDataField;
    memcpy(pemit,p,sizeof(*p));
    emit pqfather->broadcast_marketdata(pemit);
}
bool ctp_quote::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (bResult)
        cout << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
    return bResult;
}
