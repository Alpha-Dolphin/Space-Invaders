#Ben Elleman

#this is where you create an entry to build your zip file
#it will also update with new labs
#change the lab number
lab4.zip:	makefile *.a *.c *.h README_LAB4 reliable.o unreliable.o
	zip $@ $^
	rm -rf install
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4

#change the last dependency for each new lab
all:  tags headers lab4

#this entry stays for C code labs
tags: *.c
	ctags -R.

# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -Wconversion -g -c $< -o $@

#Prototype to test out terse insert
protoIn: protoIn.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders -llinkedlist
#Prototype to test out any function 
protoA: protoA.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders -llinkedlist
#Prototype to test out linkedList
protoIt: protoIt.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders -llinkedlist
#Prototype to test out terse deleteSome
protoDS: protoDS.o reliable.o 
	gcc -g -o $@ $^ -lncurses -L. -linvaders -llinkedlist
#Prototype to test out sort
protoS: protoS.o 
	gcc -g -o $@ $^ -lncurses -L. -linvaders -llinkedlist
lab4: lab4.o motion.o code.o output.o memory.o llfunc.o jumpTable.o files.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 
lab4u: lab4.o motion.o code.o output.o memory.o llfunc.o jumpTable.o files.o linkedlist.o unreliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 

