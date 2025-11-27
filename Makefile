CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = genomas

OBJS = main.o Secuencia.o ArbolHuffman.o Grafo.o Utilidades.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Secuencia.h Utilidades.h Grafo.h Punto.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Secuencia.o: Secuencia.cxx Secuencia.h
	$(CXX) $(CXXFLAGS) -c Secuencia.cxx

ArbolHuffman.o: ArbolHuffman.cxx ArbolHuffman.h NodoHuffman.h
	$(CXX) $(CXXFLAGS) -c ArbolHuffman.cxx

Grafo.o: Grafo.cxx Grafo.h Secuencia.h
	$(CXX) $(CXXFLAGS) -c Grafo.cxx

Utilidades.o: Utilidades.cxx Utilidades.h Secuencia.h ArbolHuffman.h
	$(CXX) $(CXXFLAGS) -c Utilidades.cxx

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)