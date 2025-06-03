#include "menu.h"

using namespace std;

int main() {
    int comando;
    bool admin=true;
    bool ciclo=true;
    cout<<fixed;//deshabilita notacion cientifica para floats en cout
    if (admin) {
        cout<<"MODO ADMINISTRADOR\n";
    } else {
        cout<<"MODO REGULAR\n";
    }
    while (ciclo) {
        if (admin) {
            admin_listar_comandos();
            cin>>comando;
            switch (comando) {
            case 1:
                admin_menu_registrar();
                break;
            case 2:
                admin_menu_consultar();
                break;
            case 3:
                admin_menu_listar();
                break;
            case 4:
                admin_menu_informe();
                break;
            case 5:
                admin_menu_borrar_recuperar();
                break;
            case 6:
                //admin_menu_modificar();
                break;
            case 7:
                clear_screen();
                admin=false;
                cout<<"MODO ADMINISTRADOR\n";
                break;
            case 8:
                menu_generacion_datos();
                break;
            case -1:
                ciclo=false;
                break;
            case -2:
                clear_screen();
                cout<<"MODO ADMINISTRADOR\n";
                break;
            default:
                cout<<"\nComando invalido\n";
                break;
            }
        } else {
            //comun_listar_comandos();
            cin>>comando;
            switch (comando) {
            case 1:
                //comun_menu_registrar();
                break;
            case 2:
                //comun_consultar();
                break;
            case 3:
                //comun_modificar();
            case 4:
                clear_screen();
                admin=true;
                cout<<"MODO ADMINISTRADOR\n";
                break;
            case -1:
                ciclo=false;
                break;
            case -2:
                clear_screen();
                break;
            default:
                cout<<"\nComando invalido\n";
                break;
            }
        }
    }
}
