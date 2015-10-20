/****************************************
 *@system CTP下单系统
 *@company 兴证期货
 *@file ctp_manager.h
 *@brief 整体管理ctp对象
 *@history
 *20141219 王德扬 创建此注释
 ****************************************/

#ifndef CTP_MANAGER_H
#define CTP_MANAGER_H
#include"QObject"
class ctp_manager:public QObject
{
    Q_OBJECT
public:

    void init();
    bool check_quote_init_para();
    bool check_trade_init_para();
    void start_ctp_quote();

    bool is_quote_running(){return ctp_quote_running;}

public slots:

private:
    bool ctp_quote_running;

};

#endif // CTP_MANAGE_H
