# Proyecto de Genomas - Guía de Compilación y Uso

## Estructura de Archivos

Tu proyecto debe tener la siguiente estructura:

```
proyecto/
├── Punto.h
├── Secuencia.h
├── Secuencia.cxx
├── NodoHuffman.h
├── ArbolHuffman.h
├── ArbolHuffman.cxx
├── Grafo.h
├── Grafo.cxx
├── Utilidades.h
├── Utilidades.cxx
├── main.cpp
└── Makefile
```

## Makefile

Crea un archivo `Makefile` con el siguiente contenido:

```makefile
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
```

## Compilación

### En Linux/Mac:
```bash
make
./genomas
```

### En Windows (con MinGW):
```bash
g++ -std=c++11 -o genomas.exe main.cpp Secuencia.cxx ArbolHuffman.cxx Grafo.cxx Utilidades.cxx
genomas.exe
```

### Compilación manual:
```bash
g++ -std=c++11 -Wall -g -c main.cpp
g++ -std=c++11 -Wall -g -c Secuencia.cxx
g++ -std=c++11 -Wall -g -c ArbolHuffman.cxx
g++ -std=c++11 -Wall -g -c Grafo.cxx
g++ -std=c++11 -Wall -g -c Utilidades.cxx
g++ -std=c++11 -Wall -g -o genomas main.o Secuencia.o ArbolHuffman.o Grafo.o Utilidades.o
```

## Archivo FASTA de Prueba

Crea un archivo `test.fa` con el siguiente contenido:

```
>Full_SEQUENCE
CTCCGGTGAGAAATTTTGGGATGTATCAAATCACGGTCCTACTAC
TTACCGCCAACACGAGCCGGAACCCCCTAGATCAATTCATGCTTT
TCCCTTCACGCGAAGGAGTCGGAAGTGATCTGTATGAAGCTATTA
CCCTAGGTGGCCACACCTAC
>Incomplete_sequence
URDNSHVNKSCUANADDDVMMDVHRSRGNUNTSBTTMCGNBUUBTUMNAYKSTRYMVBWVNSC
SUUDDYVBCGNDRUURUBDHVGTYAVAVVSAKHUTSWCUBUUMSMDVDKBWRHHBHDBDWUDC
CAUWBRNYSTVTBBCKGDCMSNTKBNTRTNYRNWNWNVCSCNDDWHUHWRRTUMWNKHUBDWA
DUNYUVKHNKSDCYAVARTUWDVSTDVVMMVUHVBCDGVBSKKBHKSVHHGKSAADDVBRKSS
UKURTKTNAWYBKVRRBGKGBMGKUCGSMDTDTKCKVUYNVDWRWNBRCGKDWWUNBYMTGBN
YTAHCUTAGNBKWWGNDRKMNCDVDTKNRGVBRVMKGBKUBGBRHVUSTBCGDV
```

## Ejemplos de Uso

### Componente 1 - Estructuras Lineales

```bash
$ cargar test.fa
2 secuencias cargadas correctamente desde test.fa.

$ listar_secuencias
Hay 2 secuencias cargadas en memoria:
Secuencia Full_SEQUENCE contiene 180 bases.
Secuencia Incomplete_sequence contiene 378 bases.

$ histograma Full_SEQUENCE
A : 35
C : 45
G : 40
T : 60

$ es_subsecuencia ACGT
La subsecuencia dada se repite 3 veces dentro de las secuencias cargadas en memoria.

$ enmascarar ACGT
3 subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.

$ guardar salida.fa
Las secuencias han sido guardadas en salida.fa.
```

### Componente 2 - Huffman

```bash
$ codificar test.fabin
Secuencias codificadas y almacenadas en test.fabin.

$ decodificar test.fabin
Secuencias decodificadas desde test.fabin y cargadas en memoria.
```

### Componente 3 - Grafos

```bash
$ ruta_mas_corta Full_SEQUENCE 0 0 3 44
Para la secuencia Full_SEQUENCE, la ruta más corta entre la base C en [0,0] 
y la base C en [3,44] es: C -> T -> C -> ... -> C. El costo total de la ruta es: 15.2345

$ base_remota Full_SEQUENCE 0 0
Para la secuencia Full_SEQUENCE, la base remota está ubicada en [3,28], 
y la ruta entre la base en [0,0] y la base remota en [3,28] es: C -> T -> ... -> C. 
El costo total de la ruta es: 18.5432
```

## Solución de Problemas

### Error de compilación con C++11
Si obtienes errores, asegúrate de usar `-std=c++11` o superior.

### Error: "No such file or directory"
Verifica que todos los archivos .h y .cxx estén en el mismo directorio.

### Error en tiempo de ejecución
- Verifica que el archivo FASTA exista
- Verifica que tenga el formato correcto (líneas que empiezan con '>')
- Revisa que las rutas de archivos sean correctas

## Notas Importantes

1. **Formato FASTA**: Los archivos deben empezar con '>' seguido del nombre de la secuencia
2. **Codificación binaria**: Los archivos .fabin son binarios, no los abras con editores de texto
3. **Memoria**: El comando `cargar` o `decodificar` sobrescribe las secuencias anteriores
4. **Grafos**: Se construyen automáticamente la primera vez que se usan comandos del componente 3

## Entregables

Según el enunciado, debes entregar:

1. **Código fuente**: .h, .hxx, .cxx, .cpp
2. **Documento de diseño**: .pdf con TADs, diagramas y esquemáticos
3. **Plan de pruebas**: para comandos específicos según la entrega
4. **Todo en un .zip**: sin estructura de carpetas interna

## Testing Recomendado

1. Prueba cada comando individualmente
2. Prueba con archivos FASTA vacíos
3. Prueba con secuencias muy largas
4. Prueba enmascaramiento múltiple
5. Prueba codificación/decodificación para verificar integridad
6. Prueba grafos con posiciones inválidas