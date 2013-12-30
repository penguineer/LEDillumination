# bigBULB - 42x WS2811 / WS2812(B)
# Copyright 2013 Stefan Schuermans <stefan@blinkenarea.org>
# Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
# a BlinkenArea project - http://www.blinkenarea.org/

SRCS_C=$(wildcard *.c)
SRCS_S=$(wildcard *.s)
TARGET=bigBULB

PROGRAMMER = avrisp2
PROGRAMMER_PORT = usb
#PROGRAMMER = stk200
#PROGRAMMER_PORT = /dev/parport0

MCU=atmega8
DEVICE=m8
LFUSE=0xBF
HFUSE=0xC9
LOCK=0xFC

CC=avr-gcc
DEFINES=
INCLUDE=
CFLAGS=-std=gnu99 -Wall -Wextra -Wstrict-prototypes -Werror -g -Os \
       -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
       -fno-strict-aliasing -mmcu=$(MCU)
SFLAGS=-Wa,-gstabs -mmcu=$(MCU)
LDFLAGS= -Wl,--cref -mmcu=$(MCU)
LIBS=-lm
OBJCOPY=avr-objcopy
SIZE=avr-size
NM=avr-nm

AVRDUDE=avrdude
AVRDUDE_CALL=$(AVRDUDE) -c $(PROGRAMMER) -P $(PROGRAMMER_PORT) -p $(DEVICE)

SRCS_C_BASE=$(patsubst %.c,%,$(SRCS_C))
SRCS_S_BASE=$(patsubst %.s,%,$(SRCS_S))
SRCS_BASE=$(SRCS_C_BASE) $(SRCS_S_BASE)
DEPS=$(addsuffix .d,$(SRCS_BASE))
LSTS=$(addsuffix .lst,$(SRCS_BASE))
OBJS=$(addsuffix .o,$(SRCS_BASE))


.PHONY: all clean prog_fuses prog prog_auto
.SUFFIXES:
.SECONDARY:

all: deps $(TARGET).hex

ifneq ($(MAKECMDGOALS),clean)
  include deps
endif

deps: $(DEPS)
	cat /dev/null $+ >$@

%.d: %.c
	$(CC) $(DEFINES) $(INCLUDE) -mmcu=$(MCU) -M -o $@ $<

%.d: %.s
	touch $@

%.o: %.c
	$(CC) $(DEFINES) $(INCLUDE) $(CFLAGS) \
	      -Wa,-adhlns=$(@:.o=.lst) -c -o $@ $<

%.o: %.s
	$(CC) $(DEFINES) $(SFLAGS) \
	      -Wa,-adhlns=$(@:.o=.lst) -c -x assembler-with-cpp -o $@ $<

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -Wl,-Map=$(@:.elf=.map) -o $@ $+ $(LIBS)
	$(NM) -n $@ >$(@:.elf=.sym)
	$(SIZE) -A $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

prog_fuses: Makefile
	$(AVRDUDE_CALL) -u -e
	$(AVRDUDE_CALL) -u -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

prog: $(TARGET).hex Makefile
	$(AVRDUDE_CALL) -u -e
	$(AVRDUDE_CALL) -u -U flash:w:$<
	$(AVRDUDE_CALL) -u -V -U lock:w:$(LOCK):m

prog_auto: $(TARGET).hex
	while ! $(MAKE) prog_fuses && $(MAKE) prog; do echo -n; done; beep

clean:
	rm -f deps $(DEPS) $(LSTS) $(OBJS) \
	      $(TARGET).elf $(TARGET).hex $(TARGET).map $(TARGET).sym \

