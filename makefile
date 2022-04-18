# all: main

# main: main.o Stack.o
# 	g++ main.o Stack.o -o main; ./main

# main.o:main.cpp
# 	g++ main.cpp -c -g -Wall

# Stack.o: Stack.cpp 
# 	g++ Stack.cpp -c 
	
# # g++ main.cpp
# # g++ Stack.cpp Stack.hpp

# clean:
# 	rm -f Stack.o main.o

CXX=g++ 
CXXFLAGS=-Wall

HEADERS=Stack.hpp
OBJECTS=Stack.o
SOURCES=Stack.cpp

run: demo
	./$^

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=-* --

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test