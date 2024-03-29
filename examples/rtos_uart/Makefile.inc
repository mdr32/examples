USE_RTOS=y

EXAMPLES_SRCFILES = common/core_clock.c

LIB_SRCFILES =  SPL/MDR32FxQI/src/MDR32FxQI_rst_clk.c \
                SPL/MDR32FxQI/src/MDR32FxQI_port.c \
                SPL/MDR32FxQI/src/MDR32FxQI_uart.c \
                SPL/MDR32FxQI/src/MDR32FxQI_timer.c

EXAMPLES_LOCAL_SRCFILES = drivers/serial.c \
                          drivers/button.c \
                          drivers/MDR32F9Q2I_IT.c