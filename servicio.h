#ifndef SERVICIO_H
#define SERVICIO_H


#include "fecha.h"

class Servicio {
private:
    int nro_factura, nro_mesa, id_mozo;
    Fecha fecha_serv;
    float importe_serv, monto_abon;
    bool estado;
public:
    Servicio();
    Servicio(int n_nro_factura, int n_nro_mesa, int n_id_mozo, Fecha n_fecha_serv, float n_importe_serv, float n_monto_abon);
    int get_nro_factura();
    int get_nro_mesa();
    int get_id_mozo();
    Fecha get_fecha_serv();
    float get_importe_serv();
    float get_monto_abon();
    bool get_estado();
    void set_nro_factura(int n_nro_factura);
    void set_nro_mesa(int n_nro_mesa);
    void set_id_mozo(int n_id_mozo);
    void set_fecha_serv(Fecha n_fecha_serv);
    void set_importe_serv(float n_importe_serv);
    void set_monto_abon(float n_monto_abon);
    void set_estado(bool n_estado);
    float get_propina();
};
#endif // SERVICIO_H
