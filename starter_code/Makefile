black_jack_solver.o: black_jack_solver.h black_jack_solver.cpp
	g++ -c black_jack_solver.cpp

main: black_jack_solver.o main.cpp
	g++ -o main main.cpp black_jack_solver.o

clean:
	rm -f main black_jack_solver.o