#include "config.h"

Configuracion::Configuracion() {
    int i;
    contrasenia[0]='1';
    contrasenia[1]='2';
    contrasenia[2]='3';
    for (i=3; i<20; i++) {
        contrasenia[i]='\0';
    }
    modo=2;
}

Configuracion::Configuracion(char n_contrasenia[20], int n_modo) {
    int i;
    for (i=0; i<20; i++) {
        contrasenia[i]=n_contrasenia[i];
    }

    if (n_modo<1 || n_modo>2) {
        modo=0;
    } else {
        modo=n_modo;
    }
}

bool Configuracion::comparar_contrasenia(char intento[20]) {
    bool aceptar=true;
    int i;
    for (i=0; i<20 && aceptar; i++) {
        aceptar=intento[i]==contrasenia[i];
    }
    return aceptar;
}

int Configuracion::cambiar_contrasenia(char intento[20], char contrasenia_nueva[20]) {
    int i;
    if (comparar_contrasenia(intento)) {
        for (i=0; i<20; i++) {
            contrasenia[i]=contrasenia_nueva[i];
        }
        return 1;
    }
    return 0;
}

int Configuracion::get_modo() {
    return modo;
}

void Configuracion::set_modo(char intento[20], int n_modo) {
    if (comparar_contrasenia(intento) && n_modo>=1 && n_modo<=2) {
        modo=n_modo;
    }
}
