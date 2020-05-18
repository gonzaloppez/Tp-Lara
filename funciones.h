#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

struct platos
{
    int id;
    char nombre[50];
    float costo;
    float precio;
    int tiempoPreparacion;
    int idRestaurante;
    int comision;
    int idCategoria;
    bool estado;
};

struct fecha
{
    int dia, mes,anio;
};

struct clientes
{
    int id;
    char apellidos[50];
    char nombres[50];
    char mail[50];
    char domicilio[100];
    int cp;
    fecha fec;
    bool estado;
};

struct pedidos
{
    int id;
    int idCliente;
    int idPlato;
    int cantidad;
    int precioU;
    fecha fec;
    float valoracion;
    int estado;
};


platos leer_platos(int pos)
{
    platos reg;
    FILE *p;
    p = fopen("archivos.dat","rb");
        if(p==NULL)
        {
            reg.id=-1;
            return reg;
        }
    fseek(p,pos * sizeof(platos),SEEK_SET);
    fread(&reg, sizeof(platos),1,p);
    fclose(p);
    return reg;
}

void listarPlatos(platos reg)
{

    if(reg.estado==true)
    {

    cout<<"ID: "<<reg.id<<endl;
    cout<<"nombre: "<<reg.nombre<<endl;
    cout<<"costo: "<<reg.costo<<endl;
    cout<<"precio: "<<reg.precio<<endl;
    cout<<"tiempo: "<<reg.tiempoPreparacion<<endl;
    cout<<"ID Restaurante: "<<reg.idRestaurante<<endl;
    cout<<"Comision: "<<reg.idRestaurante<<endl;
    cout<<"categoria: "<<reg.idCategoria<<endl;

    }
}

int listarPlato(platos reg)
{
    FILE *p;
    p = fopen("archivos.dat","rb");
    if (p==NULL)
        {
            cout<<"No se pudo abrir archivo"<<endl;
            return 1;
        }
    while(fread(&reg,sizeof(platos),1,p)==1)
    {
        cout<<endl;
        listarPlatos(reg);
    }
    fclose(p);
    return 0;
}

int buscarId(int idBuscado)
{
    platos reg;
    int i=0;
    FILE *p;
    p = fopen("archivos.dat","rb");
    if (p==NULL)
        {
            cout<<"No se pudo abrir archivo";
            return -2;
        }
        while(fread(&reg,sizeof(platos),1,p))
        {

        if (idBuscado == reg.id)
        {
        fclose(p);
        return i;
        }
    i++;
    }
    fclose(p);
    return -1;
}


bool cargarPlatos(struct platos *reg)
{

    int i;
    system("cls");
    setColor(RED);
    cout<<"*//////////////////////////////////////////////////*"<<endl;
    cout<<"*              CARGAR NUEVO PRODUCTO               *"<<endl;
    cout<<"*//////////////////////////////////////////////////*"<<endl;
    cout<<endl;
    setColor(LIGHTGREEN);
    cout<<"ID: ";
    cin>>reg->id;
     if(reg->id<0)
     {
         cout<<"El ID no puede ser negativo!";
         system("pause");
         return false;
     }
    i = buscarId(reg->id);
        if(i>=0)
        {
            cout<<"El ID esta duplicado"<<endl;
            system("pause");
            return false;
        }

    cout<<"NOMBRE: ";
    cin.ignore();
    cin.getline(reg->nombre,50);
    if (reg->nombre[0]=='\0')
    {
        cout<<"este campo no puede estar vacio"<<endl;
        system("pause");
        return false;
    }

    cout<<"COSTO DE PREPARACION: ";
    cin>>reg->costo;
    if (reg->costo<0)
    {
        cout<<"Este campo no puede ser negativo"<<endl;
        system("pause");
        return false;
    }

    cout<<"PRECIO DE VENTA: ";
    cin>>reg->precio;
    if (reg->precio<0||reg->precio<reg->costo)
    {
        cout<<"Este campo no puede ser negativo ni menor al costo de preparacion"<<endl;
        system("pause");
        return false;
    }

    cout<<"TIEMPO DE PREPARACION: ";
    cin>>reg->tiempoPreparacion;
    if (reg->tiempoPreparacion<0)
    {
        cout<<"Este campo no puede ser negativo"<<endl;
        system("pause");
        return false;
    }

    cout<<"RESTAURANTE: ";
    cin>>reg->idRestaurante;
     if (reg->idRestaurante<0)
    {
        cout<<"Este campo no puede ser negativo"<<endl;
        system("pause");
        return false;
    }

    cout<<"COMISION: ";
    cin>>reg->comision;
    if (reg->comision<0||reg->comision>100)
    {
        cout<<"Este campo no puede ser mayor a 100 ni menor 0"<<endl;
        system("pause");
        return false;
    }

    cout<<"CATEGORIA: ";
    cin>>reg->idCategoria;
     if (reg->idCategoria<0)
    {
        cout<<"Este campo no puede ser negativo"<<endl;
        system("pause");
        return false;
    }
    reg->estado=true;
    return true;

}

bool guardarPlato(platos reg)
{
    bool guardo;
    FILE *p;
    p=fopen("archivos.dat","ab");
    if(p==NULL)
        {
            return false;
        }
    guardo= fwrite(&reg,sizeof(platos),1,p);
    fclose(p);
    return guardo;
}

void listarPlatosId(platos reg)
{

    int id_buscado, pos;
    cout<<"Ingresar ID del plato a buscar: ";
    cin>>id_buscado;
    pos = buscarId(id_buscado);
    if(pos>=0)
    {
        platos reg = leer_platos(pos);
        listarPlatos(reg);
    }else
    {
        cout<<"No existe ID buscado";
    }
}

bool sobreescribir_plato(platos reg, int pos)
{
    bool guardo;
    FILE *p;
    p=fopen("archivos.dat","rb+");
    if(p==NULL)
        {
            return false;
        }
    fseek(p,pos *sizeof(platos),SEEK_SET);
    guardo= fwrite(&reg,sizeof(platos),1,p);
    fclose(p);
    return guardo;

}


void editar_plato(){
    int id_buscado,pos;
    cout<<"Pedir el ID del Plato a editar: ";
    cin>>id_buscado;
    pos = buscarId(id_buscado);
    if (pos>=0)
    {
        platos reg = leer_platos(pos);
        cout<<endl;
        listarPlatos(reg);
        cout<<endl;
        cout<<"Nuevo costo de venta: ";
        cin>>reg.costo;
        cout<<"Nuevo Tiempo de preparacion: ";
        cin>>reg.tiempoPreparacion;
        if(sobreescribir_plato(reg, pos))
        {
            cout<<"Producto modificado con exito";
            cout<<endl;
        }
        else{
            cout<<"No se modifico el plato";
            cout<<endl;
        }
    }
    else {
        cout<<"El producto no existe";
        cout<<endl;
    }


}

void bajaPlato(){
    int id_buscado,pos,baja;
    cout<<"Pedir el ID del Plato a dar de baja: ";
    cin>>id_buscado;
    pos = buscarId(id_buscado);
    if (pos>=0)
    {
        platos reg = leer_platos(pos);
        cout<<endl;
        listarPlatos(reg);
        cout<<endl;
        cout<<"Confirmar baja del plato"<<endl;
        cout<<"Coloque 1 para dar de baja: ";
        cin>>baja;
        if (baja==1)
        {
            reg.estado = false;
        }
        else{
            cout<<"No se modifico el plato";
            cout<<endl;
        }
        if(sobreescribir_plato(reg, pos))
        {
            cout<<"Producto eliminado con exito";
            cout<<endl;
        }
        else{
            cout<<"No se modifico el plato";
            cout<<endl;
        }
    }
    else {
        cout<<"El producto no existe";
        cout<<endl;
    }


}


void listarPorRestaurante(platos reg)
{   int idRestaurant;
    cout<<"Indique el ID del restaurant para ver los platos: ";
    cin>>idRestaurant;
    FILE *p;
    p = fopen("archivos.dat","rb");
    if (p==NULL)
        {
            cout<<"No se pudo abrir archivo";
        }
    while(fread(&reg,sizeof(platos),1,p))
    {
        if (idRestaurant == reg.idRestaurante)
        {
            if(reg.estado==true){
                    system("cls");
        cout<<"ID: "<<reg.id<<endl;
        cout<<"nombre: "<<reg.nombre<<endl;
        cout<<"costo: "<<reg.costo<<endl;
        cout<<"precio: "<<reg.precio<<endl;
        cout<<"tiempo: "<<reg.tiempoPreparacion<<endl;
        cout<<"ID Restaurante: "<<reg.idRestaurante<<endl;
        cout<<"Comision: "<<reg.idRestaurante<<endl;
        cout<<"categoria: "<<reg.idCategoria<<endl;
        cout<<endl;}
        }

}

}

void menuPlatos()
{

     while(true)
    {

        int opcion;
        system("cls");
        setColor(RED);
    cout<<"**********************************************************************************"<<endl;
    cout<<"*    $$$$$$$$$$$$    $$$$$$$$       $$       $$$$$$$$$  $$$$$$$$    $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$$$$$$$$  $$      $$  $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$$$$$$$       $$       $$     $$  $$$$$$$$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$       $$     $$  $$    $$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$$$$$$$ $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<endl;
    setColor(LIGHTGREEN);
        cout<<"MENU PLATOS"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"1) NUEVO PLATO"<<endl;
        cout<<"2) MODIFICAR PLATO"<<endl;
        cout<<"3) LISTAR PLATO POR ID"<<endl;
        cout<<"4) PLATOS POR RESTAURANT"<<endl;
        cout<<"5) LISTAR TODOS LOS PLATOS"<<endl;
        cout<<"6) ELIMINAR PLATO"<<endl;
        cout<<"0) Salir"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"Ingresar opcion: ";
        cin>>opcion;

    switch (opcion)
    {

        case 1:
            platos reg;
            if(cargarPlatos(&reg)==true)
            {   if(guardarPlato(reg)==true)
                {
                cout<<endl;
                cout<<"Se agrego el plato"<<endl;
                system("pause");
                }
                else
                {
                    cout<<endl;
                    cout<<"No se pudo agregar el plato"<<endl;
                    system("pause");
                }
            }
        break;
        case 2:
            editar_plato();
            system("pause");
        break;
        case 3:
            system("cls");
            listarPlatosId(reg);
            system("pause");
        break;
        case 4:
          listarPorRestaurante(reg);
          system("pause");
        break;
        case 5:
            system("cls");
            listarPlato(reg);
            system("pause");
        break;
        case 6:
            bajaPlato();
            system("pause");
        break;
        case 0:
            return;
        break;

    }

}

}

///-------------------------------------------------------------------

clientes leerClientes(int pos)
{
    clientes registros;
    FILE *p;
    p = fopen("clientes.dat","rb");
    if (p==NULL){
            registros.id=-1;
            return registros;
        }
    fseek(p,pos*sizeof(clientes),SEEK_SET);
    fread(&registros,sizeof(clientes),1,p);
    fclose(p);
    return registros;
}

int buscarIdC(int idBuscado)
{
    int i=0;
    clientes registros;
    FILE *p;
    p = fopen("clientes.dat","rb");
    if (p==NULL){
        return -1;
    }
    while(fread(&registros,sizeof(clientes),1,p)==1)
    {
        if (idBuscado==registros.id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -2;
}



void listarCliente(clientes registro)
{
      if(registro.estado==true)
    {

    cout<<"ID: "<<registro.id<<endl;
    cout<<"Apellido: "<<registro.apellidos<<endl;
    cout<<"Nombre: "<<registro.nombres<<endl;
    cout<<"Mail: "<<registro.mail<<endl;
    cout<<"Domicilio: "<<registro.domicilio<<endl;
    cout<<"Codigo postal: "<<registro.cp<<endl;
    cout<<"Fecha de nacimiento: "<<registro.fec.dia<<"/"<<registro.fec.mes<<"/"<<registro.fec.anio<<endl;
    }

}

void listarPorId(clientes registro)
{
    int idBuscado,pos;

    cout<<"Ingrese ID de restaurant: ";
    cin>>idBuscado;
    pos= buscarIdC(idBuscado);
    if (pos>=0)
    {
    clientes registros=leerClientes(pos);
    listarCliente(registros);
    system("pause");
    }else{
        cout<<"No existe el registro";
    }

}

int listarClientes(clientes registro)
{
    system("cls");
    FILE *p;
    p = fopen("clientes.dat","rb");
    if(p==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        return 1;
    }
    while(fread(&registro,sizeof(clientes),1,p))
    {
        cout<<endl;
        listarCliente(registro);
    }
    system("pause");
    fclose(p);
    return 0;
}

bool guardarCliente(clientes registro)
{
    bool guardo;
    FILE *p;
    p = fopen("clientes.dat","ab");
    if (p==NULL)
        {
        cout<<"No se pudo crear achivo"<<endl;
        return false;
        }
        guardo=fwrite(&registro, sizeof(clientes),1,p);
        fclose(p);
        return guardo;
}
bool validarFecha(int dia, int mes , int anio){

}
switch ( mes )
        {
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 : if ( dia >= 1 && dia <= 31 ){
                          
                          return true;
                          }
                      else{
                          cout<<( "   FECHA INCORRECTA" );
                          return false;
                      break;

            case  4 :
            case  6 :
            case  9 :
            case 11 : if ( dia >= 1 && dia <= 30 ){
                          
                          return true;}

                      else{
                          cout<<( "   FECHA INCORRECTA" )<<endl;
                          return false;}
                      break;

            case  2 : if( anio % 4 == 0 && anio % 100 != 0 || anio % 400 == 0 ){
                          if ( dia >= 1 && dia <= 29 ){
                              
                              return true;}
                        else if ( dia >= 1 && dia <= 28 ){
                              
                              return true;}
                        else{
                              cout<<( "   FECHA INCORRECTA" );
                              return false;}


        }
        else{  cout<<( "   FECHA INCORRECTA" );
                              return false;}
    }

}}

bool validarMail(char *mail)
{

    int tam;
    int contadorArrobas=0;
    tam=strlen(mail);
    for (int i=0; i<tam; i++)
    {

        if((mail[i]>=1 && mail[i]<=45) || (mail[i]>=58 && mail[i]<=63) || (mail[i]>=91 && mail[i]<=94) || (mail[i]>=123 && mail[i]<=249))
        {
            cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
            return false;
        }
        if (mail[0]=='@' || mail[0]=='.')
        {
            cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
            return false;
        }

        if (mail[i]=='@')
        {
            if((mail[i-1]>=1 && mail[i-1]<=48) || (mail[i-1]>=58 && mail[i-1]<=64) || (mail[i-1]>=91 && mail[i-1]<=96) || (mail[i-1]>=123 && mail[i-1]<=255) &&
                    (mail[i+1]>=1 && mail[i+1]<=48) || (mail[i+1]>=58 && mail[i+1]<=64) || (mail[i+1]>=91 && mail[i+1]<=96) || (mail[i+1]>=123 && mail[i+1]<=255) )
            {
                cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
                return false;
            }

        }
        if(mail[i]=='.')
        {
            if(mail[i-1]=='.' || mail[i+1]=='.')
            {
                cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
                return false;
            }
        }
        if (mail[i]=='@')
        {
            contadorArrobas=contadorArrobas+1;
            if (contadorArrobas==2)
            {
                cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
                return false;
            }

        }


    }
    if (contadorArrobas==0)
        {
            cout<<"El email ingresado es incorrecto , por favor ingreselo con el siguiente formato name@example.com"<<endl;
            return false;
        }

    return true;
}

int generadorDeId()
{
    FILE *p;
    p=fopen("clientes.dat","ab");
    fseek(p,SEEK_SET,SEEK_END);
    int id=((ftell(p)/sizeof(clientes))+1);
    fclose(p);
    return id;

}

bool cargarCliente(clientes *registro)
{   system("cls");

    registro->id=generadorDeId();
    cout<<"Cliente ID"<<" "<<registro->id<<endl;


    cout<<"Ingrese apellido del cliente: ";
    cin.ignore();
    cin.getline(registro->apellidos,50);
     if(registro->apellidos[0] == '\0')
    {
         cout<<"Este campo no puede estar vacio"<<endl;
        system("pause");
        return false;
    }

    cout<<"Ingrese nombre del cliente: ";
    cin.getline(registro->nombres,50);
     if(registro->nombres[0] == '\0')
    {
         cout<<"Este campo no puede estar vacio"<<endl;
        system("pause");
        return false;
    }

    cout<<"Ingrese Mail del cliente: ";
    cin.getline(registro->mail,50);

       if (validarMail(registro->mail)==false)
        {
            return false;
        }

    cout<<"Ingrese domicilio: ";
    cin.getline(registro->domicilio,100);
    cin.ignore();
    if(registro->domicilio[0] == '\0')
    {
         cout<<"Este campo no puede estar vacio"<<endl;
        system("pause");
        return false;
    }

    cout<<"Ingrese codigo postal: ";

    cin>>registro->cp;
     if(registro->cp<1000 || registro->cp>9999)
    {
         cout<<"Debe ser un numero entre 1000 y 9999"<<endl;
        return false;
    }

    cout<<"Ingrese fecha de nacimiento: "<<endl;
    cout<<"Dia: ";
    cin>>registro->fec.dia;
    cout<<"Mes: ";
    cin>>registro->fec.mes;
    cout<<"Año: ";
    cin>>registro->fec.anio;
 
   if (validarFecha(registro->fec.dia,registro->fec.mes,registro->fec.anio)==false)
    {
        return false;
    }


    registro->estado=true;
    return true;
    }

bool sobreescribirCliente(clientes registro, int pos)
{
    int guardado;
    FILE *p;
    p = fopen("clientes.dat","rb+");
    if(p==NULL)
    {
       return -1;
    }
    fseek(p,pos*sizeof(clientes),SEEK_SET);
    guardado = fwrite(&registro,sizeof(clientes),1,p);
    fclose(p);
    return guardado;

}

void modificarCliente()
{
system("cls");
    int pos,id_buscado;
    cout<<"Indicar ID de cliente a modificar: ";
    cin>>id_buscado;
    pos = buscarIdC(id_buscado);
    if(pos>=0)
    {
        clientes registro=leerClientes(pos);
        cout<<endl;
        listarCliente(registro);
        cout<<endl;
        cout<<"Ingrese nuevo domicilio: "<<endl;
        cin.ignore();
        cin.getline(registro.domicilio,100);
        if(registro.domicilio[0] == '\0')
        {
        cout<<"Este campo no puede estar vacio"<<endl;
        system("pause");

        }
        if(sobreescribirCliente(registro,pos))
        {
            cout<<"Cliente modificado con exito"<<endl;
            system("pause");

        }else{
        cout<<"No se pudo modificar el registro"<<endl;
        }

    }else{
    cout<<"No se encontro cliente"<<endl;
    }

}

void bajaCliente()
{system("cls");
    int pos,idBuscado,baja;
    cout<<"Ingrese el cliente a dar de baja: ";
    cin>>idBuscado;
    pos = buscarIdC(idBuscado);
    if (pos>=0)
    {
        clientes registro = leerClientes(pos);
        cout<<endl;
        listarCliente(registro);
        cout<<endl;
        cout<<"Confirme con 1 para eliminar: "<<endl;
        cin>>baja;
        if(baja==1)
        {
            registro.estado=false;
        }
        else{
        cout<<"No se pudo dar de baja el cliente"<<endl;
        }
        if(sobreescribirCliente(registro,pos)==true)
        {
            cout<<"El cliente se dio de baja con exito"<<endl;
        }
            else{
                cout<<"No se pudo dar de baja el cliente"<<endl;
            }
    }
    else{
    cout<<"No se encontro el registro"<<endl;
    }


}


void menuClientes()
   {

while(true)
    {
        int opcion;
        system("cls");
        setColor(RED);
    cout<<"**********************************************************************************"<<endl;
    cout<<"*    $$$$$$$$$$$$    $$$$$$$$       $$       $$$$$$$$$  $$$$$$$$    $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$$$$$$$$  $$      $$  $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$$$$$$$       $$       $$     $$  $$$$$$$$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$       $$     $$  $$    $$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$$$$$$$ $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<endl;
    setColor(LIGHTGREEN);
        cout<<"MENU CLIENTES"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"1) NUEVO CLIENTE"<<endl;
        cout<<"2) MODIFICAR CLIENTE"<<endl;
        cout<<"3) LISTAR CLIENTE POR ID"<<endl;
        cout<<"4) LISTAR TODOS LOS CLIENTES"<<endl;
        cout<<"5) ELIMINAR CLIENTE"<<endl;
        cout<<"0) Salir"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"Ingresar opcion: ";
        cin>>opcion;

        switch (opcion)
        {

            case 1:
                clientes registro;
                if(cargarCliente(&registro)==true)
                    {
                        if(guardarCliente(registro))
                        {
                            cout<<endl;
                            cout<<"El cliente ha sido guardado de manera exitosa"<<endl;
                            system("pause");
                        }else{
                            cout<<"El cliente no pudo ser guardado"<<endl;
                            system("pause");
                        }
                    }
                    system("pause");
            break;
            case 2:
                modificarCliente();
            break;
            case 3:
                system("cls");
                listarPorId(registro);
                system("cls");
            break;
            case 4:
                listarClientes(registro);

            break;
            case 5:
                bajaCliente();
                system("pause");
            break;
            case 6:

            break;
            case 0:
                return;
            break;

    }

}
 }

 ///-------------------------------------------------------------------------------------

int generadorDeIdPedido()
{

   FILE *p;
    p = fopen("pedidos.dat","ab");
    if(p==NULL) return false;
    fseek(p,SEEK_SET,SEEK_END);
    int id = ((ftell(p)/sizeof(pedidos))+1);
    return id;
}

bool buscarIdPlato(int idBuscar)
{
    platos reg;
    FILE *p;
    p = fopen("archivos.dat","rb");
    if (p==NULL)
        {
            cout<<"No se pudo abrir archivo";
            return false;
        }
        while(fread(&reg,sizeof(platos),1,p))
        {
        if (idBuscar == reg.id)
        {
        fclose(p);
        return true;
        }
        }
    fclose(p);
    return false;

}

float buscarValorPlato(int idBuscar)
{
    platos reg;
    FILE *p;
    p = fopen("archivos.dat","rb");
    if (p==NULL)
        {
            cout<<"No se pudo abrir archivo";
            return -1;
        }
        while(fread(&reg,sizeof(platos),1,p))
        {
        if (idBuscar == reg.id)
        {
        fclose(p);
        return reg.precio;
        }
        }
    fclose(p);
    return -1;

}

bool nuevoPedido(pedidos ped)
{
    FILE *p;
    p = fopen("pedidos.dat","ab");
    if(p==NULL)
        {
        cout<<"El archivo no pudo ser creado"<<endl;
        return false;
        }
    fwrite(&ped,sizeof(pedidos),1,p);
    fclose(p);
    return true;
    }

bool cargarPedido(pedidos *ped)
{
    int idBuscado,pos;
    ped->id=generadorDeIdPedido();
    cout<<"ID de pedido "<<ped->id<<endl;


    cout<<"Ingrese ID del cliente: ";
    cin>>idBuscado;
    pos=buscarIdC(idBuscado);
    if (pos>=0){
        ped->idCliente=pos+1;
    }else{
    cout<<"ID del cliente no existe"<<endl;
    system("pause");
    }


    int idBuscar,posP;
    cout<<"Ingrese ID del plato: ";
    cin>>idBuscar;
    posP=buscarIdPlato(idBuscar);
    if(posP==1)
    {
        ped->idPlato = idBuscar;
        }else{
        cout<<"No existe plato"<<endl;
        system("pause");
        }

    cout<<"Ingrese la cantidad pedida: ";
    cin>>ped->cantidad;
    if (ped->cantidad<=0)
    {
        cout<<"La cantidad ingresada es incorrecta"<<endl;
        return false;
    }

    int valor= buscarValorPlato(idBuscar);
    ped->precioU=valor;
    cout<<"El precio unitario es "<<ped->precioU<<endl;

    cout<<"Ingrese fecha de pedido: "<<endl;
    cout<<"Dia: ";
    cin>>ped->fec.dia;
    cout<<"Mes: ";
    cin>>ped->fec.mes;
    cout<<"Año: ";
    cin>>ped->fec.anio;
    if (validarFecha(ped->fec.dia,ped->fec.mes,ped->fec.anio)==false)
    {
        return false;
    }  
    
    cout<<"Ingrese la valoracion: ";
    cin>>ped->valoracion;
    if(ped->valoracion<0 || ped->valoracion>10)
    {
        cout<<"El numero debe ser entre 0 y 10 segun corresponda"<<endl;
        system("pause");
        return false;
    }

    ped->estado=1;

    return true;
    }

void listarPedido(pedidos ped)
{

    if(ped.estado==1){
    cout<<"PEDIDOS EN CURSO"<<endl;
    cout<<"ID: "<<ped.id<<endl;
    cout<<"ID Cliente: "<<ped.idCliente<<endl;
    cout<<"ID Plato: "<<ped.idPlato<<endl;
    cout<<"Cantidad: "<<ped.cantidad<<endl;
    cout<<"Precio unitario: "<<ped.precioU<<endl;
    cout<<"Fecha de pedido: "<<ped.fec.dia<<"/"<<ped.fec.mes<<"/"<<ped.fec.anio<<endl;
    cout<<"Valoracion: "<<ped.valoracion<<endl;

        }else if(ped.estado==2)
            {
    cout<<"PEDIDOS COMPLETADOS"<<endl;
    cout<<"ID: "<<ped.id<<endl;
    cout<<"ID Cliente: "<<ped.idCliente<<endl;
    cout<<"ID Plato: "<<ped.idPlato<<endl;
    cout<<"Cantidad: "<<ped.cantidad<<endl;
    cout<<"Precio unitario: "<<ped.precioU<<endl;
    cout<<"Fecha de pedido: "<<ped.fec.dia<<"/"<<ped.fec.mes<<"/"<<ped.fec.anio<<endl;
    cout<<"Valoracion: "<<ped.valoracion<<endl;
            }else if(ped.estado==3)
            {
        cout<<"PEDIDOS CANCELADOS"<<endl;
    cout<<"ID: "<<ped.id<<endl;
    cout<<"ID Cliente: "<<ped.idCliente<<endl;
    cout<<"ID Plato: "<<ped.idPlato<<endl;
    cout<<"Cantidad: "<<ped.cantidad<<endl;
    cout<<"Precio unitario: "<<ped.precioU<<endl;
    cout<<"Fecha de pedido: "<<ped.fec.dia<<"/"<<ped.fec.mes<<"/"<<ped.fec.anio<<endl;
    cout<<"Valoracion: "<<ped.valoracion<<endl;

            }
}

int listarPedidos()
{   system("cls");
    pedidos ped;
    FILE *p;
    p = fopen("pedidos.dat","rb");
    if (p==NULL){
                cout <<"no se pudo abrir"<<endl;
                return 1;
                }
    while(fread(&ped,sizeof(pedidos),1,p))
    {
        cout<<endl;
        listarPedido(ped);
    }
    fclose(p);
    system("pause");
    return 0;
}

int buscarIdPedido(int idPedido)
{   pedidos ped;
    int i=0;
    FILE *p;
    p = fopen("pedidos.dat","rb");
    if (p==NULL) return -1;
    while(fread(&ped,sizeof(pedidos),1,p))
        {
            if(idPedido==ped.id)
            {
                fclose(p);
                return i;
            }
        i++;
        }

}

pedidos leerPedidos(int pos)
{   pedidos ped;
    FILE *p;
    p = fopen("pedidos.dat","rb");
    if (p==NULL){ ped.id=-1; return ped;}
    fseek(p,pos*sizeof(pedidos),SEEK_SET);
    fread(&ped,sizeof(pedidos),1,p);
    fclose(p);
    return ped;
}

void listarPedidosId(pedidos ped)
{
    int idPedido,pos;
    cout<<"Ingrese el ID del pedido que quiere buscar: ";
    cin>>idPedido;
    pos = buscarIdPedido(idPedido);
    if (pos>=0)
        {
        pedidos ped = leerPedidos(pos);
        listarPedido(ped);
        system("pause");
        }
}

bool sobreescribirPedido(pedidos ped, int pos)
{
    FILE *p;
    p=fopen("pedidos.dat","rb+");
    if(p==NULL) return -1;
    fseek(p,pos*sizeof(pedidos),SEEK_SET);
    int guardo = fwrite(&ped,sizeof(pedidos),1,p);
    fclose(p);
    return guardo;
}

void modificarPedido()
{
    pedidos ped;
    int idBuscado,opcion;
    cout<<"Indique el pedido que desea modificar: ";
    cin>>idBuscado;
   int pos = buscarIdPedido(idBuscado);
    if(pos<=0)
    {
        pedidos ped= leerPedidos(pos);
        cout<<endl;
        listarPedido(ped);
        cout<<endl;
        cout<<"Ingrese nuevo estado"<<endl;
        cout<<"Elija 1 para no modificar"<<endl;
        cout<<"Elija 2 para pasar el pedido a completado"<<endl;
        cout<<"Elija 3 para pasar el estado del pedido a cancelado"<<endl;
        cout<<"OPCION: ";
        cin>>opcion;
        if(opcion>3)
        {
            cout<<"No es una opcion correcta"<<endl;
            return;
            system("pause");
        }
        ped.estado=opcion;
        if (sobreescribirPedido(ped,pos))
            {
                cout<<"Se modifico el pedido con exito"<<endl;
                system("pause");
            }else{
                cout<<"No se modifico el pedido"<<endl;
            }

    }else{
    cout<<"No se encontro el pedido solicitado"<<endl;
    }
}

 void menuPedidos()
 {
     while(true)
    {
        int opcion;
        system("cls");
        setColor(RED);
    cout<<"**********************************************************************************"<<endl;
    cout<<"*    $$$$$$$$$$$$    $$$$$$$$       $$       $$$$$$$$$  $$$$$$$$    $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"*        $$$         $$      $$     $$       $$$$$$$$$  $$      $$  $$$$$$$$$    *"<<endl;
    cout<<"*        $$$         $$$$$$$$       $$       $$     $$  $$$$$$$$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$       $$     $$  $$    $$    $$     $$    *"<<endl;
    cout<<"*        $$$         $$             $$$$$$$$ $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<endl;
    setColor(LIGHTGREEN);
        cout<<"MENU CLIENTES"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"1) NUEVO PEDIDO"<<endl;
        cout<<"2) MODIFICAR PEDIDO"<<endl;
        cout<<"3) LISTAR PEDIDO POR ID"<<endl;
        cout<<"4) LISTAR TODOS LOS PEDIDOS"<<endl;
        cout<<"0) Salir"<<endl;
        setColor(RED);
        cout<<"****************"<<endl;
        setColor(LIGHTGREEN);
        cout<<"Ingresar opcion: ";
        cin>>opcion;

     switch (opcion)
     {
            case 1:
                pedidos ped;
                if (cargarPedido(&ped)==true);
                    {
                        if(nuevoPedido(ped)==true)
                        {
                            cout<<"Se cargo nuevo plato"<<endl;
                            system("pause");
                        }else{
                            cout<<"No se pudo generar nuevo plato"<<endl;
                            }

                    }
                system("cls");
                break;
            case 2:
                modificarPedido();
                break;
            case 3:
                listarPedidosId(ped);
                system("cls");
                break;
            case 4:
                listarPedidos();
                system("cls");
                break;
            case 0:
                return;
                break;
         }
 }
 }

#endif // FUNCIONES_H_INCLUDED
