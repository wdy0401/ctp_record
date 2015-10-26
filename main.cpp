#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>

#include <QCoreApplication>
#include<QObject>
#include<QThread>
#include <QTextCodec>

#include"../libs/ctp/ThostFtdcMdApi.h"

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/log_info/log_info.h"

#include"./ctp_quote.h"
#include"./ctp_quote_qthread.h"
#include"./ctp_log.h"
#include"./ctp_manager.h"

using namespace std;

wtimer tm;
cfg simu_cfg;
ctp_log ctp_quote_log;//quote log


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	//reg string
    qRegisterMetaType<string>("std::string");


    //load simu para
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");
    if(argc>1)
    {
        cout << argv[1]<<endl;
        simu_cfg.addcfgfile(argv[1]);
    }
    //set para
    if(!ctp_quote_log.set_file(simu_cfg.getparam("quote_dir")+"/"+wfunction::get_now_second()+".csv"))
    {
        cerr<<"STDERR　qoute dir error"<<endl;
        return 0;
    }
    ctp_quote_log.set_file(simu_cfg.getparam("quote_dir")+"/"+wfunction::get_now_second()+".csv");

    //set cm ordermanager and tactic

    ctp_manager * cm=new ctp_manager();
    cm->init();
    cm->start_ctp_quote();

    return a.exec();
}

