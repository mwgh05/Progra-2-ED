#include "Estructuras.h"

int main(int argc, char** argv) {
  ListaHumanos*humanos=new ListaHumanos();
  generarDemonios();
  humanos->crearHumanos(1000);
  ArbolAngeles*angeles=new ArbolAngeles();
  int option, val;
  option=-1;

  while (option != 0){
    cout<<"***********MENU***********"<<endl;
    cout << "1. Insertar Humanos" << endl;
    cout << "2. Mostrar arbol" << endl;
    cout << "3. Publicar en red social" << endl;
    cout << "4. Condenacion" << endl;
    cout << "5. Mostrar infierno" << endl;
    cout << "6. Salvacion" << endl;
    cout << "7. Mostrar el cielo" << endl;
    cout << "8. Ganador" << endl;
    cout << "9. Consultar humano" << endl;
    cout << "10. Buscar Familia"<<endl;
    cout << "0. Salir" << endl;
    cout << "Digite el numero de su opcion: ";
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //Node n1;
   // TreeNode * new_node = new TreeNode();

    switch (option) {
    case 0:
      break;
    case 1:
      	cout <<"CREAR HUMANOS"<<endl;
	    cout <<"Cantidad de humanos a insertar: ";
	    cin >> val;
        humanos->crearHumanos(val);
	    cout<<endl;
    	break;
    case 2:
        //
        break;
    case 3:
        humanos->publicar();
      
    break;
    case 4:
        condenarPorDemonio(humanos);
    break;
    case 5:
        for(int i=0; i<7; i++){
            demonios[i]->imprimir();
        }
    break;
    case 6:
        angeles->salvar();
    break;
    case 7:
        angeles->hash->imprimir();
    break;
    case 8:
        cout<<"GANADOR"<<endl;
        if(cantidadInfierno()>angeles->hash->cantidad()){
            cout<<"El infierno es el ganador con "<<cantidadInfierno()<<" humanos"<<endl;
            cout<<"Cielo: "<<angeles->hash->cantidad()<<endl;
            cout<<"Vivos: "<<humanos->mostrarVivos()<<endl;
        }else{
            cout<<"El cielo es el ganador con "<<angeles->hash->cantidad()<<" humanos"<<endl;
            cout<<"Infierno: "<<cantidadInfierno()<<endl;
            cout<<"Vivos: "<<humanos->mostrarVivos()<<endl;
        }
    break;
    case 9:
        humanos->buscarHumano();
    break;
    case 10:
        humanos->mostrarfamilia();
    break;/*
    case 11:

    break;
    case 12:
      
      break;*/
    default:
      cout << "Ingrese un numero valido " << endl;
    }

  } ;
  delete humanos;

}
