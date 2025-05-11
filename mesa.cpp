#include "mesa.h"

Mesa::Mesa(int n_nro_mesa) {
    nro_mesa=n_nro_mesa;
    can_sillas=4;
    ubic=1;
    desc=new std::string("");
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char * n_desc) {
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;
    desc=new std::string(n_desc);
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc) {
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;
    desc=new std::string(n_desc);
}

Mesa::~Mesa() {
    delete desc;
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
    return std::string(*desc);
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
    desc->clear();
    desc->append(n_desc);
}

void Mesa::set_desc(std::string n_desc) {
    desc->clear();
    desc->append(n_desc);
}
