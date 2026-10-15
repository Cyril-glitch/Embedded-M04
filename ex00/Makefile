CC = avr-gcc
C_FLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  utils.c

BIN_DIR = bin/
BIN = bin/main.bin
HEX = bin/main.hex
ASM = bin/main.s

MCU = atmega328p
F_CPU = -DF_CPU=16000000UL 

BOOT_LOAD = arduino
PORT = /dev/ttyUSB0


all : hex flash

hex :
	mkdir -p $(BIN_DIR)
	$(CC) -mmcu=$(MCU) $(C_FLAGS) $(F_CPU) -Os -o $(BIN) $(SRC)
	avr-objcopy -O ihex $(BIN) $(HEX)

flash :  
	avrdude -p $(MCU) -c $(BOOT_LOAD) -P $(PORT) -U flash:w:$(HEX)

asm :
	mkdir -p $(BIN_DIR)
	$(CC) -mmcu=$(MCU) $(C_FLAGS) $(F_CPU) -Os -S main.c -o $(ASM)

clean: 
	rm -rf $(BIN_DIR)