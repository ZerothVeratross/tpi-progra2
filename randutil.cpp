#include "randutil.h"

//hay que establecer la semilla de srand antes de llamar esta funcion
char gen_char(int mayus) {
    char c;
    if (mayus) { //26 posibilidades en ascii estandar
        c=rand()%26;
    } else { //53 posibilidades contando el espacio en ascii estandar
        c=rand()%53;
    }

    if (c<26) {
        //el codigo ascii de las letras mayusculas va desde 65=65+0 para 'A'
        //hasta 90=65+25 para 'Z'
        c+=65;
    } else if (c==52) {
        //ultimo valor posible se reserva para ' ' con codigo ascii 32
        c=32;
    } else {
        //el codigo ascii de las letras minusculas va desde 97=65+6+26 para 'a'
        //hasta 122=65+6+51 para 'z'; suma 6 entre 91 y 96 inclusive
        c+=65+6;
    }
    return c;
}

//hay que establecer la semilla de srand antes de llamar esta funcion
int gen_big_int(int digits) {
    int i, num=0;
    for (i=0; i<digits; i++) {
        num+=(rand()%10)*potencia(10, i);
    }
    return num;
}

int potencia(int base, int exponente) {
    int i, pot=1;
    for (i=0; i<exponente; i++) {
        pot*=base;
    }
    return pot;
}

void gen_fecha_entre_anios(Fecha * fecha, int anio1, int anio2) {
    int buffer;
    buffer=rand()%(anio2-anio1+1)+anio1;
    fecha->set_anio(buffer);
    fecha->set_mes(rand()%12+1);
    switch (fecha->get_mes()) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        fecha->set_dia(rand()%31+1);
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        fecha->set_dia(rand()%30+1);
        break;
    case 2:
        if (buffer%4==0 && (buffer%100!=0 || buffer%400==0)) {
            fecha->set_dia(rand()%29+1);
        } else {
            fecha->set_dia(rand()%28+1);
        }
        break;
    }
}
