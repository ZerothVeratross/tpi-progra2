#include "mozo.h"

Fecha::Fecha() {
    //la fecha en que salio Dark Souls
    dia=22;
    mes=9;
    anio=2011;
}

Fecha::Fecha(int n_dia, int n_mes, int n_anio) {
    dia=n_dia;
    mes=n_mes;
    anio=n_anio;
}

Fecha::Fecha(Fecha &n_fecha) {
    dia=n_fecha.get_dia();
    mes=n_fecha.get_mes();
    anio=n_fecha.get_anio();
}

Fecha::~Fecha() {
}

int Fecha::get_dia() {
    return dia;
}

int Fecha::get_mes() {
    return mes;
}

int Fecha::get_anio() {
    return anio;
}

void Fecha::set_dia(int n_dia) {
    dia=n_dia;
}

void Fecha::set_mes(int n_mes) {
    mes=n_mes;
}

void Fecha::set_anio(int n_anio) {
    anio=n_anio;
}

std::string Fecha::get_str() {
    std::string buffer;
    buffer.append(std::to_string(dia));
    buffer.append("/");
    buffer.append(std::to_string(mes));
    buffer.append("/");
    buffer.append(std::to_string(anio));
    return buffer;
}

void Fecha::copiar(Fecha * fecha) {
    fecha->set_dia(dia);
    fecha->set_mes(mes);
    fecha->set_anio(anio);
}

int Fecha::comparar(Fecha fecha) {
    int comp;
    if (anio>fecha.get_anio()) {
        comp=1;
    } else if (anio==fecha.get_anio()) {
        if (mes>fecha.get_mes()) {
            comp=1;
        } else if (mes==fecha.get_mes()) {
            if (dia>fecha.get_dia()) {
                comp=1;
            } else if (dia==fecha.get_dia()) {
                comp=0;
            } else {
                comp=-1;
            }
        } else {
            comp=-1;
        }
    } else {
        comp=-1;
    }
    return comp;
}
