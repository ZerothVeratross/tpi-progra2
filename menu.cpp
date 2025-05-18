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

Mesa * crear_mesa() {
    int datos_int[3];
    string dato_str("");
    cout<<"\nIngrese numero de mesa: ";
    cin>>datos_int[0];
    cout<<"\nIngrese cantidad de sillas: ";
    cin>>datos_int[1];
    cout<<"\nElija ubicacion: ";
    cout<<"\n1. Interior\n2. Terraza\n";
    cin>>datos_int[2];

    cout<<"\nEscriba una descripcion de la mesa: ";
    cin>>dato_str;
    return new Mesa(datos_int[0], datos_int[1], datos_int[2], dato_str);
}

void listar_mesa(Mesa * mesa) {
    cout<<"\nNumero de mesa: "<<mesa->get_nro_mesa();
    cout<<"\nCantidad de sillas: "<<mesa->get_can_sillas();
    cout<<"\nUbicacion: ";
    if (mesa->get_ubic() == 1) {
        cout<<"interior";
    } else {
        cout<<"terraza";
    }
    cout<<"\nDescripcion: "<<mesa->get_desc()<<"\n";
}

void cambiar_desc(Mesa * mesa) {
    char dato_str[30];
    cout<<"\nIngrese la nueva descripcion de la mesa: ";
    cin>>dato_str;
    mesa->set_desc(dato_str);
}
