#include "archivoMesa.h"

ArchivoMesa::ArchivoMesa() : Archivo() {
    set_direccion("mesas.dat");
    set_tam_reg(sizeof(Mesa));
}

int ArchivoMesa::registrar_mesa(Mesa * mesa) {
    FILE *pMesas;
    int i;

    pMesas=fopen(get_direccion().c_str(), "ab");
    if (pMesas==NULL) {
        return 0;
    }

    i=fwrite(mesa, get_tam_reg(), 1, pMesas);
    fclose(pMesas);
    return i;
}

int ArchivoMesa::consultar_mesas(Mesa * buffer, int cant_regs, int tipo_dato, int cota_inf, int cota_sup, int ubic) {
    FILE *pMesas=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMesas==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMesas);
        switch(tipo_dato) {
        case 1:
            buffer[i].set_estado(buffer[i].get_nro_mesa()>=cota_inf && buffer[i].get_nro_mesa()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 2:
            buffer[i].set_estado(buffer[i].get_can_sillas()>=cota_inf && buffer[i].get_can_sillas()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 3:
            buffer[i].set_estado(buffer[i].get_can_sillas()>=cota_inf && buffer[i].get_can_sillas()<=cota_sup &&
                                 buffer[i].get_ubic()==ubic && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

int ArchivoMesa::listar_mesas(Mesa * buffer, int cant_regs) {
    int i;
    FILE * pMesas=fopen(get_direccion().c_str(), "rb");
    if (pMesas==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMesas);
    }

    return 1;
}

int ArchivoMesa::guardar_mesas(Mesa * buffer, int cant_regs) {
    FILE *pMesas;
    int i;

    pMesas=fopen(get_direccion().c_str(), "wb");
    if (pMesas==NULL) {
        return 0;
    }

    i=fwrite(buffer, get_tam_reg(), cant_regs, pMesas);
    fclose(pMesas);
    return i;
}

int ArchivoMesa::generar_mesas(int cantidad) {
    int i, desc_len, can_sillas, ubic, nro_mesa;
    std::string desc;
    FILE * pMesas=fopen(get_direccion().c_str(), "wb");
    Mesa mesa;
    if (pMesas==NULL) {
        return 0;
    }

    srand(time(NULL));  //utiliza la hora como semilla para el generador de numeros aleatorios
    for (nro_mesa=1; nro_mesa<=cantidad; nro_mesa++) {
        can_sillas=rand()%8+1;
        ubic=rand()%2+1;

        desc_len=rand()%30+1;
        desc.erase(0, desc.npos);
        for (i=0; i<desc_len; i++) {
            desc.append(1, gen_char(!i));   //!i para que el primer char sea mayuscula
        }

        mesa=Mesa(nro_mesa, can_sillas, ubic, desc);

        if (rand()%4==3) {
            mesa.set_estado(false);
        }
        fwrite(&mesa, get_tam_reg(), 1, pMesas);
    }
    fclose(pMesas);
    return 1;
}
