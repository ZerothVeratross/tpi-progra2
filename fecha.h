#ifndef FECHA_H
#define FECHA_H

#include <iostream>

class Fecha {
private:
    int dia, mes, anio;
public:
    Fecha();
    Fecha(int n_dia, int n_mes, int n_anio);
    Fecha(Fecha &n_fecha);
    ~Fecha();
    int get_dia();
    int get_mes();
    int get_anio();
    void set_dia(int n_dia);
    void set_mes(int n_mes);
    void set_anio(int n_anio);
    std::string get_str();
    void copiar(Fecha * fecha);
    int comparar(Fecha fecha);
};
#endif // FECHA_H
