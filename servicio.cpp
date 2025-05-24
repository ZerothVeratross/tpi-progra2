#include "servicio.h"

Servicio::Servicio() {
    nro_factura=0;
    nro_mesa=0;
    id_mozo=0;
    fecha_serv=Fecha();
    importe_serv=0;
    monto_abon=0;
    estado=true;
}

Servicio::Servicio(int n_nro_factura, int n_nro_mesa, int n_id_mozo, Fecha n_fecha_serv, float n_importe_serv, float n_monto_abon) {
    nro_factura=n_nro_factura;
    nro_mesa=n_nro_mesa;
    id_mozo=n_id_mozo;
    fecha_serv=Fecha(n_fecha_serv);
    importe_serv=n_importe_serv;
    monto_abon=n_monto_abon;
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
    nro_factura=n_nro_factura;
}

void Servicio::set_nro_mesa(int n_nro_mesa) {
    nro_mesa=n_nro_mesa;
}

void Servicio::set_id_mozo(int n_id_mozo) {
    id_mozo=n_id_mozo;
}

void Servicio::set_fecha_serv(Fecha n_fecha_serv) {
    n_fecha_serv.copiar(&fecha_serv);
}

void Servicio::set_importe_serv(float n_importe_serv) {
    importe_serv=n_importe_serv;
}

void Servicio::set_monto_abon(float n_monto_abon) {
    monto_abon=n_monto_abon;
}

void Servicio::set_estado(bool n_estado) {
    estado=n_estado;
}

float Servicio::get_propina() {
    return monto_abon-importe_serv;
}
