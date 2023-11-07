#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Paises.txt"
#include "Profesiones.txt"
#include "Creencias.txt"
#include "Nombres.txt"
#include "Apellidos.txt"

using namespace std;

vector<string> nombres=cargarArchivo("Nombres.txt");
vector<string> apellidos=cargarArchivo("Apellidos.txt");
vector<string> paises=cargarArchivo("Paises.txt");
vector<string> creencias=cargarArchivo("Creencias.txt");
vector<string> profesiones=cargarArchivo("Profesiones.txt");
string pecados[]={"Lujuria","Gula","Avaricia","Pereza","Ira","Envidia","Soberbia"};
vector<int> ids;
struct NodoHumano{
    int id;
    string estado;
    string nombre;
    string apellido;
    string pais;
    string creencia;
    string profesion;
    string nacimiento;
    ListaPecados*listaPecados;
    ListaHumanos*listaAmigos;
    int redes[7]; //Twiter, Instagram, Netflix, Tinder, Facebook,Linkedin, Pinterest
    NodoHumano*siguiente;
    NodoHumano*hijoder;
    int generacion;
    NodoHumano(int gen){
        id=generarId();
        estado="vivo";
        nombre=nombres[random(1000)];
        apellido=apellidos[random(30)];
        pais=paises[random(20)];
        creencia=creencias[random(10)];
        profesion=profesiones[random(20)];
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        nacimiento=ctime(&now_time);
        listaPecados=new ListaPecados();
        //listaAmigos=generarAmigos();
        for(int i=0;i<7;i++){
            redes[i]=random(100);
        }
        siguiente=NULL;
        hijoder=NULL;
        generacion=gen;
        
    }

    bool idusado(int id){
        for (int i = 0; i < ids.size(); i++) {
            if (ids[i] == id) {
                return true;
            }
        }
        return false;
    }
    int generarId(){
        int x=random(9999999);
        while(idusado(x)){
            x=random(9999999);
        }
        ids.push_back(x);
        return x;
    }
    void publicarFav(int n){
        int numeros[7];
        for(int i=0;i<7;i++){
            numeros[i]=redes[i];
        }
        int tam = sizeof(numeros) / sizeof(numeros[0]);
        sort(numeros, numeros + tam, greater<int>());
        int x=0;
        while(x<n){
            for(int i=0; i<7; i++){
                if(redes[i]==numeros[x]){
                    sumarPecados(i);
                    break;
                }
            }
            x++;
        }
    }
    void publicar(int red){ //0 Twiter, 1 Instagram, 2 Netflix, 3 Tinder, 4 Facebook, 5 Linkedin, 6 Pinterest
        NodoHumano*tmp=listaAmigos->pn;
        while(tmp!=NULL){
            tmp->sumarPecados(red);
            tmp=tmp->siguiente;
        }
    }
    void sumarPecados(int red){
        int numeros[7];
        for(int i=0;i<7;i++){
            numeros[i]=redes[i];
        }
        int tam = sizeof(numeros) / sizeof(numeros[0]);
        sort(numeros, numeros + tam, greater<int>());
        for(int i=0;i<7;i++){
            if(i==red){
                for(int j=0; j<7; j++){
                    if(redes[i]==numeros[j]){
                        //redes[i]+=7-j;
                        int x=i;
                        Pecado*tmp=listaPecados->pn;
                        while(x>0){
                            tmp=tmp->siguiente;
                            x--;
                        }
                        tmp->cantidad+=7-j;
                        break;
                    }
                }
                break;
            }
        }
    }

};

int gen=0;

struct ListaHumanos{
    NodoHumano*pn;
    ListaHumanos(){
        pn=NULL;
    }
    void insertarNodo(NodoHumano*nodo){
        if(pn==NULL){
            pn=new NodoHumano(gen);
        }else{
            NodoHumano*nuevo=new NodoHumano(gen);
            if(nuevo->id<pn->id){
                nuevo->siguiente=pn;
                pn=nuevo;
            }else{
                NodoHumano*tmp=pn;
                while(tmp!=NULL && nuevo->id>tmp->siguiente->id){
                    tmp=tmp->siguiente;
                }
                nuevo->siguiente=tmp->siguiente;
                tmp->siguiente=nuevo;
            }
        }
    }
    ListaHumanos* generarAmigos(NodoHumano*humano) {
        ListaHumanos* amigos = new ListaHumanos();
        int cont=random(100);
        NodoHumano* tmp = pn; 

        while (tmp != NULL && cont!=0) {
            if (tmp != humano) {  
                if (tmp->pais == humano->pais &&
                    (tmp->creencia == humano->creencia || 
                    tmp->profesion == humano->profesion || 
                    tmp->apellido == humano->apellido)) {
                    amigos->insertarNodo(tmp);
                }
            }
            cont--;
            tmp = tmp->siguiente;
        }

        return amigos;
    }

    NodoHumano*buscarPorId(int _id){
        NodoHumano*tmp=pn;
        while(tmp!=NULL){
            if(tmp->id==_id){
                return tmp;
            }
            tmp=tmp->siguiente;
        }
        cout<<"No se encontro el humano con id: "<<_id<<endl;
        return NULL;
    }

    void publicar(int _id, int red){
        NodoHumano*humano=buscarPorId(_id);
        if(humano!=NULL){
            humano->publicar(red);
        }
    }
    
    void publicar(string religion){
        NodoHumano*tmp=pn;
        while(tmp!=NULL){
            if(tmp->creencia==religion){
                tmp->publicarFav(1);
            }
            tmp=tmp->siguiente;
        }
    }

    void publicar(string profesion, int favoritos){
        if(favoritos>7 || favoritos<1){
            cout<<"Debe ser un numero del 1 al 7"<<endl;
        }else{
            NodoHumano*tmp=pn;
            while(tmp!=NULL){
                if(tmp->profesion==profesion){
                    tmp->publicarFav(favoritos);
                }
                tmp=tmp->siguiente;
            }
        }
    }

    void publicar(string pais, string apellido, int favoritos){
        if(favoritos>7 || favoritos<1){
            cout<<"Debe ser un numero del 1 al 7"<<endl;
        }else{
            NodoHumano*tmp=pn;
            while(tmp!=NULL){
                if(tmp->pais==pais && tmp->apellido==apellido){
                    tmp->publicarFav(favoritos);
                }
                tmp=tmp->siguiente;
            }
        }
    }
};

struct Nodo{
    int valor;
    Nodo*hijoizq;
    Nodo*hijoder;
    Nodo(int _valor){
        valor=_valor;
        hijoizq=NULL;
        hijoder=NULL;
    }
};
struct ArbolHumanos{
    Nodo*raiz;
    ArbolHumanos(){
        raiz=NULL;
    }
    void insertar(int dato,Nodo*nodo,ArbolHumanos*arbol){
        if(nodo==NULL){
            nodo=new Nodo(dato);
        }else if(nodo->valor<dato){
            insertar(dato,nodo->hijoder,arbol);
        }
    }
};

struct Pecado{
    int cantidad;
    string nombre;
    Pecado*siguiente;
    Pecado(string _nombre){
        nombre=_nombre;
        cantidad=0;
        siguiente=NULL;
    }

    void sumarPecado(int _cantidad){
        cantidad+=_cantidad;
    }
};
struct ListaPecados{
    Pecado*pn;
    ListaPecados(){
        for(int i=6; i>0 ;i--){
            insertarPecado(pecados[i]);
        }
    }

    void insertarPecado(string nombre){
        if(pn==NULL){
                pn=new Pecado(nombre);
            }else{
                Pecado*nuevo=new Pecado(nombre);
                nuevo->siguiente=pn;
                pn=nuevo;
            }
    }
};

int random(int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribucion(0, max);
    int numero = distribucion(gen);
    return numero;
}


string trim(string str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> cargarArchivo(string nombreArchivo) {
    vector<string> palabras;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string palabra;
        while (getline(archivo, palabra, ',')) {
            palabra.erase(0, palabra.find_first_not_of(" \"'"));
            palabra.erase(palabra.find_last_not_of(" \"'") + 1);
            palabras.push_back(palabra);
        }
        archivo.close();
    }
    return palabras;
}
