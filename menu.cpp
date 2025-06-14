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

void comando_invalido() {
    cout<<"\nComando invalido, regresando al menu principal...\n";
}

void numero_invalido() {
    cout<<"\nNumero invalido, regresando al menu principal...\n";
}

void numero_debe_ser_mayor() {
    cout<<"\nEl numero mayor debe ser mayor al anterior, regresando al menu principal...\n";
}

void acceso_archivo_fallido() {
    cout<<"\nNo se pudo acceder al archivo, regresando al menu principal...\n";
}

int pedir_comando(const char * pedido, int cant_com, int * comando) {
    cout<<pedido;
    cin>>*comando;
    if (*comando<1 || *comando>cant_com) {
        comando_invalido();
        return 0;
    }
    return 1;
}

int pedir_int(const char * pedido, int cota_inf, int cota_sup, int * dato_int) {
    int buffer;
    cout<<pedido;
    cin>>buffer;
    if (buffer<cota_inf || buffer>cota_sup) {
        numero_invalido();
        return 0;
    }
    *dato_int=buffer;
    return 1;
}

int pedir_rango_int(const char * pedido, int * datos_int, int pos1, int pos2) {
    int buffer1, buffer2;
    cout<<pedido<<"\nNumero menor: ";
    cin>>buffer1;
    if (buffer1<1) {
        numero_invalido();
        return 0;
    }
    cout<<"\nNumero mayor: ";
    cin>>buffer2;
    if (buffer2<1) {
        numero_invalido();
        return 0;
    }
    if (buffer2<buffer1) {
        numero_debe_ser_mayor();
        return 0;
    }
    datos_int[pos1]=buffer1;
    datos_int[pos2]=buffer2;
    return 1;
}

int pedir_string(const char * pedido, string * dato_str, int tam_max, bool cin_antes, bool espacios) {
    string buffer;
    cout<<pedido;
    if (espacios) {
        if (cin_antes){vaciar_input();} //si cin fue accedido por el operador >> antes
        getline(cin, buffer);
    } else {
        cin>>buffer;
    }
    //length devuelve long long int, que es un entero gigante. se convierte a int
    //para que el compilador no grite. si por alguna razon mistica, el usuario ingresa
    //un string con mas de 2147483647 caracteres, el resultado seria reducido a dicho
    //numero
    if (int(buffer.length())>tam_max) {
        cout<<"\nHa ingresado demasiados caracteres, regresando al menu principal...\n";
        return 0;
    }
    if (int(buffer.length())==0) {
        cout<<"\nAlgo fallo pues no se registro input, regresando al menu principal...\n";
    }
    dato_str->erase(0, dato_str->npos);
    dato_str->append(buffer);
    return 1;
}

int pedir_float(const char * pedido, float cota_inf, float cota_sup, float * dato_float) {
    float buffer;
    cout<<pedido;
    cin>>buffer;
    if (buffer<cota_inf || buffer>cota_sup) {
        numero_invalido();
        return 0;
    }
    *dato_float=buffer;
    return 1;
}

int pedir_rango_float(const char * pedido, float * datos_float, int pos1, int pos2) {
    float buffer1, buffer2;
    cout<<pedido<<"\nNumero menor: ";
    cin>>buffer1;
    if (buffer1<1) {
        numero_invalido();
        return 0;
    }
    cout<<"\nNumero mayor: ";
    cin>>buffer2;
    if (buffer2<1) {
        numero_invalido();
        return 0;
    }
    if (buffer2<buffer1) {
        numero_debe_ser_mayor();
        return 0;
    }
    datos_float[pos1]=buffer1;
    datos_float[pos2]=buffer2;
    return 1;
}

int pedir_fecha(const char * pedido, Fecha * fecha, int anio1, int anio2) {
    int dia, mes, anio;
    cout<<pedido;
    if (!pedir_int("\nDia: ", 1, 31, &dia)) {return 0;}
    if (!pedir_int("Mes: ", 1, 12, &mes)) {return 0;}
    if (!pedir_int("Anio: ", anio1, anio2, &anio)) {return 0;}
    if (dia<1) {return 0;}
    switch (mes) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (dia>31) {
            cout<<"\nDia invalido en mes de 31 dias, regresando al menu principal...\n";
            return 0;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (dia>30) {
            cout<<"\nDia invalido en mes de 30 dias, regresando al menu principal...\n";
            return 0;
        }
        break;
    case 2:
        if (dia>28 && (dia!=29 || anio%4!=0 || (anio%100==0 && anio%400!=0))) {
            cout<<"\nDia invalido en febrero, regresando al menu principal...\n";
            return 0;
        }
        break;
    default:
        cout<<"\nMes invalido, regresando al menu principal...\n";
        return 0;
    }
    fecha->set_dia(dia);
    fecha->set_mes(mes);
    fecha->set_anio(anio);
    cout<<fecha->get_str();
    return 1;
}

int pedir_rango_fecha(const char * pedido, Fecha * fechas, int anio1, int anio2, int pos1, int pos2) {
    Fecha buffer1, buffer2;
    fechas[pos1].copiar(&buffer1);
    fechas[pos2].copiar(&buffer2);
    cout<<pedido;
    if (!pedir_fecha("\nFecha lejana.", &fechas[pos1], anio1, anio2)) {return 0;}
    if (!pedir_fecha("\nFecha reciente.", &fechas[pos2], anio1, anio2)) {
        buffer1.copiar(&fechas[pos1]);
        return 0;
    }
    if (fechas[pos2].comparar(fechas[pos1])<0) {
        cout<<"\nLa segunda fecha ingresada debe ser mas reciente que la segunda, regresando al menu principal...\n";
        buffer1.copiar(&fechas[pos1]);
        buffer2.copiar(&fechas[pos2]);
        return 0;
    }
    return 1;
}

void admin_listar_comandos() {
    imprimir_separador();
    cout<<"\nLista de comandos:";
    cout<<"\n1. Registrar";
    cout<<"\n2. Consultar";
    cout<<"\n3. Listar";
    cout<<"\n4. Generar informe";
    cout<<"\n5. Borrar o recuperar";
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
    pedir_comando("\nIngrese su eleccion:\n1. Registrar mesa\n2. Registrar mozo\n3. Registrar servicio\n", 3, &dato_int);
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
        comando_invalido();
        break;
    }
}

int menu_registrar_mesa() {
    ArchivoMesa archivo;
    int datos_int[3], pos, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return 0;
    }

    Mesa mesas[cant_regs];
    Mesa n_mesa;
    string dato_str;

    if (!pedir_int("\nIngrese numero de mesa: ", 1, 99999, &datos_int[0])){return 0;}
    if (!archivo.listar_mesas(mesas, cant_regs)){acceso_archivo_fallido();};
    pos=buscar_nro_mesa(mesas, cant_regs, datos_int[0]);
    if (pos!=-1) {
        if (mesas[pos].get_estado()) {
            cout<<"\nYa existe una mesa con este numero, regresando al menu principal...\n";
        } else {
            cout<<"\nYa existe una mesa con este numero que fue dada de baja, regresando al menu principal...\n";
        }
        return 0;
    }

    if (!pedir_int("\nIngrese cantidad de sillas: ", 1, 12, &datos_int[1])){return 0;}

    if (!pedir_comando("\nElija ubicacion:\n1. Interior\n2. Terraza\n", 2, &datos_int[2])){return 0;}

    if (!pedir_string("\nEscriba una descripcion de la mesa con no mas de 29 caracteres:\n", &dato_str, 29, true)){return 0;}

    n_mesa=Mesa(datos_int[0], datos_int[1], datos_int[2], dato_str);

    mostrar_mesa(&n_mesa, true);
    if (!pedir_comando("\nEsta es la mesa que desea registrar?\n1. Si\n2. No\n", 2, &datos_int[0])){return 0;}
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=archivo.registrar_mesa(&n_mesa);
    return datos_int[0];
}

int menu_registrar_mozo() {
    ArchivoMozo archivo;
    int datos_int[3], cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return 0;
    }

    Mozo mozos[cant_regs];
    Mozo n_mozo;
    string datos_str[4];
    Fecha dato_fecha;

    if (!pedir_int("\nIngrese ID del mozo: ", 1, 99999, &datos_int[2])) {return 0;}
    if (!archivo.listar_mozos(mozos, cant_regs)){acceso_archivo_fallido();};
    if (buscar_id_mozo(mozos, cant_regs, datos_int[5])!=-1) {
        cout<<"\nYa existe un mozo con este ID, regresando al menu principal...\n";
        return 0;
    }

    //una persona con DNI por debajo de 1 millon probablemente no este en condiciones de trabajar de mozo
    if (!pedir_int("\nIngrese DNI mayor a 1 millon: ", 1000000, 80000000, &datos_int[0])) {return 0;}

    if (!pedir_string("\nEscriba el nombre del mozo con no mas de 19 caracteres:\n", &datos_str[0], 19, true)) {return 0;}

    if (!pedir_string("\nEscriba el apellido del mozo con no mas de 29 caracteres:\n", &datos_str[1], 29, false)) {return 0;}

    if (!pedir_string("\nEscriba el numero de telefono del mozo con no mas de 19 caracteres:\n", &datos_str[2], 19, false)) {return 0;}

    if (!pedir_string("\nEscriba el email del mozo con no mas de 49 caracteres:\n", &datos_str[3], 49, false)) {return 0;}

    if (!pedir_fecha("\nIngrese fecha de nacimiento del mozo en numeros.", &dato_fecha, 1900, 2025)) {return 0;}

    if (!pedir_comando("\nIngrese turno del mozo.\n1. Maniana\n2. Tarde\n3. Noche\n", 3, &datos_int[1])) {return 0;}

    n_mozo=Mozo(datos_int[0], datos_str[0], datos_str[1], datos_str[2], datos_str[3], dato_fecha, datos_int[1], datos_int[2]);

    mostrar_mozo(&n_mozo, true);
    if (!pedir_comando("\nEste es el mozo que desea registrar?\n1. Si\n2. No\n", 2, &datos_int[0])) {return 0;}
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=archivo.registrar_mozo(&n_mozo);
    return datos_int[0];
}

int menu_registrar_servicio() {
    ArchivoServicio pServicios;
    ArchivoMesa pMesas;
    ArchivoMozo pMozos;
    int datos_int[3], pos, cant_servicios=pServicios.contar_regs();

    if (!cant_servicios) {
        acceso_archivo_fallido();
        return 0;
    }

    int cant_mesas=pMesas.contar_regs();

    if (!cant_mesas) {
        acceso_archivo_fallido();
        return 0;
    }

    int cant_mozos=pMozos.contar_regs();

    if (!cant_mozos) {
        acceso_archivo_fallido();
        return 0;
    }

    Servicio servicios[cant_servicios];
    Mesa mesas[cant_mesas];
    Mozo mozos[cant_mozos];
    Servicio n_servicio;
    Fecha dato_fecha;
    float datos_float[2];

    if (!pedir_int("\nIngrese numero de factura: ", 1, 9999999, &datos_int[0])) {return 0;}
    if (!pServicios.listar_servicios(servicios, cant_servicios)){acceso_archivo_fallido();};
    if (buscar_nro_factura(servicios, cant_servicios, datos_int[0])!=-1) {
        cout<<"\nYa existe un servicio con este numero, regresando al menu principal...\n";
        return 0;
    }

    if (!pedir_int("\nIngrese numero de mesa: ", 1, 99999, &datos_int[1])) {return 0;}
    if (!pMesas.listar_mesas(mesas, cant_mesas)){acceso_archivo_fallido();};
    pos=buscar_nro_mesa(mesas, cant_mesas, datos_int[1]);
    if (pos==-1) {
        cout<<"\nEsta mesa no esta registrada, regresando al menu principal...\n";
        return 0;
    }
    if (!mesas[pos].get_estado()) {
        if (!pedir_comando("\nEsta mesa fue dada de baja. Registrar de todos modos?\n1. Si\n2. No\n", 2, &pos)){return 0;}
        if (pos==2) {
            cout<<"\nAbortando operacion...\n";
            return 0;
        }
    }

    if (!pedir_int("\nIngrese ID de mozo: ", 1, 99999, &datos_int[2])) {return 0;}
    if (!pMozos.listar_mozos(mozos, cant_mozos)){acceso_archivo_fallido();};
    pos=buscar_id_mozo(mozos, cant_mozos, datos_int[2]);
    if (pos==-1) {
        cout<<"\nEste mozo no esta registrado, regresando al menu principal...\n";
        return 0;
    }
    if (!mozos[pos].get_estado()) {
        if (!pedir_comando("\nEste mozo fue dado de baja. Registrar de todos modos?\n1. Si\n2. No\n", 2, &pos)){return 0;}
        if (pos==2) {
            cout<<"\nAbortando operacion...\n";
            return 0;
        }
    }

    if (!pedir_fecha("\nIngrese fecha del servicio en numeros.", &dato_fecha, 2000, 2025)) {return 0;}

    //supongo que 10 millones es un techo razonable para gastarse en comida con 12 personas
    if (!pedir_float("\nIngrese importe del servicio, utilizando punto para marcar decimales: ", 1, 10000000, &datos_float[0])) {return 0;}

    if (!pedir_float("\nIngrese monto abonado por el cliente, utilizando punto para marcar decimales: ", 1, 10000000, &datos_float[1])) {return 0;}

    if (datos_float[0]>datos_float[1]) {
        cout<<"\nEl monto abonado no puede ser menor que el importe del servicio, regresando al menu principal...\n";
        return 0;
    }

    n_servicio=Servicio(datos_int[0], datos_int[1], datos_int[2], dato_fecha, datos_float[0], datos_float[1]);
    mostrar_servicio(&n_servicio, true);
    cout<<"\nEste es el servicio que desea registrar?\n1. Si\n2. No\n";
    cin>>datos_int[0];
    if (datos_int[0]==2) {
        return 0;
    }

    datos_int[0]=pServicios.registrar_servicio(&n_servicio);
    return datos_int[0];
}
//Fin funciones para registrar datos

//Comienzo funciones para consultar base de datos
void admin_menu_consultar() {
    int dato_int;
    pedir_comando("\nQue archivo desea consultar?\n1. Mesas\n2. Mozos\n3. Servicios\n", 3, &dato_int);
    switch(dato_int) {
    case 1:
        menu_consultar_mesas();
        break;
    case 2:
        menu_consultar_mozos();
        break;
    case 3:
        menu_consultar_servicios();
        break;
    default:
        comando_invalido();
        break;
    }

}

void menu_consultar_mesas() {
    ArchivoMesa archivo;
    int i, mesas_encontradas=0, datos_int[3], cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    Mesa mesas[cant_regs];

    pedir_comando("Que tipo de consulta desea realizar?\n1. Por numero de mesa\n2. Por cantidad de sillas\n3. Por ubicacion y cantidad de sillas\n",
                  3, &datos_int[0]);
    switch(datos_int[0]) {
    case 1:
        if (!pedir_rango_int("\nIndique el rango de numeros de mesa. Si solo quiere buscar una mesa, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {
            return;
        }
        datos_int[0]=archivo.consultar_mesas(mesas, cant_regs, 1, datos_int[1], datos_int[2]);
        ordenar_mesas_por_nro(mesas, cant_regs);
        break;
    case 2:
        if (!pedir_rango_int("\nIndique el rango de cantidad de sillas. Si solo quiere buscar por una cantidad especifica, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {
            return;
        }
        datos_int[0]=archivo.consultar_mesas(mesas, cant_regs, 2, datos_int[1], datos_int[2]);
        ordenar_mesas_por_can_sillas(mesas, cant_regs);
        break;
    case 3:
        if (!pedir_comando("\nIndique la ubicacion.\n1. Interior\n2. Terraza\n", 2, &datos_int[0])) {
            return;
        }
        if (!pedir_rango_int("\nIndique el rango de cantidad de sillas. Si solo quiere buscar por una cantidad especifica, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {
            return;
        }
        datos_int[0]=archivo.consultar_mesas(mesas, cant_regs, 3, datos_int[1], datos_int[2], datos_int[0]);
        ordenar_mesas_por_can_sillas(mesas, cant_regs);
        break;
    default:
        comando_invalido();
        break;
    }

    if (!datos_int[0]) {
        acceso_archivo_fallido();
        return;
    }

    for (i=0; i<cant_regs; i++) {
        mostrar_mesa(&mesas[i], true);
        if (mesas[i].get_estado()) {
            mesas_encontradas++;
        }
    }
    if (mesas_encontradas!=1) {
        cout<<"\nSe encontraron "<<mesas_encontradas<<" mesas\n";
    } else {
        cout<<"\nSe encontro "<<mesas_encontradas<<" mesa\n";
    }
}

void menu_consultar_mozos() {
    ArchivoMozo archivo;
    int i, mozos_encontrados=0, datos_int[3], cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    string datos_str[2];
    Mozo mozos[cant_regs];

    pedir_comando("Que tipo de consulta desea realizar?\n1. Por ID de mozo\n2. Por nombre y/o apellido\n3. Por turno\n",
                  3, &datos_int[0]);
    switch(datos_int[0]) {
    case 1:
        if (!pedir_rango_int("\nIndique el rango de IDs de mozo. Si solo quiere buscar un mozo, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {
            return;
        }
        datos_int[0]=archivo.consultar_mozos(mozos, cant_regs, 1, datos_int[1], datos_int[2]);
        ordenar_mozos_por_id(mozos, cant_regs);
        break;
    case 2:
        pedir_comando("\nIndique que desea buscar. Note que debe escribir el nombre y/o apellido exacto.\n1. Nombre\n2. Apellido\n3. Nombre y apellido\n",
                      3, &datos_int[1]);
        switch(datos_int[1]) {
        case 1:
            cout<<"Nombre: ";
            cin>>datos_str[0];
            datos_int[0]=archivo.consultar_mozos(mozos, cant_regs, 1, datos_str[0]);
            break;
        case 2:
            cout<<"Apellido: ";
            cin>>datos_str[0];
            datos_int[0]=archivo.consultar_mozos(mozos, cant_regs, 2, datos_str[0]);
            break;
        case 3:
            cout<<"Nombre: ";
            cin>>datos_str[1];
            cout<<"Apellido: ";
            cin>>datos_str[2];
            datos_int[0]=archivo.consultar_mozos(mozos, cant_regs, 3, datos_str[0], datos_str[1]);
            break;
        default:
            comando_invalido();
            return;
        }
        break;
    case 3:
        pedir_comando("\nIndique el turno.\n1. Maniana\n2. Tarde\n3. Noche\n", 3, &datos_int[1]);
        datos_int[0]=archivo.consultar_mozos(mozos, cant_regs, 2, datos_int[1], datos_int[1]);
        ordenar_mozos_por_turno_id(mozos, cant_regs);
        break;
    default:
        comando_invalido();
        break;
    }

    if (!datos_int[0]) {
        acceso_archivo_fallido();
        return;
    }

    for (i=0; i<cant_regs; i++) {
        mostrar_mozo(&mozos[i], true);
        if (mozos[i].get_estado()) {
            mozos_encontrados++;
        }
    }
    if (mozos_encontrados!=1) {
        cout<<"\nSe encontraron "<<mozos_encontrados<<" mozos\n";
    } else {
        cout<<"\nSe encontro "<<mozos_encontrados<<" mozo\n";
    }
}

void menu_consultar_servicios() {
    ArchivoServicio archivo;
    int i, servicios_encontrados=0, datos_int[3], cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    float datos_float[2];
    Fecha datos_fecha[2];
    Servicio servicios[cant_regs];

    cout<<"Que tipo de consulta desea realizar?\n1. Por numero de factura\n2. Por numero de mesa\n3. Por ID de mozo\n4. Por fecha de servicio\n5. Por importe de servicio\n6. Por monto abonado\n";
    cin>>datos_int[0];
    switch(datos_int[0]) {
    case 1:
        if (!pedir_rango_int("\nIndique el rango de numeros de factura. Si solo quiere buscar un servicio, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 1, datos_int[1], datos_int[2]);
        ordenar_servicios_por_nro_factura(servicios, cant_regs);
        break;
    case 2:
        if (!pedir_rango_int("\nIndique el rango de numeros de mesa. Si solo quiere buscar por un numero, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 2, datos_int[1], datos_int[2]);
        ordenar_servicios_por_nro_mesa(servicios, cant_regs);
        break;
    case 3:
        if (!pedir_rango_int("\nIndique el rango de IDs de mozo. Si solo quiere buscar por un ID, escriba dos veces el mismo numero.",
                         datos_int, 1, 2)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 3, datos_int[1], datos_int[2]);
        ordenar_servicios_por_id_mozo(servicios, cant_regs);
        break;
    case 4:
        if (!pedir_rango_fecha("\nIndique el rango de fechas. Si solo quiere buscar un dia especifico, escriba dos veces la misma fecha.\n",
                               datos_fecha, 2000, 2025, 0, 1)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 4, datos_fecha[0], datos_fecha[1]);
        ordenar_servicios_por_fecha_serv(servicios, cant_regs);
        break;
    case 5:
        if (!pedir_rango_float("\nIndique el rango de importes. Si solo quiere buscar por un importe especifico, escriba dos veces el mismo numero.",
                         datos_float, 0, 1)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 5, datos_float[0], datos_float[1]);
        ordenar_servicios_por_importe_serv(servicios, cant_regs);
        break;
    case 6:
        if (!pedir_rango_float("\nIndique el rango de montos. Si solo quiere buscar por un monto especifico, escriba dos veces el mismo numero.",
                         datos_float, 0, 1)) {return;}
        datos_int[0]=archivo.consultar_servicios(servicios, cant_regs, 6, datos_float[0], datos_float[1]);
        ordenar_servicios_por_monto_abon(servicios, cant_regs);
        break;
    default:
        comando_invalido();
        break;
    }

    if (!datos_int[0]) {
        acceso_archivo_fallido();
        return;
    }

    for (i=0; i<cant_regs; i++) {
        mostrar_servicio(&servicios[i], true);
        if (servicios[i].get_estado()) {
            servicios_encontrados++;
        }
    }
    if (servicios_encontrados!=1) {
        cout<<"\nSe encontraron "<<servicios_encontrados<<" servicios\n";
    } else {
        cout<<"\nSe encontro "<<servicios_encontrados<<" servicio\n";
    }
}
//Fin funciones para consultar base de datos

//Comienzo funciones para listar datos
void admin_menu_listar() {
    int dato_int;
    pedir_comando("\nIngrese su eleccion:\n1. Listar mesas\n2. Listar mozos\n3. Listar servicios\n", 3, &dato_int);
    switch(dato_int) {
    case 1:
        menu_listar_mesas();
        break;
    case 2:
        menu_listar_mozos();
        break;
    case 3:
        menu_listar_servicios();
        break;
    default:
        comando_invalido();
        break;
    }
}

void menu_listar_mesas() {
    ArchivoMesa archivo;
    int i, orden, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    bool ignorar_borrado=true;
    Mesa mesas[cant_regs];

    pedir_comando("Como deben estar ordenadas las mesas?\n1. Por numero de mesa\n2. Por cantidad de sillas\n3. Por ubicacion y numero de mesa\n4. Listar mesas dadas de baja\n", 4, &orden);

    if (!cant_regs || !archivo.listar_mesas(mesas, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

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

void menu_listar_mozos() {
    ArchivoMozo archivo;
    int i, orden, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    bool ignorar_borrado=true;
    Mozo mozos[cant_regs];

    pedir_comando("Como deben estar ordenadas los mozos?\n1. Por ID de mozo\n2. Alfabeticamente por nombre\n3. Alfabeticamente por apellido\n4. Por fecha de nacimiento\n5. Por turno e ID de mozo\n6. Listar mozos dados de baja\n", 6, &orden);

    if (!cant_regs || !archivo.listar_mozos(mozos, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

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

void menu_listar_servicios() {
    ArchivoServicio archivo;
    int i, orden, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    bool ignorar_borrado=true;
    Servicio servicios[cant_regs];

    pedir_comando("Como deben estar ordenados los servicios?\n1. Por numero de factura\n2. Por numero de mesa\n3. Por ID de mozo\n4. Por fecha de servicio\n5. Por importe de servicio\n6. Listar servicios dados de baja\n", 6, &orden);

    if (!archivo.listar_servicios(servicios, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

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
    pedir_comando("\nQue tipo de informe desea generar?\n1. Recaudacion anual\n2. Recaudacion por mozo\n3. Recaudacion por mesa\n4. Recaudacion mensual\n5. Propinas percibidas por cada mozo\n", 5, &dato_int);
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
        comando_invalido();
        break;
    }
}

void informe_recaudacion_anual() {
    ArchivoServicio archivo;
    int i, pos, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    Servicio servicios[cant_regs];
    int anios[30];
    float recaudaciones[30];

    for (i=0; i<30; i++) {
        anios[i]=0;
        recaudaciones[i]=0;
    }

    if (!archivo.listar_servicios(servicios, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

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

    if (!cant_mozos) {
        acceso_archivo_fallido();
        return;
    }

    int cant_servicios=aServicio.contar_regs();

    if (!cant_servicios) {
        acceso_archivo_fallido();
        return;
    }

    Mozo mozos[cant_mozos];
    Servicio servicios[cant_servicios];
    float recaudaciones[cant_mozos];

    aMozo.listar_mozos(mozos, cant_mozos);
    ordenar_mozos_por_id(mozos, cant_mozos);

    if (!aServicio.listar_servicios(servicios, cant_servicios)) {
        acceso_archivo_fallido();
        return;
    }
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

    if (!cant_mesas) {
        acceso_archivo_fallido();
        return;
    }

    int cant_servicios=aServicio.contar_regs();

    if (!cant_servicios) {
        acceso_archivo_fallido();
        return;
    }

    Mesa mesas[cant_mesas];
    Servicio servicios[cant_servicios];
    float recaudaciones[cant_mesas];

    if (aMesa.listar_mesas(mesas, cant_mesas)) {
        acceso_archivo_fallido();
        return;
    }

    ordenar_mesas_por_nro(mesas, cant_mesas);

    if (!cant_servicios || !aServicio.listar_servicios(servicios, cant_servicios)) {
        acceso_archivo_fallido();
        return;
    }

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

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

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

    if (!archivo.listar_servicios(servicios, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    for (i=0; i<cant_regs; i++) {
        if (!servicios[i].get_estado()) {
            continue;
        }
        if (anio==servicios[i].get_fecha_serv().get_anio()) {
            recaudaciones[servicios[i].get_fecha_serv().get_mes()-1]+=servicios[i].get_importe_serv();
        }
    }

    cout<<"ANIO "<<anio<<"\n";
    cout<<"MES        | Recaudacion\n";
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

    if (!cant_mozos) {
        acceso_archivo_fallido();
        return;
    }

    int cant_servicios=aServicio.contar_regs();

    if (!cant_servicios) {
        acceso_archivo_fallido();
        return;
    }

    Mozo mozos[cant_mozos];
    Servicio servicios[cant_servicios];
    float propinas[cant_mozos];

    if (!aMozo.listar_mozos(mozos, cant_mozos)) {
        acceso_archivo_fallido();
        return;
    }

    ordenar_mozos_por_id(mozos, cant_mozos);

    if (!aServicio.listar_servicios(servicios, cant_servicios)) {
        acceso_archivo_fallido();
        return;
    }

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

//Comienzo funciones para borrar
void admin_menu_borrar_recuperar() {
    int dato_int;
    pedir_comando("\nQue tipo de dato desea borrar?\n1. Mesa\n2. Mozo\n3. Servicio\n", 3, &dato_int);
    switch (dato_int) {
    case 1:
        menu_borrar_recuperar_mesa();
        break;
    case 2:
        menu_borrar_recuperar_mozo();
        break;
    case 3:
        menu_borrar_recuperar_servicio();
        break;
    default:
        comando_invalido();
        return;
    }
}

void menu_borrar_recuperar_mesa() {
    ArchivoMesa archivo;
    int dato_int, pos, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    Mesa mesas[cant_regs];

    if (!archivo.listar_mesas(mesas, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    if (!pedir_int("\nIngrese el numero de mesa que desea borrar: ", 1, cant_regs, &dato_int)) {return;}

    pos=buscar_nro_mesa(mesas, cant_regs, dato_int);

    if (pos==-1) {
        cout<<"\nNo hay una mesa habilitada con ese numero.";
        return;
    }

    mostrar_mesa(&mesas[pos], false);
    if (!mesas[pos].get_estado()) {
        pedir_comando("\nLa mesa indicada ya fue dada de baja. Desea habilitarla de nuevo?\n1. Si\n2. No\n", 2, &dato_int);
        if (dato_int==1) {
            cout<<"\nHabilitando mesa...\n";
            mesas[pos].set_estado(true);
            archivo.guardar_mesas(mesas, cant_regs);
        } else if (dato_int==2) {
            cout<<"\nAbortando operacion de habilitacion...\n";
        }
        return;
    }

    pedir_comando("\nEsta es la mesa que desea dar de baja?\n1. Si\n2. No\n", 2, &dato_int);
    if (dato_int==1) {
        cout<<"\nDando de baja la mesa indicada...\n";
        mesas[pos].set_estado(false);
        archivo.guardar_mesas(mesas, cant_regs);
    } else if (dato_int==2) {
        cout<<"\nAbortando operacion de borrado...\n";
    }
}

void menu_borrar_recuperar_mozo() {
    ArchivoMozo archivo;
    int dato_int, pos, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    Mozo mozos[cant_regs];

    if (!archivo.listar_mozos(mozos, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    if (!pedir_int("\nIngrese el ID de mozo que desea borrar: ", 1, cant_regs, &dato_int)) {return;}

    pos=buscar_id_mozo(mozos, cant_regs, dato_int);

    if (pos==-1) {
        cout<<"\nNo hay un mozo habilitado con ese ID.";
        return;
    }

    mostrar_mozo(&mozos[pos], false);
    if (!mozos[pos].get_estado()) {
        pedir_comando("\nEl mozo indicado ya fue dado de baja. Desea habilitarlo de nuevo?\n1. Si\n2. No\n", 2, &dato_int);
        if (dato_int==1) {
                cout<<"\nHabilitando mozo...\n";
            mozos[pos].set_estado(true);
            archivo.guardar_mozos(mozos, cant_regs);
        } else if (dato_int==2) {
            cout<<"\nAbortando operacion de habilitacion...\n";
        }
        return;
    }

    pedir_comando("\nEste es el mozo que desea dar de baja?\n1. Si\n2. No\n", 2, &dato_int);
    if (dato_int==1) {
        cout<<"\nDando de baja el mozo indicado...\n";
        mozos[pos].set_estado(false);
        archivo.guardar_mozos(mozos, cant_regs);
    } else if (dato_int==2) {
        cout<<"\nAbortando operacion de borrado...\n";
    }
}

void menu_borrar_recuperar_servicio() {
    ArchivoServicio archivo;
    int dato_int, pos, cant_regs=archivo.contar_regs();

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    Servicio servicios[cant_regs];

    if (!archivo.listar_servicios(servicios, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    if (!pedir_int("\nIngrese el numero de factura del servicio que desea borrar: ", 1, cant_regs, &dato_int)) {return;}

    pos=buscar_nro_factura(servicios, cant_regs, dato_int);

    if (pos==-1) {
        cout<<"\nNo hay un servicio habilitado con ese numero de factura.";
        return;
    }

    mostrar_servicio(&servicios[pos], false);
    if (!servicios[pos].get_estado()) {
        pedir_comando("\nEl servicio indicado ya fue dado de baja. Desea habilitarlo de nuevo?\n1. Si\n2. No\n", 2, &dato_int);
        if (dato_int==1) {
                cout<<"\nHabilitando servicio...\n";
            servicios[pos].set_estado(true);
            archivo.guardar_servicios(servicios, cant_regs);
        } else if (dato_int==2) {
            cout<<"\nAbortando operacion de habilitacion...\n";
        }
        return;
    }

    pedir_comando("\nEste es el servicio que desea dar de baja?\n1. Si\n2. No\n", 2, &dato_int);
    if (dato_int==1) {
        cout<<"\nDando de baja el servicio indicado...\n";
        servicios[pos].set_estado(false);
        archivo.guardar_servicios(servicios, cant_regs);
    } else if (dato_int==2) {
        cout<<"\nAbortando operacion de borrado...\n";
    }
}
//Fin funciones para borrar

//Comienzo funciones para modificar
void admin_menu_modificar() {
    int dato_int;

    pedir_comando("\nQue tipo de registro desea modificar?\n1. Mesa\n2. Mozo\n3. Servicio\n", 3, &dato_int);
    switch (dato_int) {
    case 1:
        menu_modificar_mesa();
        break;
    case 2:
        menu_modificar_mozo();
        break;
    case 3:
        menu_modificar_servicio();
        break;
    default:
        break;
    }
}

void menu_modificar_mesa() {
    ArchivoMesa archivo;
    int dato_int, cant_regs=archivo.contar_regs();
    int tpos, pos=-1;

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    string dato_str;
    bool control=true;
    bool cin_antes=true;
    Mesa mesas[cant_regs];

    if (!archivo.listar_mesas(mesas, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    while (control) {
        if (pos==-1) {
            if(!pedir_int("\nIngrese el numero de la mesa que desea modificar: ", 1, 99999, &dato_int)){return;}
            pos=buscar_nro_mesa(mesas, cant_regs, dato_int);
        }
        if (pos==-1 || !mesas[pos].get_estado()) {
            cout<<"\nNo se ha encontrado la mesa especificada.\n";
            pos=-1;
            imprimir_separador();
            continue;
        } else {
            mostrar_mesa(&mesas[pos], true);
        }

        if (!pedir_comando("\nQue atributo desea modificar?\n1. Numero de mesa\n2. Cantidad de sillas\n3. Ubicacion\n4. Descripcion\n5. Modificar otra mesa\n6. Guardar y salir\n", 6, &dato_int)){return;}

        switch (dato_int) {
        case 1:
            if (!pedir_int("\nIngrese el nuevo numero de mesa: ", 1, 99999, &dato_int)){return;}
            cin_antes=true;
            tpos=buscar_nro_mesa(mesas, cant_regs, dato_int);
            if (tpos!=-1) {
                if (mesas[tpos].get_estado()) {
                    cout<<"\nYa existe una mesa con el numero especificado. Elija otro numero.\n";
                } else {
                    cout<<"\nYa existe una mesa con el numero especificado, aunque fue dada de baja. Elija otro numero\n";
                }
            } else {
                mesas[pos].set_nro_mesa(dato_int);
            }
            break;
        case 2:
            if (!pedir_int("\nIngrese la nueva cantidad de sillas: ", 1, 12, &dato_int)) {return;}
            cin_antes=true;
            mesas[pos].set_can_sillas(dato_int);
            break;
        case 3:
            if (!pedir_comando("\nIngrese la nueva ubicacion\n1. Interior\n2. Terraza\n", 2, &dato_int)) {return;}
            cin_antes=true;
            mesas[pos].set_ubic(dato_int);
            break;
        case 4:
            if (!pedir_string("\nIngrese la nueva descripcion con no mas de 29 caracteres\n", &dato_str, 29, cin_antes, true)) {return;}
            cin_antes=false;
            mesas[pos].set_desc(dato_str);
            break;
        case 5:
            pos=-1;
            break;
        case 6:
            archivo.guardar_mesas(mesas, cant_regs);
            control=false;
            break;
        default:
            control=false;
            break;
        }
        imprimir_separador();
    }
}

void menu_modificar_mozo() {
    ArchivoMozo archivo;
    int dato_int, cant_regs=archivo.contar_regs();
    int tpos, pos=-1;

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    string dato_str;
    bool control=true;
    bool cin_antes=true;
    Mozo mozos[cant_regs];

    if (!archivo.listar_mozos(mozos, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    while (control) {
        if (pos==-1) {
            if(!pedir_int("\nIngrese el ID del mozo que desea modificar: ", 1, 99999, &dato_int)){return;}
            pos=buscar_id_mozo(mozos, cant_regs, dato_int);
        }
        if (pos==-1 || !mozos[pos].get_estado()) {
            cout<<"\nNo se ha encontrado el mozo especificado.\n";
            pos=-1;
            imprimir_separador();
            continue;
        } else {
            mostrar_mozo(&mozos[pos], true);
        }

        if (!pedir_comando("\nQue atributo desea modificar?\n1. ID de mozo\n2. DNI\n3. Turno\n4. Nombre\n5. Apellido\n6. Numero de telefono\n7. Email\n8. Modificar otra mozo\n9. Guardar y salir\n", 9, &dato_int)){return;}

        switch (dato_int) {
        case 1:
            if (!pedir_int("\nIngrese el nuevo ID de mozo: ", 1, 99999, &dato_int)){return;}
            cin_antes=true;
            tpos=buscar_id_mozo(mozos, cant_regs, dato_int);
            if (tpos!=-1) {
                if (mozos[tpos].get_estado()) {
                    cout<<"\nYa existe un mozo con el ID especificado. Elija otro ID.\n";
                } else {
                    cout<<"\nYa existe un mozo con el ID especificado, aunque fue dado de baja. Elija otro ID\n";
                }
            } else {
                mozos[pos].set_id_mozo(dato_int);
            }
            break;
        case 2:
            if (!pedir_int("\nIngrese el nuevo DNI: ", 1000000, 80000000, &dato_int)) {return;}
            cin_antes=true;
            mozos[pos].set_dni(dato_int);
            break;
        case 3:
            if (!pedir_comando("\nIngrese el nuevo turno\n1. Maniana\n2. Tarde\n3. Noche\n", 3, &dato_int)) {return;}
            cin_antes=true;
            mozos[pos].set_turno(dato_int);
            break;
        case 4:
            if (!pedir_string("\nIngrese el nuevo nombre con no mas de 19 caracteres\n", &dato_str, 19, cin_antes, true)) {return;}
            cin_antes=false;
            mozos[pos].set_nombre(dato_str);
            break;
        case 5:
            if (!pedir_string("\nIngrese el nuevo apellido con no mas de 29 caracteres\n", &dato_str, 29, cin_antes, true)) {return;}
            cin_antes=false;
            mozos[pos].set_apellido(dato_str);
            break;
        case 6:
            if (!pedir_string("\nIngrese el nuevo numero de telefono con no mas de 19 caracteres\n", &dato_str, 19, cin_antes, true)) {return;}
            cin_antes=false;
            mozos[pos].set_nombre(dato_str);
            break;
        case 7:
            if (!pedir_string("\nIngrese el nuevo email con no mas de 49 caracteres\n", &dato_str, 19, cin_antes, true)) {return;}
            cin_antes=false;
            mozos[pos].set_nombre(dato_str);
            break;
        case 8:
            pos=-1;
            break;
        case 9:
            archivo.guardar_mozos(mozos, cant_regs);
            control=false;
            break;
        default:
            control=false;
            break;
        }
        imprimir_separador();
    }
}

void menu_modificar_servicio() {
    ArchivoServicio archivo;
    int dato_int, cant_regs=archivo.contar_regs();
    int tpos, pos=-1;

    if (!cant_regs) {
        acceso_archivo_fallido();
        return;
    }

    float dato_float;
    bool control=true;
    bool cin_antes=true;
    Servicio servicios[cant_regs];

    if (!archivo.listar_servicios(servicios, cant_regs)) {
        acceso_archivo_fallido();
        return;
    }

    while (control) {
        if (pos==-1) {
            if(!pedir_int("\nIngrese el numero de factura del servicio que desea modificar: ", 1, 999999, &dato_int)){return;}
            pos=buscar_nro_mesa(mesas, cant_regs, dato_int);
        }
        if (pos==-1 || !mesas[pos].get_estado()) {
            cout<<"\nNo se ha encontrado la mesa especificada.\n";
            pos=-1;
            imprimir_separador();
            continue;
        } else {
            mostrar_mesa(&mesas[pos], true);
        }

        if (!pedir_comando("\nQue atributo desea modificar?\n1. Numero de factura\n2. Numero de mesa\n3. ID de mozo\n4. Fecha\n5. Importe de servicio\n6. Monto abonado\n7. Modificar otro servicio\n8. Guardar y salir\n", 8, &dato_int)){return;}

        switch (dato_int) {
        case 1:
            if (!pedir_int("\nIngrese el nuevo numero de factura: ", 1, 9999999, &dato_int)){return;}
            cin_antes=true;
            tpos=buscar_nro_factura(servicios, cant_regs, dato_int);
            if (tpos!=-1) {
                if (mesas[tpos].get_estado()) {
                    cout<<"\nYa existe un servicio con el numero especificado. Elija otro numero.\n";
                } else {
                    cout<<"\nYa existe un servicio con el numero especificado, aunque fue dado de baja. Elija otro numero\n";
                }
            } else {
                mesas[pos].set_nro_mesa(dato_int);
            }
            break;
        case 2:
            if (!pedir_int("\nIngrese la nueva cantidad de sillas: ", 1, 12, &dato_int)) {return;}
            cin_antes=true;
            mesas[pos].set_can_sillas(dato_int);
            break;
        case 3:
            if (!pedir_comando("\nIngrese la nueva ubicacion\n1. Interior\n2. Terraza\n", 2, &dato_int)) {return;}
            cin_antes=true;
            mesas[pos].set_ubic(dato_int);
            break;
        case 4:
            if (!pedir_string("\nIngrese la nueva descripcion con no mas de 29 caracteres\n", &dato_str, 29, cin_antes, true)) {return;}
            cin_antes=false;
            mesas[pos].set_desc(dato_str);
            break;
        case 7:
            pos=-1;
            break;
        case 8:
            archivo.guardar_mesas(mesas, cant_regs);
            control=false;
            break;
        default:
            control=false;
            break;
        }
        imprimir_separador();
    }
}
//Fin funciones para modificar

void menu_generacion_datos() {
    ArchivoMesa aMesa;
    ArchivoMozo aMozo;
    ArchivoServicio aServicio;
    int datos_int[2];
    if (!pedir_comando("Que archivo desea generar? Recuerde que la generacion de servicios depende de la existencia de datos para mesas y mozos.\n1. Mesas\n2. Mozos\n3. Servicios\n",
                       3, &datos_int[0])) {
        return;
    }

    if (!pedir_int("Cuantos desea generar?\n", 1, 99999, &datos_int[1])) {return;}

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
        comando_invalido();
        break;
    }
    if (!datos_int[0]) {
        cout<<"\nUno de los archivos no pudo ser accedido, volviendo al menu principal...\n";
    }
}
