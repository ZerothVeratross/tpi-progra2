#include "mesa.h"

Mesa::Mesa(int n_nro_mesa) {
    int i;
    nro_mesa=n_nro_mesa;
    can_sillas=4;
    ubic=1;
    desc=new char[20];
    for (i=0; i<20; i++) {
        desc[i]='\0';
    }
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char * n_desc) {
    char c=n_desc[0];
    int i, tam_desc=0;
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;

    //corta ciclo en null terminator
    while (c) {
        tam_desc++;
        c=n_desc[tam_desc];
    }

    desc=new char[tam_desc+1];
    for (i=0; i<tam_desc; i++) {
        desc[i]=n_desc[i];
    }
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc) {
    int tam_desc=n_desc.length()+1;
    nro_mesa=n_nro_mesa;
    can_sillas=n_can_sillas;
    ubic=n_ubic;

    desc=new char[tam_desc];
    n_desc.copy(desc, tam_desc-1, 0);
    desc[tam_desc-1]='\0';
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
    std::cout<<"\n"<<desc<<"\n";
    std::string str(desc);
    return str;
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
    int i, tam_desc=0;
    char c=n_desc[0];

    //el caracter terminador en C es '\0', cuyo codigo numerico es 0
    while (c) {
        tam_desc++;
        c=n_desc[tam_desc];
    }
    tam_desc++; //un lugar mas para el terminador

    delete desc;
    desc=new char[tam_desc];
    for (i=0; i<tam_desc; i++) {
        desc[i]=n_desc[i];
    }
}

void Mesa::set_desc(std::string n_desc) {
    int tam_desc=n_desc.length()+1;

    delete desc;
    desc=new char[tam_desc];
    n_desc.copy(desc, tam_desc-1, 0);
    desc[tam_desc-1]='\0';
}
