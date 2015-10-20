#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>

#include <QCoreApplication>
#include<QObject>
#include<QThread>
#include <QTextCodec>

#include"../libs/ctp/ThostFtdcMdApi.h"
#include"../libs/ctp/ThostFtdcTraderApi.h"

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
log_info simu_log;//ctp log
log_info loginfo;//gpp_qt log
ctp_log ctp_quote_log;//qoute log


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	//reg string
    qRegisterMetaType<string>("std::string");


    //load simu para
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");

    //set para
    simu_log.set_file("d:/record/"+wfunction::get_now_second()+".txt");
    ctp_quote_log.set_file("d:/record/quote_"+wfunction::get_now_second()+".csv");

    //set cm ordermanager and tactic

    ctp_manager * cm=new ctp_manager();
    cm->init();
    cm->start_ctp_quote();



    return a.exec();
}

