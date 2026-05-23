##############################################################################
# @author: ThuanHuynh
# @date: 23/05/2026
##############################################################################

# Toolchain
GCC_DIR := E:/GNU-toolchain/bin
CC=$(GCC_DIR)/arm-none-eabi-gcc
OBJ_CPY_TOOL=$(GCC_DIR)/arm-none-eabi-objcopy
PROGRAMMER := E:/STM32CubeProgrammer/bin/STM32_Programmer_CLI
CHIP = cortex-m3

# Output file
PATH_OUTPUT := ./output
MODULE := baremetal_uart

# Linker file
LD_FILE := Linker/stm32_ls.ld


# Include header files
INC_DIRS += driver/gpio	\
			driver/uart \
			driver/ring_buffer \
			user/inc

INC_FILES = $(foreach dir, $(INC_DIRS), $(wildcard $(dir)/*.h))

# Source files
SRC_DIRS += driver/gpio \
			driver/uart \
			driver/ring_buffer \
			user/src \
			startup

SRC_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

# Object files
OBJ_FILES = $(foreach file, $(SRC_FILES), $(PATH_OUTPUT)/$(notdir $(file:.c=.o)))

# Foreach for -I$() in compiler options
INC_DIR_OPT = $(foreach dir, $(INC_DIRS), -I$(dir))


# Flags: compiler & linker options
CCFLAGS= -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 $(INC_DIR_OPT)
LDFLAGS= -nostdlib -T $(LD_FILE) -Wl,-Map=$(PATH_OUTPUT)/$(MODULE).map 

.PHONY: build
build: $(PATH_OUTPUT)/$(MODULE).hex

# Compile object file
vpath %.c $(SRC_DIRS)

$(PATH_OUTPUT)/%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $^
	
# Build excutable file
$(PATH_OUTPUT)/$(MODULE).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

# Build .hex file
$(PATH_OUTPUT)/$(MODULE).hex: $(PATH_OUTPUT)/$(MODULE).elf
	$(OBJ_CPY_TOOL) -O ihex "$^" "$@"

# Flash firmware into chip
.PHONY: flash
flash: 
	$(PROGRAMMER) -c port=SWD -e all
	$(PROGRAMMER) -c port=SWD -w "$(PATH_OUTPUT)/$(MODULE).hex" 0x08000000 -rst


# Clear all output file
.PHONY: clean
clean:
	rm -rf ./Output/*
	
# Print
print-%:
	@echo $($(subst print-,,$@))