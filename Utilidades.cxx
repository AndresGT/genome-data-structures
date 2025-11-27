
// ============================================
// ARCHIVO: Utilidades.cxx
// ============================================
#include "Utilidades.h"
#include "ArbolHuffman.h"
#include <sstream>
#include <algorithm>

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
            if (!descripcion.empty()) {
                secuencias.push_back(Secuencia(descripcion, datos, anchoLinea));
            }
            descripcion = linea.substr(1);
            datos = "";
            anchoLinea = 0;
            primeraLinea = true;
        } else {
            if (primeraLinea) {
                anchoLinea = linea.length();
                primeraLinea = false;
            }
            datos += linea;
        }
    }
    
    if (!descripcion.empty()) {
        secuencias.push_back(Secuencia(descripcion, datos, anchoLinea));
    }
    
    file.close();
    return true;
}

bool Utilidades::guardarFASTA(const std::string& archivo, const std::vector<Secuencia>& secuencias) {
    std::ofstream file(archivo.c_str());
    if (!file.is_open()) return false;
    
    for (const auto& sec : secuencias) {
        file << ">" << sec.obtenerDescripcion() << "\n";
        std::string datos = sec.obtenerDatos();
        int ancho = sec.obtenerAnchoLinea();
        
        for (int i = 0; i < (int)datos.length(); i += ancho) {
            int len = std::min(ancho, (int)datos.length() - i);
            file << datos.substr(i, len) << "\n";
        }
    }
    
    file.close();
    return true;
}

int Utilidades::contarSubsecuencias(const std::vector<Secuencia>& secuencias, const std::string& sub) {
    int contador = 0;
    for (const auto& sec : secuencias) {
        std::string datos = sec.obtenerDatos();
        size_t pos = 0;
        while ((pos = datos.find(sub, pos)) != std::string::npos) {
            contador++;
            pos++;
        }
    }
    return contador;
}

int Utilidades::enmascararSubsecuencias(std::vector<Secuencia>& secuencias, const std::string& sub) {
    int contador = 0;
    for (auto& sec : secuencias) {
        std::string datos = sec.obtenerDatos();
        size_t pos = 0;
        while ((pos = datos.find(sub, pos)) != std::string::npos) {
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

std::map<char, uint64_t> Utilidades::calcularFrecuenciasGlobales(const std::vector<Secuencia>& secuencias) {
    std::map<char, uint64_t> frecuencias;
    for (const auto& sec : secuencias) {
        std::string datos = sec.obtenerDatos();
        for (char c : datos) {
            frecuencias[c]++;
        }
    }
    return frecuencias;
}

void Utilidades::escribirBits(std::ofstream& out, const std::string& bits, std::string& buffer) {
    buffer += bits;
    while (buffer.length() >= 8) {
        unsigned char byte = 0;
        for (int i = 0; i < 8; i++) {
            if (buffer[i] == '1') {
                byte |= (1 << (7 - i));
            }
        }
        out.write((char*)&byte, 1);
        buffer = buffer.substr(8);
    }
}

void Utilidades::finalizarBuffer(std::ofstream& out, std::string& buffer) {
    if (!buffer.empty()) {
        while (buffer.length() < 8) {
            buffer += '0';
        }
        unsigned char byte = 0;
        for (int i = 0; i < 8; i++) {
            if (buffer[i] == '1') {
                byte |= (1 << (7 - i));
            }
        }
        out.write((char*)&byte, 1);
    }
}

bool Utilidades::codificarHuffman(const std::string& archivo, const std::vector<Secuencia>& secuencias) {
    std::ofstream out(archivo.c_str(), std::ios::binary);
    if (!out.is_open()) return false;
    
    auto frecuencias = calcularFrecuenciasGlobales(secuencias);
    
    uint16_t n = frecuencias.size();
    out.write((char*)&n, 2);
    
    for (const auto& par : frecuencias) {
        uint8_t codigo = par.first;
        uint64_t freq = par.second;
        out.write((char*)&codigo, 1);
        out.write((char*)&freq, 8);
    }
    
    ArbolHuffman arbol;
    arbol.construir(frecuencias);
    
    uint32_t ns = secuencias.size();
    out.write((char*)&ns, 4);
    
    std::string buffer;
    
    for (const auto& sec : secuencias) {
        std::string desc = sec.obtenerDescripcion();
        uint16_t len = desc.length();
        out.write((char*)&len, 2);
        out.write(desc.c_str(), len);
        
        uint64_t longitud = sec.obtenerNumBases();
        out.write((char*)&longitud, 8);
        
        uint16_t ancho = sec.obtenerAnchoLinea();
        out.write((char*)&ancho, 2);
        
        std::string codificado = arbol.codificar(sec.obtenerDatos());
        escribirBits(out, codificado, buffer);
    }
    
    finalizarBuffer(out, buffer);
    out.close();
    return true;
}

std::string Utilidades::leerBits(std::ifstream& in, int numBits) {
    std::string resultado;
    static unsigned char byteActual = 0;
    static int bitsRestantes = 0;
    
    while (numBits > 0) {
        if (bitsRestantes == 0) {
            if (!in.read((char*)&byteActual, 1)) {
                break;
            }
            bitsRestantes = 8;
        }
        
        int bit = (byteActual >> (bitsRestantes - 1)) & 1;
        resultado += (bit ? '1' : '0');
        bitsRestantes--;
        numBits--;
    }
    
    return resultado;
}

bool Utilidades::decodificarHuffman(const std::string& archivo, std::vector<Secuencia>& secuencias) {
    std::ifstream in(archivo.c_str(), std::ios::binary);
    if (!in.is_open()) return false;
    
    uint16_t n;
    in.read((char*)&n, 2);
    
    std::map<char, uint64_t> frecuencias;
    for (int i = 0; i < n; i++) {
        uint8_t codigo;
        uint64_t freq;
        in.read((char*)&codigo, 1);
        in.read((char*)&freq, 8);
        frecuencias[(char)codigo] = freq;
    }
    
    ArbolHuffman arbol;
    arbol.construir(frecuencias);
    
    uint32_t ns;
    in.read((char*)&ns, 4);
    
    secuencias.clear();
    
    for (uint32_t i = 0; i < ns; i++) {
        uint16_t len;
        in.read((char*)&len, 2);
        
        char* desc = new char[len + 1];
        in.read(desc, len);
        desc[len] = '\0';
        std::string descripcion(desc);
        delete[] desc;
        
        uint64_t longitud;
        in.read((char*)&longitud, 8);
        
        uint16_t ancho;
        in.read((char*)&ancho, 2);
        
        std::string binario;
        while (binario.length() < longitud * 10) {
            unsigned char byte;
            if (!in.read((char*)&byte, 1)) break;
            for (int b = 7; b >= 0; b--) {
                binario += ((byte >> b) & 1) ? '1' : '0';
            }
        }
        
        std::string datos = arbol.decodificar(binario);
        datos = datos.substr(0, longitud);
        
        secuencias.push_back(Secuencia(descripcion, datos, ancho));
    }
    
    in.close();
    return true;
}
