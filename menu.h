#include "archivoMesa.h"
#include "archivoMozo.h"
#include "archivoServicio.h"
#include "arrutil.h"
#include "rlutil.h"
#include "archivoConfig.h"
#include <iomanip>
#include <windows.h>    //header principal de la API de Windows https://learn.microsoft.com/en-us/windows/win32/api/

void clear_screen(char fill = ' ');
void vaciar_input();
void imprimir_separador();
void imprimir_error(const char * msj_error);
void imprimir_exito(const char * msj_exito);
void imprimir_comando(const char * msj_comando);
void comando_invalido();
void numero_invalido();
void numero_debe_ser_mayor();
void acceso_archivo_fallido();

int pedir_comando(const char *, int cant_com, int * comando);
int pedir_int(const char * pedido, int cota_inf, int cota_sup, int * dato_int);
int pedir_rango_int(const char * pedido, int * datos_int, int pos1, int pos2);
int pedir_string(const char * pedido, std::string * str, int tam_max, bool cin_antes, bool espacios=true);
int pedir_float(const char * pedido, float cota_inf, float cota_sup, float * dato_int);
int pedir_rango_float(const char * pedido, float * datos_float, int pos1, int pos2);
int pedir_fecha(const char * pedido, Fecha * fecha, int anio1, int anio2);

bool comandos_principales();
bool menu_cambiar_modo(Configuracion * config, int modo);
bool menu_cambiar_contrasenia(Configuracion * config);

void mostrar_mesa(Mesa * mesa, bool ignorar_borrado, int color, bool mostrar_nombres);
void mostrar_mozo(Mozo * mozo, bool ignorar_borrado, int color, bool mostrar_nombres);
void mostrar_servicio(Servicio * servicio, bool ignorar_borrado, int color, bool mostrar_nombres);

void admin_menu_registrar();
int menu_registrar_mesa();
int menu_registrar_mozo();
int menu_registrar_servicio();

void admin_menu_consultar();
void comun_menu_consultar();
void menu_consultar_mesas();
void menu_consultar_mozos();
void menu_consultar_servicios();

void admin_menu_listar();
void menu_listar_mesas();
void menu_listar_mozos();
void menu_listar_servicios();

void admin_menu_informe();
void informe_recaudacion_anual();
void informe_recaudacion_por_mozo();
void informe_recaudacion_por_mesa();
void informe_recaudacion_mensual();
void informe_propinas_percibidas();

void admin_menu_borrar_recuperar();
void menu_borrar_recuperar_mesa();
void menu_borrar_recuperar_mozo();
void menu_borrar_recuperar_servicio();

void admin_menu_modificar();
void menu_modificar_mesa();
void menu_modificar_mozo();
void menu_modificar_servicio();

void menu_generacion_datos();
