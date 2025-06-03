#include "archivoServicio.h"

ArchivoServicio::ArchivoServicio() : Archivo() {
    set_direccion("servicios.dat");
    set_tam_reg(sizeof(Servicio));
}

int ArchivoServicio::registrar_servicio(Servicio * servicio) {
    FILE *pServicios;
    int i;

    pServicios=fopen(get_direccion().c_str(), "ab");
    if (pServicios==NULL) {
        return 0;
    }

    i=fwrite(servicio, get_tam_reg(), 1, pServicios);
    fclose(pServicios);
    return i;
}

int ArchivoServicio::consultar_servicios(Servicio * buffer, int cant_regs, int tipo_dato, int cota_inf, int cota_sup) {
    FILE *pMozos=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
        switch(tipo_dato) {
        case 1: //consulta por numero de factura
            buffer[i].set_estado(buffer[i].get_nro_factura()>=cota_inf && buffer[i].get_nro_factura()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 2: //consulta por numero de mesa
            buffer[i].set_estado(buffer[i].get_nro_mesa()>=cota_inf && buffer[i].get_nro_mesa()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 3: //consulta por id de mozo
            buffer[i].set_estado(buffer[i].get_id_mozo()>=cota_inf && buffer[i].get_id_mozo()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

int ArchivoServicio::consultar_servicios(Servicio * buffer, int cant_regs, int tipo_dato, float cota_inf, float cota_sup) {
    FILE *pMozos=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
        switch(tipo_dato) {
        case 5: //consulta por importe de servicio
            buffer[i].set_estado(buffer[i].get_importe_serv()>=cota_inf && buffer[i].get_importe_serv()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 6: //consulta por monto abonado
            buffer[i].set_estado(buffer[i].get_monto_abon()>=cota_inf && buffer[i].get_monto_abon()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

int ArchivoServicio::consultar_servicios(Servicio * buffer, int cant_regs, int tipo_dato, Fecha cota_inf, Fecha cota_sup) {
    FILE *pMozos=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
        switch(tipo_dato) {
        case 4: //consulta por fecha de servicio
            buffer[i].set_estado(buffer[i].get_fecha_serv().comparar(cota_inf)>=0 && buffer[i].get_fecha_serv().comparar(cota_sup)<=0
                                 && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

int ArchivoServicio::listar_servicios(Servicio * buffer, int cant_regs) {
    int i;
    FILE * pServicios=fopen(get_direccion().c_str(), "rb");
    if (pServicios==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pServicios);
    }

    return 1;
}

int ArchivoServicio::guardar_servicios(Servicio * buffer, int cant_regs) {
    FILE *pServicios;
    int i;

    pServicios=fopen(get_direccion().c_str(), "wb");
    if (pServicios==NULL) {
        return 0;
    }

    i=fwrite(buffer, get_tam_reg(), cant_regs, pServicios);
    fclose(pServicios);
    return i;
}

//requiere que los archivos de Mesas y Mozos ya existan
int ArchivoServicio::generar_servicios(int cantidad) {
    int i, nro_mesa, id_mozo, nro_factura;
    float importe_serv, monto_abon;
    Fecha fecha_serv;
    FILE * pArchivo;
    ArchivoMesa archivo_mesa;
    ArchivoMozo archivo_mozo;
    Mesa mesa;
    Mozo mozo;
    Servicio servicio;

    int mesas=archivo_mesa.contar_regs();
    int mozos=archivo_mozo.contar_regs();
    int nros_mesas[mesas];
    int ids_mozos[mozos];

    pArchivo=fopen(archivo_mesa.get_direccion().c_str(), "rb");
    if (pArchivo==NULL) {
        return 0;
    }
    for (i=0; i<mesas; i++) {
        fread(&mesa, archivo_mesa.get_tam_reg(), 1, pArchivo);
        nros_mesas[i]=mesa.get_nro_mesa();
    }

    pArchivo=fopen(archivo_mozo.get_direccion().c_str(), "rb");
    if (pArchivo==NULL) {
        return 0;
    }
    for (i=0; i<mozos; i++) {
        fread(&mozo, archivo_mozo.get_tam_reg(), 1, pArchivo);
        ids_mozos[i]=mozo.get_id_mozo();
    }

    pArchivo=fopen(get_direccion().c_str(), "wb");
    if (pArchivo==NULL) {
        return 0;
    }
    srand(time(NULL));  //utiliza la hora como semilla para el generador de numeros aleatorios
    for (nro_factura=1; nro_factura<=cantidad; nro_factura++) {
        nro_mesa=nros_mesas[rand()%mesas];
        id_mozo=ids_mozos[rand()%mozos];

        importe_serv=gen_big_int(6);
        monto_abon=importe_serv+gen_big_int(5);
        gen_fecha_entre_anios(&fecha_serv, 2015, 2025);

        servicio=Servicio(nro_factura, nro_mesa, id_mozo, fecha_serv, importe_serv, monto_abon);

        if (rand()%4==3) {
            servicio.set_estado(false);
        }
        fwrite(&servicio, get_tam_reg(), 1, pArchivo);
    }
    fclose(pArchivo);
    return 1;
}
