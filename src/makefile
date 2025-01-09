assembler_program: main.o macro.o command.o command_methods.o link_list.o first_pass.o second_pass.o memory.o bits_utils.o utils.o
	gcc -ansi -Wall -g -pedantic -o assembler_program main.o macro.o command.o command_methods.o link_list.o first_pass.o second_pass.o memory.o bits_utils.o utils.o

main.o: main.c data.h
	gcc -ansi -Wall -g -pedantic -c main.c -o main.o

macro.o: macro.c data.h
	gcc -ansi -Wall -g -pedantic -c macro.c -o macro.o

command.o: command.c data.h
	gcc -ansi -Wall -g -pedantic -c command.c -o command.o

command_methods.o: command_methods.c data.h
	gcc -ansi -Wall -g -pedantic -c command_methods.c -o command_methods.o

link_list.o: link_list.c data.h
	gcc -ansi -Wall -g -pedantic -c link_list.c -o link_list.o

first_pass.o: first_pass.c data.h
	gcc -ansi -Wall -g -pedantic -c first_pass.c -o first_pass.o

second_pass.o: second_pass.c data.h
	gcc -ansi -Wall -g -pedantic -c second_pass.c -o second_pass.o

memory.o: memory.c data.h
	gcc -ansi -Wall -g -pedantic -c memory.c -o memory.o

bits_utils.o: bits_utils.c data.h
	gcc -ansi -Wall -g -pedantic -c bits_utils.c -o bits_utils.o

utils.o: utils.c data.h
	gcc -ansi -Wall -g -pedantic -c utils.c -o utils.o

