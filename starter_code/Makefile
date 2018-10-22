main: black_jack_solver.o main.cpp
	g++ -std=c++11 -o main main.cpp black_jack_solver.o

black_jack_solver.o: black_jack_solver.h black_jack_solver.cpp
	g++ -std=c++11 -c black_jack_solver.cpp
clean:
	rm -f main black_jack_solver.o