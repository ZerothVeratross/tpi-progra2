#ifndef ARCHIVO_SERVICIO_H
#define ARCHIVO_SERVICIO_H

#include "archivo.h"
#include "archivoMesa.h"
#include "archivoMozo.h"
#include "randutil.h"
#include "servicio.h"

class ArchivoServicio: public Archivo {
private:
public:
    ArchivoServicio();
    int registrar_servicio(Servicio * servicio);
    int listar_servicios(Servicio * buffer, int cant_regs);
    int generar_servicios(int cantidad);
};
#endif // ARCHIVO_SERVICIO_H
