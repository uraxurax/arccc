CFLAGS=-std=c11 -g -static

arccc: arccc.c

test: arccc
	./test.sh

clean:
	rm -f arccc *.o *~ tmp*

.PHONY: test clean