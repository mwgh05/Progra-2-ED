#include "Estructuras.h"

int main(int argc, char** argv) {
  ListaHumanos*humanos=new ListaHumanos();
  generarDemonios();
  ArbolAngeles*angeles=new ArbolAngeles();
  int option, val;

  while (option != 0){
    cout << "What operation do you want to perform? " <<
      " Select Option number. Enter 0 to exit." << endl;
    cout << "1. Insertar Humanos" << endl;
    cout << "2. Mostrar arbol" << endl;
    cout << "3. Publicar en red social" << endl;
    cout << "4. Condenación" << endl;
    cout << "5. Mostrar infierno" << endl;
    cout << "6. Salvación" << endl;
    cout << "7. Mostrar el cielo" << endl;
    cout << "8. Ganador" << endl;
    cout << "9. Consultar humano" << endl;
    cout << "10. Buscar Familia"<<endl;
    cout << "0. Exit Program" << endl;


    cin >> option;
    //Node n1;
   // TreeNode * new_node = new TreeNode();

    switch (option) {
    case 0:
      break;
    case 1:
      	cout <<"CREAR HUMANOS"<<endl;
	    cout <<"Cantida de humanos a insertar: ";
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
      
      break;
    default:
      cout << "Enter Proper Option number " << endl;
    }
*/
  } ;


}
}