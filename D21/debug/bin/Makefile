PROJNAME = bm_d21_debug
DEPS = -I../inc


OBJS=$(BOOTUP) main.o debug.o

# Tools
CC=gcc
CFLAGS+= -w -Wall
#CFLAGS+= -I xdk-asf -I xdk-asf/include -I xdk-asf/cmsis -I .
CFLAGS+= $(DEPS)

$(PROJNAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROJNAME)

# compile
%.o: ../src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(PROJNAME) *.o

run: $(PROJNAME)
	@./$(PROJNAME)
