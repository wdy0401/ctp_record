#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>

#include<QCoreApplication>
#include<QObject>
#include<QThread>
#include<QTextCodec>
#include<QDateTime>

#include"../libs/ctp/ThostFtdcMdApi.h"

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/wfunction/udp_sender.h"

#include"./ctp_quote.h"
#include"./ctp_quote_qthread.h"
#include"./ctp_log.h"
#include"./ctp_manager.h"

using namespace std;

wtimer tm;
cfg simu_cfg;
ctp_log ctp_quote_log;//qoute log


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	//reg string
    qRegisterMetaType<string>("std::string");


    //load simu para
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");

    //add contract
    if(argc>1)
    {
        cout << argv[1]<<endl;
        simu_cfg.addcfgfile(argv[1]);
    }

    //set para
    if(!ctp_quote_log.set_file(simu_cfg.getparam("quote_dir")+"/"+QDateTime::currentDateTime().toString("yyyyMMdd_hh_mm_ss").toStdString()+".csv"))
    {
        cerr<<"STDERR　qoute dir error"<<endl;
        return 0;
    }
    //connect broadcast quote from ctp_log to udp_sender
    udp_sender sender;
    QObject::connect(&ctp_quote_log, &ctp_log::broadcast_quote, &sender, &udp_sender::broadcastDatagram);
    sender.init();
    //set cm ordermanager and tactic
    ctp_manager * cm=new ctp_manager();
    cm->init();
    cm->start_ctp_quote();

    return a.exec();
}

