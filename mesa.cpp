#include "mesa.h"

Mesa::Mesa() {
    int i;
    nro_mesa=0;
    can_sillas=4;
    ubic=1;
    for (i=0; i<30; i++) {
        desc[i]='\0';
    }
    estado=true;
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char n_desc[20]) {
    int i;
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;

    for (i=0; i<30; i++) {
        desc[i]=n_desc[i];
    }
    estado=true;
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc) {
    int i;
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;

    n_desc.copy(desc, 30, 0);
    //asegurar que las posiciones que sobren no tengan basura
    for (i=n_desc.length(); i<30; i++) {
        desc[i]='\0';
    }
    estado=true;
}

Mesa::~Mesa() {
}

int Mesa::get_nro_mesa() {
    return nro_mesa;
}

int Mesa::get_can_sillas() {
    return can_sillas;
}

int Mesa::get_ubic() {
    return ubic;
}

std::string Mesa::get_desc() {
    std::string str(desc);
    return str;
}

bool Mesa::get_estado() {
    return estado;
}

void Mesa::set_nro_mesa(int n_nro_mesa) {
    nro_mesa=n_nro_mesa;
}

void Mesa::set_can_sillas(int n_can_sillas) {
    can_sillas=n_can_sillas;
}

void Mesa::set_ubic(int n_ubic) {
    ubic=n_ubic;
}

void Mesa::set_desc(char * n_desc) {
    int i;

    for (i=0; i<30; i++) {
        desc[i]=n_desc[i];
    }
}

void Mesa::set_desc(std::string n_desc) {
    int i;
    n_desc.copy(desc, 30, 0);
    for (i=n_desc.length(); i<30; i++) {
        desc[i]='\0';
    }
}

void Mesa::set_estado(bool n_estado) {
    estado=n_estado;
}
