CC=avr-gcc
F_CPU=16000000UL
UART_BAUDRATE=115200
CFLAGS=-mmcu=atmega328 -D F_CPU=$(F_CPU) -D UART_BAUDRATE=$(UART_BAUDRATE) -Os -MMD

NAME=main

SRCS_DIR = srcs/

SRCS_LIST=main.c \
	uart.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objs/

OBJS_LIST=$(SRCS_LIST:.c=.o)

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

INCLUDES_PATH = -Iincludes

HEADER = $(patsubst %.o,%.d, $(OBJS))

all: hex flash

-include $(HEADER)

hex: $(NAME).hex

$(NAME).hex: $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME).bin
	avr-objcopy -O ihex $(NAME).bin $(NAME).hex

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES_PATH) -c $< -o $@

flash:
	avrdude -p m328p -c arduino -P /dev/ttyACM0 -b $(UART_BAUDRATE) -u -U flash:w:$(NAME).hex:i
	screen -S ex00 /dev/ttyACM0 $(UART_BAUDRATE)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(NAME).bin $(NAME).hex
	rm -rf $(OBJS_DIR)

.PHONY : all hex flash clean