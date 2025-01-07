// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef GPIO_UART_ENABLE
#    ifndef IDEBUG_INFO
#        define IDEBUG_INFO(fmt, ...) iprintf(fmt "\r\n", ##__VA_ARGS__)
#    endif
#    ifndef MM_DEBUG_ENABLE
#        define MM_DEBUG_ENABLE
#        define MM_DEBUG_INFO IDEBUG_INFO
#    endif
#    ifndef IM_DEBUG_ENABLE
#        define IM_DEBUG_ENABLE
#        define IM_DEBUG_INFO IDEBUG_INFO
#    endif
#else
#    define IDEBUG_INFO(fmt, ...)
#endif

void iprint_init(void);
int iprintf(const char *fmt, ...);
