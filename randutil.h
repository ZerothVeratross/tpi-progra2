#ifndef RANDUTIL_H
#define RANDUTIL_H

#include "fecha.h"
#include <cstdlib>  //libreria usada para generar numeros aleatorios: https://cplusplus.com/reference/cstdlib/
#include <ctime>    //libreria utilizada para obtener la hora actual: https://cplusplus.com/reference/ctime/

char gen_char(int mayus);
int gen_big_int(int digits);
int potencia(int base, int exponente);
void gen_fecha_entre_anios(Fecha * fecha, int anio1, int anio2);
#endif // RANDUTIL_H
