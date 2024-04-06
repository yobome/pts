#include "stlog/stlog.h"
#include "zmq.h"
#include "ctp/ThostFtdcMdApi.h"
#include "pts/config_manager.hpp"
int main(int argc, char** argv)
{
    pts::ConfigManager::GetInstance().Init(argc, argv);
    return 0;
}