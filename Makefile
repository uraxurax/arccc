CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

arccc: $(OBJS)
		$(CC) -o arccc $(OBJS) $(LDFLAGS)

$(OBJS): arccc.h

test: arccc
		./test.sh

clean:
		rm -f arccc *.o *~ tmp*

.PHONY: test clean