#ifndef CONFIG_H
#define CONFIG_H

class Configuracion {
private:
    char contrasenia[20];
    int modo;//1=admin, 2=comun
public:
    Configuracion();
    Configuracion(char n_contrasenia[20], int n_modo);
    int cambiar_contrasenia(char intento[20], char contrasenia_nueva[20]);
    bool comparar_contrasenia(char intento[20]);
    int get_modo();
    void set_modo(char intento[20], int n_modo);
};
#endif // CONFIG_H
