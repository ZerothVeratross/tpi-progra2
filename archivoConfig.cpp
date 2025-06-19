#include "archivoConfig.h"

ArchivoConfiguracion::ArchivoConfiguracion() : Archivo() {
    set_direccion("config.dat");
    set_tam_reg(sizeof(Configuracion));
}

int ArchivoConfiguracion::comprobar_config() {
    FILE * pConfig;
    Configuracion dummy;
    char condummy[20] = {'1', '2', '3', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    if (contar_regs()==-1) {
        pConfig=fopen(get_direccion().c_str(), "wb");
        fwrite(&dummy, get_tam_reg(), 1, pConfig);
        fclose(pConfig);
        return 0;
    } else {
        leer_config(&dummy);
        if (dummy.comparar_contrasenia(condummy)) {
            return 1;
        }
    }
    return 2;
}

int ArchivoConfiguracion::leer_config(Configuracion * config) {
    FILE * pConfig=fopen(get_direccion().c_str(), "rb");
    if (pConfig==NULL) {
        return 0;
    }

    fread(config, get_tam_reg(), 1, pConfig);
    fclose(pConfig);
    return 1;
}

int ArchivoConfiguracion::guardar_config(Configuracion * config) {
    FILE * pConfig=fopen(get_direccion().c_str(), "wb");
    if (pConfig==NULL) {
        return 0;
    }

    fwrite(config, get_tam_reg(), 1, pConfig);
    fclose(pConfig);
    return 1;
}
