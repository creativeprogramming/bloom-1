CFLAGS=-Wall

all:
	gcc ${CFLAGS} bloom.c spellcheck.c -o spellcheck

test:
	gcc ${CFLAGS} bloom.c test.c -o test
	./test

clean:
	rm -rf spellcheck test
