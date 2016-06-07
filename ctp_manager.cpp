#include"ctp_manager.h"
#include"ctp_quote_qthread.h"
#include"ctp_log.h"

#include"../gpp_qt/cfg/cfg.h"


extern cfg cfg_info;
extern ctp_log ctp_quote_log;

void ctp_manager::init()
{
    start_ctp_quote();
}
bool ctp_manager::check_quote_init_para()
{
    if(cfg_info.get_para("QUOTE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
void ctp_manager::start_ctp_quote()
{
    if(this->check_quote_init_para())
    {
        ctp_quote_qthread  * cqq;
        cqq = new ctp_quote_qthread;
        QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, &ctp_quote_log, &ctp_log::writeinfo);
        cqq->init();
        cqq->start();
    }
}
