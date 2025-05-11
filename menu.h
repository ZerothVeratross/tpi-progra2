#include "mesa.h"
#include "rlutil.h"
#include <iostream>
#include <windows.h>    //header principal de la API de Windows https://learn.microsoft.com/en-us/windows/win32/api/

void clear_screen(char fill = ' ');
void imprimir_separador();
void listar_comandos();
void listar_mesa(Mesa mesa);
void cambiar_desc(Mesa mesa);
