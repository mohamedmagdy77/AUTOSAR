##########################################################
# File Name: Makefile
# Description: make file contains shell commands
# Author Name: Mohamed Madgy
##########################################################

CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -gdwarf-2 -std=gnu11 -O0
LFLAGS= -nostdlib -T linker_script.ld -Wl,-Map=final.map
ASSFLAGS= $(CFLAGS) -S
PFLAGS= $(CFLAGS) -E

SRCS=$(wildcard *.c)
PRES=$(SRCS:.c=.i)
ASMS=$(SRCS:.c=.s)
OBJS=$(SRCS:.c=.o)

all: final.elf

final.elf: $(OBJS) linker_script.ld
	$(CC) $(LFLAGS) $(OBJS) -o final.elf

.c.o:
	$(CC) $(CFLAGS) $^ -o $@

assembly: $(ASMS)
.c.s:
	$(CC) $(ASSFLAGS) $^ -o $@

preprocessor: $(PRES)
.c.i:
	$(CC) $(PFLAGS) $^ -o $@

clean:
	del /f $(OBJS) final.elf
	
cleanasm:
	del /f $(ASMS)
	
cleanpre:
	del /f $(PRES)