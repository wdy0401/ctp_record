#include"ctp_manager.h"
#include"ctp_quote_qthread.h"
#include"ctp_log.h"

#include"../gpp_qt/cfg/cfg.h"


extern cfg simu_cfg;
extern ctp_log ctp_quote_log;

void ctp_manager::init()
{
    ctp_quote_running=false;
}
bool ctp_manager::check_trade_init_para()
{
    if(simu_cfg.getparam("TRADE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
bool ctp_manager::check_quote_init_para()
{
    if(simu_cfg.getparam("QUOTE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
void ctp_manager::start_ctp_quote()
{
    if(!ctp_quote_running)
    {
        if(this->check_quote_init_para())
        {
            ctp_quote_qthread  * cqq;
            cqq = new ctp_quote_qthread;
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, &ctp_quote_log, &ctp_log::writeinfo);
            ctp_quote_running = true;
            cqq->init();
            cqq->start();
        }
    }
}
