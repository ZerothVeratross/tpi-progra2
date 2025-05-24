#include "arrutil.h"

void ordenar_mesas_por_nro(Mesa * mesas, int tam) {
    int i, j, posmin;
    Mesa temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mesas[j].get_nro_mesa()<mesas[posmin].get_nro_mesa()) {
                posmin=j;
            }
        }
        temp=mesas[i];
        mesas[i]=mesas[posmin];
        mesas[posmin]=temp;
    }
}

void ordenar_mesas_por_can_sillas(Mesa * mesas, int tam) {
    int i, j, posmin;
    Mesa temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mesas[j].get_can_sillas()<mesas[posmin].get_can_sillas()) {
                posmin=j;
            }
        }
        temp=mesas[i];
        mesas[i]=mesas[posmin];
        mesas[posmin]=temp;
    }
}

void ordenar_mesas_por_ubicacion_nro_mesa(Mesa * mesas, int tam) {
    int i, j, posmin;
    Mesa temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mesas[j].get_ubic()<mesas[posmin].get_ubic() ||
                (mesas[j].get_ubic()==mesas[posmin].get_ubic() &&
                mesas[j].get_nro_mesa()<mesas[posmin].get_nro_mesa())) {
                posmin=j;
            }
        }
        temp=mesas[i];
        mesas[i]=mesas[posmin];
        mesas[posmin]=temp;
    }
}

void ordenar_mozos_por_id(Mozo * mozos, int tam) {
    int i, j, posmin;
    Mozo temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mozos[j].get_id_mozo()<mozos[posmin].get_id_mozo()) {
                posmin=j;
            }
        }
        temp=mozos[i];
        mozos[i]=mozos[posmin];
        mozos[posmin]=temp;
    }
}

void ordenar_mozos_por_nombre(Mozo * mozos, int tam) {
    int i, j, posmin;
    Mozo temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mozos[j].get_nombre().compare(mozos[posmin].get_nombre())<0) {
                posmin=j;
            }
        }
        temp=mozos[i];
        mozos[i]=mozos[posmin];
        mozos[posmin]=temp;
    }
}

void ordenar_mozos_por_apellido(Mozo * mozos, int tam) {
    int i, j, posmin;
    Mozo temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mozos[j].get_apellido().compare(mozos[posmin].get_apellido())<0) {
                posmin=j;
            }
        }
        temp=mozos[i];
        mozos[i]=mozos[posmin];
        mozos[posmin]=temp;
    }
}

void ordenar_mozos_por_fecha_naci(Mozo * mozos, int tam) {
    int i, j, posmin;
    Mozo temp;
    Fecha temp2;    //algun concepto que aun no entiendo no me permite pasar el resultado de un
                    //getter a la funcion del resultado de otro getter si no creo el objeto afuera
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            temp2=mozos[posmin].get_fecha_naci();
            if (mozos[j].get_fecha_naci().comparar(temp2)<0) {
                posmin=j;
            }
        }
        temp=mozos[i];
        mozos[i]=mozos[posmin];
        mozos[posmin]=temp;
    }
}

void ordenar_mozos_por_turno_id(Mozo * mozos, int tam) {
    int i, j, posmin;
    Mozo temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (mozos[j].get_turno()<mozos[posmin].get_turno() ||
                (mozos[j].get_turno()==mozos[posmin].get_turno() &&
                mozos[j].get_id_mozo()<mozos[posmin].get_id_mozo())) {
                posmin=j;
            }
        }
        temp=mozos[i];
        mozos[i]=mozos[posmin];
        mozos[posmin]=temp;
    }
}

void ordenar_servicios_por_nro_factura(Servicio * servicios, int tam) {
    int i, j, posmin;
    Servicio temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (servicios[j].get_nro_factura()<servicios[posmin].get_nro_factura()) {
                posmin=j;
            }
        }
        temp=servicios[i];
        servicios[i]=servicios[posmin];
        servicios[posmin]=temp;
    }
}

void ordenar_servicios_por_nro_mesa(Servicio * servicios, int tam) {
    int i, j, posmin;
    Servicio temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (servicios[j].get_nro_mesa()<servicios[posmin].get_nro_mesa()) {
                posmin=j;
            }
        }
        temp=servicios[i];
        servicios[i]=servicios[posmin];
        servicios[posmin]=temp;
    }
}

void ordenar_servicios_por_id_mozo(Servicio * servicios, int tam) {
    int i, j, posmin;
    Servicio temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (servicios[j].get_id_mozo()<servicios[posmin].get_id_mozo()) {
                posmin=j;
            }
        }
        temp=servicios[i];
        servicios[i]=servicios[posmin];
        servicios[posmin]=temp;
    }
}

void ordenar_servicios_por_fecha_serv(Servicio * servicios, int tam) {
    int i, j, posmin;
    Servicio temp;
    Fecha temp2;    //algun concepto que aun no entiendo no me permite pasar el resultado de un
                    //getter a la funcion del resultado de otro getter si no creo el objeto afuera
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            temp2=servicios[posmin].get_fecha_serv();
            if (servicios[j].get_fecha_serv().comparar(temp2)<0) {
                posmin=j;
            }
        }
        temp=servicios[i];
        servicios[i]=servicios[posmin];
        servicios[posmin]=temp;
    }
}

void ordenar_servicios_por_importe_serv(Servicio * servicios, int tam) {
    int i, j, posmin;
    Servicio temp;
    for (i=0; i<tam-1; i++) {
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (servicios[j].get_importe_serv()<servicios[posmin].get_importe_serv()) {
                posmin=j;
            }
        }
        temp=servicios[i];
        servicios[i]=servicios[posmin];
        servicios[posmin]=temp;
    }
}

int buscar_int(int * arr, int tam, int target) {
    int i, pos=-1;
    for (i=0; i<tam; i++) {
        if (arr[i]==target) {   //encontro el objetivo
            pos=i;
            break;
        }
        if (arr[i]==0) {//no quedan elementos no vacios en el array
            break;
        }
    }
    return pos;
}

bool agregar_int(int * arr, int tam, int element) {
    int i;
    for (i=0; i<tam; i++) {
        if (arr[i]==0) {//encontro lugar para el elemento nuevo
            arr[i]=element;
            return true;
        }
    }
    return false;
}

void ordenar_int_con_float_secundario(int * primario, float * secundario, int tam) {
    int i, j, posmin, tempi;
    float tempf;
    for (i=0; i<tam-1; i++) {
        if (primario[i]==0) {
            break;
        }
        posmin=i;
        for (j=i+1; j<tam; j++) {
            if (primario[j]==0) {
                break;
            }
            if (primario[j]<primario[posmin]) {
                posmin=j;
            }
        }
        tempi=primario[i];
        tempf=secundario[i];
        primario[i]=primario[posmin];
        secundario[i]=secundario[posmin];
        primario[posmin]=tempi;
        secundario[posmin]=tempf;
    }
}

int buscar_id_mozo(Mozo * mozos, int cant_mozos, int id) {
    int i, pos=-1;
    for (i=0; i<cant_mozos; i++) {
        if (mozos[i].get_id_mozo()==id) {   //encontro el objetivo
            pos=i;
            break;
        }
    }
    return pos;
}

int buscar_nro_mesa(Mesa * mesas, int cant_mesas, int nro) {
    int i, pos=-1;
    for (i=0; i<cant_mesas; i++) {
        if (mesas[i].get_nro_mesa()==nro) {   //encontro el objetivo
            pos=i;
            break;
        }
    }
    return pos;
}
