#ifndef ARCHIVO_MESA_H
#define ARCHIVO_MESA_H

#include "archivo.h"
#include "randutil.h"
#include "mesa.h"

class ArchivoMesa: public Archivo {
private:
public:
    ArchivoMesa();
    int registrar_mesa(Mesa * mesa);
    int consultar_mesas(Mesa * buffer, int cant_regs, int tipo_dato, int cota_inf, int cota_sup, int ubic=3);
    int listar_mesas(Mesa * buffer, int cant_regs);
    int generar_mesas(int cantidad);
};
#endif // ARCHIVO_MESA_H
