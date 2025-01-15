NAME=test

FORMAT = ihex

CC=avr-gcc

OBJCOPY = avr-objcopy

MCU = atmega328p

F_CPU=16000000UL

UART_BAUDRATE=115200

CFLAGS=-mmcu=$(MCU) -D GCC_MEGA_AVR -D F_CPU=$(F_CPU) -D UART_BAUDRATE=$(UART_BAUDRATE) -Os -MMD

CFLAGS+= -Wall -Wextra

# ---------- AVRDUDE --------------

AVRDUDE = avrdude

AVRDUDE_PROGRAMMER = arduino
 
AVRDUDE_PORT = /dev/ttyACM0
 
AVRDUDE_WRITE_FLASH = -U flash:w:$(NAME).hex:i
 
AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

# ---------- SOURCE --------------

SRCS_DIR = Source/
PORT_DIR = Source/portable/GCC/ATMega328/

SRCS_LIST=main.c \
$(SRCS_DIR)tasks.c \
$(SRCS_DIR)queue.c \
$(SRCS_DIR)list.c \
$(SRCS_DIR)croutine.c \
$(SRCS_DIR)portable/MemMang/heap_1.c \
$(PORT_DIR)port.c

OBJS=$(SRCS_LIST:.c=.o)

INCLUDES_PATH =-I. -ISource/include -ISource/portable/GCC/ATMega328

HEADER = $(patsubst %.o,%.d, $(OBJS))

all: $(NAME).hex flash

-include $(HEADER)

hex: $(NAME).hex

$(NAME).hex: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME).bin
	$(OBJCOPY) -O $(FORMAT) $(NAME).bin $(NAME).hex

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES_PATH) -c $< -o $@

flash: $(NAME).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -b $(UART_BAUDRATE) -u $(AVRDUDE_WRITE_FLASH)

clean:
	rm -rf $(OBJS)
	rm -rf $(HEADER)

fclean: clean
	rm -rf $(NAME).bin $(NAME).hex

re: fclean all

.PHONY : all hex flash clean fclean re