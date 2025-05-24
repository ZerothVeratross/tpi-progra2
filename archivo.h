#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>

class Archivo {
private:
    std::string direccion;
    int tam_reg;
public:
    Archivo();
    void set_direccion(std::string n_direccion);
    void set_tam_reg(int n_tam_reg);
    std::string get_direccion();
    int get_tam_reg();
    int contar_regs();
};
#endif // ARCHIVO_H
