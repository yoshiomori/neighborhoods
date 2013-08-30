FLAGS := -Wall -pedantic -ansi

neighborhood: main.o read_data.o alphabet.o
	gcc -o neighborhood $^

main.o: main.c read_data.h
	gcc -c $(FLAGS) $<

read_data.o: read_data.c read_data.h glob.h
	gcc -c $(FLAGS) $<

alphabet.o: alphabet.c alphabet.h
	gcc -c $(FLAGS) $<

clean:
	rm *.o *~ neighborhood
