#ifndef MESA_H
#define MESA_H

#include <iostream>

class Mesa {
private:
    //ubicacion 1: interior, 2: terraza
    int nro_mesa, can_sillas, ubic;
    char desc[30];
    bool estado;
public:
    Mesa();
    Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char n_desc[30]);
    Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc);
    ~Mesa();
    int get_nro_mesa();
    int get_can_sillas();
    int get_ubic();
    std::string get_desc();
    bool get_estado();
    void set_nro_mesa(int n_nro_mesa);
    void set_can_sillas(int n_can_sillas);
    void set_ubic(int n_ubic);
    void set_desc(char n_desc[30]);
    void set_desc(std::string n_desc);
    void set_estado(bool n_estado);
};
#endif // MESA_H
