#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __DEBUG__

#ifdef __DEBUG__
    #include "rtt/SEGGER_RTT.h"
    #define printf(...) SEGGER_RTT_printf(0, __VA_ARGS__)
    #define __ERROR(...) printf(RTT_CTRL_BG_RED RTT_CTRL_TEXT_BRIGHT_WHITE " Error " RTT_CTRL_RESET " " __VA_ARGS__)
    #define __INFO(...) printf(RTT_CTRL_BG_BLUE RTT_CTRL_TEXT_BRIGHT_WHITE " Info " RTT_CTRL_RESET " " __VA_ARGS__)
    #define __WARNING(...) printf(RTT_CTRL_BG_YELLOW RTT_CTRL_TEXT_BLACK " Warning " RTT_CTRL_RESET " " __VA_ARGS__ )
    // #define __READ() SEGGER_RTT_Read(0, &acIn[0], NumBytes)
    // telnet localhost 9090
    // echo 0x01 > /dev/tcp/localhost/9090
    // print &_SEGGER_RTT // get address
#else
    #define __DEBUG(...)
    #define __ERROR(...)
    #define __INFO(...)
    #define __WARNING(...)
#endif

#endif