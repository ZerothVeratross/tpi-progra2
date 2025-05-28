#include "mesa.h"
#include "mozo.h"
#include "servicio.h"

void ordenar_mesas_por_nro(Mesa * mesas, int tam);
void ordenar_mesas_por_can_sillas(Mesa * mesas, int tam);
void ordenar_mesas_por_ubicacion_nro_mesa(Mesa * mesas, int tam);
int buscar_nro_mesa(Mesa * mesas, int cant_mesas, int nro);

void ordenar_mozos_por_id(Mozo * mozos, int tam);
void ordenar_mozos_por_nombre(Mozo * mozos, int tam);
void ordenar_mozos_por_apellido(Mozo * mozos, int tam);
void ordenar_mozos_por_fecha_naci(Mozo * mozos, int tam);
void ordenar_mozos_por_turno_id(Mozo * mozos, int tam);
int buscar_id_mozo(Mozo * mozos, int cant_mozos, int id);

void ordenar_servicios_por_nro_factura(Servicio * servicios, int tam);
void ordenar_servicios_por_nro_mesa(Servicio * servicios, int tam);
void ordenar_servicios_por_id_mozo(Servicio * servicios, int tam);
void ordenar_servicios_por_fecha_serv(Servicio * servicios, int tam);
void ordenar_servicios_por_importe_serv(Servicio * servicios, int tam);
void ordenar_servicios_por_monto_abon(Servicio * servicios, int tam);
int buscar_nro_factura(Servicio * servicios, int cant_servicios, int nro);

int buscar_int(int * arr, int tam, int target);
bool agregar_int(int * arr, int tam, int element);
void ordenar_int_con_float_secundario(int * primario, float * secundario, int tam);
