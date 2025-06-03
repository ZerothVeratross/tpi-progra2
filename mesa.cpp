#include "mesa.h"

Mesa::Mesa() {
    int i;
    nro_mesa=1;
    can_sillas=4;
    ubic=1;
    for (i=0; i<30; i++) {
        desc[i]='\0';
    }
    estado=true;
}

//los constructores no pueden hacer un return, ni siquiera de void. dado que no
//tengo acceso a excepciones, inicializo el objeto con valores predeterminados validos
//si los parametros no son validos
Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char n_desc[30]) {
    int i;
    if (n_nro_mesa<1) {
        nro_mesa=1;
    } else {
        nro_mesa=n_nro_mesa;
    }

    if (n_can_sillas<1 || n_can_sillas>12) {
        can_sillas=4;
    } else {
        can_sillas=n_can_sillas;
    }

    if (n_ubic<1 || n_ubic>2) {
        ubic=1;
    } else {
        ubic=n_ubic;
    }

    for (i=0; i<30; i++) {
        desc[i]=n_desc[i];
    }
    estado=true;
}

Mesa::Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc) {
    int i;
    if (n_nro_mesa<1) {
        nro_mesa=1;
    } else {
        nro_mesa=n_nro_mesa;
    }

    if (n_can_sillas<1 || n_can_sillas>12) {
        can_sillas=4;
    } else {
        can_sillas=n_can_sillas;
    }

    if (n_ubic<1 || n_ubic>2) {
        ubic=1;
    } else {
        ubic=n_ubic;
    }

    if (n_desc.length()>29) {
        for (i=0; i<30; i++) {
            desc[i]='\0';
        }
    } else {
        n_desc.copy(desc, 30, 0);
        //asegurar que las posiciones que sobren no tengan basura
        for (i=n_desc.length(); i<30; i++) {
            desc[i]='\0';
        }
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
    if (n_nro_mesa<1) {return;}
    nro_mesa=n_nro_mesa;
}

void Mesa::set_can_sillas(int n_can_sillas) {
    if (n_can_sillas<1 || n_can_sillas>12) {return;}
    can_sillas=n_can_sillas;
}

void Mesa::set_ubic(int n_ubic) {
    if (n_ubic<1 || n_ubic>2) {return;}
    ubic=n_ubic;
}

void Mesa::set_desc(char n_desc[30]) {
    int i;
    for (i=0; i<30; i++) {
        desc[i]=n_desc[i];
    }
}

void Mesa::set_desc(std::string n_desc) {
    int i;
    if (n_desc.length()>29) {return;}
    n_desc.copy(desc, 30, 0);
    for (i=n_desc.length(); i<30; i++) {
        desc[i]='\0';
    }
}

void Mesa::set_estado(bool n_estado) {
    estado=n_estado;
}
