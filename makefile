CXX=clang++
CXXFLAGS=
# -Wall -Werror -g
HEADERS=Stack.hpp
OBJECTS=Stack.o
SOURCES=Stack.cpp server.cpp client.cpp

run: demo server.o client.o
	./$^

server.o:server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server	

client.o:client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client	

demo: main.o $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $^ -o demo

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=-* --

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test client server