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

wtimer wtm;
cfg cfg_info;
ctp_log ctp_quote_log;//qoute log


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	//reg string
    qRegisterMetaType<string>("std::string");

    udp_sender sender;
    ctp_manager * cm=new ctp_manager();

    cfg_info.init_cl(argc,argv);
    cfg_info.setcfgfile(cfg_info.get_para("cfg"));
    cfg_info.addcfgfile(cfg_info.get_para("ctr_file"));

    if(!ctp_quote_log.set_file(cfg_info.get_para("quote_dir")+"/"+QDateTime::currentDateTime().toString("yyyyMMdd_hh_mm_ss").toStdString()+".csv"))
    {
        cerr<<"STDERR qoute dir error"<<endl;
        return 0;
    }

    QObject::connect(&ctp_quote_log, &ctp_log::broadcast_quote, &sender, &udp_sender::broadcast_string);

    sender.init();
    cm->init();

    return a.exec();
}

