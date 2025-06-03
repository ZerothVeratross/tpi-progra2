#include "servicio.h"

Servicio::Servicio() {
    nro_factura=1;
    nro_mesa=1;
    id_mozo=1;
    fecha_serv=Fecha();
    importe_serv=9;
    monto_abon=10;
    estado=true;
}

//los constructores no puede hacer un return, ni siquiera de void. dado que no
//tengo acceso a excepciones, inicializo el objeto con valores predeterminados validos
//si los parametros no son validos
Servicio::Servicio(int n_nro_factura, int n_nro_mesa, int n_id_mozo, Fecha n_fecha_serv, float n_importe_serv, float n_monto_abon) {
    if (n_nro_factura<1) {
        nro_factura=1;
    } else {
        nro_factura=n_nro_factura;
    }

    if (n_nro_mesa<1) {
        nro_mesa=1;
    } else {
        nro_mesa=n_nro_mesa;
    }

    if (n_id_mozo<1) {
        id_mozo=1;
    } else {
        id_mozo=n_id_mozo;
    }

    fecha_serv=Fecha(n_fecha_serv);

    if (n_importe_serv<1) {
        importe_serv=1;
    } else {
        importe_serv=n_importe_serv;
    }

    if (n_monto_abon<1 || n_monto_abon<importe_serv) {
        n_monto_abon=importe_serv+1;
    } else {
        monto_abon=n_monto_abon;
    }
    estado=true;
}

int Servicio::get_nro_factura() {
    return nro_factura;
}

int Servicio::get_nro_mesa() {
    return nro_mesa;
}
int Servicio::get_id_mozo() {
    return id_mozo;
}

Fecha Servicio::get_fecha_serv() {
    return fecha_serv;
}

float Servicio::get_importe_serv() {
    return importe_serv;
}

float Servicio::get_monto_abon() {
    return monto_abon;
}

bool Servicio::get_estado() {
    return estado;
}

void Servicio::set_nro_factura(int n_nro_factura) {
    if (n_nro_factura<1) {return;}
    nro_factura=n_nro_factura;
}

void Servicio::set_nro_mesa(int n_nro_mesa) {
    if (n_nro_mesa<1) {return;}
    nro_mesa=n_nro_mesa;
}

void Servicio::set_id_mozo(int n_id_mozo) {
    if (n_id_mozo<1) {return;}
    id_mozo=n_id_mozo;
}

void Servicio::set_fecha_serv(Fecha n_fecha_serv) {
    n_fecha_serv.copiar(&fecha_serv);
}

void Servicio::set_importe_serv(float n_importe_serv) {
    if (n_importe_serv<1 || n_importe_serv>monto_abon) {return;}
    importe_serv=n_importe_serv;
}

void Servicio::set_monto_abon(float n_monto_abon) {
    if (n_monto_abon<1 || n_monto_abon<importe_serv) {return;}
    monto_abon=n_monto_abon;
}

void Servicio::set_estado(bool n_estado) {
    estado=n_estado;
}

float Servicio::get_propina() {
    return monto_abon-importe_serv;
}
