#include "config.h"
#include "archivo.h"

class ArchivoConfiguracion: public Archivo {
private:
public:
    ArchivoConfiguracion();
    int inicializar();
    int leer_config(Configuracion * config);
    int guardar_config(Configuracion * config);
};
