#pragma once

#include "es_socket.hpp"
#include "es_can.h"
#include "es_timer.h"
#include "es_backdoor.hpp"
#include "es_ctrl.h"

#ifdef __cplusplus

namespace smbus
{

class AppBase : protected socket::AppSocket, protected can::CanSocket, protected timer::WallTimer, protected ctrl::CtrlInterface
{
private:
    ESPort_t _port;

public:
    virtual void init(void) = 0;
    virtual void process(void) = 0;

protected:
    AppBase(ESPort_t can_port) : socket::AppSocket(), can::CanSocket(), timer::WallTimer(), ctrl::CtrlInterface()
    {
        _port = can_port;
    }

    void setup_callbacks(ESEther_appid_t appid)
    {
        ESBackdoor_setApp(_port, appid);

        socket::AppSocket::init(_port, appid);
        can::CanSocket::bind(_port);

        timer::WallTimer::bind(_port);
        ctrl::CtrlInterface::bind(_port);
    }

    void info(std::string msg)
    {
        ES_INFO(_port, msg);
    }
    
    void err(std::string msg)
    {
        ES_ERR(_port, msg);
    }
};

}

#endif /*__cplusplus*/
