#include "menu.h"

using namespace std;

int main() {
    int comando;
    bool ciclo=true;
    Mesa * mesa_ejemplo;
    while (ciclo) {
        listar_comandos();
        cin>>comando;
        switch (comando) {
        case 1:
            mesa_ejemplo = crear_mesa();
            break;
        case 2:
            listar_mesa(mesa_ejemplo);
            break;
        case 3:
            cambiar_desc(mesa_ejemplo);
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
