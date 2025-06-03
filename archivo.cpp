#include "archivo.h"

Archivo::Archivo() {
    direccion=std::string("");
    tam_reg=0;
}

void Archivo::set_direccion(std::string n_direccion) {
    direccion.erase(0, direccion.npos);
    direccion.append(n_direccion);
}

void Archivo::set_tam_reg(int n_tam_reg) {
    tam_reg=n_tam_reg;
}

std::string Archivo::get_direccion() {
    return direccion;
}

int Archivo::get_tam_reg() {
    return tam_reg;
}

int Archivo::contar_regs() {
    FILE * pArchivo=fopen(direccion.c_str(), "rb");
    if (pArchivo==NULL) {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    return ftell(pArchivo) / tam_reg;
}
