TOP ?= $(TINYUSB_ROOT)
BOARD ?= uno_r4
PROJECT_NAME ?= asinino

# run 
# python tools/get_deps.py ra
# once in the tinyusb root folder

include $(TOP)/examples/build_system/make/make.mk

INC += \
	src \
	$(TOP)/hw \


EXAMPLE_SOURCE += $(wildcard src/hal/*.c)
EXAMPLE_SOURCE += $(wildcard src/*.c)
FSP_SOURCE += $(TOP)/hw/mcu/renesas/fsp/ra/fsp/src/r_flash_lp/r_flash_lp.c
CFLAGS += -DFLASH_LP_CFG_CODE_FLASH_PROGRAMMING_ENABLE -DFLASH_LP_CFG_DATA_FLASH_PROGRAMMING_ENABLE
CFLAGS += -DUSB_PID=0x0369 -DBOARD_NAME=\"UNO\ R4\ Minima\"
CFLAGS += -DLED_FADE_PWM_OUT_A=1 -DLED_FADE_PWM_OUT_B=0 -DLED_FADE_PWM_CHANNEL=3 -DLED_TIMER_SOURCE_DIV=2
CFLAGS += -DLED_FADE_GPIO=BSP_IO_PORT_01_PIN_11
CFLAGS += -DDFU_LOADER
CFLAGS += -DOVERRIDE_VECTOR_TABLE=1
CFLAGS += -DCODE_FLASH_DESCRIPTOR=\"@CodeFlash\ /0x00000000/8*2Ka,120*2Kg\"
FSP_SOURCE += $(TOP)/hw/mcu/renesas/fsp/ra/fsp/src/r_gpt/r_gpt.c


SRC_C += $(addprefix $(CURRENT_PATH)/, $(EXAMPLE_SOURCE))
SRC_C += $(FSP_SOURCE)

CFLAGS += -Os -flto
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wno-null-dereference -Wno-unused-const-variable -Wno-unused-function -Wno-unused-parameter
CFLAGS += --warn-no-undef
LDFLAGS += -Wl,--gc-sections -flto

include $(TOP)/examples/build_system/make/rules.mk

LD_FILE = $(FAMILY_PATH)/linker/gcc/$(MCU_VARIANT).ld

.PHONY: clean

build: all
