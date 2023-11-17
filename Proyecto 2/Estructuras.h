#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <ctime>



using namespace std;

string pecados[7]={"Lujuria","Gula","Avaricia","Pereza","Ira","Envidia","Soberbia"};
string nombredemonios[]={"Asmodeo","Belfegor","Mammon","Abadon","Satan","Belcebu","Lucifer"};
vector<int> ids;

string obtenerFechaYHoraActual() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    tm local_tm = *localtime(&now_time);

    ostringstream formattedDateTime;
    formattedDateTime << put_time(&local_tm, "%Y%m%d_%H%M%S");

    return formattedDateTime.str();
}

vector<string> cargarArchivo(string nombreArchivo) {
    vector<string> palabras;
    ifstream archivo(nombreArchivo.c_str()); 
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


int random(int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribucion(0, max);
    int numero = distribucion(gen);
    return numero;
}
int seleccionarRed(){ //0 Twiter, 1 Instagram, 2 Netflix, 3 Tinder, 4 Facebook, 5 Linkedin, 6 Pinterest
    int x=0;
    cout<<"1. Twitter"<<endl;
    cout<<"2. Instagram"<<endl;
    cout<<"3. Netflix"<<endl;
    cout<<"4. Tinder"<<endl;
    cout<<"5. Facebook"<<endl;
    cout<<"6. LinkedIn"<<endl;
    cout<<"7. Pinterest"<<endl;
    cout<<"Digite el numero de red: "<<endl;
    cin>>x;
    return x;
}

string seleccionarDeVector(vector<string> vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << i << ". " << vector[i] << endl;
    }

    int opcion=0;
    cout << "Digite el número de la opción que desea seleccionar: ";
    cin >> opcion;

    if (opcion >= 0 && opcion < vector.size()) {
        return vector[opcion];
    } else {
        return "Opción no válida";
    }
}

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
    	pn=NULL;
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

    void imprimir(){
        Pecado*tmp=pn;
        cout<<"[";
        while(tmp!=NULL){
            cout<<tmp->nombre<<"("<<tmp->cantidad<<")"<<",";
            tmp=tmp->siguiente;
        }
        cout<<"]"<<endl;
    }
};


vector<string> nombres=cargarArchivo("Nombres.txt");
vector<string> apellidos=cargarArchivo("Apellidos.txt");
vector<string> paises=cargarArchivo("Paises.txt");
vector<string> creencias=cargarArchivo("Creencias.txt");
vector<string> profesiones=cargarArchivo("Profesiones.txt");

struct NodoHumano{
    int id;
    string estado; //vivo, infierno, cielo
    string nombre;
    string apellido;
    string pais;
    string creencia;
    string profesion;
    string nacimiento;
    ListaPecados*listaPecados;
    vector<NodoHumano*>listaAmigos;
    int redes[7]; //Twiter, Instagram, Netflix, Tinder, Facebook,Linkedin, Pinterest
    NodoHumano*siguiente;
    //NodoHumano*hijoder;
    int generacion;
    NodoHumano(){
        generacion=0;
        id=generarId();
        estado="vivo";
        nombre=nombres[random(1000)];
        apellido=apellidos[random(30)];
        pais=paises[random(20)];
        creencia=creencias[random(10)];
        profesion=profesiones[random(20)];
        nacimiento=obtenerFechaYHoraActual();
        listaPecados=new ListaPecados();
        //listaAmigos=NULL;
        for(int i=0;i<7;i++){
            redes[i]=random(100);
        }
        siguiente=NULL;
        
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
    Pecado* mayorPecado(){
        Pecado*mayor=listaPecados->pn;
        if(mayor!=NULL){
        Pecado*tmp=listaPecados->pn->siguiente;
        while(tmp!=NULL){
            if(tmp->cantidad>mayor->cantidad){
                mayor=tmp;
            }
            tmp=tmp->siguiente;
        }}
        return mayor;
    }
    int obtenerCantidadPecado(string nombrePecado) {
        Pecado* tmp = listaPecados->pn;
        while (tmp != NULL) {
            if (tmp->nombre == nombrePecado) {
                return tmp->cantidad;
            }
            tmp = tmp->siguiente;
        }
        return 0;
    }
    int obtenerCantidadPecados() {
        Pecado* tmp = listaPecados->pn;
        int cont=0;
        while (tmp != NULL) {
            cont+=tmp->cantidad;    
            tmp = tmp->siguiente;
        }
        return cont;
    }
    void publicarFav(int n){
        if(estado=="vivo"){
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
    }
    void publicar(int red){ //0 Twiter, 1 Instagram, 2 Netflix, 3 Tinder, 4 Facebook, 5 Linkedin, 6 Pinterest
        for(int i=0;i<listaAmigos.size();i++){
            listaAmigos[i]->sumarPecados(red);
        }
    }
    void sumarPecados(int red){
        if(estado=="vivo"){
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
    }
    void imprimirAmigos(){
        cout<<"[";
        for(int i=0;i<listaAmigos.size();i++){
            cout<<listaAmigos[i]->id<<",";
        }
        cout<<"]"<<endl;
    }
    void imprimir(){
        cout<<id<<endl;
        cout<<nombre<<endl;
        cout<<apellido<<endl;
        cout<<estado<<endl;
        cout<<"\n";
        cout<<pais<<endl;
        cout<<creencia<<endl;
        cout<<profesion<<endl;
        listaPecados->imprimir();
        cout<<"Amigos";
        imprimirAmigos();
        cout<<"Redes";
        cout<<"[";
        for(int i=0; i<7; i++){
            cout<<redes[i]<<",";
        }
        cout<<"]"<<endl;
    }

};


struct ListaHumanos{
    int gen=0;
    NodoHumano*pn;
    ListaHumanos(){
        pn=NULL;
    }
    
    void insertarNodo(NodoHumano*nodo){
        //NodoHumano*nuevo=new NodoHumano();
        if(nodo->listaAmigos.empty()){
            generarAmigos(nodo);
        }
        if(nodo->generacion==0){
            nodo->generacion=gen;
        }
        if(pn==NULL){
            pn=nodo;
        }else{
            if(nodo->id<pn->id){
                nodo->siguiente=pn;
                pn=nodo;
            }else{
                NodoHumano*tmp=pn;
                while(tmp!=NULL && tmp->siguiente!=NULL){
                    if(nodo->id<tmp->siguiente->id){
                        nodo->siguiente=tmp->siguiente;
                        //tmp->siguiente=nodo;
                        break;
                    }
                    tmp=tmp->siguiente;
                }
                //nodo->siguiente=tmp->siguiente;
                tmp->siguiente=nodo;
            }
        }
    }
    void crearHumanos(int n){
        for(int i=0; i<=n; i++){
            insertarNodo(new NodoHumano());
        }
        gen++;
    }
    void generarAmigos(NodoHumano*humano) {
        vector<NodoHumano*> amigos;
        int cont=random(100);
        NodoHumano* tmp = pn; 

        while (tmp != NULL && cont!=0) {
            if (tmp != humano) {  
                if (tmp->pais == humano->pais &&
                    (tmp->creencia == humano->creencia || 
                    tmp->profesion == humano->profesion || 
                    tmp->apellido == humano->apellido)) {
                    amigos.push_back(tmp);
                }
            }
            cont--;
            tmp = tmp->siguiente;
        }
        humano->listaAmigos=amigos;
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
    int mostrarVivos(){
        int cont=0;
        NodoHumano*tmp=pn;
        while(tmp!=NULL){
            if(tmp->estado=="vivo"){
                cont++;
            }
            tmp=tmp->siguiente;
        }
        return cont;
    }
    void buscarPorId(int _id, string nombre, string apellido){
        NodoHumano*tmp=pn;
        while(tmp!=NULL){
            if(tmp->id==_id && tmp->nombre==nombre &&  tmp->apellido==apellido){
                tmp->imprimir();
                break;
            }
            tmp=tmp->siguiente;
        }
       // cout<<"No se encontro el humano con id: "<<_id<<endl;
    }
    
    void imprimirIds(){
        NodoHumano*tmp=pn;
        while(tmp!=NULL){
            cout<<tmp->id<<": "<<tmp->nombre<<" "<<tmp->apellido<<endl;
            tmp=tmp->siguiente;
        }
    }
    void publicar(int _id, int red){
        NodoHumano*humano=buscarPorId(_id);
        if(humano!=NULL){
            if(humano->estado=="vivo"){
                humano->publicar(red);
            }else{
                cout<<"El humano "<<humano->nombre<<" "<<humano->apellido<<" de id "<<humano->id<<" esta muerto."<<endl;
            }
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
        cout<<"Todos los humanos con religion: "<<religion<<", publicaron en su red social favorita."<<endl;
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
        cout<<"Todos los humanos con profesion: "<<profesion<<", publicaron en sus "<<favoritos<<" redes sociales favoritas."<<endl;
    }

    void publicar(string pais, string apellido, int favoritos){
        vector<NodoHumano*> familia=buscarFamilia(pais, apellido);
        if(favoritos>7 || favoritos<1){
            cout<<"Debe ser un numero del 1 al 7"<<endl;
        }else{
            for (int i = 0; i < familia.size(); i++) {
                familia[i]->publicarFav(favoritos);
            }
        }
        cout<<"La familia "<<apellido<<" de "<<pais<<" ha publicado en sus "<<favoritos<<" redes sociales favoritas."<<endl;
    }

    vector<NodoHumano*> buscarFamilia(string pais, string apellido) {
        NodoHumano* tmp = pn;
        vector<NodoHumano*> familia;
    
        while (tmp != NULL) {
            if (tmp->pais == pais && tmp->apellido == apellido) {
                
                familia.push_back(tmp);
            }
            tmp = tmp->siguiente;
        }
    
        return familia;
    }

    void mostrarfamilia(){
        string apellido;
        string pais;
        cout<<"Ingrese el pais: ";
        getline(cin, pais);
        cout<<"Ingrese en apellido: ";
        getline(cin, apellido);
        vector<NodoHumano*> familia=buscarFamilia(pais,apellido);
        vector<NodoHumano*> cielo;
        vector<NodoHumano*> vivos;
        vector<NodoHumano*> infierno;
        for(int i=0; i<familia.size(); i++){
            familia[i]->imprimir();
            if(familia[i]->estado=="vivo"){
                vivos.push_back(familia[i]);
            }else if(familia[i]->estado=="cielo"){
                cielo.push_back(familia[i]);
            }else if(familia[i]->estado=="infierno"){
                infierno.push_back(familia[i]);
            }
        }
        cout<<"Infierno: "<<infierno.size()*100/familia.size()<<"%"<<endl;
        cout<<"Cielo: "<<cielo.size()*100/familia.size()<<"%"<<endl;
        cout<<"Vivos: "<<vivos.size()*100/familia.size()<<"%"<<endl;
    }

    void publicar(){
        cout<<"PUBLICAR"<<endl;
        string x;
        int red;
        cout<<"1. Seleccionar un humano."<<endl;
        cout<<"2. Seleccionar por religion."<<endl;
        cout<<"3. Seleccionar por profesion."<<endl;
        cout<<"4. Seleccionar por familia."<<endl;
        cout<<"Digite su opcion: "<<endl;
        getline(cin,x);
        if(x=="1"){
            cout<<"Seleccionar un humano."<<endl;
            imprimirIds();
            int id;
            cout<<"Digite el id: "<<endl;
            cin>>id;
            red=seleccionarRed();
            publicar(id,red);
        }else if(x=="2"){
            cout<<"Seleccionar por religion."<<endl;
            string religion;
            cout<<"Seleccione la religion: "<<endl;
            religion=seleccionarDeVector(creencias);
            publicar(religion);
        }else if(x=="3"){
            cout<<"Seleccionar por profesion."<<endl;
            string prof;
            cout<<"Seleccione la profesion: "<<endl;
            prof=seleccionarDeVector(profesiones);
            int n=0;
            cout<<"A cuantas redes favoritas desea publicar?: "<<endl;
            cin>>n;
            publicar(prof,n);
        }else if(x=="4"){
            cout<<"Seleccionar por familia."<<endl;
            string apellido;
            string pais;
            int n=0;
            cout<<"Seleccione el pais: "<<endl;
            pais=seleccionarDeVector(paises);
            cout<<"Seleccione el apellido: "<<endl;
            apellido=seleccionarDeVector(apellidos);
            cout<<"A cuantas redes favoritas desea publicar?: "<<endl;
            cin>>n;
            publicar(pais,apellido,n);
        }else{
            cout<<"Debe ingresar un numero del 1 al 4."<<endl;
        }
    }

    vector<NodoHumano*> ordenarPorPecado(string nombrePecado) {
    	vector<NodoHumano*> humanos;        
    	NodoHumano* tmp = pn;

	    while (tmp != NULL) {
	        if (tmp->listaPecados != NULL) { // Verifica si listaPecados no es NULL
	            Pecado* pecado = tmp->listaPecados->pn;
	
	            while (pecado != NULL) {
	                if (pecado->nombre == nombrePecado) {
	                    humanos.push_back(tmp);
	                    break;
	                }
	                pecado = pecado->siguiente;
	            }
	        }
	        tmp = tmp->siguiente;
	    }
	
	    sort(humanos.begin(), humanos.end(), [nombrePecado](NodoHumano* a, NodoHumano* b) {
	        int cantidadA = a->obtenerCantidadPecado(nombrePecado);
	        int cantidadB = b->obtenerCantidadPecado(nombrePecado);
	        return cantidadA > cantidadB;
	    });
	
	    return humanos;
	}

    
    void buscarHumano(){
        cout<<"BUSCAR HUMANO"<<endl;
        string nombre;
        string apellido;
        imprimirIds();
        int x=0;
        cout<<"Digite el ID: ";
        cin>>x;
        cout<<"Digite el nombre: ";
        cin>>nombre;
        cout<<"Digite el apellido: ";
        cin>>apellido;
        buscarPorId(x, nombre, apellido);
        //buscado->imprimir();

    }
};

//ListaHumanos*listaHumanos=new ListaHumanos();

struct Nodo{
    NodoHumano* humano;
    Nodo*hijoizq;
    Nodo*hijoder;
    Nodo(NodoHumano*_humano){
        humano=_humano;
        hijoizq=NULL;
        hijoder=NULL;
    }
};
struct ArbolHumanos{
    Nodo*raiz;
    ArbolHumanos(){
        raiz=NULL;
    }
    /*void crearHumanos(int n){
        for(int i=0; i<=n; i++){
            NodoHumano*nuevo=new NodoHumano();
            nuevo->generacion=gen;
            insertarNodo(nuevo);
        }
        gen++;
    }*/
    void crearHumanos(ListaHumanos*listahumanos, int n){
        listahumanos->crearHumanos(n);

    }
};



struct NodoHeap{
    vector<NodoHumano*> familia;
    string apellido;
    string pais;
    string pecado;
    NodoHeap*siguiente;
    NodoHeap(){
        siguiente=NULL;
    }
    void insertarHumano(NodoHumano*humano){
        if(apellido==""){
            apellido=humano->apellido;
        }
        if(pais==""){
            pais=humano->pais;
        }
        humano->estado="infierno";
        familia.push_back(humano);
    }
    int numeroPecados(){
        int cont=0;
        for(int i=0; i<familia.size(); i++){
            Pecado*pecado=familia[i]->mayorPecado();
            cont+=pecado->cantidad;
        }
        return cont;
    }
};
bool compararFamilias(NodoHeap* a, NodoHeap* b) {
        return a->numeroPecados() > b->numeroPecados();
}

struct Heap{
    NodoHeap*pn;
    Heap(){
        pn=NULL;
    }

    int tamano(){
        int cont=0;
        NodoHeap*tmp=pn;
        while(tmp!=NULL){
            cont++;
            tmp=tmp->siguiente;
        }
        return cont;
    }

    void ordenar() {
        vector<NodoHeap*> familias;
        NodoHeap* tmp = pn;
        while (tmp != NULL) {
            familias.push_back(tmp);
            tmp = tmp->siguiente;
        }
        make_heap(familias.begin(), familias.end(), compararFamilias);
        sort_heap(familias.begin(), familias.end(), compararFamilias);
        pn = NULL;

        for (size_t i = 0; i < familias.size(); ++i) {
            NodoHeap* familia = familias[i];
            familia->siguiente = pn;
            pn = familia;
        }
    }



    void insertar(NodoHumano*humano){
        if(pn==NULL){
            pn->insertarHumano(humano);
        }else{
            NodoHeap*tmp=pn;
            while(tmp!=NULL){
                if(tmp->apellido==humano->apellido && tmp->pais==humano->pais){
                    tmp->insertarHumano(humano);
                    ordenar();
                    break;
                }
                tmp=tmp->siguiente;
            }
            if(tmp==NULL){
                tmp=new NodoHeap();
                tmp->insertarHumano(humano);
                ordenar();
            }           
        }
    }
    vector<NodoHumano*> obtenerHumanosOrdenados() {
	    std::vector<NodoHumano*> humanos;
	    NodoHeap* tmp = pn;
	    while (tmp != NULL) {
	        // Reemplaza el bucle basado en rango por un bucle tradicional
	        for (size_t i = 0; i < tmp->familia.size(); ++i) {
	            NodoHumano* humano = tmp->familia[i];
	            humanos.push_back(humano);
	        }
	        tmp = tmp->siguiente;
	    }
	
	    std::sort(humanos.begin(), humanos.end(), [](NodoHumano* a, NodoHumano* b) {
	        int cantidadA = a->mayorPecado()->cantidad;
	        int cantidadB = b->mayorPecado()->cantidad;
	        return cantidadA > cantidadB;
	    });
	
	    return humanos;
	}

};
string archivosCondenacion() {
    string fechaHora = obtenerFechaYHoraActual();
    string nombreArchivo = "Condenacion_" + fechaHora + ".txt";
    ofstream archivoSalida(nombreArchivo.c_str()); 
    if (archivoSalida.is_open()) {
        archivoSalida << "INFIERNO\n";
        archivoSalida << "Fecha y hora de creaci�n: " << fechaHora << "\n";
        archivoSalida.close();
        cout << "Archivo de condenaci�n creado exitosamente.\n";
    } else {
        cerr << "Error al abrir el archivo.\n";
    }
    return nombreArchivo;
}

void escribirEnArchivo(string nombreArchivo, string contenido) {
    std::ofstream archivo(nombreArchivo.c_str(), std::ios::app); 

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    archivo << contenido << std::endl;

    std::cout << "Contenido agregado al archivo." << std::endl;
    archivo.close();
}

string fecha() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    std::ostringstream formattedDate;
    formattedDate << year << '-' << month << '-' << day;

    return formattedDate.str();
}
string obtenerHoraActual() {
    time_t now = time(NULL);
    tm* localTime = localtime(&now);

    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    std::ostringstream oss;
    oss << setfill('0') << setw(2) << hour << ':'
        << setfill('0') << setw(2) << minute << ':'
        << setfill('0') << setw(2) << second;

    return oss.str();
}
struct Demonio{
    string nombre;
    string pecado;
    Heap*heap;
    Demonio(string _nombre, string _pecado){
        heap=new Heap();
        nombre=_nombre;
        pecado=_pecado;
    }

    void condenar(ListaHumanos*listahumanos){
        int x;
        string archivo=archivosCondenacion();
        vector<NodoHumano*> pecadores=listahumanos->ordenarPorPecado(pecado);
        x=pecadores.size()/500;
        for(int i=0; i<(pecadores.size()/500); i++){
            if(pecadores[i]->estado=="vivo"){
                heap->insertar(pecadores[i]);
                string texto=fecha()+obtenerHoraActual()+"\t Humano "+to_string(i)+pecadores[i]->nombre+pecadores[i]->apellido+"\t"+pecadores[i]->pais+" Murió el "+fecha()+" condenado por "+to_string(pecadores[i]->mayorPecado()->cantidad)+" pecados de "+pecado+" por el demonio "+nombre+"\t";
                escribirEnArchivo(archivo, texto);
            }
        }
        cout<<"El demonio "<<nombre<<" ha condenado a "<<x<<" humanos."<<endl;
    }
    NodoHumano*masPecador(){
        NodoHumano*actual;
        vector<NodoHumano*> humanos=heap->obtenerHumanosOrdenados();
        for(int i=0; i<humanos.size(); i++){
            if(humanos[i]->obtenerCantidadPecados()>actual->obtenerCantidadPecados()){
                actual=humanos[i];
            }
        }
        return actual;
    }
    NodoHumano*obtenerMasPecador(){
        vector<NodoHumano*> humanos=heap->obtenerHumanosOrdenados();
        return humanos[0];
    }
    NodoHumano*obtenerMenosPecador(){
        vector<NodoHumano*> humanos=heap->obtenerHumanosOrdenados();
        return humanos[humanos.size()-1];
    }
    double obtenerPromedio(){
        vector<NodoHumano*> humanos=heap->obtenerHumanosOrdenados();
        int cont=0;
        int ac=0;
        for(int i=0; i<humanos.size(); i++){
            ac++;
            cont+=humanos[i]->mayorPecado()->cantidad;
        }
        return cont/ac;
    }
    void imprimir(){
        cout<<nombre<<": "<<pecado<<endl;
        cout<<"Cantidad de humanos: "<<heap->tamano()<<endl;
        cout<<"Promedio: "<<obtenerPromedio()<<". Maximo: "<<obtenerMasPecador()<<". Minimo: "<<obtenerMenosPecador()<<endl;
        vector<NodoHumano*> humanos=heap->obtenerHumanosOrdenados();
        for(int i=0; i<humanos.size(); i++){
           humanos[i]->imprimir();
        }
    }
};
struct Arbol{
    NodoHumano*raiz;
    Arbol*hijoizq;
    Arbol*hijoder;
    Arbol(){
        raiz=NULL;
    }
    void insertar(NodoHumano*humano){
        if(raiz==NULL){
            raiz=humano;
        }else if(raiz->id<humano->id){
            hijoder->insertar(humano);
        }else{
            hijoizq->insertar(humano);
        }
    }
    void imprimir(){
        if (raiz == NULL) {
        return;
    }

        hijoizq->imprimir();
        raiz->imprimir();
        hijoder->imprimir();
    }
    int cantidadAux(Arbol*arbol){
        if(raiz==NULL){
            return 0;
        }else{
            return 1+cantidadAux(arbol->hijoizq)+cantidadAux(arbol->hijoder);
        }
    }
    int cantidad(){
        if(raiz==NULL){
            return 0;
        }else{
            return 1+cantidadAux(hijoizq)+cantidadAux(hijoder);
        }
    }
};
struct Hash{
    Arbol*humanos[1000];
    Hash(){
        for(int i=0; i<1000; i++){
            humanos[i]=new Arbol();
        }
    }
    void insertar(NodoHumano*humano){
        humanos[humano->id%1000]->insertar(humano);
    }
    void imprimir(){
        for(int i=0; i<1000; i++){
            humanos[i]->imprimir();
        }
    }
    int cantidad(){
        int cont=0;
        for(int i=0; i<1000; i++){
            cont+=humanos[i]->cantidad();
        }
        return cont;
    }
};
Demonio*demonios[7];
void condenarPorDemonio(ListaHumanos*listahumanos){
    int x=0;
    cout<<"CONDENAR"<<endl;
    for(int i=0; i<7; i++){
        cout<<i+1<<demonios[i]->nombre<<": "<<demonios[i]->pecado<<endl;
    }
    cout<<"Digite su opcion: "<<endl;
    cin>>x;
    demonios[x-1]->condenar(listahumanos);
}
void mostrarDemonios(){
    for(int i=0; i<7; i++){
        cout<<demonios[i]->nombre<<demonios[i]->pecado<<endl;
    }
}
void generarDemonios(){
    for(int i=0; i<7; i++){
        demonios[i]=new Demonio(nombredemonios[i],pecados[i]);
    }
}
int cantidadInfierno(){
    int cont=0;
    for(int i=0; i<7; i++){
        cont+=demonios[i]->heap->tamano();
    }
    return cont;
}
string nombresangeles[10]={"Miguel","Nuriel","Aniel","Rafael","Gabriel","Shamsiel","Raguel","Uriel","Azrael","Sariel"};
struct NodoAngel{
    /*Nombre: es uno de los nomres de la lista de ángeles
Versión: es el número de ese angel en esa generación
Generación: es el nivel del árbol
Humano: es un puntero al humano que fue salvado por
el ángel.*/
    string nombre;
    int version;
    int gen;
    NodoHumano*humano;
    NodoAngel*izquierdo;
    NodoAngel*central;
    NodoAngel*derecho;
    NodoAngel(int _gen){
        nombre=nombresangeles[random(10)];
        gen=_gen;
        izquierdo=NULL;
        central=NULL;
        derecho=NULL;
        humano=NULL;
    }
    NodoHumano* salvar(){
        NodoHumano*actual=NULL;
        for(int i=0; i<7; i++){
            if(demonios[i]->masPecador()->obtenerCantidadPecados()>actual->obtenerCantidadPecados()){
                actual=demonios[i]->masPecador();
            }
        }humano=actual;
        humano->estado="cielo";
        return humano;
    }
};
struct ArbolAngeles{
    Hash*hash;
    int gen=0;
    NodoAngel*raiz;
    ArbolAngeles(){
        hash=new Hash();
        raiz=new NodoAngel(gen);
        raiz->nombre="El Dios";
        gen++;
        raiz->izquierdo=new NodoAngel(gen);
        raiz->central=new NodoAngel(gen);
        raiz->derecho=new NodoAngel(gen);
        raiz->izquierdo->nombre="Serafines";
        raiz->central->nombre="Querubines";
        raiz->derecho->nombre="Tronos";
        gen++;
    }
    
    void insertarEnUltimoNivel(NodoAngel* raiz, NodoAngel*nuevo) {
        if (raiz==NULL) {
            raiz = nuevo;
            return;
        }

    std::queue<NodoAngel*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoAngel* nodoActual = cola.front();
        cola.pop();

        // Verifica si el nodo tiene espacio en el nivel actual.
        if (!nodoActual->central) {
            // Si hay espacio, agrega el nuevo nodo aquí.
            
                nodoActual->central = nuevo;
            
            return; // Termina el proceso de inserción.
        }

        // Agrega los hijos del nodo actual a la cola para seguir buscando espacio.
        
        if (nodoActual->central) cola.push(nodoActual->central);
        
    }
}
void salvar(){
        
    if (!raiz) return;

    std::queue<NodoAngel*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoHumano*humano;
        NodoAngel* nodoActual = cola.front();
        cola.pop();

        if (!nodoActual->central) {
            // Si es un nodo del último nivel, ejecuta la función en él.
            humano=nodoActual->salvar();
            insertarEnUltimoNivel(raiz, new NodoAngel(gen));
            hash->insertar(humano);
        }

        if (nodoActual->central) cola.push(nodoActual->central);
        

    }
    gen++;
}
};


string trim(string str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}





/*
void mandarCorreo(){
    httplib::Client cli("smtps://smtp.gmail.com");

    // Configuración para Gmail (modifica con tus propias credenciales)
    const char *email = "tucorreo@gmail.com";
    const char *password = "tupassword";
    const char *recipient = "destinatario@gmail.com";
    const char *subject = "Asunto del correo";
    const char *body = "Cuerpo del correo";

    // Construir el cuerpo del correo
    std::string payload =
        "From: " + std::string(email) + "\r\n"
        "To: " + std::string(recipient) + "\r\n"
        "Subject: " + std::string(subject) + "\r\n\r\n"
        + std::string(body);

    // Enviar el correo
    auto res = cli.Post("/sendmail", httplib::Headers{{"Authorization", "Basic " + httplib::base64_encode(std::string(email) + ":" + std::string(password))}}, payload, "application/x-www-form-urlencoded");

    if (res && res->status == 200) {
        std::cout << "Correo enviado con éxito.\n";
    } else {
        std::cerr << "Error al enviar el correo. Código de estado: " << (res ? res->status : -1) << "\n";
    }

}
*/
//generarDemonios();
//ORDENELO DEL MAS AL MENOS PECADOR POR DEMONIO (archivo)
