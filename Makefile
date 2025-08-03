# Base
#-----------------------
TARGET_NAME = stm32f103_baremetal
TOOLCHAIN_PREFIX = arm-none-eabi-
BUILD_DIRECTION = build
APP_DIRECTION = app
DRIVER_DIRECTION = drivers
MICROCONTROLLER_ABSTRACTION_LAYER = mcal/stm32f1xx
BOARD_SUPPORT_PACKAGE_DIRECTION = bsp
OBJ_DIRECTION = $(BUILD_DIRECTION)/obj

#----------------------------------
# TOOLCHAIN
#----------------------------------
BOARD_NAME ?= BLUEPILL_F103
BUILD_PLATFORM ?= DEBIAN
CC = $(TOOLCHAIN_PREFIX)gcc
OBJ_COPY = $(TOOLCHAIN_PREFIX)objcopy
SIZE = $(TOOLCHAIN_PREFIX)size
ifeq ($(BUILD_PLATFORM), DEBIAN)
	GDB = gdb-multiarch
else
	GDB = $(TOOLCHAIN_PREFIX)gdb
endif
AS = $(TOOLCHAIN_PREFIX)as
LD = $(TOOLCHAIN_PREFIX)ld

#----------------------------------
# FLAGS
#----------------------------------
MCU_FLAGS = -mcpu=cortex-m3 -mthumb
WARN_FLAGS = -Wall -Wextra
OPT_FLAGS = -O0
DBG_FLAGS = -g3
C_FLAGS = $(MCU_FLAGS) $(WARN_FLAGS) $(OPT_FLAGS) $(DBG_FLAGS) -DSTM32F103xB -MMD -MP
AS_FLAGS = $(MCU_FLAGS) $(DBG_FLAGS)
#LD_FLAGS = $(MCU_FLAGS) --specs=nosys.specs -Tstartup/stm32f103c8tx_flash.ld -Wl,-Map=$(BUILD_DIRECTION)/$(TARGET_NAME).map -Wl,--gc-sections
LD_FLAGS = $(MCU_FLAGS) --specs=nano.specs --specs=nosys.specs -nostartfiles \
           -T$(MICROCONTROLLER_ABSTRACTION_LAYER)/startup/stm32f103c8tx_flash.ld \
           -Wl,-Map=$(BUILD_DIRECTION)/$(TARGET_NAME).map -Wl,--gc-sections


BUILD_TYPE ?= DEBUG
ifeq ($(BUILD_TYPE), RELEASE)
	OPT_FLAGS = -Os
	DBG_FLAGS =
	C_FLAGS += -DNDEBUG
endif

#-----------------Direction Set----------------------#

S_DIRECTIONS = $(MICROCONTROLLER_ABSTRACTION_LAYER)/startup

C_DIRECTIONS = \
	$(APP_DIRECTION)/ \
	$(BOARD_SUPPORT_PACKAGE_DIRECTION)/ \
	$(DRIVER_DIRECTION)/src/ \
	$(MICROCONTROLLER_ABSTRACTION_LAYER)/src/ \
	$(MICROCONTROLLER_ABSTRACTION_LAYER)/system/


INCLUDE_DIRECTIONS = \
	third_party/CMSIS/Include \
	third_party/CMSIS/Device/ST/STM32F1xx/Include \
	$(DRIVER_DIRECTION)/inc \
	$(MICROCONTROLLER_ABSTRACTION_LAYER)/inc
#-----------------------------------------------------#

#-----------------Source & Objects -------------------------------#

SRC_C_FILES = $(notdir $(foreach dir,$(C_DIRECTIONS),$(wildcard $(dir)/*.c)))
SRC_S_FILES = $(S_DIRECTIONS)/startup_stm32f103xb.s

# %-> indicate all of them , -I add before %(all) , searching directory = Include_Directions
C_FLAGS += $(patsubst %,-I%,$(INCLUDE_DIRECTIONS))

OBJS_C = $(addprefix $(OBJ_DIRECTION)/,$(SRC_C_FILES:.c=.c.o))
OBJS_S = $(addprefix $(OBJ_DIRECTION)/,$(notdir $(SRC_S_FILES:.s=.s.o)))
OBJS = $(OBJS_C) $(OBJS_S)

#-------------------------------------------------------------------#

VPATH = $(C_DIRECTIONS) $(S_DIRECTIONS)
DEPS = $(OBJS:.o=.d)

.PHONY: all build clean debug flash

all: build

build: $(BUILD_DIRECTION)/$(TARGET_NAME).elf
	@echo "Build successful for [$(BUILD_TYPE)] mode"

$(BUILD_DIRECTION)/$(TARGET_NAME).elf: $(OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(LD_FLAGS) $^ -o $@
	@echo "[SIZE] Target Size: "
	@$(SIZE) $@

# C sources
$(OBJ_DIRECTION)/%.c.o: %.c
	@echo "[CC] $<"
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

# ASM sources  
$(OBJ_DIRECTION)/%.s.o: %.s
	@echo "[AS] $<"
	@mkdir -p $(dir $@)
	@$(CC) $(AS_FLAGS) -c $< -o $@

clean:
	@echo "[CLEAN] Removing build directory..."
	@rm -rf $(BUILD_DIRECTION)

flash: build
	@echo "[FLASH] Flashing target [$(TARGET_NAME)]"
	@openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(BUILD_DIRECTION)/$(TARGET_NAME).elf verify reset exit"

debug: build
	@echo "[DEBUG] Debugging target [$(TARGET_NAME)]"
	@openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "gdb_port 3333" & \
	$(GDB) $(BUILD_DIRECTION)/$(TARGET_NAME).elf \
		-ex "target extended-remote :3333" \
		-ex "b main" \
		-ex "load"

-include $(DEPS)