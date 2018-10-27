main: black_jack_solver.o main.cpp
	g++ -std=c++11 -o main main.cpp black_jack_solver.o -g

black_jack_solver.o: black_jack_solver.h black_jack_solver.cpp hide.h
	g++ -std=c++11 -c black_jack_solver.cpp -g
clean:
	rm -f main black_jack_solver.o