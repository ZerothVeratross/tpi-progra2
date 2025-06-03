#include "mozo.h"

Mozo::Mozo() {
    int i;
    dni=1;

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
    turno=1;
    id_mozo=1;
    estado=true;
}

//los constructores no puede hacer un return, ni siquiera de void. dado que no
//tengo acceso a excepciones, inicializo el objeto con valores predeterminados validos
//si los parametros no son validos
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

    if (n_turno<1 || n_turno>3) {
        n_turno=1;
    } else {
        turno=n_turno;
    }

    if (id_mozo<1) {
        id_mozo=1;
    } else {
        id_mozo=n_id_mozo;
    }
    estado=true;
}

Mozo::Mozo(int n_dni, std::string n_nombre, std::string n_apellido, std::string n_nro_telef, std::string n_email, Fecha n_fecha_naci, int n_turno, int n_id_mozo) {
    int i;
    dni=n_dni;

    if (n_nombre.length()>19) {
        for (i=0; i<20; i++) {
            nombre[i]='\0';
        }
    } else {
        n_nombre.copy(nombre, 20, 0);
        //asegurar que las posiciones que sobren no tengan basura
        for (i=n_nombre.length(); i<20; i++) {
            nombre[i]='\0';
        }
    }

    if (n_apellido.length()>29) {
        for (i=0; i<29; i++) {
            apellido[i]='\0';
        }
    } else {
        n_apellido.copy(apellido, 30, 0);
        for (i=n_apellido.length(); i<30; i++) {
            apellido[i]='\0';
        }
    }

    if (n_nro_telef.length()>19) {
        for (i=0; i<19; i++) {
            nro_telef[i]='\0';
        }
    } else {
        n_nro_telef.copy(nro_telef, 20, 0);
        for (i=n_nro_telef.length(); i<20; i++) {
            nro_telef[i]='\0';
        }
    }

    if (n_email.length()>49) {
        for (i=0; i<49; i++) {
            email[i]='\0';
        }
    } else {
        n_email.copy(email, 50, 0);
        for (i=n_email.length(); i<50; i++) {
            email[i]='\0';
        }
    }


    fecha_naci=Fecha(n_fecha_naci);

    if (n_turno<1 || n_turno>3) {
        n_turno=1;
    } else {
        turno=n_turno;
    }

    if (id_mozo<1) {
        id_mozo=1;
    } else {
        id_mozo=n_id_mozo;
    }
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
    if (n_nombre.length()>19) {return;}
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
    if (n_apellido.length()>29) {return;}
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
    if (n_nro_telef.length()>19) {return;}
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
    if (n_email.length()>19) {return;}
    n_email.copy(email, 50, 0);
    for (i=n_email.length(); i<50; i++) {
        email[i]='\0';
    }
}

void Mozo::set_fecha_naci(Fecha n_fecha_naci) {
    n_fecha_naci.copiar(&fecha_naci);
}

void Mozo::set_turno(int n_turno) {
    if (turno<1 || turno>3) {return;}
    turno=n_turno;
}

void Mozo::set_id_mozo(int n_id_mozo) {
    if (id_mozo<1) {return;}
    id_mozo=n_id_mozo;
}

void Mozo::set_estado(bool n_estado) {
    estado=n_estado;
}
