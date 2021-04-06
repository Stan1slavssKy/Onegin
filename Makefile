SOURCE  = main.cpp Onegin.cpp sorting.cpp
OBJECT  = main.o   Onegin.o   sorting.o
OUTPUT  = Onegin
LIBRARY = libonegin.a

default: $(OUTPUT) library

$(OUTPUT): $(OBJECT)
	g++ -Wall -Wextra $(OBJECT) -o $(OUTPUT)
	valgrind ./$(OUTPUT) hamlet.txt

main.o: main.cpp
	g++ -g3 -O0 main.cpp -c

stack.o: Onegin.cpp
	g++ -g3 -O0 Onegin.cpp -c

protection.o: sorting.cpp
	g++ -g3 -O0 sorting.cpp -c

library: $(OBJECT)
	ar cr $(LIBRARY) Onegin.o

clean:
	rm -f *.o *.a $(OUTPUT)
