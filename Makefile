#Makefile
CC=gcc
INCLUDE=
LIB=-lpthread -lcrypto
CFLAGS=-g   -D_REENTRANT -D_GNU_SOURCE ${LIB} ${INCLUDE}
#CFLAGS=-g ${LIB} ${INCLUDE}
MainFile=getGpsSpgByWget.c
#OutPut=$(patsubst %.c, %, ${MainFile})
OutPut=getGpsSpgByWget
src=
target=$(patsubst %.c, %.o, ${MainFile})
target+=$(patsubst %.c, %.o, ${src})
springcleaning=$(patsubst %.c, %, $(wildcard ./*.c))
springcleaning+=$(patsubst %.c, %.o, $(wildcard ./*.c))
springcleaning+=$(patsubst %.c, %.o, ${src})
springcleaning+=$(OutPut)

.PHONY: all clean

all: $(OutPut)
$(OutPut):${target}
	$(CC) ${target}  -o $@ ${CFLAGS} ${INCLUDE} 
	
clean:
	-@rm  ${springcleaning}
