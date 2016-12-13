OBJ = test.o

all:test

test:$(OBJ)
	gcc -o $@ $^

clean:
	rm -rf *.o

.c.o:
	gcc -c $<
.PHONY:all,clean

