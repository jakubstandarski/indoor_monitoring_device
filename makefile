#
# Author: Jakub Standarski
# Email: jstand.jakub.standarski@gmail.com
#
# Date: 26.10.2020
#

#-----------------------------------------------------------------------------#
# GENERAL SETTINGS #
#-----------------------------------------------------------------------------#

DEPENDENCIES_PATH = ./dependencies

TOOLCHAIN_VERSION = 9-2020-q2-update
TOOLCHAIN_PATH = /opt/gcc-arm-none-eabi/$(TOOLCHAIN_VERSION)

PROJECT_NAME = indoor_monitoring_device



#-----------------------------------------------------------------------------#
# APPLICATION SETTINGS #
#-----------------------------------------------------------------------------#

APPLICATION_PATH = ./application

APPLICATION_INCLUDE_DIR = $(APPLICATION_PATH)/include
APPLICATION_SOURCE_DIR = $(APPLICATION_PATH)/source
APPLICATION_SOURCE_FILES = main.c



#-----------------------------------------------------------------------------#
# SENSORS SETTINGS #
#-----------------------------------------------------------------------------#

SENSORS_PATH = ./sensors
SENSORS_INCLUDE_DIR = $(SENSORS_PATH)/include
SENSORS_SOURCE_DIR = $(SENSORS_PATH)/source
SENSORS_SOURCE_FILES =



#-----------------------------------------------------------------------------#
# SERVICES SETTINGS #
#-----------------------------------------------------------------------------#

SERVICES_PATH = ./services
SERVICES_INCLUDE_DIR = $(SERVICES_PATH)/include
SERVICES_SOURCE_DIR = $(SERVICES_PATH)/source
SERVICES_SOURCE_FILES =



#-----------------------------------------------------------------------------#
# PERIPHERALS DRIVERS SETTINGS #
#-----------------------------------------------------------------------------#

PERIPHERALS_DRIVERS_PATH = $(DEPENDENCIES_PATH)/peripherals_drivers/

PERIPHERALS_DRIVERS_INCLUDE_DIR = $(PERIPHERALS_DRIVERS_PATH)/include
PERIPHERALS_DRIVERS_SOURCE_DIR = $(PERIPHERALS_DRIVERS_PATH)/source
PERIPHERALS_DRIVERS_SOURCE_FILES =



#-----------------------------------------------------------------------------#
# CMSIS SETTINGS #
#-----------------------------------------------------------------------------#

CMSIS_PATH = $(DEPENDENCIES_PATH)/cmsis

CMSIS_COMPILER_INCLUDE_DIR = $(CMSIS_PATH)/compiler

CMSIS_CORE_INCLUDE_DIR = $(CMSIS_PATH)/core

CMSIS_SYSTEM_INCLUDE_DIR = $(CMSIS_PATH)/system/include
CMSIS_SYSTEM_SOURCE_DIR = $(CMSIS_PATH)/system/source
CMSIS_SYSTEM_SOURCE_FILES = system_stm32f4xx.c

CMSIS_STARTUP_SOURCE_DIR = $(CMSIS_PATH)/startup
CMSIS_STARTUP_SOURCE_FILES = startup_stm32f407xx.s




#-----------------------------------------------------------------------------#
# COMPILER SETTINGS #
#-----------------------------------------------------------------------------#

WARNING_FLAGS = -Wall -Wextra -Werror -Wdouble-promotion -Wconversion
WARNING_FLAGS += -Wformat=2 -Wformat-truncation

DEBUG_LVL = -g3

OPTIMIZATION_LVL = -O0

SECTIONS_FLAGS = -ffunction-sections -fdata-sections

ENDIANNESS = -mlittle-endian

ISA_TYPE = -mthumb

FPU_TYPE = -mfloat-abi=soft

CPU = -mcpu=cortex-m4

MCU = -DSTM32F407xx

PERIPHERALS_DRIVERS_TYPE = -DUSE_FULL_LL_DRIVER

HEADER_FILES = -I$(APPLICATION_INCLUDE_DIR)
HEADER_FILES += -I$(SENSORS_INCLUDE_DIR)
HEADER_FILES += -I$(SERVICES_INCLUDE_DIR)
HEADER_FILES += -I$(PERIPHERALS_DRIVERS_INCLUDE_DIR)
HEADER_FILES += -I$(CMSIS_COMPILER_INCLUDE_DIR)
HEADER_FILES += -I$(CMSIS_CORE_INCLUDE_DIR)
HEADER_FILES += -I$(CMSIS_SYSTEM_INCLUDE_DIR)


COMPILER_BIN = $(TOOLCHAIN_PATH)/bin/arm-none-eabi-gcc
COMPILER_FLAGS = $(WARNING_FLAGS) $(DEBUG_LVL) $(OPTIMIZATION_LVL)
COMPILER_FLAGS += $(SECTIONS_FLAGS) $(ISA_TYPE) $(FPU_TYPE) $(CPU) $(MCU)
COMPILER_FLAGS += $(ENDIANNESS)
COMPILER_FLAGS += $(PERIPHERALS_DRIVERS_TYPE) $(HEADER_FILES)



#-----------------------------------------------------------------------------#
# LINKER SETTINGS #
#-----------------------------------------------------------------------------#

LINKER_SCRIPT_DIR = $(DEPENDENCIES_PATH)/linker_script

LINKER_SCRIPT_FILE = stm32f407vgtx_flash.ld

LINKER_FLAGS = -T$(LINKER_SCRIPT_DIR)/$(LINKER_SCRIPT_FILE)
LINKER_FLAGS += $(ISA_TYPE) $(CPU_TYPE)
LINKER_FLAGS += -Wl,--gc-sections



#-----------------------------------------------------------------------------#
# OBJCOPY SETTINGS #
#-----------------------------------------------------------------------------#

OBJCOPY_BIN = $(TOOLCHAIN_PATH)/bin/arm-none-eabi-objcopy



#-----------------------------------------------------------------------------#
# BUILD PROCEDURE #
#-----------------------------------------------------------------------------#

BUILD_DIR = ./build

ELF_FILE = $(addprefix $(BUILD_DIR)/, $(PROJECT_NAME).elf)
BIN_FILE = $(addprefix $(BUILD_DIR)/, $(PROJECT_NAME).bin)
HEX_FILE = $(addprefix $(BUILD_DIR)/, $(PROJECT_NAME).hex)
.PHONY: $(ELF_FILE) $(BIN_FILE) $(HEX_FILE)

SOURCE_FILES = $(addprefix $(APPLICATION_SOURCE_DIR)/, \
	$(APPLICATION_SOURCE_FILES))
SOURCE_FILES += $(addprefix $(SENSORS_SOURCE_DIR)/, \
	$(SENSORS_SOURCE_FILES))
SOURCE_FILES += $(addprefix $(SERVICES_SOURCE_DIR)/, \
	$(SERVICES_SOURCE_FILES))
SOURCE_FILES += $(addprefix $(PERIPHERALS_DRIVERS_SOURCE_DIR)/, \
	$(PERIPHERALS_DRIVERS_SOURCE_FILES))
SOURCE_FILES += $(addprefix $(CMSIS_SYSTEM_SOURCE_DIR)/, \
	$(CMSIS_SYSTEM_SOURCE_FILES))
SOURCE_FILES += $(addprefix $(CMSIS_STARTUP_SOURCE_DIR)/, \
	$(CMSIS_STARTUP_SOURCE_FILES))

build: $(HEX_FILE) $(BIN_FILE) $(ELF_FILE)

$(HEX_FILE): $(ELF_FILE)
	$(OBJCOPY_BIN) -O ihex $< $@

$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY_BIN) -O binary $< $@

$(ELF_FILE): $(SOURCE_FILES)
	mkdir -p $(BUILD_DIR)
	$(COMPILER_BIN) $(COMPILER_FLAGS) $(LINKER_FLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)



#-----------------------------------------------------------------------------#
# FLASH PROCEDURE #
#-----------------------------------------------------------------------------#

FLASH_START_ADDRESS = 0x08000000

flash:
	st-flash write $(BIN_FILE) $(FLASH_START_ADDRESS)

erase:
	st-flash erase

