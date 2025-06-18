#include "menu.h"

using namespace std;

int main() {
    HWND hWnd=GetConsoleWindow();
    bool ciclo=true;

    ShowWindow(hWnd, SW_SHOWMAXIMIZED); //debido a un limitacion de rlutil, se requiere que la ventana de la consola
                                        //sea grande para que las funciones de listas e informes puedan dibujar sin
                                        //errores. si no hay suficiente espacio físico en la ventana, los llamados a
                                        //locate con coordenadas que excedan las dimensiones de la ventana seran ignorados
                                        //y la informacion no sera distribuida adecuadamente en las tablas

    cout<<fixed<<setprecision(2);   //deshabilita notacion cientifica para floats en cout y limita los decimales a 2 digitos
    rlutil::setColor(rlutil::WHITE);
    while (ciclo) {
        ciclo=comandos_principales();
    }
}
