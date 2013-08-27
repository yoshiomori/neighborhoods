FLAGS := -Wall -pedantic -ansi

neighborhood: main.o read_data.o
	gcc -o neighborhood $^

main.o: main.c read_data.h
	gcc -c $(FLAGS) $<

read_data.o: read_data.c read_data.h glob.h
	gcc -c $(FLAGS) $<

clean:
	rm *.o *~ neighborhood
