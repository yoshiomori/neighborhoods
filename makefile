FLAGS := -Wall -pedantic -ansi

neighborhood: main.o read_data.o alphabet.o constant.o vertice.o
	gcc -o neighborhood $^

main.o: main.c read_data.h
	gcc -c $(FLAGS) $<

read_data.o: read_data.c read_data.h alphabet.h constant.h vertice.h
	gcc -c $(FLAGS) $<

alphabet.o: alphabet.c alphabet.h glob.h
	gcc -c $(FLAGS) $<

constant.o: constant.c glob.h
	gcc -c $(FLAGS) $<

vertice.o: vertice.c vertice.h
	gcc -c $(FLAGS) $<

clean:
	rm *.o *~ neighborhood
