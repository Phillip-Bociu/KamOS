ARCH = aarch64-elf-
CC = $(ARCH)gcc
LD = $(ARCH)ld
OBJCOPY = $(ARCH)objcopy

CPU = cortex-a7

ifeq ($(RASPI_MODEL),1)
    CPU = arm1176jzf-s
    DIRECTIVES = -D MODEL_1
	IMG_NAME = image/kernel7.img
endif

ifeq ($(RASPI_MODEL),3ap)
    CPU = cortex-a53
	IMG_NAME = image/kernel8.img
endif

CFLAGS =  -fpic -ffreestanding $(DIRECTIVES) -O2 
CSRCFLAGS= -Wall -Wextra
LFLAGS=  -nostdlib -O2 -nostartfiles

KERNEL_SRC_DIR=src/kernel
KERNEL_HEADER_DIR=include/kernel
OBJ_DIR=bin
KERNEL_SOURCES=$(wildcard $(KERNEL_SRC_DIR)/*.c)
ASM_SOURCES=$(wildcard $(KERNEL_SRC_DIR)/*.s)

OBJECTS = $(patsubst $(KERNEL_SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SOURCES))
OBJECTS += $(patsubst $(KERNEL_SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_SOURCES))
HEADERS = $(wildcard $(KERNEL_HEADER_DIR)/*.h)

all: clean build

.SILENT: clean build

build: $(OBJECTS) $(HEADERS)
	#echo "Objects: $(OBJECTS)"
	#echo "KERNEL_SOURCES: $(KERNEL_SOURCES)"
	#echo "ASM_SOURCES: $(ASM_SOURCES)\n"
	mkdir -p image/
	$(LD) -T build/linker.ld $(LFLAGS) $(OBJECTS) -o $(OBJ_DIR)/os.elf
	$(OBJCOPY) $(OBJ_DIR)/os.elf -O binary $(IMG_NAME)

	echo "$(IMG_NAME) successfully created!\n"

$(OBJ_DIR)/%.o: $(KERNEL_SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(KERNEL_HEADER_DIR) -c $< -o $@ $(CSRCFLAGS)
	
$(OBJ_DIR)/%.o: $(KERNEL_SRC_DIR)/%.s
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@

clean:
	rm -fr $(OBJ_DIR)
	rm -fr image/

