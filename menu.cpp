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

//para que std::getline funcione, se debe remover el final de linea que cin>> no extrae
void vaciar_input() {
    char c;
    while (cin.get(c) && c != '\n');
}

void imprimir_separador() {
    cout<<"-------------------------------------------------------------------";
}

void admin_listar_comandos() {
    imprimir_separador();
    cout<<"\nLista de comandos:";
    cout<<"\n1. Registrar";
    cout<<"\n2. Consultar";
    cout<<"\n3. Listar";
    cout<<"\n4. Generar informe";
    cout<<"\n5. Borrar";
    cout<<"\n6. Modificar";
    cout<<"\n7. Salir de modo administrador";
    cout<<"\n8. Generar datos aleatorios";
    cout<<"\n-1. Cerrar programa\n-2. Limpiar consola\n\nIngrese un comando: ";
}

void mostrar_mesa(Mesa * mesa, bool ignorar_borrado) {
    if (!mesa->get_estado() && ignorar_borrado) {
        return;
    }
    cout<<"\nNumero de mesa: "<<mesa->get_nro_mesa();
    cout<<" | Cantidad de sillas: "<<mesa->get_can_sillas();
    cout<<" | Ubicacion: ";
    if (mesa->get_ubic() == 1) {
        cout<<"interior";
    } else {
        cout<<"terraza";
    }
    cout<<" | Descripcion: "<<mesa->get_desc()<<"\n";
}

void mostrar_mozo(Mozo * mozo, bool ignorar_borrado) {
    if (!mozo->get_estado() && ignorar_borrado) {
        return;
    }
    cout<<"\nID del mozo: "<<mozo->get_id_mozo();
    cout<<" | Nombre: "<<mozo->get_nombre();
    cout<<" | Apellido: "<<mozo->get_apellido();
    cout<<" | Numero de telefono: "<<mozo->get_nro_telef();
    cout<<" | email: "<<mozo->get_email();
    cout<<" | Fecha de nacimiento: "<<mozo->get_fecha_naci().get_str();
    cout<<" | Turno: ";
    switch(mozo->get_turno()) {
    case 1:
        cout<<"Maniana";
        break;
    case 2:
        cout<<"Tarde";
        break;
    case 3:
        cout<<"Noche";
        break;
    default:
        cout<<"registro invalido";
    }
}

void mostrar_servicio(Servicio * servicio, bool ignorar_borrado) {
    if (!servicio->get_estado() && ignorar_borrado) {
        return;
    }
    cout<<"\nNumero de factura: "<<servicio->get_nro_factura();
    cout<<" | Numero de mesa: "<<servicio->get_nro_mesa();
    cout<<" | ID de mozo: "<<servicio->get_id_mozo();
    cout<<" | Fecha de servicio: "<<servicio->get_fecha_serv().get_str();
    cout<<" | Importe de servicio: "<<servicio->get_importe_serv();
    cout<<" | Monto abonado por cliente: "<<servicio->get_monto_abon()<<"\n";
}

//Comienzo funciones para registrar datos
void admin_menu_registrar() {
    int dato_int;
    cout<<"\nIngrese su eleccion:\n1. Registrar mesa\n2. Registrar mozos\n3. Registrar servicio\n";
    cin>>dato_int;
    switch(dato_int) {
    case 1:
        if (menu_registrar_mesa()) {
            cout<<"\nNueva mesa registrada exitosamente\n";
        } else {
            cout<<"\nNo se registro una mesa nueva\n";
        }
        break;
    case 2:
        if (menu_registrar_mozo()) {
            cout<<"\nNuevo mozo registrado exitosamente\n";
        } else {
            cout<<"\nNo se registro un mozo nuevo\n";
        }
        break;
    case 3:
        if (menu_registrar_servicio()) {
            cout<<"\nNuevo servicio registrado exitosamente\n";
        } else {
            cout<<"\nNo se registro un servicio nuevo\n";
        }
        break;
    default:
        cout<<"\nComando invalido, volviendo al menu principal...\n";
        break;
    }
}

int menu_registrar_mesa() {
    ArchivoMesa archivo;
    Mesa * mesa;
    int chars=0,datos_int[3];
    string dato_str;

    cout<<"\nIngrese numero de mesa: ";
    cin>>datos_int[0];
    cout<<"\nIngrese cantidad de sillas: ";
    cin>>datos_int[1];
    cout<<"\nElija ubicacion: ";
    cout<<"\n1. Interior\n2. Terraza\n";
    cin>>datos_int[2];

    vaciar_input();
    do {
        cout<<"\nEscriba una descripcion de la mesa con no mas de 29 caracteres:\n";
        getline(cin, dato_str, '\n');
        chars=dato_str.length();
    } while(chars>29);
    mesa=new Mesa(datos_int[0], datos_int[1], datos_int[2], dato_str);

    mostrar_mesa(mesa, true);
    cout<<"\nEsta es la mesa que desea registrar?\n1. Si\n2. No\n";
    cin>>datos_int[0];
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=archivo.registrar_mesa(mesa);
    delete mesa;
    return datos_int[0];
}

int menu_registrar_mozo() {
    ArchivoMozo archivo;
    Mozo * mozo;
    int chars=0,datos_int[6];
    string datos_str[4];
    Fecha fecha_naci;

    cout<<"\nIngrese DNI: ";
    cin>>datos_int[0];

    vaciar_input();
    do {
        cout<<"\nEscriba el nombre del mozo con no mas de 19 caracteres:\n";
        getline(cin, datos_str[0], '\n');
        chars=datos_str[0].length();
    } while(chars>19);
    chars=0;

    do {
        cout<<"\nEscriba el apellido del mozo con no mas de 29 caracteres:\n";
        getline(cin, datos_str[1], '\n');
        chars=datos_str[1].length();
    } while(chars>29);
    chars=0;

    do {
        cout<<"\nEscriba el numero de telefono del mozo con no mas de 19 caracteres:\n";
        getline(cin, datos_str[2], '\n');
        chars=datos_str[2].length();
    } while(chars>19);
    chars=0;

    do {
        cout<<"\nEscriba el email del mozo con no mas de 49 caracteres:\n";
        getline(cin, datos_str[3], '\n');
        chars=datos_str[3].length();
    } while(chars>49);

    cout<<"\nIngrese fecha de nacimiento del mozo. Dia: ";
    cin>>datos_int[1];
    cout<<"Mes: ";
    cin>>datos_int[2];
    cout<<"Anio: ";
    cin>>datos_int[3];
    fecha_naci=Fecha(datos_int[1], datos_int[2], datos_int[3]);

    cout<<"\nIngrese turno del mozo.\n1. Maniana\n2. Tarde\n3. Noche\n";
    cin>>datos_int[4];
    cout<<"\nIngrese ID del mozo: ";
    cin>>datos_int[5];

    mozo=new Mozo(datos_int[0], datos_str[0], datos_str[1], datos_str[2], datos_str[3], fecha_naci, datos_int[4], datos_int[5]);

    mostrar_mozo(mozo, true);
    cout<<"\nEste es el mozo que desea registrar?\n1. Si\n2. No\n";
    cin>>datos_int[0];
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=archivo.registrar_mozo(mozo);
    delete mozo;
    return datos_int[0];
}

int menu_registrar_servicio() {
    ArchivoServicio archivo;
    Servicio * servicio;
    int datos_int[6];
    Fecha fecha_serv;
    float datos_float[2];

    cout<<"\nIngrese numero de factura: ";
    cin>>datos_int[0];
    cout<<"\nIngrese numero de mesa: ";
    cin>>datos_int[1];
    cout<<"\nIngrese ID de mozo: ";
    cin>>datos_int[2];

    cout<<"\nIngrese fecha del servicio. Dia: ";
    cin>>datos_int[3];
    cout<<"Mes: ";
    cin>>datos_int[4];
    cout<<"Anio: ";
    cin>>datos_int[5];
    fecha_serv=Fecha(datos_int[3], datos_int[4], datos_int[5]);

    cout<<"\nIngrese importe del servicio, utilizando punto para marcar decimales: ";
    cin>>datos_float[0];
    cout<<"\nIngrese monto abonado por el cliente, utilizando punto para marcar decimales: ";
    cin>>datos_float[1];

    servicio=new Servicio(datos_int[0], datos_int[1], datos_int[2], fecha_serv, datos_float[0], datos_float[1]);
    mostrar_servicio(servicio, true);
    cout<<"\nEste es el servicio que desea registrar?\n1. Si\n2. No\n";
    cin>>datos_int[0];
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=archivo.registrar_servicio(servicio);
    delete servicio;
    return datos_int[0];
}
//Fin funciones para registrar datos

//Comienzo funciones para listar datos
void admin_menu_listar() {
    int dato_int;
    cout<<"\nIngrese su eleccion:\n1. Listar mesas\n2. Listar mozos\n3. Listar servicios\n";
    cin>>dato_int;
    switch(dato_int) {
    case 1:
        cout<<"Como deben estar ordenadas las mesas?\n1. Por numero de mesa\n2. Por cantidad de sillas\n3. Por ubicacion y numero de mesa\n4. Listar mesas dadas de baja\n";
        cin>>dato_int;
        if (dato_int>0 && dato_int<5) {
            menu_listar_mesas(dato_int);
        } else {
            cout<<"\nComando invalido, volviendo al menu principal...\n";
        }
        break;
    case 2:
        cout<<"Como deben estar ordenadas los mozos?\n1. Por ID de mozo\n2. Alfabeticamente por nombre\n3. Alfabeticamente por apellido\n4. Por fecha de nacimiento\n5. Por turno e ID de mozo\n6. Listar mozos dados de baja\n";
        cin>>dato_int;
        if (dato_int>0 && dato_int<7) {
            menu_listar_mozos(dato_int);
        } else {
            cout<<"\nComando invalido, volviendo al menu principal...\n";
        }
        break;
    case 3:
        cout<<"Como deben estar ordenados los servicios?\n1. Por numero de factura\n2. Por numero de mesa\n3. Por ID de mozo\n4. Por fecha de servicio\n5. Por importe de servicio\n6. Listar servicios dados de baja\n";
        cin>>dato_int;
        if (dato_int>0 && dato_int<7) {
            menu_listar_servicios(dato_int);
        } else {
            cout<<"\nComando invalido, volviendo al menu principal...\n";
        }
        break;
    default:
        cout<<"\nComando invalido, volviendo al menu principal...\n";
        break;
    }
}

void menu_listar_mesas(int orden) {
    ArchivoMesa archivo;
    int i, cant_regs=archivo.contar_regs();
    bool ignorar_borrado=true;
    Mesa mesas[cant_regs];

    archivo.listar_mesas(mesas, cant_regs);

    switch(orden) {
    case 1:
        ordenar_mesas_por_nro(mesas, cant_regs);
        break;
    case 2:
        ordenar_mesas_por_can_sillas(mesas, cant_regs);
        break;
    case 3:
        ordenar_mesas_por_ubicacion_nro_mesa(mesas, cant_regs);
        break;
    case 4:
        ignorar_borrado=false;
        break;
    default:
        break;
    }

    for (i=0; i<cant_regs; i++) {
        if (mesas[i].get_estado() && !ignorar_borrado) {
            continue;
        }
        mostrar_mesa(&mesas[i], ignorar_borrado);
    }
    cout<<"\n";
}

void menu_listar_mozos(int orden) {
    ArchivoMozo archivo;
    int i, cant_regs=archivo.contar_regs();
    bool ignorar_borrado=true;
    Mozo mozos[cant_regs];

    archivo.listar_mozos(mozos, cant_regs);

    switch(orden) {
    case 1:
        ordenar_mozos_por_id(mozos, cant_regs);
        break;
    case 2:
        ordenar_mozos_por_nombre(mozos, cant_regs);
        break;
    case 3:
        ordenar_mozos_por_apellido(mozos, cant_regs);
        break;
    case 4:
        ordenar_mozos_por_fecha_naci(mozos, cant_regs);
        break;
    case 5:
        ordenar_mozos_por_turno_id(mozos, cant_regs);
        break;
    case 6:
        ignorar_borrado=false;
        break;
    default:
        break;
    }

    for (i=0; i<cant_regs; i++) {
        if (mozos[i].get_estado() && !ignorar_borrado) {
            continue;
        }
        mostrar_mozo(&mozos[i], ignorar_borrado);
    }
    cout<<"\n";
}

void menu_listar_servicios(int orden) {
    ArchivoServicio archivo;
    int i, cant_regs=archivo.contar_regs();
    bool ignorar_borrado=true;
    Servicio servicios[cant_regs];

    archivo.listar_servicios(servicios, cant_regs);

    switch(orden) {
    case 1:
        ordenar_servicios_por_nro_factura(servicios, cant_regs);
        break;
    case 2:
        ordenar_servicios_por_nro_mesa(servicios, cant_regs);
        break;
    case 3:
        ordenar_servicios_por_id_mozo(servicios, cant_regs);
        break;
    case 4:
        ordenar_servicios_por_fecha_serv(servicios, cant_regs);
        break;
    case 5:
        ordenar_servicios_por_importe_serv(servicios, cant_regs);
        break;
    case 6:
        ignorar_borrado=false;
        break;
    default:
        break;
    }

    for (i=0; i<cant_regs; i++) {
        if (servicios[i].get_estado() && !ignorar_borrado) {
            continue;
        }
        mostrar_servicio(&servicios[i], ignorar_borrado);
    }
    cout<<"\n";
}
//Fin funciones para listar datos

//Comienzo funciones para generar informes
void admin_menu_informe() {
    int dato_int;
    cout<<"\nQue tipo de informe desea generar?";
    cout<<"\n1. Recaudacion anual\n2. Recaudacion por mozo\n3. Recaudacion por mesa\n4. Recaudacion mensual\n5. Propinas percibidas por cada mozo\n";
    cin>>dato_int;
    switch(dato_int) {
    case 1:
        informe_recaudacion_anual();
        break;
    case 2:
        informe_recaudacion_por_mozo();
        break;
    case 3:
        informe_recaudacion_por_mesa();
        break;
    case 4:
        informe_recaudacion_mensual();
        break;
    case 5:
        informe_propinas_percibidas();
        break;
    default:
        cout<<"\nComando invalido, regresando al menu principal...\n";
        break;
    }
}

void informe_recaudacion_anual() {
    ArchivoServicio archivo;
    int i, pos, cant_regs=archivo.contar_regs();
    Servicio servicios[cant_regs];
    int anios[30];
    float recaudaciones[30];

    for (i=0; i<30; i++) {
        anios[i]=0;
        recaudaciones[i]=0;
    }
    archivo.listar_servicios(servicios, cant_regs);

    for (i=0; i<cant_regs; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        pos=buscar_int(anios, 30, servicios[i].get_fecha_serv().get_anio());
        if (pos>-1) {
            recaudaciones[pos]+=servicios[i].get_importe_serv();
        } else {
            agregar_int(anios, 30, servicios[i].get_fecha_serv().get_anio());
        }
    }

    ordenar_int_con_float_secundario(anios, recaudaciones, 30);
    cout<<"Anio | Recaudacion\n";
    for (i=0; i<30; i++) {
        if (anios[i]==0) {
            break;
        }
        cout<<anios[i]<<" | $"<<recaudaciones[i]<<"\n";
    }
}

void informe_recaudacion_por_mozo() {
    ArchivoMozo aMozo;
    ArchivoServicio aServicio;
    int i, pos, cant_mozos=aMozo.contar_regs();
    int cant_servicios=aServicio.contar_regs();
    Mozo mozos[cant_mozos];
    Servicio servicios[cant_servicios];
    float recaudaciones[cant_mozos];

    aMozo.listar_mozos(mozos, cant_mozos);
    ordenar_mozos_por_id(mozos, cant_mozos);
    aServicio.listar_servicios(servicios, cant_servicios);
    for (i=0; i<cant_mozos; i++) {
        recaudaciones[i]=0;
    }

    for (i=0; i<cant_servicios; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        pos=buscar_id_mozo(mozos, cant_mozos, servicios[i].get_id_mozo());
        if (pos==-1) {  //esto no deberia ejecutarse ya que no puede haber servicios con
                        //mozos que no esten registrados. a lo sumo estaran dados de baja
            continue;
        }
        recaudaciones[pos]+=servicios[i].get_importe_serv();

    }

    cout<<"ID de mozo | Nombre y Apellido | Recaudacion\n";
    for (i=0; i<cant_mozos; i++) {
        if (!mozos[i].get_estado()) {
            continue;
        }
        cout<<mozos[i].get_id_mozo()<<" | "<<mozos[i].get_nombre()<<" "<<mozos[i].get_apellido()<<" | $"<<recaudaciones[i]<<"\n";
    }
}

void informe_recaudacion_por_mesa() {
    ArchivoMesa aMesa;
    ArchivoServicio aServicio;
    int i, pos, cant_mesas=aMesa.contar_regs();
    int cant_servicios=aServicio.contar_regs();
    Mesa mesas[cant_mesas];
    Servicio servicios[cant_servicios];
    float recaudaciones[cant_mesas];

    aMesa.listar_mesas(mesas, cant_mesas);
    ordenar_mesas_por_nro(mesas, cant_mesas);
    aServicio.listar_servicios(servicios, cant_servicios);
    for (i=0; i<cant_mesas; i++) {
        recaudaciones[i]=0;
    }

    for (i=0; i<cant_servicios; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        pos=buscar_nro_mesa(mesas, cant_mesas, servicios[i].get_nro_mesa());
        if (pos==-1) {  //esto no deberia ejecutarse ya que no puede haber servicios con
                        //mesas que no esten registrados. a lo sumo estaran dados de baja
            continue;
        }
        recaudaciones[pos]+=servicios[i].get_importe_serv();

    }

    cout<<"Numero de mesa | Recaudacion\n";
    for (i=0; i<cant_mesas; i++) {
        if (!mesas[i].get_estado()) {
            continue;
        }
        cout<<mesas[i].get_nro_mesa()<<" | $"<<recaudaciones[i]<<"\n";
    }
}

void informe_recaudacion_mensual() {
    ArchivoServicio archivo;
    int i, anio, cant_regs=archivo.contar_regs();
    Servicio servicios[cant_regs];
    float recaudaciones[12];

    cout<<"\nIngrese el anio del que se desea informar: ";
    cin>>anio;
    if (anio<1950 || anio>2025) {
        cout<<"\nAnio invalido ingresado, regresando al menu principal...\n";
        return;
    }

    for (i=0; i<12; i++) {
        recaudaciones[i]=0;
    }
    archivo.listar_servicios(servicios, cant_regs);

    for (i=0; i<cant_regs; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        if (anio==servicios[i].get_fecha_serv().get_anio()) {
            recaudaciones[servicios[i].get_fecha_serv().get_mes()-1]+=servicios[i].get_importe_serv();
        }
    }

    cout<<"Anio "<<anio<<"\n";
    cout<<"Mes | Recaudacion\n";
    cout<<"Enero      | $"<<recaudaciones[0]<<"\n";
    cout<<"Febrero    | $"<<recaudaciones[1]<<"\n";
    cout<<"Marzo      | $"<<recaudaciones[2]<<"\n";
    cout<<"Abril      | $"<<recaudaciones[3]<<"\n";
    cout<<"Mayo       | $"<<recaudaciones[4]<<"\n";
    cout<<"Junio      | $"<<recaudaciones[5]<<"\n";
    cout<<"Julio      | $"<<recaudaciones[6]<<"\n";
    cout<<"Agosto     | $"<<recaudaciones[7]<<"\n";
    cout<<"Septiembre | $"<<recaudaciones[8]<<"\n";
    cout<<"Octubre    | $"<<recaudaciones[9]<<"\n";
    cout<<"Noviembre  | $"<<recaudaciones[10]<<"\n";
    cout<<"Diciembre  | $"<<recaudaciones[11]<<"\n";
}

void informe_propinas_percibidas() {
    ArchivoMozo aMozo;
    ArchivoServicio aServicio;
    int i, pos, cant_mozos=aMozo.contar_regs();
    int cant_servicios=aServicio.contar_regs();
    Mozo mozos[cant_mozos];
    Servicio servicios[cant_servicios];
    float propinas[cant_mozos];

    aMozo.listar_mozos(mozos, cant_mozos);
    ordenar_mozos_por_id(mozos, cant_mozos);
    aServicio.listar_servicios(servicios, cant_servicios);
    for (i=0; i<cant_mozos; i++) {
        propinas[i]=0;
    }

    for (i=0; i<cant_servicios; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        pos=buscar_id_mozo(mozos, cant_mozos, servicios[i].get_id_mozo());
        if (pos==-1) {  //esto no deberia ejecutarse ya que no puede haber servicios con
                        //mozos que no esten registrados. a lo sumo estaran dados de baja
            continue;
        }
        propinas[pos]+=servicios[i].get_propina();

    }


    cout<<"ID de mozo | Nombre y Apellido | Propinas percibidas\n";
    for (i=0; i<cant_mozos; i++) {
        if (!mozos[i].get_estado()) {
            continue;
        }
        cout<<mozos[i].get_id_mozo()<<" | "<<mozos[i].get_nombre()<<" "<<mozos[i].get_apellido()<<" | $"<<propinas[i]<<"\n";
    }
}
//Fin funciones para generar informes

void menu_generacion_datos() {
    ArchivoMesa aMesa;
    ArchivoMozo aMozo;
    ArchivoServicio aServicio;
    int datos_int[2];
    cout<<"Que archivo desea generar?\n1. Mesas\n2. Mozos\n3. Servicios\n";
    cin>>datos_int[0];
    cout<<"Cuantos desea generar?\n";
    cin>>datos_int[1];
    switch(datos_int[0]) {
    case 1:
        datos_int[0]=aMesa.generar_mesas(datos_int[1]);
        break;
    case 2:
        datos_int[0]=aMozo.generar_mozos(datos_int[1]);
        break;
    case 3:
        datos_int[0]=aServicio.generar_servicios(datos_int[1]);
        break;
    default:
        cout<<"\nComando invalido, volviendo al menu principal...\n";
        break;
    }
    if (!datos_int[0]) {
        cout<<"\nUno de los archivos no pudo ser accedido, volviendo al menu principal...\n";
    }
}
