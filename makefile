FLAGS := -Wall -pedantic -ansi -g

neighborhood: main.o data.o alphabet.o constant.o vertice.o processing.o word_table.o
	gcc -o neighborhood $^

main.o: main.c data.h processing.h
	gcc -c $(FLAGS) $<

data.o: data.c data.h alphabet.h constant.h vertice.h
	gcc -c $(FLAGS) $<

alphabet.o: alphabet.c alphabet.h data.h
	gcc -c $(FLAGS) $<

constant.o: constant.c data.h
	gcc -c $(FLAGS) $<

vertice.o: vertice.c vertice.h data.h alphabet.h
	gcc -c $(FLAGS) $<

processing.o: processing.c processing.h data.h vertice.h
	gcc -c $(FLAGS) $<

word_table.o: word_table.c word_table.h data.h
	gcc -c $(FLAGS) $<

clean:
	rm *.o *~ neighborhood \#*
