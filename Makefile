CFLAGS=-Wall

all: a b

a: a.c
	gcc -o a a.c

b: b.c
	gcc -o b b.c

clean:
	rm -f a b
