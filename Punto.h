// ============================================
// ARCHIVO: Punto.h
// ============================================
#ifndef PUNTO_H
#define PUNTO_H

#include <cmath>

class Punto {
private:
    double x, y, z;

public:
    Punto();
    Punto(double x, double y, double z);
    double obtenerX() const;
    double obtenerY() const;
    double obtenerZ() const;
    void fijarX(double x);
    void fijarY(double y);
    void fijarZ(double z);
    double distanciaEuclidiana(const Punto& otro) const;
    double distanciaManhattan(const Punto& otro) const;
};

inline Punto::Punto() : x(0), y(0), z(0) {}
inline Punto::Punto(double x, double y, double z) : x(x), y(y), z(z) {}
inline double Punto::obtenerX() const { return x; }
inline double Punto::obtenerY() const { return y; }
inline double Punto::obtenerZ() const { return z; }
inline void Punto::fijarX(double x) { this->x = x; }
inline void Punto::fijarY(double y) { this->y = y; }
inline void Punto::fijarZ(double z) { this->z = z; }
inline double Punto::distanciaEuclidiana(const Punto& otro) const {
    double dx = x - otro.x, dy = y - otro.y, dz = z - otro.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
inline double Punto::distanciaManhattan(const Punto& otro) const {
    return fabs(x - otro.x) + fabs(y - otro.y) + fabs(z - otro.z);
}

#endif















