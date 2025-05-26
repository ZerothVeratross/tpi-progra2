#ifndef ARCHIVO_MOZO_H
#define ARCHIVO_MOZO_H

#include "archivo.h"
#include "randutil.h"
#include "mozo.h"

class ArchivoMozo: public Archivo {
private:
public:
    ArchivoMozo();
    int registrar_mozo(Mozo * mozo);
    int consultar_mozos(Mozo * buffer, int cant_regs, int tipo_dato, int cota_inf, int cota_sup);
    int consultar_mozos(Mozo * buffer, int cant_regs, int tipo_dato, std::string nombre_o_apellido, std::string apellido=std::string());
    int listar_mozos(Mozo * buffer, int cant_regs);
    int generar_mozos(int cantidad);
};
#endif // ARCHIVO_MOZO_H
