#include "menu.h"

using namespace std;

//esta funcion provee una manera segura de limpiar la consola que no utiliza llamadas a "system" https://cplusplus.com/articles/j3wTURfi/
//pero no es de mi confeccion https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
void clear_screen(char fill) {
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

void imprimir_separador() {
    cout<<"-------------------------------------------------------------------";
}

void listar_comandos() {
    imprimir_separador();
    cout<<"\nLista de comandos:";
    cout<<"\n1. Crear mesa";
    cout<<"\n2. Listar mesa";
    cout<<"\n3. Cambiar descripcion de mesa";
    cout<<"\n-1. Cerrar programa\n-2.Limpiar consola\n\nIngrese un comando: ";
}

void listar_mesa(Mesa mesa) {
    string buffer;
    cout<<"\nNumero de mesa: "<<mesa.get_nro_mesa();
    cout<<"\nCantidad de sillas: "<<mesa.get_can_sillas();
    cout<<"\nUbicacion: ";
    if (mesa.get_ubic() == 1) {
        cout<<"interior";
    } else {
        cout<<"terraza";
    }
    buffer=mesa.get_desc();
    cout<<"\nDescripcion: "<<buffer<<"\n";
}

void cambiar_desc(Mesa mesa) {
    char buffer[30];
    cout<<"\nIngrese la nueva descripcion de la mesa: ";
    cin>>buffer;
    mesa.set_desc(buffer);
}
