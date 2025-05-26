#include "menu.h"

using namespace std;

int main() {
    int comando;
    bool admin=true;
    bool ciclo=true;
    cout<<fixed;//deshabilita notacion cientifica para floats en cout
    if (admin) {
        cout<<"MODO ADMINISTRADOR\n";
        while (ciclo) {
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
                //admin_menu_borrar();
                break;
            case 6:
                //admin_menu_modificar();
                break;
            case 7:
                //clear_screen();
                //admin=false;
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
        }
    } else {
        while (ciclo) {
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
}
