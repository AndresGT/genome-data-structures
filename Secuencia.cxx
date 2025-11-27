// ============================================
// ARCHIVO: Secuencia.cxx
// ============================================
#include "Secuencia.h"

Secuencia::Secuencia() : anchoLinea(0) {}

Secuencia::Secuencia(const std::string& desc, const std::string& datos, int ancho)
    : descripcion(desc), datos(datos), anchoLinea(ancho) {}

std::string Secuencia::obtenerDescripcion() const { return descripcion; }
std::string Secuencia::obtenerDatos() const { return datos; }
int Secuencia::obtenerAnchoLinea() const { return anchoLinea; }
int Secuencia::obtenerNumBases() const { return datos.length(); }

bool Secuencia::esCompleta() const {
    return datos.find('-') == std::string::npos;
}

void Secuencia::fijarDatos(const std::string& nuevosDatos) {
    datos = nuevosDatos;
}

std::map<char, int> Secuencia::calcularHistograma() const {
    std::map<char, int> histograma;
    for (char c : datos) {
        histograma[c]++;
    }
    return histograma;
}

int Secuencia::obtenerFilas() const {
    if (anchoLinea == 0) return 0;
    return (datos.length() + anchoLinea - 1) / anchoLinea;
}

int Secuencia::obtenerColumnas() const {
    return anchoLinea;
}

char Secuencia::obtenerBase(int fila, int col) const {
    int pos = fila * anchoLinea + col;
    if (pos >= 0 && pos < (int)datos.length()) {
        return datos[pos];
    }
    return '\0';
}

bool Secuencia::posicionValida(int fila, int col) const {
    if (fila < 0 || col < 0 || col >= anchoLinea) return false;
    int pos = fila * anchoLinea + col;
    return pos >= 0 && pos < (int)datos.length();
}