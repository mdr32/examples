EXAMPLES_SRCFILES = common/core_clock.c \
                    common/delay.c

LIB_SRCFILES =  SPL/MDR32FxQI/src/MDR32FxQI_rst_clk.c \
                LOCM3/src/locm3_rcc.c \
                LOCM3/src/locm3_systick.c \
                LOCM3/src/locm3_gpio.c \
                LOCM3/src/locm3_timer.c

EXAMPLES_LOCAL_SRCFILES = DHT.c