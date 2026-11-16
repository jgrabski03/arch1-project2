COMMON_OBJECTS  = main.o led.o buzzer.o switches.o stateMachines.o wdInterruptHandler.o transition.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h -I/opt/ti/msp430-gcc/include
LDFLAGS         = -L/opt/ti/msp430-gcc/include

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy.elf

toy.elf: ${COMMON_OBJECTS} ../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	mspdebug ${MSPLOADER_OPTION} "prog $^"

clean:
	rm -f *.o *.elf *~

main.o: led.h buzzer.h switches.h
led.o: led.h
buzzer.o: buzzer.h
switches.o: switches.h buzzer.h stateMachines.h
stateMachines.o: stateMachines.h led.h buzzer.h
wdInterruptHandler.o: stateMachines.h
