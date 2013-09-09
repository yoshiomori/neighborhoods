FLAGS := -Wall -pedantic -ansi

neighborhood: main.o data.o alphabet.o constant.o vertice.o processing.o
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

processing.o: processing.c processing.h data.h
	gcc -c $(FLAGS) $<

clean:
	rm *.o *~ neighborhood \#*
