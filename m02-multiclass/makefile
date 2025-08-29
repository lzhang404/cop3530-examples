# compiler and flags
CXX = g++
# compiler options, -Wall enbales all common warnings
FLAGS = -Wall -std=c++14
# Build target
# -o $@ outputs file named after the target 
# $^ expands to all dependencies
test: test.o store.o store-item.o
	$(CXX) -o $@ $^
# compilation Rules, build test.o from test.cpp
# also listed header dependencies
# $<, first depenndency -> test.cpp
# -c, compile only dont link
test.o: test.cpp store.hpp store-item.hpp
	$(CXX) $(FLAGS) -c $<

store.o: store.cpp store.hpp
	$(CXX) $(FLAGS) -c $<

store-item.o: store-item.cpp store-item.hpp
	$(CXX) $(FLAGS) -c $<
# clean target. *.o objects files, *.gc, coverage files
# test compiled exectuable, *.dSYM debug symbol folders
clean:
	rm -rf *.o *.gc* test *.dSYM
