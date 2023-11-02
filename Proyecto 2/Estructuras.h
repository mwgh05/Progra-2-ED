#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
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
    string redes[7]; //Twiter, Instagram, Netflix, Tinder, Facebook,Linkedin, Pinterest
    NodoHumano*hijoizq;
    NodoHumano*hijoder;
    NodoHumano(){
        id=random(9999999);
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
        hijoizq=NULL;
        hijoder=NULL;
        
    }
};

struct ListaHumanos{
    NodoHumano*pn;
    ListaHumanos(){
        pn=NULL;
    }
    void insertarNodo(NodoHumano*nodo){
        if(pn==NULL){
            pn=new NodoHumano();
        }else{

        }
    }
    ListaHumanos*generarAmigos(){
        ListaHumanos*amigos;
        return amigos;
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
