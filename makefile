all: assign2

assign2: assign2.c pslibrary.c
	cc -o assign2 assign2.c pslibrary.c

clean:
	rm -f assign2 assign2 *.o

run0:
	assign2 3 8 7 3 6 3 3
runa:
	assign2 3 8 7 3 6 7 2
runb:
	assign2 4 8 7 3 6 1 2
runc:
	assign2 3 3 3 4 2 1 2
run1:
	assign2 3 3 2 3 2 1 2
run2:
	assign2 3 5 2 5 4 1 1
