#include "menu.h"

using namespace std;

int main() {
    int comando;
    bool ciclo=true;
    Mesa * mesa_ejemplo;
    int datos_int[5]={-1,-1,-1,-1,-1};
    string dato_str;
    while (ciclo) {
        listar_comandos();
        cin>>comando;
        switch (comando) {
        case 1:
            cout<<"\nIngrese numero de mesa: ";
            cin>>datos_int[0];
            cout<<"\nIngrese cantidad de sillas: ";
            cin>>datos_int[1];
            cout<<"\nElija ubicacion: ";
            cout<<"\n1. Interior\n2. Terraza\n";
            cin>>datos_int[2];

            cout<<"\nEscriba una descripcion de la mesa: ";
            cin>>dato_str;
            mesa_ejemplo=new Mesa(datos_int[0], datos_int[1], datos_int[2], dato_str);
            break;
        case 2:
            listar_mesa(*mesa_ejemplo);
            break;
        case 3:
            cambiar_desc(*mesa_ejemplo);
            break;
        case -1:
            ciclo=false;
            break;
        case -2:
            clear_screen();
            break;
        }
    }
}
