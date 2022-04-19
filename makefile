CXX=clang++
CXXFLAGS=-Wall -Werror -g -v
# -Wall -Werror -g
HEADERS=Stack.hpp main.hpp
OBJECTS=Stack.o
SOURCES=Stack.cpp server.cpp client.cpp

run: clean demo server.o client.o
	./$^

server.o:server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server	-fPIE

client.o:client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client	-fPIE

demo: main.o $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $^ -o demo -fPIE

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=-* --

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@ -fPIE

clean:
	rm -f *.o demo test client server main.o Stack.o