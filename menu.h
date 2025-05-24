#include "archivoMesa.h"
#include "archivoMozo.h"
#include "archivoServicio.h"
#include "arrutil.h"
#include "rlutil.h"
#include <windows.h>    //header principal de la API de Windows https://learn.microsoft.com/en-us/windows/win32/api/

void clear_screen(char fill = ' ');
void vaciar_input();
void imprimir_separador();
void admin_listar_comandos();
void mostrar_mesa(Mesa * mesa, bool ignorar_borrado);
void mostrar_mozo(Mozo * mozo, bool ignorar_borrado);
void mostrar_servicio(Servicio * servicio, bool ignorar_borrado);

void admin_menu_registrar();
int menu_registrar_mesa();
int menu_registrar_mozo();
int menu_registrar_servicio();

void admin_menu_listar();
void menu_listar_mesas(int orden);
void menu_listar_mozos(int orden);
void menu_listar_servicios(int orden);

void admin_menu_informe();
void informe_recaudacion_anual();
void informe_recaudacion_por_mozo();
void informe_recaudacion_por_mesa();
void informe_recaudacion_mensual();
void informe_propinas_percibidas();

void menu_generacion_datos();
