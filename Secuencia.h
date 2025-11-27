// ============================================
// ARCHIVO: Secuencia.h
// ============================================
#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <vector>
#include <map>

class Secuencia {
private:
    std::string descripcion;
    std::string datos;
    int anchoLinea;

public:
    Secuencia();
    Secuencia(const std::string& desc, const std::string& datos, int ancho);
    
    std::string obtenerDescripcion() const;
    std::string obtenerDatos() const;
    int obtenerAnchoLinea() const;
    int obtenerNumBases() const;
    bool esCompleta() const;
    
    void fijarDatos(const std::string& nuevosDatos);
    std::map<char, int> calcularHistograma() const;
    
    // Para representación matricial
    int obtenerFilas() const;
    int obtenerColumnas() const;
    char obtenerBase(int fila, int col) const;
    bool posicionValida(int fila, int col) const;
};

#endif