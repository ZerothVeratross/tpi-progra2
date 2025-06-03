#include "archivoMozo.h"

ArchivoMozo::ArchivoMozo() : Archivo() {
    set_direccion("mozos.dat");
    set_tam_reg(sizeof(Mozo));
}

int ArchivoMozo::registrar_mozo(Mozo * mozo) {
    FILE *pMozos;
    int i;

    pMozos=fopen(get_direccion().c_str(), "ab");
    if (pMozos==NULL) {
        return 0;
    }

    i=fwrite(mozo, get_tam_reg(), 1, pMozos);
    fclose(pMozos);
    return i;
}

int ArchivoMozo::consultar_mozos(Mozo * buffer, int cant_regs, int tipo_dato, int cota_inf, int cota_sup) {
    FILE *pMozos=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
        switch(tipo_dato) {
        case 1:
            buffer[i].set_estado(buffer[i].get_id_mozo()>=cota_inf && buffer[i].get_id_mozo()<=cota_sup
                                 && buffer[i].get_estado());
            break;
        case 2:
            buffer[i].set_estado(buffer[i].get_turno()==cota_inf && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

//esto requeriria usar expresiones regulares para buscar nombres parecidos, lo cual me excede por ahora
int ArchivoMozo::consultar_mozos(Mozo * buffer, int cant_regs, int tipo_datos, std::string nombre_o_apellido, std::string apellido) {
    FILE *pMozos=fopen(get_direccion().c_str(), "rb");
    int i;

    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
        switch(tipo_datos) {
        case 1:
            //std::cout<<nombre_o_apellido<<" - "<<nombre_o_apellido.length()<<" | "<<buffer[i].get_nombre()<<" - "<<buffer[i].get_nombre().length()<<"\n";
            buffer[i].set_estado(buffer[i].get_nombre().compare(nombre_o_apellido)==0 && buffer[i].get_estado());
            break;
        case 2:
            buffer[i].set_estado(buffer[i].get_apellido().compare(nombre_o_apellido)==0 && buffer[i].get_estado());
            break;
        case 3:
            buffer[i].set_estado(buffer[i].get_nombre().compare(nombre_o_apellido)==0 && buffer[i].get_apellido().compare(apellido)==0
                                 && buffer[i].get_estado());
            break;
        default:
            return 0;
        }
    }
    return 1;
}

int ArchivoMozo::listar_mozos(Mozo * buffer, int cant_regs) {
    int i;
    FILE * pMozos=fopen(get_direccion().c_str(), "rb");
    if (pMozos==NULL) {
        return 0;
    }

    for (i=0; i<cant_regs; i++) {
        fread(&buffer[i], get_tam_reg(), 1, pMozos);
    }

    return 1;
}

int ArchivoMozo::guardar_mozos(Mozo * buffer, int cant_regs) {
    FILE *pMozos;
    int i;

    pMozos=fopen(get_direccion().c_str(), "wb");
    if (pMozos==NULL) {
        return 0;
    }

    i=fwrite(buffer, get_tam_reg(), cant_regs, pMozos);
    fclose(pMozos);
    return i;
}

int ArchivoMozo::generar_mozos(int cantidad) {
    int i, str_len, dni, turno, id_mozo;
    std::string nombre, apellido, nro_telef, email;
    FILE * pMozos=fopen(get_direccion().c_str(), "wb");
    Mozo mozo;
    Fecha fecha_naci;
    if (pMozos==NULL) {
        return 0;
    }

    srand(time(NULL));  //utiliza la hora como semilla para el generador de numeros aleatorios
    for (id_mozo=1; id_mozo<=cantidad; id_mozo++) {
        dni=gen_big_int(8);
        turno=rand()%3+1;

        str_len=rand()%20+1;
        nombre.erase(0, nombre.npos);
        for (i=0; i<str_len; i++) {
            nombre.append(1, gen_char(!i));   //!i para que el primer char sea mayuscula
        }

        str_len=rand()%30+1;
        apellido.erase(0, apellido.npos);
        for (i=0; i<str_len; i++) {
            apellido.append(1, gen_char(!i));   //!i para que el primer char sea mayuscula
        }

        nro_telef.erase(0, nro_telef.npos);
        nro_telef.append("11-");
        nro_telef.append(std::to_string(gen_big_int(4)));
        nro_telef.append("-");
        nro_telef.append(std::to_string(gen_big_int(4)));

        str_len=rand()%30+1;
        email.erase(0, email.npos);
        for (i=0; i<str_len; i++) {
            email.append(1, gen_char(0));   //siempre minuscula en un email
        }
        switch((int)rand()%3+1) {
        case 1:
            email.append("@gmail.com");
            break;
        case 2:
            email.append("@outlook.com");
            break;
        case 3:
            email.append("@hotmail.com");
            break;
        default:
            break;
        }

        gen_fecha_entre_anios(&fecha_naci, 1967, 2006);

        mozo=Mozo(dni, nombre, apellido, nro_telef, email, fecha_naci, turno, id_mozo);

        if (rand()%4==3) {
            mozo.set_estado(false);
        }
        fwrite(&mozo, sizeof(Mozo), 1, pMozos);
    }
    fclose(pMozos);
    return 1;
}
