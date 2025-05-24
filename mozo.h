#ifndef MOZO_H
#define MOZO_H

#include "fecha.h"

class Mozo {
private:
    //turno 1: mañana, 2: tarde, 3: noche
    int dni, turno, id_mozo;
    Fecha fecha_naci;
    char nombre[20], apellido[30], nro_telef[20], email[50];
    bool estado;
public:
    Mozo();
    Mozo(int n_dni, char n_nombre[20], char n_apellido[30], char n_nro_telef[20], char n_email[50], Fecha n_fecha_naci, int n_turno, int n_id_mozo);
    Mozo(int n_dni, std::string n_nombre, std::string n_apellido, std::string n_nro_telef, std::string n_email, Fecha n_fecha_naci, int n_turno, int n_id_mozo);
    ~Mozo();
    int get_dni();
    std::string get_nombre();
    std::string get_apellido();
    std::string get_nro_telef();
    std::string get_email();
    Fecha get_fecha_naci();
    int get_turno();
    int get_id_mozo();
    bool get_estado();
    void set_nombre(char n_nombre[20]);
    void set_nombre(std::string n_nombre);
    void set_apellido(char n_apellido[30]);
    void set_apellido(std::string n_apellido);
    void set_nro_telef(char n_nro_telef[20]);
    void set_nro_telef(std::string n_nro_telef);
    void set_email(char n_email[50]);
    void set_email(std::string n_email);
    void set_fecha_naci(Fecha n_fecha_naci);
    void set_turno(int n_turno);
    void set_id_mozo(int n_id_mozo);
    void set_estado(bool n_estado);
};
#endif // MOZO_H
