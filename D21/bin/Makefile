PROJNAME = bm_d21
LDSCRIPT = samd21j18a_flash.ld
#xdk-asf/
BOOTUP = startup_samd21.o system_samd21.o
MCUTYPE=__SAMD21J18A__
DEPS = -I../inc \
	-I../inc/cmsis \
	-I../cfg \
	-I../inc/include \
	-I../inc/include/component \
	-I../inc/include/instance \
	-I../inc/include/pio \

OBJS=$(BOOTUP) main.o project.o

# Tools
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as

ELF=$(PROJNAME).elf

LDFLAGS+= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m0 -Wl,--gc-sections
CFLAGS+= -mcpu=cortex-m0 -mthumb -g
#CFLAGS+= -I xdk-asf -I xdk-asf/include -I xdk-asf/cmsis -I .
CFLAGS+= $(DEPS)
CFLAGS+= -D$(MCUTYPE)

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# compile and generate dependency info
%.o: ../src/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

%.o: ../src/%.s
	$(AS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(ELF) *.o *.d $(CLEANOTHER)

debug: $(ELF)
	arm-none-eabi-gdb -iex "target extended-remote localhost:3333" $(ELF)

# pull in dependencies
-include $(OBJS:.o=.d)
