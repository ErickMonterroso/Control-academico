/*
ERICK ESTUARDO MONTERROSO VILLATORO
090-15-9458
PROGRAMACION 1

SE CREA ESTE PROGRAMA CON EL FIN DE CREAR UN CONTROL ACEDEMICO
MANEJANDO ARBOLES Y PILAS DINAMICOS.
-NOTA: SE ACTIVO -std = c ++ 14
codeblocks  -17.12- 06/2020
*/
#include <iostream>  //Libreria para el flujo de entrada y salida
#include <fstream> //Manejo de archivos
#include <memory>//para manejo de memoria dinamica
#include <string>//para uso de cadenas
#include <sstream>//Encabezado que proporciona clases de secuencia de cadena
#include <vector> //para uso de vectores
#include <experimental/optional>//objetos grandes que han sido asignados dinámicamente y ya están gestionados por punteros
#include <string.h>//Asignatura de mas cadenas
#include <stdlib.h>// gestión dinámica de la memoria
#include <limits>//Proporciona información sobre las propiedades de los tipos aritméticos
#include<stdio.h>

using namespace std; //declaracion estandar


//--------------------Estructura para lectura de alumno-----------------//
struct Person {
  intmax_t key;
  string dpi;
  string name;
  string segundonombre;
  string primerapellido;//------------Campos a leer
  string segundoapellido;
  string fechadenacimiento;
  string correo;
  string direccion;
  intmax_t numerodecasa;
  intmax_t num;
};
//---------------------Estructura tipo persona para crear un puntero a ella---------------//
struct Node : Person {
  Node(const Person &person) : Person(person) {}
  unique_ptr<Node> left, right; //Gestiona el almacenamiento de un puntero unico
  void insert(const Person &person);
};

//----------------------Estructura para lectura del archivo Cursos----------------------//
struct Archivocursos {
    intmax_t ID;
    string cursoganados;
    string fecha;
    string nota;
    Archivocursos *siguiente;
};

typedef Archivocursos *prtNodo; //Apuntador para estructura de cursos

//------------------Variables Globales del programa-----------------------///
  string line;
  const char delim = ',';
  unique_ptr<Node> root;
  bool band;
  int n;
  intmax_t dato;
  Archivocursos *pila = NULL;
  vector <Archivocursos> a;
  vector<Person> persons;
//---------------------Funcion para crear pila del archivo cursos--------------//
  void agregarPila( prtNodo *ptrCima, Archivocursos i){
    prtNodo ptrNuevo;
    ptrNuevo = new Archivocursos;
    if ( ptrNuevo != NULL  ) {
        ptrNuevo->ID = i.ID;
        ptrNuevo->cursoganados = i.cursoganados;
        ptrNuevo->fecha = i.fecha;
        ptrNuevo->nota = i.nota;
        ptrNuevo->siguiente = *ptrCima;
        *ptrCima = ptrNuevo;
    }
    cout << "\tAlumno con carnet: [" << i.ID <<"] detectado"<<endl;
}
//----------------------Funcion para imprimir pila----------------------------//
void imprimirPila( prtNodo cursor )
{
    if( cursor == NULL ) {
        cout << "\n\t\nLa pila esta vacia\n";
    } else {
        cout << "\n\n\t\nLa pila ingreso de la siguiente forma:\n *" ;

        while( cursor != NULL ) {
           cout << cursor->ID << "->";
            cursor = cursor->siguiente;
        }
        cout << "NULL\n\n";
    }
    cout << endl;
}
//----------------------Funcion para insertar en arbol ABB-----------------------//
void Node::insert(const Person &person) {
  /* recorre el arbol para abajo */
  if (key > person.key) {
    if (left)
        left->insert(person);
    else
        left = make_unique<Node>(person);
  } else if (key < person.key) {
    if (right)
        right->insert(person);
    else
        right = make_unique<Node>(person);
  }
}

//----------------------Funcion para colocar arbol en orden-----------//
void inorder(Node *root) {

  if (root) {
    inorder(root->left.get());
    cout <<"Carnet: " << root->key <<"\nDPI: "<< root->dpi
              <<"\nNombre: " << root->name <<"\nSegundo Nombre: "<< root->segundonombre
              <<"\nApellido Paterno: "<<root->primerapellido<<"\nApellido Materno: "<<root->segundoapellido
              <<"\nFecha De Nacimiento: "<<root->fechadenacimiento<<"\nCorreo: "<<root->correo
              <<"\nDireccion: "<<root->direccion<<"\nNumero De Casa: "<<root->numerodecasa<<"\nNumero Celular: "
              <<root->num <<"\n"<< '\n';
    inorder(root->right.get());

  }
}
//----------------------Funcion para recorrer el arbol en prePorden------------------------//
void preOrden(Node *root){

 if (root)
    {
              cout <<"Carnet: " << root->key <<"\nDPI: "<< root->dpi
              <<"\nNombre: " << root->name <<"\nSegundo Nombre: "<< root->segundonombre
              <<"\nApellido Paterno: "<<root->primerapellido<<"\nApellido Materno: "<<root->segundoapellido
              <<"\nFecha De Nacimiento: "<<root->fechadenacimiento<<"\nCorreo: "<<root->correo
              <<"\nDireccion: "<<root->direccion<<"\nNumero De Casa: "<<root->numerodecasa<<"\nNumero Celular: "
              <<root->num <<"\n"<< '\n';
        preOrden(root->left.get());
        preOrden(root->right.get());
    }

}
//----------------------Funcion para recorrer el arbol en Postorden------------------------//
void postOrden(Node *root){

    if(root!=NULL){
    postOrden(root->left.get());
    postOrden(root->right.get());
    cout <<"Carnet: " << root->key <<"\nDPI: "<< root->dpi
              <<"\nNombre: " << root->name <<"\nSegundo Nombre: "<< root->segundonombre
              <<"\nApellido Paterno: "<<root->primerapellido<<"\nApellido Materno: "<<root->segundoapellido
              <<"\nFecha De Nacimiento: "<<root->fechadenacimiento<<"\nCorreo: "<<root->correo
              <<"\nDireccion: "<<root->direccion<<"\nNumero De Casa: "<<root->numerodecasa<<"\nNumero Celular: "
              <<root->num <<"\n"<< '\n';
    }

}
//-------------------------Funcion para buscar un dato en el arbol usando la llave-------------///
std::experimental::optional<Person> busqueda(Node *root, intmax_t dato) {
    if(root==NULL){
    return {};
    }
    else if(root->key==dato){
        return *root;
    }
    else if(dato<root->key){
       return busqueda(root->left.get(),dato);
    }
    else{
        return busqueda(root->right.get(),dato);
    }
}

//-------------------------Funcion de carga de Alumnos-------------------------//
void carga(){

  ifstream fin;//("1.txt");
  string abrir;
  cout<<"\nIngrese el nombre del archivo a cargar: "<<endl;; cin.ignore();
  getline(cin,abrir);

  fin.open(abrir.c_str(), ios::in);


 if (fin.good()) {

    cout<<"\n\n**********************Datos Originales***********************\n"<<endl;
    while (getline(fin, line)) {
    istringstream ss(line);
    Person person;
    ss >> person.key;
    ss.ignore(10, delim);
    getline(ss, person.dpi, delim);
    getline(ss, person.name, delim);
    getline(ss, person.segundonombre, delim);
    getline(ss, person.primerapellido, delim);
    getline(ss, person.segundoapellido, delim); //Leyendo archivo Csv linea por linea
    getline(ss, person.fechadenacimiento, delim);
    getline(ss, person.correo, delim);
    getline(ss, person.direccion, delim);
    ss >> person.numerodecasa;
    ss.ignore(10, delim);
    ss >> person.num;
    if (ss) persons.push_back(person);//se usa para insertar elementos en un vector desde atrás
  }

  for (unsigned int i = 0; i < persons.size(); i++) {
        std::cout<<"ALUMNO ["<< i+1 <<"]:\n"<<std::endl;
        cout <<"Carnet: " << persons[i].key <<"\nDPI: "<< persons[i].dpi
        <<"\nNombre: " << persons[i].name <<"\nSegundo Nombre: "<< persons[i].segundonombre
              <<"\nApellido Paterno: "<<persons[i].primerapellido<<"\nApellido Materno: "<<persons[i].segundoapellido
              <<"\nFecha De Nacimiento: "<<persons[i].fechadenacimiento<<"\nCorreo: "<<persons[i].correo
              <<"\nDireccion: "<<persons[i].direccion<<"\nNumero De Casa: "<<persons[i].numerodecasa<<"\nNumero Celular: "
              <<persons[i].num <<"\n"<< '\n';

    if (!root) root = make_unique<Node>(persons[i]);
    else root->insert(persons[i]);
  }
  }else{

  //system("cls");
  cout<<"\n\tNo se pudo abrir ese archivo, intente de nuevo"<<endl;
  system("pause");
  system("cls");
}
}
//---------------------------Funcion para la carga de el archivo Cursos--------------//
void cargaAlumnos(){

    string namefile, line;
    cout << "Ingrese nombre de archivo a cargar:" << endl;
    cin >> namefile;
    ifstream file;
    file.open(namefile.c_str());
    if(!file.is_open()) {
        cout << "\nArchivo "<< namefile <<" no encontrado, intente nuevamente\n" << endl;
        int main();
    }
    for (Archivocursos i;
        (file >> i.ID).ignore(numeric_limits<streamsize>::max(), ',')
        && getline(file, i.cursoganados, ',')
        && getline(file, i.fecha, ',')
        && getline(file, i.nota);
        )
    {
        cout<<"\n\nCurso: "<<i.cursoganados;
        cout<<"\nFecha: "<<i.fecha;
        cout<<"\nNota: "<<i.nota;
        agregarPila( &pila, i);
    }
    system("pause");
    file.close();
}
//-------------------------------------Funcion de busqueda en la pila por clave-----------------------//
void buscar(prtNodo cursor)
{
    if( cursor == NULL ) {
        cout << "\n\t\n\t-No hay datos cargados-\n";
        return;
    }
    intmax_t n;
    n=dato;
    bool found=false;
    //cout<<"\n\nIngrese carnet a bsucar: "<<endl;
    //cin>>dato;
    while( cursor != NULL ) {
            if(n==cursor->ID){
                cout<<"\n\tCarnet: "<<cursor->ID<<"\n";
                cout<<"\tCurso: "<<cursor->cursoganados<<"\n";
                cout<<"\tFecha: "<<cursor->fecha<<"\n";
                cout<<"\tNota: "<<cursor->nota<<"\n";
                found = true;
            }
            cursor = cursor->siguiente;
        }
        if(found==false){
        cout << "\n\t\tNo se econtraron cursos"<<endl;
    }
}

//----------------------------------Princio del programa-----------------------------------//
int main() {
    system("cls");//Menu del programa
    system("color f1"); //3,4,6,9
    cout<<"\n\t\t\t\tMENU\n"<<endl;
    cout << "\t\t1.Subir Archivo de Estudiantes"<<endl;
    cout<<"\t\t2.Subir Archivo de Cursos"<<endl;
    cout<<"\t\t3.Buscar Estudiante"<<endl;
    cout << "\t\t4.Mostrar recorrido en-orden de estudiantes"<<endl;
    cout<<"\t\t5.Mostrar recorrido pre-orden de estudiantes"<<endl;
    cout<<"\t\t6.Mostrar recorrido post-orden de estudiantes"<<endl;
    cout<<"\t\t7.Salir"<<endl;
    cout << "\n\tIngrese la Opcion a ejecutar: ";
    int opcion = 0;
    cin >> opcion;

//-------------------------Opciones del menu------------------------------------//
  switch(opcion)
    {
    case 1: {
        system("cls");
        carga();
        cout<<"\n\t\t -DATOS ENCONTRADOS-\n\n"<<endl;
        system("pause");
        main();
       // .......
    }break;
    case 2: {
        system("cls");
        cout<<"\n\t\t-Carga de Cursos-\n"<<endl;
        cargaAlumnos();

        system("pause");
        main();
    }break;
    case 3: {

        system("cls");
       // Archivocursos *pila = NULL;
        cout<<" Ingrese Carnet para buscar estudiante: "; cin>> dato;
        auto result =busqueda(root.get(),dato);
        if(result){
                cout<<"\n Alumno Encontrado"<<std::endl;
                cout<<"\n Datos:"<<std::endl;
                //std::cout<<"\n Carnet: "<<dato;
                cout<<"\n Carnet: "<<result->key;
                cout<<"\n Dpi: "<<result->dpi;
                cout<<"\n Primer Nombre: "<<result->name;
                cout<<"\n Segundo Nombre: "<<result->segundonombre;
                cout<<"\n Apellido Paterno: "<<result->primerapellido;
                cout<<"\n Apellido Materno: "<<result->segundoapellido;
                cout<<"\n Fecha de Nacimiento: "<<result->fechadenacimiento;
                cout<<"\n Correo: "<<result->correo;
                cout<<"\n Direccion :"<<result->direccion;
                cout<<"\n Numero De Casa: "<<result->numerodecasa;
                cout<<"\n Numero De Celular: "<<result->num;
                cout<<"\n"<<endl;
                cout<<"\n\n---------------------Cursos Ganados:--------------------\n"<<endl;
                buscar(pila);
                cout<<"\n";
         }
        else{
            std::cout<<"\n\tCarnet ["<<dato<<"] no existe en la base de datos.\n"<<std::endl;
        }

        system("pause");
        main();

    };
    case 4: {
         system("cls");
         cout << "\n\n\tDatos ordenados en order:\n\n";
         inorder(root.get());
         cout<<"\t\t-DATOS EN-ORDEN-\n\n"<<endl;
         system("pause");
         main();

    }break;
    case 5: {
        system("cls");
        cout<<"\n\n\tDatos ordenados en Preorden\n"<<endl;
        preOrden(root.get());
        cout<<"\t\t-DATOS ORDENADOS EN PRE-ORDEN-\n\n"<<endl;
        system("pause");
        main();
    }break;
    case 6: {

        system("cls");
        cout<<"\n\n\tDatos ordenados en Post-Orden\n"<<endl;
        postOrden(root.get());
        cout<<"\t\t-DATOS ORDENADOS EN POST-ORDEN-\n\n"<<endl;
        system("pause");
        main();
    }break;
    default: system("cls");cout << "\n\n\tSaliendo del programa....\n";
    exit(1);
    }

  return 0;
}//----------------------------------------FIN DEL PROGRAMA---------------------------------//

