CPPFLAGS=-Wall -std=c++14 -pedantic
CC=g++
SRC=src/
IPATH=-I inc/
OBJ=obj/
BIN=bin/

all:  main.o
	@${CC} -o ${BIN}App ${OBJ}main.o ${OBJ}controller.o ${OBJ}sistema.o ${OBJ}cliente.o ${OBJ}transacao.o

main.o: controller.o
	@${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}main.cpp -o ${OBJ}main.o -ld	

controller.o: cliente.o transacao.o sistema.o 
	@${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}controller.cpp -o ${OBJ}controller.o -lm

sistema.o: cliente.o transacao.o #rep.o
	@${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}sistema.cpp -o ${OBJ}sistema.o -lm 

#rep.o:
#	${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}rep.cpp -o ${OBJ}rep.o -lm

cliente.o:
	@${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}cliente.cpp -o ${OBJ}cliente.o -lm

transacao.o:
	@${CC} ${CPPFLAGS} ${IPATH} -c ${SRC}transacao.cpp -o ${OBJ}transacao.o -lm

run:
	@${BIN}App < test.txt