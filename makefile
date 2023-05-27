a.exe : Assignment4PartA.o
	gcc Assignment4PartA.o

Assignment4.o : Assignment4PartA.c
	gcc -c Assignment4PartA.c

clean : 
	rm a.exe
	rm Assignment4PartA.o


