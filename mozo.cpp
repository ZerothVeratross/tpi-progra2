#include "mozo.h"

Mozo::Mozo() {
    int i;
    dni=0;

    for (i=0; i<20; i++) {
        nombre[i]='\0';
    }
    for (i=0; i<30; i++) {
        apellido[i]='\0';
    }
    for (i=0; i<50; i++) {
        nro_telef[i]='\0';
    }
    for (i=0; i<50; i++) {
        email[i]='\0';
    }

    fecha_naci=Fecha();
    turno=0;
    id_mozo=0;
    estado=true;
}

Mozo::Mozo(int n_dni, char n_nombre[20], char n_apellido[30], char n_nro_telef[20], char n_email[50], Fecha n_fecha_naci, int n_turno, int n_id_mozo) {
    int i;
    dni=n_dni;

    for (i=0; i<20; i++) {
        nombre[i]=n_nombre[i];
    }
    for (i=0; i<30; i++) {
        apellido[i]=n_apellido[i];
    }
    for (i=0; i<20; i++) {
        nro_telef[i]=n_nro_telef[i];
    }
    for (i=0; i<50; i++) {
        email[i]=n_email[i];
    }

    fecha_naci=Fecha(n_fecha_naci);
    turno=n_turno;
    id_mozo=n_id_mozo;
    estado=true;
}

Mozo::Mozo(int n_dni, std::string n_nombre, std::string n_apellido, std::string n_nro_telef, std::string n_email, Fecha n_fecha_naci, int n_turno, int n_id_mozo) {
    int i;
    dni=n_dni;

    n_nombre.copy(nombre, 20, 0);
    n_apellido.copy(apellido, 30, 0);
    n_nro_telef.copy(nro_telef, 20, 0);
    n_email.copy(email, 50, 0);

    //asegurar que las posiciones que sobren no tengan basura
    for (i=n_nombre.length(); i<20; i++) {
        nombre[i]='\0';
    }
    for (i=n_apellido.length(); i<30; i++) {
        apellido[i]='\0';
    }
    for (i=n_nro_telef.length(); i<20; i++) {
        nro_telef[i]='\0';
    }
    for (i=n_email.length(); i<50; i++) {
        email[i]='\0';
    }

    fecha_naci=Fecha(n_fecha_naci);
    turno=n_turno;
    id_mozo=n_id_mozo;
    estado=true;
}

Mozo::~Mozo() {
}

int Mozo::get_dni() {
    return dni;
}

std::string Mozo::get_nombre() {
    std::string str(nombre);
    return str;
}

std::string Mozo::get_apellido() {
    std::string str(apellido);
    return str;
}

std::string Mozo::get_nro_telef() {
    std::string str(nro_telef);
    return str;
}

std::string Mozo::get_email() {
    std::string str(email);
    return str;
}

Fecha Mozo::get_fecha_naci() {
    return fecha_naci;
}

int Mozo::get_turno() {
    return turno;
}

int Mozo::get_id_mozo() {
    return id_mozo;
}

bool Mozo::get_estado() {
    return estado;
}

void Mozo::set_nombre(char n_nombre[20]) {
    int i;
    for (i=0; i<20; i++) {
        nombre[i]=n_nombre[i];
    }
}

void Mozo::set_nombre(std::string n_nombre) {
    int i;
    n_nombre.copy(nombre, 20, 0);
    for (i=n_nombre.length(); i<20; i++) {
        nombre[i]='\0';
    }
}

void Mozo::set_apellido(char n_apellido[30]) {
    int i;
    for (i=0; i<30; i++) {
        apellido[i]=n_apellido[i];
    }
}

void Mozo::set_apellido(std::string n_apellido) {
    int i;
    n_apellido.copy(apellido, 30, 0);
    for (i=n_apellido.length(); i<30; i++) {
        apellido[i]='\0';
    }
}

void Mozo::set_nro_telef(char n_nro_telef[20]) {
    int i;
    for (i=0; i<20; i++) {
        nro_telef[i]=n_nro_telef[i];
    }
}

void Mozo::set_nro_telef(std::string n_nro_telef) {
    int i;
    n_nro_telef.copy(nro_telef, 20, 0);
    for (i=n_nro_telef.length(); i<20; i++) {
        nro_telef[i]='\0';
    }
}


void Mozo::set_email(char n_email[50]) {
    int i;
    for (i=0; i<50; i++) {
        email[i]=n_email[i];
    }
}

void Mozo::set_email(std::string n_email) {
    int i;
    n_email.copy(email, 50, 0);
    for (i=n_email.length(); i<50; i++) {
        email[i]='\0';
    }
}

void Mozo::set_fecha_naci(Fecha n_fecha_naci) {
    n_fecha_naci.copiar(&fecha_naci);
}

void Mozo::set_turno(int n_turno) {
    turno=n_turno;
}

void Mozo::set_id_mozo(int n_id_mozo) {
    id_mozo=n_id_mozo;
}

void Mozo::set_estado(bool n_estado) {
    estado=n_estado;
}
