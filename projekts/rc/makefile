#defalt avr arduino makefile V1.0

TARGET	= rc

MCU		= atmega328p
#PORT	= $(ls /dev/ | egrep ttyUSB)
PORT	= /dev/ttyUSB0
AVRDUDE_BOUT	= 57600
PROGRAMMER	= stk500v1
LFUSE	= 0xC0
HFUSE	= 0x00

#FUSE	+= -U lfuse:w:$(LFUSE):m 
#FUSE	+= -U hfuse:w:$(HFUSE):m

F_CPU	= 16000000 
USART0_BAUDRATE	= 57600
#USART0_BAUDRATE = 9600
USART1_BAUDRATE	= 9600


CC		= avr-gcc

CFLAGS	+= -Os
CFLAGS	+= -funsigned-char 
CFLAGS  += -funsigned-bitfields 
CFLAGS  += -fpack-struct 
CFLAGS  += -fshort-enums 
CFLAGS  += -Wall 
#CFLAGS  += -Wstrict-prototypes 
CFLAGS  += -std=gnu99

#Präprozessor direktiven mit -D... Hinzufügen
CFLAGS	+= -DF_CPU=$(F_CPU)
CFLAGS	+= -DUSART0_BAUDRATE=$(USART0_BAUDRATE)
CFLAGS  += -DUSART1_BAUDRATE=$(USART1_BAUDRATE)
#CFLAGS	+= -D_PORTTOOL
#CFLAGS	+= -D_SERVOTOOL
CFLAGS	+= -D_ADCTOOL
CFLAGS	+= -DMCU
#CFLAGS	+= -DDEBUG

rm 		= rm -rf

#List all SORCE FILES hier
#src		+= test.c
#src		+= test2.c
#...

src		+= ./rc.c
src		+= ../../klib/uart/uart.c
src		+= ../../klib/nsh/nsh.c
#src		+= ../../klib/servo/servo.c
src		+= ../../klib/std/static_malloc.c
src		+= ../../klib/loop_control/loop_control.c
src		+= ../../klib/uart/soft_uart_timer.c
src   += ./prof.c
src		+= ./tool.c
src		+= ./tx.c
#...

bulid: $(src)
	@echo make ihex
	$(CC) -mmcu=$(MCU) $(CFLAGS) -g $(src) -o $(TARGET).elf
	
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex
	avr-size --mcu=$(MCU) -C $(TARGET).elf

upload:
	avrdude -p $(MCU) -P $(PORT) -U flash:w:$(TARGET).hex $(FUSE) -c $(PROGRAMMER) -b $(AVRDUDE_BOUT)

clean:
	$(rm) $(TARGET).elf $(TARGET).hex
