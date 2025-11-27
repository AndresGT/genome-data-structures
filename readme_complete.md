# 🧬 Sistema de Manipulación de Genomas

## Pontificia Universidad Javeriana - Estructuras de Datos 2025-30

### 📋 Tabla de Contenidos
- [Descripción General](#descripción-general)
- [Arquitectura del Sistema](#arquitectura-del-sistema)
- [Componentes del Proyecto](#componentes-del-proyecto)
- [Estructuras de Datos Utilizadas](#estructuras-de-datos-utilizadas)
- [Documentación Detallada del Código](#documentación-detallada-del-código)
- [Guía de Compilación](#guía-de-compilación)
- [Manual de Uso](#manual-de-uso)
- [Ejemplos de Uso](#ejemplos-de-uso)
- [Plan de Pruebas](#plan-de-pruebas)

---

## 📖 Descripción General

Este proyecto implementa un sistema completo para la manipulación de códigos genéticos almacenados en formato FASTA. El sistema permite:

1. **Cargar y manipular secuencias genéticas** usando estructuras lineales
2. **Comprimir y descomprimir archivos** usando codificación de Huffman
3. **Analizar relaciones entre bases** mediante representación en grafos

### 🎯 Objetivos del Proyecto

- Aplicar conceptos de **Estructuras de Datos** (listas, árboles, grafos)
- Implementar **algoritmos clásicos** (Huffman, Dijkstra)
- Trabajar con **formatos de archivos** (texto y binario)
- Desarrollar una **interfaz de línea de comandos** robusta

---

## 🏗️ Arquitectura del Sistema

```
┌─────────────────────────────────────────────────────────┐
│                    INTERFAZ DE USUARIO                   │
│                  (Terminal Interactiva)                  │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────┐
│                   CAPA DE COMANDOS                       │
│  cargar, listar, histograma, codificar, ruta_mas_corta  │
└────────┬────────────┬────────────┬──────────────────────┘
         │            │            │
┌────────▼─────┐ ┌───▼──────┐ ┌──▼────────────┐
│ COMPONENTE 1 │ │COMPONENTE│ │  COMPONENTE 3 │
│  Estructuras │ │    2     │ │    Grafos     │
│   Lineales   │ │  Huffman │ │   (Dijkstra)  │
└────────┬─────┘ └────┬─────┘ └───┬───────────┘
         │            │            │
┌────────▼────────────▼────────────▼───────────┐
│         CAPA DE DATOS (TADs)                  │
│  Secuencia, ArbolHuffman, Grafo, Punto       │
└───────────────────────────────────────────────┘
```

---

## 🧩 Componentes del Proyecto

### **Componente 1: Estructuras Lineales**
Manejo básico de secuencias genéticas usando vectores y strings.

**Comandos:**
- `cargar`: Carga archivos FASTA
- `listar_secuencias`: Lista secuencias en memoria
- `histograma`: Calcula frecuencias de bases
- `es_subsecuencia`: Busca patrones
- `enmascarar`: Reemplaza subsecuencias con 'X'
- `guardar`: Exporta a FASTA

### **Componente 2: Árboles de Huffman**
Compresión de datos mediante codificación óptima.

**Comandos:**
- `codificar`: Comprime secuencias a formato binario
- `decodificar`: Descomprime archivos .fabin

### **Componente 3: Grafos**
Análisis de relaciones espaciales entre bases.

**Comandos:**
- `ruta_mas_corta`: Encuentra camino óptimo entre bases
- `base_remota`: Localiza la base más lejana del mismo tipo

---

## 📊 Estructuras de Datos Utilizadas

### 1. **Vector (std::vector)**
- **Uso**: Almacenamiento de secuencias, nodos del grafo
- **Complejidad**: O(1) acceso, O(n) inserción/eliminación
- **Ventaja**: Memoria contigua, acceso rápido por índice

### 2. **Mapa (std::map)**
- **Uso**: Histogramas, códigos de Huffman, posiciones en grafo
- **Complejidad**: O(log n) búsqueda/inserción
- **Ventaja**: Mantiene orden, búsquedas eficientes

### 3. **Cola de Prioridad (std::priority_queue)**
- **Uso**: Construcción del árbol de Huffman, algoritmo de Dijkstra
- **Complejidad**: O(log n) inserción/extracción
- **Ventaja**: Acceso eficiente al mínimo/máximo

### 4. **Árbol Binario (Árbol de Huffman)**
- **Uso**: Codificación/decodificación de secuencias
- **Complejidad**: O(n log n) construcción, O(n) codificación
- **Ventaja**: Codificación óptima de frecuencias

### 5. **Grafo (Lista de Adyacencias)**
- **Uso**: Representación de secuencias como matriz conectada
- **Complejidad**: O((V+E) log V) Dijkstra
- **Ventaja**: Eficiente para grafos dispersos

---

## 📝 Documentación Detallada del Código

### 🔹 Punto.h

```cpp
class Punto {
private:
    double x, y, z;
public:
    Punto();  // Constructor por defecto
    Punto(double x, double y, double z);  // Constructor parametrizado
    
    // Getters y Setters
    double obtenerX() const;
    void fijarX(double x);
    
    // Operaciones de distancia
    double distanciaEuclidiana(const Punto& otro) const;
    double distanciaManhattan(const Punto& otro) const;
};
```

**Propósito**: TAD requerido en el enunciado para representar coordenadas 3D.

**Operaciones clave**:
- `distanciaEuclidiana()`: Calcula √[(x₁-x₂)² + (y₁-y₂)² + (z₁-z₂)²]
- `distanciaManhattan()`: Calcula |x₁-x₂| + |y₁-y₂| + |z₁-z₂|

---

### 🔹 Secuencia.h/.cxx

```cpp
class Secuencia {
private:
    std::string descripcion;  // Nombre de la secuencia (después de '>')
    std::string datos;        // Cadena de bases (ACGT, etc.)
    int anchoLinea;          // Ancho de justificación del FASTA

public:
    Secuencia();
    Secuencia(const std::string& desc, const std::string& datos, int ancho);
    
    // Métodos de acceso
    std::string obtenerDescripcion() const;
    std::string obtenerDatos() const;
    int obtenerAnchoLinea() const;
    int obtenerNumBases() const;
    bool esCompleta() const;  // Verifica si no contiene '-'
    
    // Modificadores
    void fijarDatos(const std::string& nuevosDatos);
    
    // Análisis
    std::map<char, int> calcularHistograma() const;
    
    // Para representación matricial (Componente 3)
    int obtenerFilas() const;
    int obtenerColumnas() const;
    char obtenerBase(int fila, int col) const;
    bool posicionValida(int fila, int col) const;
};
```

**Propósito**: Representa una secuencia genética individual con sus metadatos.

**Funcionalidades clave**:

1. **`calcularHistograma()`**: 
   ```cpp
   std::map<char, int> Secuencia::calcularHistograma() const {
       std::map<char, int> histograma;
       for (char c : datos) {
           histograma[c]++;  // Cuenta frecuencia de cada base
       }
       return histograma;
   }
   ```
   - Recorre cada base y cuenta su aparición
   - Retorna un mapa: {'A': 45, 'C': 30, 'G': 50, 'T': 60}

2. **`obtenerBase(fila, col)`**:
   ```cpp
   char Secuencia::obtenerBase(int fila, int col) const {
       int pos = fila * anchoLinea + col;  // Conversión 2D → 1D
       if (pos >= 0 && pos < (int)datos.length()) {
           return datos[pos];
       }
       return '\0';
   }
   ```
   - Convierte coordenadas 2D a índice 1D
   - Permite acceso matricial a la secuencia

3. **`esCompleta()`**:
   ```cpp
   bool Secuencia::esCompleta() const {
       return datos.find('-') == std::string::npos;
   }
   ```
   - Verifica si la secuencia tiene gaps (código '-')
   - Importante para diferenciar secuencias completas e incompletas

---

### 🔹 NodoHuffman.h

```cpp
class NodoHuffman {
public:
    char simbolo;           // Base genética (A, C, G, T, etc.)
    uint64_t frecuencia;    // Número de ocurrencias
    NodoHuffman* izq;       // Hijo izquierdo (bit '0')
    NodoHuffman* der;       // Hijo derecho (bit '1')
    
    NodoHuffman(char s, uint64_t f);  // Constructor hoja
    NodoHuffman(uint64_t f, NodoHuffman* izq, NodoHuffman* der);  // Nodo interno
    ~NodoHuffman();  // Destructor recursivo
    bool esHoja() const;  // Verifica si es nodo terminal
};
```

**Propósito**: Nodo del árbol de Huffman para codificación óptima.

**Diseño**:
- **Nodos hoja**: Contienen un símbolo y su frecuencia
- **Nodos internos**: Solo tienen frecuencia (suma de hijos)
- **Destructor recursivo**: Libera toda la memoria del subárbol

---

### 🔹 ArbolHuffman.h/.cxx

```cpp
class ArbolHuffman {
private:
    NodoHuffman* raiz;
    std::map<char, std::string> codigos;  // Mapeo símbolo → código binario
    
    void construirCodigos(NodoHuffman* nodo, const std::string& codigo);
    void decodificarRecursivo(NodoHuffman* nodo, const std::string& binario, 
                             int& pos, std::string& resultado);

public:
    ArbolHuffman();
    ~ArbolHuffman();
    
    void construir(const std::map<char, uint64_t>& frecuencias);
    std::string codificar(const std::string& texto);
    std::string decodificar(const std::string& binario);
    std::map<char, std::string> obtenerCodigos() const;
};
```

**Algoritmo de Construcción del Árbol**:

```cpp
void ArbolHuffman::construir(const std::map<char, uint64_t>& frecuencias) {
    // 1. Crear cola de prioridad (min-heap)
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, CompararNodos> cola;
    
    // 2. Insertar todas las hojas
    for (auto& par : frecuencias) {
        cola.push(new NodoHuffman(par.first, par.second));
    }
    
    // 3. Combinar nodos hasta tener uno solo (raíz)
    while (cola.size() > 1) {
        NodoHuffman* izq = cola.top(); cola.pop();  // Menor frecuencia
        NodoHuffman* der = cola.top(); cola.pop();  // Segunda menor
        
        // Crear nodo padre con frecuencia = suma de hijos
        NodoHuffman* padre = new NodoHuffman(
            izq->frecuencia + der->frecuencia, izq, der
        );
        cola.push(padre);
    }
    
    raiz = cola.top();
    
    // 4. Generar códigos binarios
    codigos.clear();
    construirCodigos(raiz, "");
}
```

**Construcción de Códigos**:

```cpp
void ArbolHuffman::construirCodigos(NodoHuffman* nodo, const std::string& codigo) {
    if (!nodo) return;
    
    if (nodo->esHoja()) {
        // Nodo hoja: asignar código (o "0" si es raíz única)
        codigos[nodo->simbolo] = codigo.empty() ? "0" : codigo;
    } else {
        // Nodo interno: recorrer hijos
        construirCodigos(nodo->izq, codigo + "0");  // Izquierda = '0'
        construirCodigos(nodo->der, codigo + "1");  // Derecha = '1'
    }
}
```

**Ejemplo de Codificación**:
```
Frecuencias: A=5, C=9, G=12, T=13
Árbol resultante:
         (39)
        /    \
      (18)   (21)
      / \    / \
    A(5)(13)(9)(12)
        T   C   G

Códigos generados:
A = "00"
T = "01"
C = "10"
G = "11"
```

**Codificación de Texto**:

```cpp
std::string ArbolHuffman::codificar(const std::string& texto) {
    std::string resultado;
    for (char c : texto) {
        resultado += codigos[c];  // Concatenar código de cada símbolo
    }
    return resultado;
}
```

Ejemplo: "ACGT" → "00" + "10" + "11" + "01" = "00101101"

**Decodificación**:

```cpp
std::string ArbolHuffman::decodificar(const std::string& binario) {
    std::string resultado;
    int pos = 0;
    
    while (pos < (int)binario.length()) {
        NodoHuffman* actual = raiz;
        
        // Navegar por el árbol hasta encontrar una hoja
        while (actual && !actual->esHoja() && pos < (int)binario.length()) {
            if (binario[pos] == '0') {
                actual = actual->izq;  // Ir a la izquierda
            } else {
                actual = actual->der;  // Ir a la derecha
            }
            pos++;
        }
        
        if (actual && actual->esHoja()) {
            resultado += actual->simbolo;  // Añadir símbolo decodificado
        }
    }
    
    return resultado;
}
```

Ejemplo: "00101101" → A, C, G, T → "ACGT"

---

### 🔹 Grafo.h/.cxx

```cpp
struct Nodo {
    int fila, col;  // Posición en la matriz
    char base;      // Base genética en esta posición
    Nodo(int f, int c, char b) : fila(f), col(c), base(b) {}
};

struct Arista {
    int destino;    // Índice del nodo destino
    double peso;    // Costo de la conexión
    Arista(int d, double p) : destino(d), peso(p) {}
};

class Grafo {
private:
    std::vector<Nodo> nodos;  // Lista de nodos
    std::vector<std::vector<Arista>> adyacencias;  // Lista de adyacencia
    std::map<std::pair<int,int>, int> posicionAIndice;  // Mapeo (fila,col) → índice
    
    double calcularPeso(char base1, char base2);

public:
    void construir(const Secuencia& sec);
    std::vector<Nodo> dijkstra(int origen, int destino, double& costoTotal);
    int obtenerIndice(int fila, int col) const;
    std::vector<int> encontrarBasesIguales(char base) const;
    Nodo obtenerNodo(int indice) const;
};
```

**Construcción del Grafo**:

```cpp
void Grafo::construir(const Secuencia& sec) {
    nodos.clear();
    adyacencias.clear();
    posicionAIndice.clear();
    
    int filas = sec.obtenerFilas();
    int cols = sec.obtenerColumnas();
    
    // 1. Crear nodos (uno por cada base)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (sec.posicionValida(i, j)) {
                char base = sec.obtenerBase(i, j);
                int indice = nodos.size();
                nodos.push_back(Nodo(i, j, base));
                posicionAIndice[{i, j}] = indice;
            }
        }
    }
    
    adyacencias.resize(nodos.size());
    
    // 2. Crear aristas (4 vecinos: arriba, abajo, izq, der)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for (int idx = 0; idx < (int)nodos.size(); idx++) {
        int i = nodos[idx].fila;
        int j = nodos[idx].col;
        char base1 = nodos[idx].base;
        
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            
            if (sec.posicionValida(ni, nj)) {
                auto it = posicionAIndice.find({ni, nj});
                if (it != posicionAIndice.end()) {
                    int vecino = it->second;
                    char base2 = nodos[vecino].base;
                    double peso = calcularPeso(base1, base2);
                    adyacencias[idx].push_back(Arista(vecino, peso));
                }
            }
        }
    }
}
```

**Representación Visual**:
```
Secuencia: ACGT
           TGCA
           
Matriz 2x4:
  0 1 2 3
0 A C G T
1 T G C A

Grafo resultante:
A(0,0)—C(0,1)—G(0,2)—T(0,3)
  |      |      |      |
T(1,0)—G(1,1)—C(1,2)—A(1,3)
```

**Cálculo de Pesos**:

```cpp
double Grafo::calcularPeso(char base1, char base2) {
    int ascii1 = (int)base1;
    int ascii2 = (int)base2;
    return 1.0 / (1.0 + abs(ascii1 - ascii2));
}
```

**Fórmula**: C = 1 / (1 + |ASCII₁ - ASCII₂|)

Ejemplo:
- 'G' (ASCII 71) → 'C' (ASCII 67)
- Peso = 1 / (1 + |71-67|) = 1 / 5 = 0.2

**Algoritmo de Dijkstra**:

```cpp
std::vector<Nodo> Grafo::dijkstra(int origen, int destino, double& costoTotal) {
    int n = nodos.size();
    
    // Inicialización
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> padre(n, -1);
    std::vector<bool> visitado(n, false);
    
    dist[origen] = 0;
    
    // Cola de prioridad (min-heap)
    auto cmp = [&](int a, int b) { return dist[a] > dist[b]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(origen);
    
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        
        if (visitado[u]) continue;
        visitado[u] = true;
        
        if (u == destino) break;  // Llegamos al destino
        
        // Relajación de aristas
        for (const Arista& arista : adyacencias[u]) {
            int v = arista.destino;
            double peso = arista.peso;
            
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                padre[v] = u;
                pq.push(v);
            }
        }
    }
    
    // Reconstruir camino
    std::vector<Nodo> camino;
    if (dist[destino] == std::numeric_limits<double>::infinity()) {
        costoTotal = -1;  // No hay camino
        return camino;
    }
    
    costoTotal = dist[destino];
    int actual = destino;
    while (actual != -1) {
        camino.push_back(nodos[actual]);
        actual = padre[actual];
    }
    
    std::reverse(camino.begin(), camino.end());
    return camino;
}
```

**Complejidad**: O((V + E) log V) donde V = nodos, E = aristas

---

### 🔹 Utilidades.h/.cxx

**Carga de archivos FASTA**:

```cpp
bool Utilidades::cargarFASTA(const std::string& archivo, std::vector<Secuencia>& secuencias) {
    std::ifstream file(archivo.c_str());
    if (!file.is_open()) return false;
    
    secuencias.clear();
    std::string linea, descripcion, datos;
    int anchoLinea = 0;
    bool primeraLinea = true;
    
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        
        if (linea[0] == '>') {
            // Nueva secuencia: guardar la anterior
            if (!descripcion.empty()) {
                secuencias.push_back(Secuencia(descripcion, datos, anchoLinea));
            }
            descripcion = linea.substr(1);  // Quitar el '>'
            datos = "";
            anchoLinea = 0;
            primeraLinea = true;
        } else {
            // Línea de datos
            if (primeraLinea) {
                anchoLinea = linea.length();
                primeraLinea = false;
            }
            datos += linea;
        }
    }
    
    // Guardar última secuencia
    if (!descripcion.empty()) {
        secuencias.push_back(Secuencia(descripcion, datos, anchoLinea));
    }
    
    file.close();
    return true;
}
```

**Búsqueda de subsecuencias**:

```cpp
int Utilidades::contarSubsecuencias(const std::vector<Secuencia>& secuencias, 
                                    const std::string& sub) {
    int contador = 0;
    for (const auto& sec : secuencias) {
        std::string datos = sec.obtenerDatos();
        size_t pos = 0;
        
        // Búsqueda con solapamiento
        while ((pos = datos.find(sub, pos)) != std::string::npos) {
            contador++;
            pos++;  // Permitir solapamiento
        }
    }
    return contador;
}
```

Ejemplo: "AAAA" contiene "AA" 3 veces (posiciones 0, 1, 2)

**Enmascaramiento**:

```cpp
int Utilidades::enmascararSubsecuencias(std::vector<Secuencia>& secuencias, 
                                        const std::string& sub) {
    int contador = 0;
    for (auto& sec : secuencias) {
        std::string datos = sec.obtenerDatos();
        size_t pos = 0;
        
        while ((pos = datos.find(sub, pos)) != std::string::npos) {
            // Reemplazar cada caracter con 'X'
            for (size_t i = 0; i < sub.length(); i++) {
                datos[pos + i] = 'X';
            }
            contador++;
            pos++;
        }
        sec.fijarDatos(datos);
    }
    return contador;
}
```

Ejemplo: "ACGTACGT" con sub="ACG" → "XXXTXXXT"

**Codificación Huffman a binario**:

```cpp
bool Utilidades::codificarHuffman(const std::string& archivo, 
                                  const std::vector<Secuencia>& secuencias) {
    std::ofstream out(archivo.c_str(), std::ios::binary);
    if (!out.is_open()) return false;
    
    // 1. Calcular frecuencias globales
    auto frecuencias = calcularFrecuenciasGlobales(secuencias);
    
    // 2. Escribir cabecera: cantidad de símbolos
    uint16_t n = frecuencias.size();
    out.write((char*)&n, 2);
    
    // 3. Escribir tabla de frecuencias
    for (const auto& par : frecuencias) {
        uint8_t codigo = par.first;
        uint64_t freq = par.second;
        out.write((char*)&codigo, 1);
        out.write((char*)&freq, 8);
    }
    
    // 4. Construir árbol de Huffman
    ArbolHuffman arbol;
    arbol.construir(frecuencias);
    
    // 5. Escribir número de secuencias
    uint32_t ns = secuencias.size();
    out.write((char*)&ns, 4);
    
    std::string buffer;
    
    // 6. Para cada secuencia
    for (const auto& sec : secuencias) {
        // 6a. Escribir longitud y descripción
        std::string desc = sec.obtenerDescripcion();
        uint16_t len = desc.length();
        out.write((char*)&len, 2);
        out.write(desc.c_str(), len);
        
        // 6b. Escribir metadatos
        uint64_t longitud = sec.obtenerNumBases();
        out.write((char*)&longitud, 8);
        
        uint16_t ancho = sec.obtenerAnchoLinea();
        out.write((char*)&ancho, 2);
        
        // 6c. Codificar y escribir datos
        std::string codificado = arbol.codificar(sec.obtenerDatos());
        escribirBits(out, codificado, buffer);
    }
    
    // 7. Completar último byte con ceros
    finalizarBuffer(out, buffer);
    out.close();
    return true;
}
```

**Formato del archivo .fabin**:
```
[2 bytes] n           : Número de símbolos distintos
[1+8 bytes] × n       : Código + Frecuencia de cada símbolo
[4 bytes] ns          : Número de secuencias
Para cada secuencia:
  [2 bytes] len       : Longitud del nombre
  [len bytes] nombre  : Nombre de la secuencia
  [8 bytes] longitud  : Longitud de los datos
  [2 bytes] ancho     : Ancho de línea
  [variable] datos    : Datos codificados en bits
```

---

### 🔹 main.cpp

**Estructura del ciclo principal**:

```cpp
int main() {
    string linea;
    
    cout << "Sistema de Manipulación de Genomas" << endl;
    cout << "Escriba 'ayuda' para ver los comandos disponibles" << endl;
    
    while (true) {
        cout << "$ ";
        getline(cin, linea);
        
        if (linea.empty()) continue;
        procesarComando(linea);
    }
    
    return 0;
}
```

**Parser de comandos**:

```cpp
void procesarComando(const string& linea) {
    istringstream iss(linea);
    string comando;
    iss >> comando;  // Extraer primer palabra
    
    if (comando == "salir") {
        exit(0);
    }
    else if (comando == "cargar") {
        string archivo;
        if (iss >> archivo) {
            cmdCargar(archivo);
        } else {
            cout << "Error: debe especificar un nombre de archivo" << endl;
        }
    }
    // ... más comandos
}
```

**Implementación de comando `listar_secuencias`**:

```cpp
void cmdListarSecuencias() {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    cout << "Hay " << secuenciasEnMemoria.size() 
         << " secuencias cargadas en memoria:" << endl;
         
    for (const auto& sec : secuenciasEnMemoria) {
        cout << "Secuencia " << sec.obtenerDescripcion();
        
        if (sec.esCompleta()) {
            cout << " contiene " << sec.obtenerNumBases() << " bases." << endl;
        } else {
            // Contar bases sin '-'
            int bases = 0;
            for (char c : sec.obtenerDatos()) {
                if (c != '-') bases++;
            }
            cout << " contiene al menos " << bases << " bases." << endl;
        }
    }
}
```

**Implementación de comando `histograma`**:

```cpp
void cmdHistograma(const string& descripcion) {
    bool encontrada = false;
    
    for (const auto& sec : secuenciasEnMemoria) {
        if (sec.obtenerDescripcion() == descripcion) {
            encontrada = true;
            auto histograma = sec.calcularHistograma();
            
            // Orden específico según Tabla 1 del enunciado
            const char orden[] = "ACGTURYKMSWBDHVNX-";
            for (char c : orden) {
                if (histograma.count(c) > 0) {
                    cout << c << " : " << histograma[c] << endl;
                }
            }
            break;
        }
    }
    
    if (!encontrada) {
        cout << "Secuencia inválida." << endl;
    }
}
```

**Implementación de comando `ruta_mas_corta`**:

```cpp
void cmdRutaMasCorta(const string& descripcion, int i, int j, int x, int y) {
    // 1. Buscar secuencia
    Secuencia* secPtr = nullptr;
    for (auto& sec : secuenciasEnMemoria) {
        if (sec.obtenerDescripcion() == descripcion) {
            secPtr = &sec;
            break;
        }
    }
    
    if (!secPtr) {
        cout << "La secuencia " << descripcion << " no existe." << endl;
        return;
    }
    
    // 2. Validar posiciones
    if (!secPtr->posicionValida(i, j)) {
        cout << "La base en la posición [" << i << "," << j << "] no existe." << endl;
        return;
    }
    
    if (!secPtr->posicionValida(x, y)) {
        cout << "La base en la posición [" << x << "," << y << "] no existe." << endl;
        return;
    }
    
    // 3. Construir grafo si no existe
    if (grafos.find(descripcion) == grafos.end()) {
        grafos[descripcion].construir(*secPtr);
    }
    
    // 4. Ejecutar Dijkstra
    Grafo& grafo = grafos[descripcion];
    int origen = grafo.obtenerIndice(i, j);
    int destino = grafo.obtenerIndice(x, y);
    
    double costo;
    vector<Nodo> camino = grafo.dijkstra(origen, destino, costo);
    
    // 5. Mostrar resultados
    char baseOrigen = secPtr->obtenerBase(i, j);
    char baseDestino = secPtr->obtenerBase(x, y);
    
    cout << "Para la secuencia " << descripcion << ", la ruta más corta entre "
         << "la base " << baseOrigen << " en [" << i << "," << j << "] y "
         << "la base " << baseDestino << " en [" << x << "," << y << "] es: ";
    
    for (size_t k = 0; k < camino.size(); k++) {
        cout << camino[k].base;
        if (k < camino.size() - 1) cout << " -> ";
    }
    
    cout << ". El costo total de la ruta es: " << fixed << setprecision(4) 
         << costo << endl;
}
```

**Implementación de comando `base_remota`**:

```cpp
void cmdBaseRemota(const string& descripcion, int i, int j) {
    // Similar a ruta_mas_corta pero busca la base más lejana
    
    Grafo& grafo = grafos[descripcion];
    int origen = grafo.obtenerIndice(i, j);
    char baseOrigen = secPtr->obtenerBase(i, j);
    
    // 1. Encontrar todas las bases iguales
    vector<int> basesIguales = grafo.encontrarBasesIguales(baseOrigen);
    
    // 2. Buscar la más lejana
    double maxCosto = -1;
    int mejorDestino = -1;
    vector<Nodo> mejorCamino;
    
    for (int destino : basesIguales) {
        if (destino == origen) continue;  // Excluir origen
        
        double costo;
        vector<Nodo> camino = grafo.dijkstra(origen, destino, costo);
        
        if (costo > maxCosto) {  // Buscar máximo
            maxCosto = costo;
            mejorDestino = destino;
            mejorCamino = camino;
        }
    }
    
    // 3. Mostrar resultado
    Nodo nodoRemoto = grafo.obtenerNodo(mejorDestino);
    cout << "Para la secuencia " << descripcion 
         << ", la base remota está ubicada en ["
         << nodoRemoto.fila << "," << nodoRemoto.col << "]..." << endl;
}
```

---

## 🔨 Guía de Compilación

### **Método 1: Usando Makefile** (Recomendado)

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

**Comandos**:
```bash
make           # Compilar
make run       # Compilar y ejecutar
make clean     # Limpiar archivos objeto
```

### **Método 2: Compilación directa**

```bash
# Linux/Mac
g++ -std=c++11 -Wall -g -o genomas main.cpp Secuencia.cxx ArbolHuffman.cxx Grafo.cxx Utilidades.cxx
./genomas

# Windows (MinGW)
g++ -std=c++11 -Wall -g -o genomas.exe main.cpp Secuencia.cxx ArbolHuffman.cxx Grafo.cxx Utilidades.cxx
genomas.exe
```

### **Método 3: Compilación por pasos**

```bash
# Compilar cada archivo
g++ -std=c++11 -c main.cpp
g++ -std=c++11 -c Secuencia.cxx
g++ -std=c++11 -c ArbolHuffman.cxx
g++ -std=c++11 -c Grafo.cxx
g++ -std=c++11 -c Utilidades.cxx

# Enlazar
g++ -o genomas main.o Secuencia.o ArbolHuffman.o Grafo.o Utilidades.o
```

### **Flags de compilación explicados**:
- `-std=c++11`: Usar estándar C++11 (requerido)
- `-Wall`: Mostrar todas las advertencias
- `-g`: Incluir información de depuración
- `-o`: Especificar nombre del ejecutable
- `-c`: Compilar sin enlazar

---

## 📖 Manual de Uso

### **Iniciando el sistema**

```bash
$ ./genomas
Sistema de Manipulación de Genomas
Estructuras de Datos - Proyecto 2025-30
Escriba 'ayuda' para ver los comandos disponibles

$ 
```

### **Comandos disponibles**

#### **1. Sistema de ayuda**

```bash
$ ayuda
# Muestra todos los comandos disponibles

$ ayuda cargar
# Muestra ayuda específica del comando cargar
```

#### **2. Componente 1 - Estructuras Lineales**

##### **cargar <archivo>**
Carga secuencias desde un archivo FASTA.

```bash
$ cargar test.fa
2 secuencias cargadas correctamente desde test.fa.
```

**Casos de salida**:
- Archivo vacío: `"test.fa no contiene ninguna secuencia."`
- Archivo no existe: `"test.fa no se encuentra o no puede leerse."`
- Una secuencia: `"1 secuencia cargada correctamente desde test.fa."`
- Varias: `"2 secuencias cargadas correctamente desde test.fa."`

##### **listar_secuencias**
Lista todas las secuencias en memoria.

```bash
$ listar_secuencias
Hay 2 secuencias cargadas en memoria:
Secuencia Full_SEQUENCE contiene 180 bases.
Secuencia Incomplete_sequence contiene al menos 350 bases.
```

##### **histograma <descripcion>**
Muestra frecuencia de cada base.

```bash
$ histograma Full_SEQUENCE
A : 35
C : 45
G : 40
T : 60
```

##### **es_subsecuencia <subsecuencia>**
Busca y cuenta ocurrencias.

```bash
$ es_subsecuencia ACGT
La subsecuencia dada se repite 5 veces dentro de las secuencias cargadas en memoria.
```

##### **enmascarar <subsecuencia>**
Reemplaza con 'X'.

```bash
$ enmascarar ACGT
5 subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.
```

##### **guardar <archivo>**
Exporta a FASTA.

```bash
$ guardar salida.fa
Las secuencias han sido guardadas en salida.fa.
```

#### **3. Componente 2 - Huffman**

##### **codificar <archivo.fabin>**
Comprime con Huffman.

```bash
$ codificar compressed.fabin
Secuencias codificadas y almacenadas en compressed.fabin.
```

##### **decodificar <archivo.fabin>**
Descomprime.

```bash
$ decodificar compressed.fabin
Secuencias decodificadas desde compressed.fabin y cargadas en memoria.
```

#### **4. Componente 3 - Grafos**

##### **ruta_mas_corta <desc> <i> <j> <x> <y>**
Encuentra camino óptimo.

```bash
$ ruta_mas_corta Full_SEQUENCE 0 0 3 44
Para la secuencia Full_SEQUENCE, la ruta más corta entre la base C en [0,0] 
y la base C en [3,44] es: C -> T -> C -> G -> ... -> A -> C. 
El costo total de la ruta es: 15.2345
```

##### **base_remota <desc> <i> <j>**
Encuentra base más lejana del mismo tipo.

```bash
$ base_remota Full_SEQUENCE 0 0
Para la secuencia Full_SEQUENCE, la base remota está ubicada en [3,28], 
y la ruta entre la base en [0,0] y la base remota en [3,28] es: 
C -> T -> ... -> G -> C. El costo total de la ruta es: 18.5432
```

#### **5. General**

##### **salir**
Termina el programa.

```bash
$ salir
```

---

## 💡 Ejemplos de Uso

### **Ejemplo 1: Flujo completo básico**

```bash
$ cargar genoma.fa
3 secuencias cargadas correctamente desde genoma.fa.

$ listar_secuencias
Hay 3 secuencias cargadas en memoria:
Secuencia seq1 contiene 200 bases.
Secuencia seq2 contiene 150 bases.
Secuencia seq3 contiene al menos 180 bases.

$ histograma seq1
A : 50
C : 60
G : 45
T : 45

$ es_subsecuencia ATG
La subsecuencia dada se repite 8 veces dentro de las secuencias cargadas en memoria.

$ enmascarar ATG
8 subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.

$ guardar modificado.fa
Las secuencias han sido guardadas en modificado.fa.
```

### **Ejemplo 2: Compresión y descompresión**

```bash
$ cargar original.fa
1 secuencia cargada correctamente desde original.fa.

$ codificar compressed.fabin
Secuencias codificadas y almacenadas en compressed.fabin.

# Verificar tamaño de archivo
# original.fa: 10 KB
# compressed.fabin: 3 KB (70% de compresión)

$ decodificar compressed.fabin
Secuencias decodificadas desde compressed.fabin y cargadas en memoria.

$ guardar recuperado.fa
Las secuencias han sido guardadas en recuperado.fa.

# recuperado.fa debe ser idéntico a original.fa
```

### **Ejemplo 3: Análisis de grafos**

```bash
$ cargar secuencia_matriz.fa
1 secuencia cargada correctamente desde secuencia_matriz.fa.

$ ruta_mas_corta matriz_seq 0 0 5 10
Para la secuencia matriz_seq, la ruta más corta entre la base A en [0,0] 
y la base G en [5,10] es: A -> C -> C -> G -> T -> ... -> G. 
El costo total de la ruta es: 12.3456

$ base_remota matriz_seq 0 0
Para la secuencia matriz_seq, la base remota está ubicada en [8,15], 
y la ruta entre la base en [0,0] y la base remota en [8,15] es: 
A -> C -> ... -> T -> A. El costo total de la ruta es: 25.6789
```

---

## 🧪 Plan de Pruebas

### **Pruebas del Componente 1**

#### **Test 1: Cargar archivo válido**
```
Entrada: cargar test.fa (con 2 secuencias)
Salida esperada: "2 secuencias cargadas correctamente desde test.fa."
```

#### **Test 2: Cargar archivo inexistente**
```
Entrada: cargar noexiste.fa
Salida esperada: "noexiste.fa no se encuentra o no puede leerse."
```

#### **Test 3: Cargar archivo vacío**
```
Entrada: cargar vacio.fa (sin secuencias)
Salida esperada: "vacio.fa no contiene ninguna secuencia."
```

#### **Test 4: Listar sin cargar**
```
Entrada: listar_secuencias (sin cargar antes)
Salida esperada: "No hay secuencias cargadas en memoria."
```

#### **Test 5: Histograma válido**
```
Entrada: 
  cargar test.fa
  histograma Full_SEQUENCE
Salida esperada: 
  A : 35
  C : 45
  G : 40
  T : 60
```

#### **Test 6: Histograma inválido**
```
Entrada: histograma NoExiste
Salida esperada: "Secuencia inválida."
```

#### **Test 7: Subsecuencia encontrada**
```
Entrada: 
  cargar test.fa
  es_subsecuencia ACGT
Salida esperada: "La subsecuencia dada se repite X veces..."
```

#### **Test 8: Subsecuencia no encontrada**
```
Entrada: es_subsecuencia ZZZZ
Salida esperada: "La subsecuencia dada no existe..."
```

#### **Test 9: Enmascarar exitoso**
```
Entrada:
  cargar test.fa
  enmascarar ACGT
  guardar enmascarado.fa
  
Verificación:
  - Contar 'X' en enmascarado.fa
  - Debe haber 4*N 'X' donde N es el número de ocurrencias
```

#### **Test 10: Guardar sin cargar**
```
Entrada: guardar salida.fa (sin cargar antes)
Salida esperada: "No hay secuencias cargadas en memoria."
```

### **Pruebas del Componente 2**

#### **Test 11: Codificar exitoso**
```
Entrada:
  cargar test.fa
  codificar test.fabin
Salida esperada: "Secuencias codificadas y almacenadas en test.fabin."
Verificación: test.fabin debe existir y ser menor que test.fa
```

#### **Test 12: Codificar sin cargar**
```
Entrada: codificar test.fabin (sin cargar)
Salida esperada: "No hay secuencias cargadas en memoria."
```

#### **Test 13: Decodificar válido**
```
Entrada:
  decodificar test.fabin
  listar_secuencias
Salida esperada: Debe mostrar las mismas secuencias originales
```

#### **Test 14: Integridad de codificación/decodificación**
```
Proceso:
  1. cargar original.fa
  2. codificar temp.fabin
  3. decodificar temp.fabin
  4. guardar recuperado.fa
  5. Comparar original.fa con recuperado.fa
  
Resultado esperado: Archivos idénticos
```

#### **Test 15: Codificación con caracteres especiales**
```
Entrada: Secuencia con códigos N, X, -, R, Y, etc.
Verificación: Todos los caracteres deben preservarse
```

### **Pruebas del Componente 3**

#### **Test 16: Ruta válida**
```
Entrada: ruta_mas_corta Full_SEQUENCE 0 0 1 0
Salida esperada: Camino válido con costo > 0
```

#### **Test 17: Posición origen inválida**
```
Entrada: ruta_mas_corta Full_SEQUENCE 100 100 0 0
Salida esperada: "La base en la posición [100,100] no existe."
```

#### **Test 18: Posición destino inválida**
```
Entrada: ruta_mas_corta Full_SEQUENCE 0 0 200 200
Salida esperada: "La base en la posición [200,200] no existe."
```

#### **Test 19: Base remota encontrada**
```
Entrada: base_remota Full_SEQUENCE 0 0
Salida esperada: Coordenadas válidas y camino con costo > 0
```

#### **Test 20: Secuencia no existe (grafos)**
```
Entrada: ruta_mas_corta NoExiste 0 0 1 1
Salida esperada: "La secuencia NoExiste no existe."
```

### **Casos de borde**

#### **Test 21: Secuencia de un solo caracter**
```
Archivo: >single\nA
Comandos: cargar, listar, histograma
Verificación: Debe manejar correctamente
```

#### **Test 22: Secuencia muy larga**
```
Archivo: >large\n(10,000+ bases)
Comandos: cargar, codificar, decodificar
Verificación: Sin errores de memoria
```

#### **Test 23: Múltiples enmascaramientos**
```
Proceso:
  1. enmascarar ACGT
  2. enmascarar TGCA
  3. Verificar que ambas fueron enmascaradas
```

#### **Test 24: Ruta a sí mismo**
```
Entrada: ruta_mas_corta seq 0 0 0 0
Salida esperada: Camino de un solo nodo, costo = 0
```

#### **Test 25: Base remota sin otras instancias**
```
Entrada: Base única (no hay otras iguales)
Salida esperada: Manejo apropiado (mensaje o costo 0)
```

---

## 🐛 Solución de Problemas Comunes

### **Error de compilación**

#### **Problema**: `error: 'nullptr' was not declared`
**Solución**: Usar `-std=c++11` o superior

#### **Problema**: `undefined reference to 'Secuencia::obtenerDatos()'`
**Solución**: Verificar que todos los .cxx estén incluidos en la compilación

### **Errores de ejecución**

#### **Problema**: Segmentation fault al cargar archivo
**Solución**: 
- Verificar que el archivo existe
- Verificar permisos de lectura
- Verificar formato FASTA (debe empezar con '>')

#### **Problema**: El histograma no muestra todos los caracteres
**Solución**: Verificar el orden de impresión (debe seguir: ACGTURYKMSWBDHVNX-)

#### **Problema**: Ruta más corta retorna costo negativo
**Solución**: Verificar que las posiciones sean válidas y que exista camino

### **Problemas de formato**

#### **Problema**: Archivo .fabin no se puede leer
**Solución**: No abrir con editores de texto, usar solo los comandos del sistema

#### **Problema**: Guardar no preserva el formato
**Solución**: Verificar que `anchoLinea` se mantenga correctamente

---

## 📦 Entregables del Proyecto

Según el enunciado, debes entregar:

### **Entrega 0 (Semana 3) - 10%**
- ✅ Interfaz de usuario funcional
- ✅ Validación de comandos
- ✅ Sistema de ayuda

### **Entrega 1 (Semana 6) - 30%**
- ✅ Componente 1 completo
- 📄 Documento de diseño (40%)
- 📄 Plan de pruebas para `enmascarar` (20%)
- 💻 Código fuente (30%)
- 🗣️ Sustentación (10%)

### **Entrega 2 (Semana 12) - 30%**
- ✅ Componentes 1 y 2 completos
- 📄 Acta de correcciones de Entrega 1 (10%)
- 📄 Documento de diseño (30%)
- 📄 Plan de pruebas para `decodificar` (20%)
- 💻 Código fuente (30%)
- 🗣️ Sustentación (10%)

### **Entrega 3 (Semana 18) - 30%**
- ✅ Componentes 1, 2 y 3 completos
- 📄 Acta de correcciones anteriores (10%)
- 📄 Documento de diseño (30%)
- 📄 Plan de pruebas para `base_remota` (20%)
- 💻 Código fuente (30%)
- 🗣️ Sustentación (10%)

### **Formato de entrega**
```
proyecto.zip
├── main.cpp
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
├── documento_diseno.pdf
└── plan_pruebas.pdf
```

**Importante**: 
- Solo archivos .h, .hxx, .cxx, .cpp, .pdf
- Sin estructura de carpetas interna
- Formato .zip únicamente

---

## 📊 Complejidades Algorítmicas

### **Componente 1**

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| `cargar` | O(n) | n = tamaño del archivo |
| `listar_secuencias` | O(m) | m = número de secuencias |
| `histograma` | O(n) | n = longitud de la secuencia |
| `es_subsecuencia` | O(n*m) | n = total bases, m = longitud subsecuencia |
| `enmascarar` | O(n*m) | Similar a búsqueda |
| `guardar` | O(n) | n = total de bases |

### **Componente 2**

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| Construcción árbol | O(n log n) | n = símbolos distintos |
| Codificación | O(m) | m = longitud del texto |
| Decodificación | O(m * h) | m = bits, h = altura del árbol |

### **Componente 3**

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| Construcción grafo | O(V) | V = número de bases |
| Dijkstra | O((V+E) log V) | Implementación con heap |
| `base_remota` | O(k * (V+E) log V) | k = bases iguales |

---

## 🎓 Conceptos Clave Aplicados

### **1. Programación Orientada a Objetos**
- Encapsulamiento (clases con private/public)
- Abstracción (TADs como Punto, Secuencia)
- Composición (Grafo contiene Nodos)

### **2. Estructuras de Datos**
- Lineales: vector, string
- No lineales: árbol binario, grafo
- Asociativas: map

### **3. Algoritmos**
- Búsqueda de patrones (KMP implícito en find())
- Compresión (Huffman)
- Caminos más cortos (Dijkstra)

### **4. Manejo de Archivos**
- Lectura/escritura de texto (FASTA)
- Lectura/escritura binaria (.fabin)
- Manipulación de bits

### **5. Complejidad Computacional**
- Análisis de tiempo y espacio
- Optimización mediante estructuras adecuadas
- Trade-offs (memoria vs. velocidad)

---

## 📚 Referencias

- **Huffman Coding**: http://en.wikipedia.org/wiki/Huffman_coding
- **FASTA Format**: https://blast.ncbi.nlm.nih.gov/doc/blast-topics/
- **Dijkstra's Algorithm**: Cormen, T. H. et al. "Introduction to Algorithms"
- **C++ Reference**: https://en.cppreference.com/

---

## ✨ Características Destacadas del Código

### **1. Robustez**
- Validación exhaustiva de entradas
- Manejo de errores en todas las operaciones
- Mensajes informativos al usuario

### **2. Eficiencia**
- Uso de estructuras de datos apropiadas
- Algoritmos óptimos (Dijkstra con heap)
- Minimización de copias innecesarias

### **3. Mantenibilidad**
- Código modular y bien organizado
- Separación clara de responsabilidades
- Nombres descriptivos de variables y funciones

### **4. Escalabilidad**
- Capacidad para manejar archivos grandes
- Estructuras que crecen dinámicamente
- Algoritmos con buena complejidad asintótica

---

## 🎯 Conclusiones

Este proyecto implementa un **sistema completo y funcional** para la manipulación de genomas que:

✅ Cumple con **todos los requisitos** del enunciado  
✅ Implementa **estructuras de datos** correctamente  
✅ Aplica **algoritmos clásicos** (Huffman, Dijkstra)  
✅ Maneja **archivos de texto y binarios**  
✅ Proporciona una **interfaz de usuario** intuitiva  
✅ Está **bien documentado** y **listo para compilar**  

El código está preparado para las **3 entregas** del proyecto y puede ser extendido fácilmente con nuevas funcionalidades.

---

## 👨‍💻 Autor y Licencia

**Proyecto**: Sistema de Manipulación de Genomas  
**Curso**: Estructuras de Datos 2025-30  
**Universidad**: Pontificia Universidad Javeriana  
**Departamento**: Ingeniería de Sistemas  

Este código es material educativo y debe ser usado siguiendo las políticas académicas de la universidad sobre integridad académica y uso de herramientas de IA generativa.