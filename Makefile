all: microweb1 compres2 decompres2 clean

microweb1: microweb1.o
	gcc -o microweb1 microweb1.o
microweb1.o: microweb1.h e4_base64_VF.h compres2.h
	gcc -c microweb1.c

compres2: compres2.o
	gcc -o compres2 compres2.o
compres2.o: compres2.c compres2.h
	gcc -c compres2.c

decompres2: decompres2.c decompres2.o
	gcc -o decompres2 decompres2.o
decompres2.o: decompres2.c
	gcc -c decompres2.c

clean:
	rm *.o
