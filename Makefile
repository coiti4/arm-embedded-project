PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld

DEPFLAGS = -MP -MD
GDB   = gdb-multiarch
ASFLAGS = -g
LDFLAGS = -T ld_ram.lds -nostdlib
INCDIRS = ./CMSIS/Device/ST/STM32L4xx/Include ./CMSIS/Include

CC = $(PREFIX)gcc
CFLAGS = -Wall -Wextra -Werror -c -g -O1 -ffreestanding -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb $(DEPFLAGS) $(foreach D, $(INCDIRS), -I$(D))

ASFILES  = $(wildcard *.s)
CFILES = $(wildcard *.c)
ELFFILE = main.elf
VPATH = ./clocks
OBJ = $(patsubst %.c, %.o, $(CFILES)) $(patsubst %.s, %.o, $(ASFILES)) clocks.o image.o
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

all: $(ELFFILE)

$(ELFFILE): $(OBJ)

image.o: image.raw
	arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm image.raw image.o

%.elf:%.o
	$(LD) $(LDFLAGS) $^ -o $@

.PHONY: connect debug clean

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly


debug: $(EXE)
	$(GDB) -x se203.gdb $(ELFFILE)

clean:
	rm -f $(ELFFILE) $(OBJ) *.d
	
-include $(DEPFILES)
