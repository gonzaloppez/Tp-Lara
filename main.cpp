#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "funciones.h"

#include <stdlib.h>

int main()
{

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    setColor(RED);
    cout<<"                 "<<"**********************************************************************************"<<endl;
    setColor(LIGHTGREEN);
    cout<<"                 "<<"*    $$$$$$$$$$$$    $$$$$$$$       $$       $$$$$$$$$  $$$$$$$$    $$$$$$$$$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$      $$     $$       $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$      $$     $$       $$$$$$$$$  $$      $$  $$$$$$$$$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$$$$$$$       $$       $$     $$  $$$$$$$$    $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$             $$       $$     $$  $$    $$    $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$             $$$$$$$$ $$     $$  $$      $$  $$     $$    *"<<endl;
    setColor(RED);
    cout<<"                 "<<"*************************************************By Pedro Reynoso - Gonzalo Lopez*"<<endl;
    setColor(LIGHTGREEN);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                                    ";system("pause");

    while (true)
    {
    system("cls");
    setColor(RED);
    cout<<"                 "<<"**********************************************************************************"<<endl;
    setColor(LIGHTGREEN);
    cout<<"                 "<<"*    $$$$$$$$$$$$    $$$$$$$$       $$       $$$$$$$$$  $$$$$$$$    $$$$$$$$$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$      $$     $$       $$     $$  $$      $$  $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$      $$     $$       $$$$$$$$$  $$      $$  $$$$$$$$$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$$$$$$$       $$       $$     $$  $$$$$$$$    $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$             $$       $$     $$  $$    $$    $$     $$    *"<<endl;
    cout<<"                 "<<"*        $$$         $$             $$$$$$$$ $$     $$  $$      $$  $$     $$    *"<<endl;
    setColor(RED);
    cout<<"                 "<<"**********************************************************************************"<<endl;
    cout<<endl;
    cout<<endl;
    setColor(RED);
    cout<<"                 "<<"MENU PRINCIPAL"<<"--------------------------"<<endl;
    setColor(RED);
    cout<<"                 |                                      |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      1) PLATOS";setColor(RED);cout<<"                       |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      2) CLIENTES";setColor(RED);cout<<"                     |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      3) PEDIDOS";setColor(RED);cout<<"                      |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      4) REPORTES";setColor(RED);cout<<"                     |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      5) CONFIGURACION";setColor(RED);cout<<"                |"<<endl;
    cout<<"                 ""|";setColor(LIGHTGREEN);     cout<<"      6) Salir";setColor(RED);cout<<"                        |"<<endl;
    cout<<"                 |                                      |"<<endl;
    setColor(RED);
    cout<<"                 "<<"----------------------------------------"<<endl;
    setColor(LIGHTGREEN);
    int opc;
    cout<<"                 "<<"Ingresar opcion: ";
    cin>>opc;

    switch (opc)
    {

        case 1:
            menuPlatos();
            system("cls");
        break;
        case 2:
            menuClientes();
            system("cls");
        break;
        case 3:
            menuPedidos();
            system("cls");
        break;
        case 4:
        break;
        case 5:
            menuConfiguraciones();
            system("cls");
        break;
        case 0:
            return 0;
        break;
        default:

            cout<<"Opcion incorrecta"<<endl;
            system("pause");
            system("cls");
        break;
        }
    }
  }
