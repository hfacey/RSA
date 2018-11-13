OPTS = -Wall -g

all: ReallyLongInt.o encrypt decrypt keygen factorial

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

encrypt: encrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

keygen: keygen.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

factorial: factorial.cc ReallyLongInt.o
	g++ ${OPTS} -o factorial factorial.cc ReallyLongInt.o

clean:
	rm *.o
	rm encrypt
	rm decrypt
	rm keygen
	rm factorial

cleanemacs:
	rm *~
