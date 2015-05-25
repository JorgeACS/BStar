/*
    Autor: Jorge Arturo Carvajal Siller
    Programa: Arbol B
    Descripcion: Implementa una plantilla de Arbol B
    Fecha: 5/9/2015

    Ya hace splits basicos, falta checar si puede hacer splits multiples, y ver si es necesario implementar
    un tipo diferente de separacion de hijos (para cuando no es la raiz).

    Tambien remover LOL
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

void ArbolBAsteriscoInt();
void ArbolBAsteriscoChar();
void ArbolBAsteriscoCadena();

class Excepcion{
public:
    Excepcion(char *m){strcpy(mensaje, m);}
    char *getMensaje(){return mensaje;}

private:
    char mensaje[100];
};
////////////////////////////Clase Excepcion y derivadas
class NoHayMemoria: public Excepcion{
public:
    NoHayMemoria():Excepcion("No hay memoria."){}
};




class GradoIncorrecto: public Excepcion{
public:
    GradoIncorrecto():Excepcion("El grado del arbol tiene que estar entre 3 y 7."){}
};

class ColaVacia: public Excepcion
{
public:
    ColaVacia():Excepcion("Cola vacia...") {}
};
template<class T=int> class Cola;

template <class T> class Elemento
{
    friend class Cola<T>;
public:
    Elemento(T _info, Elemento * _sig = NULL): info(_info),sig(_sig) {}
private:
    T info;
    Elemento *sig;
};

template <class T> ostream & operator << (ostream &, const Cola<T> &);


template <class T>
class Cola{
      friend ostream & operator << <>(ostream &, const Cola<T> &);
public:
    Cola():primero(NULL),ultimo(NULL),tam(0){}
    Cola(const Cola<T> &);
    Cola<T> & operator=(const Cola &);
    ~Cola(){vaciar();}
    void removerElemento();
    void push(T);
    T pop();
    void vaciar(){while(!estaVacia())removerElemento();}
    void imprimir();
    bool estaVacia()const{return primero == NULL;}
    T elementoPrimero(){ if(!estaVacia()) return primero->info; throw ColaVacia();}
    int numeroElementos() {return tam;}
private:
    Elemento<T> * primero;
    Elemento<T> * ultimo;
    int tam;
};
////////////////////////////
//////////////////////////// Clase Cola
////////////////////////////

template<class T>
Cola<T>::Cola(const Cola<T> &C)
{
    primero = NULL;
    ultimo = NULL;
    tam = 0;
    *this = C;
}
/////////////////////////Operador =
template<class T>
Cola<T>& Cola<T>::operator=(const Cola<T> &C)
{
    if (!(this==&C)){
        vaciar();
        Elemento<T> *actual = C.primero;
        for(int i = 0; i < C.tam; i++)
        {
            push(actual->info);
            actual = actual->sig;
        }
        delete actual;
    }
    return *this;
}
template<class T>
void Cola<T>::push(T x){
    Elemento<T> * nuevo = new (nothrow) Elemento<T>(x);
    if(nuevo == NULL) throw NoHayMemoria();
    if(!estaVacia()) ultimo->sig = nuevo;
    else primero = nuevo;
    ultimo =  nuevo;
    tam++;
}
template<class T>
T Cola<T>::pop(){
    if(!estaVacia()){
        Elemento<T> * aux = primero;
        T x = aux->info;
        primero = primero->sig;
        delete aux;
        tam--;
        if(tam == 0) ultimo = NULL;
        return x;
    }
    throw ColaVacia();
}
template<class T>
void Cola<T>::removerElemento(){
     Elemento<T> * aux = primero;
     primero = primero->sig;
     delete aux;
     tam--;
}
template<class T>
void Cola<T>::imprimir(){
     if(!estaVacia()){
           Elemento<T> * aux = primero;
           cout << "Primero -> ";
           for(int i = 0; i < tam; i++){
               cout<<aux->info << ",";
               aux = aux->sig;
           }
           cout << "\b ";
    }else cout <<"No hay elementos..";
}

template<class T>
ostream & operator << (ostream &out, const Cola<T> &C)
{
    if (! ( C.estaVacia() ) )
    {
        Elemento<T> * aux = C.primero;
        cout << "Primero -> ";
        for(int i = 0; i < C.tam; i++){
            cout<<aux->info << ",";
            aux = aux->sig;
        }
        cout << "\b ";
    }
    else out << "No hay elementos..";
    return out;
}
/////////////////////
/////////////////////Fin de clase Cola
/////////////////////




/////////////////////
///////////////////// Clase Cadena
/////////////////////
class IndiceNoValido: public Excepcion{
public:
    IndiceNoValido():Excepcion("El indice no fue valido."){}
};
class Cadena{
   friend ostream& operator << (ostream &, const Cadena &);
   friend istream & operator >> (istream &, Cadena &);
public:

   Cadena(char* C =  NULL);
   Cadena(const Cadena &);
   ~Cadena(){delete [] cadena;}
   void operator +=(Cadena);
   bool operator ! () const { return !(cadena[0] == '\0');}
   bool operator == (Cadena) const;
   bool operator> (Cadena info){return longitudCadena() > info.longitudCadena();}
   bool operator<(Cadena info){return longitudCadena() < info.longitudCadena();}
   char & operator [](int );
   char operator[](int) const;
   bool operator!=(Cadena C) const{return !(*this == C);}
   Cadena& operator = (const Cadena &);
   int longitudCadena(){return tam;}
   Cadena subCadena(int = 0, int = 0);
   void convertirMinusculas();
   void convertirMayusculas();
private:
   char * cadena;
   int tam;

};
///////////////////////////////////////////////////Constructor normal
Cadena::Cadena(char* C):tam(0){
   if(C == NULL){
      cadena = new (nothrow) char[1];
      if(cadena == NULL) throw NoHayMemoria();
      cadena[0] = '\0';
   }
   else{
        for(int i = 0; C[i] != '\0';i++,tam++);
        cadena = new (nothrow) char[tam+1];
        if(cadena == NULL) throw NoHayMemoria();
        cadena[tam] = '\0';
        for (int i = 0; i < tam; i++) cadena[i] = C[i];
   }
}
//////////////////////////////////////////////////Constructor de copias
Cadena::Cadena(const Cadena &C){
   tam = -1;
   cadena = NULL;
   *this = C;
}
//////////////////////////////////////////////////////Sobrecarga del operador=
Cadena& Cadena::operator=(const Cadena &C){
   if (!(this==&C)){
      if (tam != C.tam){
         delete [] cadena;
         cadena = new (nothrow) char[C.tam];
         if(cadena == NULL) throw NoHayMemoria();
         tam = C.tam;
      }
      for(int i = 0; i < tam; i++) cadena[i] = C.cadena[i];
   }
   return *this;
}
///////////////////////////////////Sobrecarga del operador de comparacion
bool Cadena::operator==(Cadena C) const{
   if (this==&C) return true;
   if (tam != C.tam) return false;
   bool esIgual = true;
   for(int i = 0; i < tam; i++) if (cadena[i] != C.cadena[i]){
      esIgual = false;
      break;
   }
   return esIgual;
}
////////////////////////////////////////////////lvalue y rvalue
char & Cadena::operator [](int x){
    if (x < 0 || x >=tam) throw IndiceNoValido();
    return cadena[x];
}
char Cadena::operator[](int x) const{
    if (x < 0 || x >=tam) throw IndiceNoValido();
    return cadena[x];
}
//////////////////////////////////////////Convertir a mayusculas/minusculas
void Cadena::convertirMayusculas(){
   for(int i = 0; i < tam; i++){
      if ((int)cadena[i] >= 97 && (int)cadena[i] <= 122) cadena[i] = char((int)cadena[i] - 32);
   }
}
void Cadena::convertirMinusculas(){
   for(int i = 0; i < tam; i++){
      if ((int)cadena[i] >= 65 && (int)cadena[i] <= 90) cadena[i] = char((int)cadena[i] + 32);
   }
}
//////////////////////////////////////////////////Operadores cout y cin
ostream& operator << (ostream &out, const Cadena &C){
   for (int i = 0; i < C.tam ;i++) out << C.cadena[i];
   return out;
}

istream & operator >> (istream &in, Cadena &C){
      char* aux = new (nothrow) char[100];
      if(aux == NULL) throw NoHayMemoria();
      for(int i = 0; i < 100; i++) aux[i] = '\0';
      in.sync();
      in.getline(aux,100);
      Cadena B(aux);
      C = B;
      delete [] aux;
      return in;
}
///////////////////////////////////////////////////Subcadena
Cadena Cadena::subCadena(int indice, int length){

    if(indice  < 0 || indice >= tam) {
        throw IndiceNoValido();
    }
   char * aux = new (nothrow) char[length+1];
   if(aux == NULL) throw NoHayMemoria();
   aux[length] = '\0';
   int i = 0;
   for(; i < length;i++) {
		if(indice + i >= tam) break;
      aux[i] = cadena[indice+i];
   }
   aux[i] = '\0';
   Cadena auxiliar(aux);
   delete [] aux;
   return auxiliar;
}
////////////////////////////////////////////////////Sobrecarga del operador +=
void Cadena::operator += (Cadena C){
   Cadena aux = *this;
   delete[]cadena;
   cadena = new (nothrow) char[aux.tam+C.tam + 1];
   if(cadena == NULL) throw NoHayMemoria();
   cadena[aux.tam+C.tam] = '\0';
   tam = aux.tam+C.tam;
   for(int i = 0; i < aux.tam; i++) cadena[i] = aux.cadena[i];
   for(int i = 0; i < C.tam; i++) cadena[aux.tam+i] = C.cadena[i];
}

/////////////////////
///////////////////// Fin de clase Cadena
/////////////////////








//Declaracion anticipada de Arbol B
template<class T = int, int grado = 3> class ArbolBAsterisco;

//Clase Nodo
template<class T = int, int grado = 3>
class Nodo{
    friend class ArbolBAsterisco<T,grado>;
public:
    Nodo(Nodo<T,grado> * papi = NULL):topeHijos(0),topeValores(0),padre(papi),maximo(grado-1),minimo((grado-1)*(2.0/3.0)){};
private:
    bool tieneHijos(){return (topeHijos > 0);}
    bool insertar(T,int);
    void InsercionInOrden(Nodo<T,grado> *);
    void vaciar();
    bool insercion(T);
    void imprimir();
    void merge(int);
    void mergeRaiz(int);
    bool buscar(T);
    bool remover(T,int);
    void splitHijos(Nodo<T,grado>*);
    void balancear(int);
    void imprimirArreglo();
    void insercionHermano(Nodo<T,grado>*,int indice);
    void impresionAscendente();
    void impresionDescendente();
    void split(int);
    void splitRaiz();
    bool quitar(T);

    Nodo<T,grado>* padre;
    int minimo;
    int maximo;
    Nodo<T,grado> *hijos [(int)  (( (grado-1)*2.0/3.0) *2 + 2)];
    T valores[(int) (( (grado-1)*2.0/3.0) *2 + 1 )];
    int topeValores;
    int topeHijos;
};
template<class T, int grado>
void Nodo<T,grado>::vaciar(){
    for(int i = 0; i <topeHijos;i++)hijos[i]->vaciar();
    delete this;
    return;
}
//////////////////////////////Metodo auxiliar para buscar en el arbol
template<class T, int grado>
bool Nodo<T,grado>::buscar(T info){
    int index = 0;
    while(index < topeValores && info > valores[index])index++;
    if(valores[index] == info)return true;
    else{
        if(tieneHijos()) return hijos[index]->buscar(info);
        else return false;
    }
}
//////////////////////////////Remover nodo
template<class T, int grado>
bool Nodo<T,grado>::remover(T info, int index){
    //cout<<endl;
    //out<<"estamos en el nodo: ";
    //imprimirArreglo();
    //cout<<endl;
    if(topeValores == 0)return false;
    int indice = 0;
    //cout<<endl<<endl;
    while(indice < topeValores && info > valores[indice]) indice++;
    //cout <<"indice donde entro: "<<indice<<endl;
    if( indice < topeValores && info ==  valores[indice]){
        if(!tieneHijos()){
            quitar(info);
            if(topeValores < minimo && padre != NULL)balancear(index);
        }else{
            Nodo<T,grado> * mayorMenores = hijos[indice];
            while(mayorMenores->tieneHijos())mayorMenores = mayorMenores->hijos[ mayorMenores-> topeHijos-1];
            valores[indice] = mayorMenores->valores[mayorMenores->topeValores-1];
            mayorMenores->topeValores--;
            while(mayorMenores != hijos[indice]){
                Nodo<T,grado> *papi = mayorMenores->padre;
                if(mayorMenores -> topeValores < minimo)mayorMenores->balancear(mayorMenores->padre->topeHijos-1);
                mayorMenores=papi;
            }
            if(mayorMenores->topeValores < minimo)mayorMenores->balancear(indice);
            if(topeValores < minimo && padre!=NULL)balancear(index);
        }
        return true;
    }else{
        if(!tieneHijos())return false;
        if(! hijos[indice]->remover(info,indice)) return false;
        if(topeValores < minimo && padre != NULL){
                cout<<"balanceando";
                system("pause");
                balancear(index);
        }
        return true;
    }
}
//////////////////////////////////Metodo merge (Al remover,raiz)
template<class T, int grado>
void Nodo<T,grado>::mergeRaiz(int index){
    if(index > 0 ){
        Nodo<T,grado> *hermano = padre->hijos[index-1];
        hermano->insercion(padre->valores[index-1]);
        padre->quitar(padre->valores[index-1]);
        for(int i = 0; i < minimo-1; i++) hermano->insercion(valores[i]);
        for(int i = 0; i < topeHijos;i++){
            hermano->hijos[hermano->topeHijos] = hijos[i];
            hermano->hijos[hermano->topeHijos]->padre = hermano;
            hermano->topeHijos++;
        }
    }else{
        Nodo<T,grado> *hermano = padre->hijos[index+1];
        hermano->insercion(padre->valores[index]);
        padre->quitar(padre->valores[index]);
        for(int i = 0; i < minimo-1;i++)hermano->insercion(valores[i]);

        for(int i = 0; i < topeHijos;i++){
            for(int j = hermano->topeHijos; j > 0;j--) hermano->hijos[j] = hermano->hijos[j-1];
            hermano->hijos[i] = hijos[i];
            hermano->hijos[i]->padre = hermano;
            hermano->topeHijos++;
        }
    }
    padre->topeHijos--;
    for(int i = index; i < padre->topeHijos;i++) padre->hijos[i] = padre->hijos[i+1];
    delete this;
    return;
}
//////////////////////////////////Metodo merge (Al remover)
template<class T, int grado>
void Nodo<T,grado>::merge(int index){
    Nodo<T,grado> *hermano1, *hermano2;
    if(index == 0){
        hermano1 = padre->hijos[1];
        hermano2 = padre->hijos[2];
        T arreglo[topeValores+hermano1->topeValores+hermano2->topeValores+2];
        int i = 0;
        for(;i < topeValores;i++)arreglo[i] = valores[i];
        T aux1 = padre->valores[0];
        T aux2 = padre->valores[1];
        padre->quitar(aux1);
        arreglo[i] = aux1;
        i++;
        for(int j = 0; j < hermano1->topeValores;j++,i++)arreglo[i] = hermano1->valores[j];
        padre->quitar(aux2);
        arreglo[i] = aux2;
        i++;
        for(int j = 0; j < hermano2->topeValores;j++,i++)arreglo[i] = hermano2->valores[j];
        i = 0;
        //metemos
        for(;i < maximo; i++)valores[i] = arreglo[i];
        padre->insercion(arreglo[i]);
        i++;
        int resto = ((topeValores+hermano1->topeValores+hermano2->topeValores+2) - i);
        hermano1->topeValores = 0;
        for(int j = 0; j < resto; j++,i++) {
            hermano1->valores[j] = arreglo[i];
            hermano1->topeValores++;
        }
        topeValores = resto;

        for(int j = 2;j < padre->topeHijos-1;j++) padre->hijos[j] = padre->hijos[j+1];
        padre->topeHijos--;

        if(tieneHijos()){
            for(int i =0;i<topeValores+1-topeHijos;++i){
                hijos[topeHijos+i] = hermano1->hijos[0];
                hijos[topeHijos+i]->padre = this;
                hermano1->topeHijos--;
                for(int j=0;j<hermano1->topeHijos;++j)
                    hermano1->hijos[j] = hermano1->hijos[j+1];
            }
            topeHijos=topeValores+1;
            for(int i=0;i<hermano2->topeHijos;++i){
                hermano1->hijos[hermano1->topeHijos+i] = hermano2->hijos[i];
                hermano1->hijos[hermano1->topeHijos+i]->padre = hermano1;
            }
            hermano1->topeHijos+=hermano2->topeHijos;
        }
        delete hermano2;
        return;
   }
    if(index == padre->topeHijos-1){
        hermano2 = padre->hijos[index-1];
        hermano1 = padre->hijos[index-2];
        T arreglo[topeValores+hermano1->topeValores+hermano2->topeValores+2];
        int i = 0;
        for(;i < hermano1->topeValores;i++)arreglo[i] = hermano1->valores[i];
        T aux1 = padre->valores[padre->topeValores-2];
        T aux2 = padre->valores[padre->topeValores-1];
        padre->quitar(aux1);
        arreglo[i] = aux1;
        i++;
        for(int j = 0; j < hermano2->topeValores;i++,j++)arreglo[i] = hermano2->valores[j];
        padre->quitar(aux2);
        arreglo[i] = aux2;
        i++;
        for(int j = 0; j < topeValores;i++,j++) arreglo[i] = valores[j];

        for(int j =0;j<i;++j) cout<<arreglo[j]<<", ";

        i = 0;
        //insertamos
        for(; i <maximo;i++)hermano1->valores[i] = arreglo[i];
        padre->insercion(arreglo[i]);
        i++;
        int resto = (topeValores+hermano1->topeValores+hermano2->topeValores+2) - i;
        hermano2->topeValores = 0;

        for(int j = 0; j < resto; j++,i++){
                hermano2->valores[j] = arreglo[i];
                hermano2->topeValores++;
        }
        hermano1->topeValores = resto;

        padre->topeHijos--;

        if(tieneHijos()){
            for(int i =0;i<hermano1->topeValores+1-hermano1->topeHijos;++i){
                hermano1->hijos[hermano1->topeHijos+i] = hermano2->hijos[0];
                hermano1->hijos[hermano1->topeHijos+i]->padre = hermano1;
                hermano2->topeHijos--;
                for(int j=0;j<hermano2->topeHijos;++j)
                    hermano2->hijos[j] = hermano2->hijos[j+1];// esta wea sabe :c
            }
            hermano1->topeHijos=hermano1->topeValores+1;
            for(int i=0;i<topeHijos;++i){
                hermano2->hijos[hermano2->topeHijos+i] = hijos[i];
                hermano2->hijos[hermano2->topeHijos+i]->padre = hermano2
                ;
            }
            hermano2->topeHijos+=topeHijos;
        }
        delete this;
        return;
    }
    hermano1 = padre->hijos[index-1];
    hermano2 = padre->hijos[index+1];

    T arreglo[topeValores+hermano1->topeValores+hermano2->topeValores+2];
    int i = 0;
    for(;i < hermano1->topeValores;i++)arreglo[i] = hermano1->valores[i];
    T aux1 = padre->valores[index-1];
    T aux2 = padre->valores[index];
    padre->quitar(aux1);
    padre->quitar(aux2);
    arreglo[i] = aux1;
    i++;
    for(int j = 0; j < topeValores;i++,j++) arreglo[i] = valores[j];
    arreglo[i] = aux2;
    i++;
    //
    for(int j = 0; j < hermano2->topeValores;i++,j++) arreglo[i] = hermano2->valores[j];
    i = 0;
    for(; i < maximo;i++){
        hermano1->valores[i] = arreglo[i];
    }
    cout <<"en padre insertamos el " <<  arreglo[i];
    padre->insercion(arreglo[i]);
    i++;
    int resto = (topeValores+hermano1->topeValores+hermano2->topeValores+2) - i;
    hermano2->topeValores = 0;
    for(int j = 0; j < resto;j++,i++){
        hermano2->valores[j] = arreglo[i];
        hermano2->topeValores++;
    }
    hermano1->topeValores = resto;

    for(int j = index;j < padre->topeHijos-1;j++)padre->hijos[j] = padre->hijos[j+1];
    padre->topeHijos--;

    if(tieneHijos()){
        int i;
        for(i=0;i<hermano1->topeValores+1-hermano1->topeHijos;++i){
            hermano1->hijos[hermano1->topeHijos+i] = hijos[i];
            hermano1->hijos[hermano1->topeHijos+i]->padre  = hermano1;
        }
        hermano1->topeHijos+=i;

        int resto = hermano2->topeValores+1-hermano2->topeHijos;
        for(int j=0;j<resto;++j){
            for(int k=0;k<hermano2->topeHijos;++k)
                hermano2->hijos[hermano2->topeHijos-k] = hermano2->hijos[hermano2->topeHijos-1-k];
            hermano2->hijos[0] = hijos[topeHijos-1-j];
            hermano2->hijos[0]->padre = hermano2;
            hermano2->topeHijos++;
        }
    }

    delete this;
    return;
}
////////////////////////////////////Metodo balancear(Decide si pedir prestado de sus hermanos, o hacer merge)
template<class T, int grado>
void Nodo<T,grado>::balancear(int index){
    if(index > 0){
        Nodo<T,grado>*hermano  = padre->hijos[index-1];
        if(hermano->topeValores > minimo){
           insercion(padre->valores[index-1]);
           padre->valores[index-1] = hermano ->valores[hermano->topeValores-1];
           hermano->quitar(hermano->valores[hermano->topeValores-1]);
           if(tieneHijos()){
               for(int i = 0; i < topeHijos;i++)hijos[topeHijos-i] = hijos[topeHijos-1-i];
               hijos[0] = hermano -> hijos [hermano->topeHijos-1];
               hijos[0]->padre = this;
               topeHijos++;
               hermano->topeHijos--;
           }
           return;
        }else
            if(index==padre->topeHijos-1 && index-1>0 && padre->hijos[index-2]->topeValores>minimo){
                insercion(padre->valores[index-1]);
                padre->valores[index-1] = hermano ->valores[hermano->topeValores-1];
                hermano->quitar(hermano->valores[hermano->topeValores-1]);
                if(tieneHijos()){
                    for(int i = 0; i < topeHijos;i++)hijos[topeHijos-i] = hijos[topeHijos-1-i];
                    hijos[0] = hermano -> hijos [hermano -> topeHijos-1];
                    hijos[0]->padre = this;
                    topeHijos++;
                    hermano->topeHijos--;
                }
                hermano->insercion(padre->valores[index-2]);
                padre->valores[index-2] = padre->hijos[index-2]->valores[padre->hijos[index-2]->topeValores-1];
                padre->hijos[index-2]->quitar(padre->hijos[index-2]->valores[padre->hijos[index-2]->topeValores-1]);
                if(tieneHijos()){
                    for(int i = 0; i < hermano->topeHijos;i++)hermano->hijos[hermano->topeHijos-i] = hermano->hijos[hermano->topeHijos-1-i];
                    hermano->hijos[0] = padre->hijos[index-2] -> hijos [padre->hijos[index-2] -> topeHijos-1];
                    hermano->hijos[0] -> padre = hermano;
                    hermano->topeHijos++;
                    padre->hijos[index-2]->topeHijos--;
                }
                return;
        }
    }
    if(index+1 < padre->topeHijos){
        Nodo<T,grado> * hermano = padre->hijos[index+1];
        if(hermano->topeValores > minimo){
           insercion(padre->valores[index]);
           padre->valores[index] = hermano-> valores[0];
           hermano->quitar(hermano->valores[0]);
           if(tieneHijos()){
                hijos[topeHijos] = hermano -> hijos [0];
                hijos[topeHijos]->padre = this;
               for(int i = 0; i < hermano->topeHijos;i++)hermano->hijos[i] = hermano->hijos[i+1];
               topeHijos++;
               hermano->topeHijos--;
           }
           return;
        }else
            if(index==0 && index+2 < padre->topeHijos && padre->hijos[index+2]->topeValores>minimo){
                insercion(padre->valores[index]);
                padre->valores[index] = hermano-> valores[0];
                hermano->quitar(hermano->valores[0]);
                if(tieneHijos()){
                    hijos[topeHijos] = hermano -> hijos [0];
                    hijos[topeHijos]->padre = this;
                   for(int i = 0; i < hermano->topeHijos;i++)hermano->hijos[i] = hermano->hijos[i+1];
                   topeHijos++;
                   hermano->topeHijos--;
                }
                hermano->insercion(padre->valores[index+1]);
                padre->valores[index+1] = padre->hijos[index+2]->valores[0];
                padre->hijos[index+2]->quitar(padre->hijos[index+2]->valores[0]);
                if(tieneHijos()){
                    hermano->hijos[hermano->topeHijos] = padre->hijos[index+2]-> hijos [0];
                    hermano->hijos[hermano->topeHijos]->padre = hermano;
                   for(int i = 0; i < padre->hijos[index+2]->topeHijos;i++)padre->hijos[index+2]->hijos[i] = padre->hijos[index+2]->hijos[i+1];
                   hermano->topeHijos++;
                   padre->hijos[index+2]->topeHijos--;
                }
           return;
            }
    }
    //cout<<"asjdhasgdashdgasdasjd"<<endl;
    if(padre->padre == NULL && padre->topeValores==1) mergeRaiz(index);
    else merge(index);
    return;
}
////////////////////////////////////Metodo auxiliar para remover un elemento del arreglo (Reordena si es necesario)
template<class T, int grado>
bool Nodo<T,grado>::quitar(T info){
    int index = 0;
    while( index < topeValores && info != valores[index])index++;
    for(int i = index; i < topeValores-1;i++)valores[i] = valores[i+1];
    topeValores--;
    return true;
}
///////////////////////////////////Metodo auxiliar para imprimir un nodo (Para pruebas)
template<class T, int grado>
void Nodo<T,grado>::imprimirArreglo(){
    cout << "[";
    for(int i = 0; i < topeValores;i++) cout << valores[i] << ",";
    cout << "\b]";
}
///////////////////////////////////Metodo auxiliar para imprimir ascendente
template<class T, int grado>
void Nodo<T,grado>::impresionAscendente(){
    if(!tieneHijos()) for(int i = 0; i < topeValores; i++) cout << valores[i] << endl;
    else{
        for(int i = 0; i < topeValores;i++){
            hijos[i]->impresionAscendente();
            cout << valores[i] << endl;
        }
        hijos[topeHijos-1]->impresionAscendente();
    }
}
//////////////////////////////////////////Metodo auxiliar para imprimir descendente
template<class T, int grado>
void Nodo<T,grado>::impresionDescendente(){
    if(!tieneHijos()) for(int i = topeValores-1; i >= 0; i--) cout << valores[i] << endl;
    else{
        for(int i = topeValores; i > 0;i--){
            hijos[i]->impresionDescendente();
            cout << valores[i-1] << endl;
        }
        hijos[0]->impresionDescendente();
    }
}
//////////////////////////////////////Insertar en el nodo
template<class T, int grado>
bool Nodo<T,grado>::insertar(T info, int index){
    if(! tieneHijos() ){
        if(!insercion(info))return false;
        //
        //****************************************************************************************************************
        //cout << "Estamos en:"; imprimirArreglo();
        //cout << endl;
        //*******************************************************************************************************************
        if(padre == NULL){
            if(topeValores == (minimo*2)+1){
                splitRaiz();
            }
        }else{
            if(topeValores == grado){cout << "haciendo split" << endl; split(index);}
        }
        return true;
    }
    int indice = 0;
    while(indice < topeValores && info > valores[indice]) indice++;
    if( indice < topeValores && info ==  valores[indice]) return false;
    if(! hijos[indice]->insertar(info,indice)) return false;
   // cout << "despues de insertar" << info;
    //system("pause");
    if(padre == NULL){
        if(topeValores == (minimo*2)+1) splitRaiz();
    }else{
        if(topeValores == grado) split(index);
    }
    return true;
}
////////////////////////////////////Metodo auxiliar para insertar en el arreglo(Reordena si es necesario)
template<class T, int grado>
bool Nodo<T,grado>::insercion( T info){

    int index = 0;
    while(index < topeValores) {
        if(valores[index] == info) return false;
        if(info < valores[index]) break;
        else index++;
    }
    for(int i = topeValores; i > index;i--) valores[i] = valores[i-1];
    valores[index] = info;
    topeValores++;

    return true;
}
////////////////////////////////////Metodo split(Al insertar)

/*
template<class T, int grado>
void Nodo<T,grado>::split(int index){
    Nodo<T,grado> * hermano;
    hermano  = new (nothrow) Nodo<T,grado>(padre);
    if(hermano == NULL) throw NoHayMemoria();
    padre->insercion(valores[minimo]);
    for(int i = minimo+1; i < topeValores;i++)hermano->insercion(valores[i]);
    padre->insercionHermano(hermano,index);
    topeValores = minimo;
    if(tieneHijos()){  cout <<"el minimo en insertar es "<< minimo << endl;

        splitHijos(hermano);
    }
}
*/


template<class T, int grado>
void Nodo<T,grado>::split(int index){
    if(index > 0){
         Nodo<T,grado> * hermano = padre->hijos[index-1];
        if(hermano-> topeValores < maximo){
            hermano->insercion(padre->valores[index-1]);//good
            padre->valores[index-1] = valores[0];
            quitar(valores[0]);
             if(tieneHijos()){
                Nodo<T,grado> *hijoReacomodar = hijos[0];
                topeHijos--;
                for(int i = 0; i <topeHijos;i++)hijos[i] = hijos[i+1];

                hermano->hijos[hermano->topeHijos] = hijoReacomodar;
                hermano->hijos[hermano->topeHijos]->padre = hermano;
                hermano->topeHijos++;
            }
            return;
        }
    }
    if(index+1 < padre->topeHijos){
        Nodo<T,grado> * hermano = padre->hijos[index+1];
        if(hermano->topeValores < maximo){
           hermano->insercion(padre->valores[index]);
           padre->valores[index] = valores[topeValores-1];
           quitar(valores[topeValores-1]);
            if(tieneHijos()){
                Nodo<T,grado> *hijoReacomodar = hijos[topeHijos-1];
                topeHijos--;
                for(int i = hermano->topeHijos; i >= 0;i--)hermano->hijos[i+1] = hermano->hijos[i];
                hermano->hijos[0] = hijoReacomodar;
                hermano->hijos[0]->padre = hermano;
                hermano->topeHijos++;
            }
           return;
        }
    }
    if(index > 0){
        //Pasamos los valores requeridos a un arreglo
        Nodo<T,grado> *nuevoHermano = new Nodo<T,grado> (padre);
        Nodo<T,grado> *hermano = padre->hijos[index-1];
        T aux = padre->valores[index-1];
        padre->quitar(padre->valores[index-1]);
        T arreglo[topeValores+hermano->topeValores+1];
        int i = 0;
        for(;i < hermano->topeValores;i++) arreglo[i] = hermano->valores[i];
        arreglo[i] = aux;
        i++;
        for(int j = 0;j < topeValores;i++,j++) arreglo[i] = valores[j];
        i = 0;
        //ahora insertamos donde debemos (Hermano-Instancia-NuevoHermano)
        for(; i < minimo;i++) hermano->valores[i] = arreglo[i];

        padre->insercion(arreglo[i]);
        i++;

        for(int j = 0; j < minimo;j++,i++) {
                valores[j] = arreglo[i];
        }

        padre->insercion(arreglo[i]);
        i++;

        for(int j = 0; i < topeValores+hermano->topeValores+1;i++,j++){
            nuevoHermano->valores[j] = arreglo[i];
            nuevoHermano->topeValores++;
        }
        //Aqui hacemos la separacion de los hijos en los 3 nodos, si es necesario
        if(tieneHijos()){
            Nodo<T,grado>* auxHijos[topeHijos+hermano->topeHijos];
            int i = 0;
            for(; i < hermano->topeHijos;i++) auxHijos[i] = hermano->hijos[i];
            for(int j = 0; j < topeHijos;j++,i++) auxHijos[i] = hijos[j];
            i = 0;
            //(Hermano-Instancia-NuevoHermano)
            for(; i < minimo+1;i++) hermano->hijos[i] = auxHijos[i];
            for(int j = 0; j < minimo+1; j++,i++){
                    hijos[j] = auxHijos[i];
                    hijos[j]->padre = this;
            }
            int resto = (topeHijos+hermano->topeHijos) - i;
            nuevoHermano->topeHijos = 0;
            for(int j = 0;j < resto;i++,j++){
                nuevoHermano->hijos[j] = auxHijos[i];
                nuevoHermano->hijos[j]->padre = nuevoHermano;
                nuevoHermano->topeHijos++;
            }
            topeHijos = minimo+1;
            hermano->topeHijos = minimo+1;
        }
        topeValores = minimo;
        hermano->topeValores = minimo;
        padre->insercionHermano(nuevoHermano,index);
        //cout << topeHijos << ","<< hermano->topeHijos <<","<< nuevoHermano << endl;
       // system("pause");
        return;
    }
    //esto es para el otro caso (Instancia-Nuevo hermano-Hermano)
    Nodo<T,grado> *nuevoHermano = new Nodo<T,grado> (padre);
    Nodo<T,grado> *hermano = padre->hijos[index+1];
    T aux = padre->valores[index];
    padre->quitar(padre->valores[index]);
    T arreglo[topeValores+hermano->topeValores+1];
    int i = 0;

    for(;i < topeValores;i++) arreglo[i] = valores[i];
    arreglo[i] = aux;
    i++;
    for(int j = 0;j < hermano->topeValores;i++,j++) arreglo[i] = hermano->valores[j];
    i = 0;

    for(; i < minimo;i++) valores[i] = arreglo[i];

    padre->insercion(arreglo[i]);
    i++;

    for(int j = 0; j < minimo;j++,i++) {
            nuevoHermano->valores[j] = arreglo[i];
            nuevoHermano->topeValores++;
    }

    padre->insercion(arreglo[i]);
    i++;
    int hermanoTopeValores = hermano->topeValores;
    for(int j = 0; i < topeValores+hermanoTopeValores+1;i++,j++) hermano->valores[j] = arreglo[i];
    /////////////Aqui separamos los hijos en los 3 nodos que tenemos, si es necesario
    if(tieneHijos()){
        Nodo<T,grado>* auxHijos[topeHijos+hermano->topeHijos];
        int i = 0;
        for(; i < topeHijos;i++) auxHijos[i] = hijos[i];
        for(int j = 0; j < hermano->topeHijos;j++,i++) auxHijos[i] = hermano->hijos[j];
        i = 0;
        //instancia-nuevo hermano-hermano
        for(; i < minimo+1;i++) hijos[i] = auxHijos[i];
        for(int j = 0; j < minimo+1; j++,i++){
                nuevoHermano->hijos[j] = auxHijos[i];
                nuevoHermano->hijos[j]->padre = nuevoHermano;
        }
        int resto = (topeHijos+hermano->topeHijos) - i;
        hermano->topeHijos = 0;
        for(int j = 0;j < resto;i++,j++){
                hermano->hijos[j] = auxHijos[i];
                hermano->hijos[j]->padre = hermano;
                hermano->topeHijos++;
        }
        topeHijos = minimo+1;
        nuevoHermano->topeHijos = minimo+1;
    }


    topeValores = minimo;
    hermano->topeValores = minimo;
    padre->insercionHermano(nuevoHermano,index);
}

//////////////////////////////////Split pa la raiz(Al insertar)
template<class T, int grado>
void Nodo<T,grado>::splitRaiz(){
    Nodo<T,grado> * hermano;
    Nodo<T,grado> * papi = new (nothrow) Nodo<T,grado>();
    if(papi == NULL) throw NoHayMemoria();
    hermano = new (nothrow) Nodo<T,grado>(papi);
    if(hermano == NULL) throw NoHayMemoria();
    papi->insercion(valores[minimo]);
    papi->hijos[0] = this;
    papi->hijos[1] = hermano;
    for(int i = minimo+1; i < topeValores;i++)hermano->insercion(valores[i]);
    topeValores = minimo;
    papi->topeHijos=2;
    if(tieneHijos()){
        splitHijos(hermano);
    }
    this->padre = papi;
    return ;
}
////////////////////////////////////////////Metodo auxiliar del split(para darle los hijos que le corresponden al nuevo hermano
template<class T, int grado>
void Nodo<T,grado>::splitHijos(Nodo<T,grado> *hermano){
    for(int i = minimo+1; i <topeHijos;i++){
                hermano->hijos[i-(minimo+1)] = hijos[i];
                hermano->hijos[i-(minimo+1)]->padre  = hermano;
    }
    hermano->topeHijos = topeHijos -(minimo+1);
    topeHijos = minimo+1;
    //hermano->topeHijos = grado+1-topeHijos;
}
///////////////////////////////////////////Metodo auxiliar del split(Para insertar el nuevo hermano en los hijos del padre)
template<class T, int grado>
void Nodo<T,grado>::insercionHermano(Nodo<T,grado> * hermano,int indice){
    for(int i = topeHijos; i > indice+1;i--)hijos[i] = hijos[i-1];
    hijos[indice+1] = hermano;
    topeHijos++;
}
/////////////////////////////////////////Metodo imprimir para pruebas
template<class T, int grado>
void Nodo<T,grado>::imprimir(){
    cout << '[';
    for(int i= 0; i < topeValores;i++)cout << valores[i] << ",";
    cout <<"P:";
    if(padre == NULL)  cout << "'0;";
    else padre->imprimirArreglo();
    cout << ",topeValores:" << topeValores << ",";
    cout << "topeHijos:" << topeHijos<<",";
    cout << "\b]" << endl;
    for(int i = 0; i < topeHijos;i++)hijos[i]->imprimir();
}
////////////////////////////////Clase Arbol B
template<class T, int grado>
class ArbolBAsterisco{
public:
    ArbolBAsterisco():raiz(new (nothrow) Nodo<T,grado>()){
        if(grado < 3 || grado > 7 ) throw GradoIncorrecto();
        if(raiz == NULL) throw NoHayMemoria();
    }
    ~ArbolBAsterisco(){raiz->vaciar();}
    void impresionAscendente(){raiz->impresionAscendente();}
    void impresionDescendente(){raiz->impresionDescendente();}
    ArbolBAsterisco(const ArbolBAsterisco &AB):raiz(NULL){*this = AB;}
    ArbolBAsterisco & operator = (const ArbolBAsterisco &);
    bool insertar(T);
    bool remover(T);
    bool buscar(T info){return raiz->buscar(info);}
    void vaciar();
    bool estaVacio();
    void impresionPorNiveles();
    void imprimir(){raiz->imprimir();}
private:
    Nodo<T,grado> *raiz;
};
///////////////////////////////Operador = del Arbol
template<class T, int grado>
ArbolBAsterisco<T,grado> & ArbolBAsterisco<T,grado>::operator = (const ArbolBAsterisco & AB){
    if(this != &AB){
        if(raiz == NULL){
            raiz = new (nothrow) Nodo<T,grado>;
            if(raiz == NULL) throw NoHayMemoria();
        }
        vaciar();
        raiz->InsercionInOrden(AB.raiz);
    }
    return *this;
}
////////////////////////////////Metodo auxiliar para el operador = del arbol
template<class T, int grado>
void Nodo<T,grado>::InsercionInOrden(Nodo<T,grado> *aux ){
    for(int i = 0; i < aux->topeValores;i++) valores[i] = aux->valores[i];
    for(int i = 0; i < aux->topeHijos;i++){
        hijos[i] = new (nothrow) Nodo<T,grado>(this);
        if(hijos[i] == NULL) throw NoHayMemoria();
        hijos[i]->InsercionInOrden(aux->hijos[i]);
    }
    topeHijos = aux->topeHijos;
    topeValores = aux->topeValores;
}

//////////////////////////////////Metodo para vaciar el Arbol
template<class T, int grado>
void ArbolBAsterisco<T,grado>::vaciar(){
    for(int i = 0; i < raiz->topeHijos;i++)raiz->hijos[i]->vaciar();
    raiz->topeHijos = 0;
    raiz->topeValores = 0;
}
//////////////////////////////////Metodo para remover un elemento del arbol
template<class T, int grado>
bool ArbolBAsterisco<T,grado>::remover(T info){
    if(!raiz->remover(info,0))return false;
    if(raiz->topeValores == 0 && raiz->tieneHijos()){
        Nodo<T,grado>* padre = raiz;
        raiz = raiz->hijos[0];
        delete padre;
        raiz->padre = NULL;
    }
    return true;
}
////////////////////////////////////Metodo para insertar un elemento en el arbol
template<class T, int grado>
bool ArbolBAsterisco<T,grado>::insertar(T info){
    int elementos = raiz->topeValores;
    bool seInserto = raiz->insertar(info,0);
    if(!seInserto) return false;
    if(raiz->topeValores < elementos) raiz = raiz->padre;
}
///////////////////////////////////Metodo para imprimir el arbol por niveles
template<class T, int grado>
void ArbolBAsterisco<T,grado>::impresionPorNiveles(){
    Cola< Nodo<T,grado> * > cola;
    cola.push(raiz);
    Nodo<T,grado> * aux;
    int elementos = 0;
    int aux2 = 1;
    while(!cola.estaVacia()){
        for(int i = 0; i < aux2;i++){
            aux = cola.pop();
            aux->imprimirArreglo();
            cout<<"  ";
            //cout << "," << aux->topeValores << ","<<aux->topeHijos;
            for(int j = 0; j < aux->topeHijos;j++){
                cola.push(aux->hijos[j]);
                elementos++;
            }
        }
        aux2 = elementos;
        elementos = 0;
        cout << endl;
    }
}
int main(){
    try{
        ArbolBAsterisco<int,4> arbol;
        //Split a la raiz
        int meh;
        int array[400];
        srand((unsigned)time(0));

        for(int i=0;i<400;++i){
            meh = rand()% 1000;
            array[i]=meh;
        }

        for(int i=0;i<400;++i){
            cout<<i+1<<endl<<endl;
            arbol.insertar(i+1);
            arbol.impresionPorNiveles();
            system("pause");
            system("cls");
        }

        for(int i=0;i<400;++i){
            meh = rand()%400;
            cout<<"Eliminando "<<meh<<endl;
            arbol.remover(meh);
            arbol.impresionPorNiveles();
            system("pause");
            cout<<endl<<endl<<endl;
        }


        //arbol.impresionPorNiveles();
        //arbol.imprimir();

        /*
        arbol.insertar(-10);
        arbol.insertar(4);
        arbol.insertar(-20);
        arbol.impresionPorNiveles();
        cout << endl << endl << endl << endl;
        //Este es el momento de la verdad~~~~~~~~~
        arbol.insertar(6);
        arbol.insertar(13);
        arbol.insertar(14);
        arbol.imprimir();
        cout << endl << endl;
        arbol.insertar(0);
        arbol.insertar(-30);
        //Ahora si es el momento de la verdad verdadera~~~~~~~
        arbol.imprimir();
        arbol.insertar(-40);
        arbol.imprimir();


        */
        //ArbolBAsteriscoInt();
        //cout  << endl;
        //system("pause");
       // ArbolBAsteriscoChar();
        //cout << endl;
        //system("pause");
        //ArbolBAsteriscoCadena();

        //Split a la raiz
       /* arbol.insertar(5);
        arbol.insertar(10);
        arbol.insertar(15);
        arbol.insertar(20);
        arbol.insertar(25);
        //End split a la raiz
        arbol.insertar(30);
        arbol.insertar(35);
        arbol.insertar(40);
        arbol.insertar(50);
        arbol.insertar(60);
        arbol.insertar(70);

        //meter mas a la raiz
        arbol.insertar(7);
        arbol.insertar(12);

        arbol.impresionPorNiveles();
        cout << endl;
        arbol.insertar(2);
        //arbol.insertar(27);
        //arbol.insertar(29);
        //meter 3 elementos para ver esta madre
        arbol.insertar(1);
        arbol.insertar(9);
        arbol.insertar(-2);
        arbol.insertar(13);
        arbol.impresionPorNiveles();
        cout << endl << endl;
        system("pause");
        arbol.remover(-2);
        arbol.impresionPorNiveles();
        cout << endl << endl;*/


        system("pause");
    }catch(NoHayMemoria &e){
        cout <<  e.getMensaje();
    }catch(GradoIncorrecto &e){
        cout << e.getMensaje();
    }
}





void ArbolBAsteriscoInt(){

    ArbolBAsterisco<int,6> arbol;
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(60);
    arbol.insertar(70);
    arbol.insertar(50);
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(18);
    arbol.insertar(23);
    arbol.remover(10);
    arbol.remover(15);
    arbol.insertar(80);
    arbol.insertar(90);
    arbol.insertar(100);
    arbol.insertar(65);
    arbol.remover(90);
    arbol.insertar(110);
    arbol.insertar(120);
    arbol.insertar(130);
    arbol.insertar(3);
    arbol.insertar(82);
    arbol.insertar(84);
    arbol.insertar(87);
    arbol.remover(3);
    //
    //
    //
    arbol.insertar(140);
    arbol.insertar(150);
    arbol.insertar(160);
    arbol.insertar(142);
    arbol.insertar(144);
    arbol.insertar(146);
    arbol.remover(110);
    arbol.remover(146);
    arbol.remover(140);
    arbol.remover(84);
    arbol.remover(150);
    //arbol.remover(160);
    ArbolBAsterisco<int,6>  a = arbol;
   // if(a.buscar(160)) cout << "Si esta";
   // else cout << "no esta";
    cout <<"ArbolBAsterisco de enteros maximo (Por niveles): " << endl << endl;
    arbol.impresionPorNiveles();
    cout << endl << "ArbolBAsterisco de enteros maximo (Igualado, por niveles): " << endl;
    a.impresionPorNiveles();
    cout << endl;
    cout << "ArbolBAsterisco de enteros maximo (Despues de remover 160, doble merge): " << endl;
    a.remover(160);
    a.impresionPorNiveles();
}
//////////////////////////Funcion usuaria de arbol char
void ArbolBAsteriscoChar(){

    ArbolBAsterisco<char,3> arbol;
    arbol.insertar('a');
    arbol.insertar('#');
    arbol.insertar('6');
    arbol.insertar(']');
    arbol.insertar('2');
    arbol.insertar('.');
    arbol.insertar('g');
    //Aqui se prueba el constructor de copias.
    ArbolBAsterisco<char> a = arbol;
    cout <<"ArbolBAsterisco de caracteres (Descendente) : " << endl;
    arbol.impresionDescendente();
    cout << "ArbolBAsterisco de caracteres minimo (Copiado,descendente): " << endl;
    a.impresionDescendente();
    cout << "ArbolBAsterisco de caracteres minimo (Despues de vaciar): " << endl;
    a.vaciar();
    a.impresionDescendente();
}
/////////////////////////////////////Funcion usuaria de arbol Cadena
void ArbolBAsteriscoCadena(){

    ArbolBAsterisco<Cadena,7> arbol;
    arbol.insertar("Hola");
    arbol.insertar("Hi");
    arbol.insertar("Hello");
    arbol.insertar("A");
    arbol.insertar("Bye");
    arbol.insertar("Saleros");
    arbol.insertar("Rapido");
    arbol.insertar("fgsfds");
    //Aqui se prueba el constructor de copias.
    ArbolBAsterisco<Cadena,7> a = arbol;
    cout <<"ArbolBAsterisco de cadenas maximo(Ascendente): " << endl;
    a.impresionAscendente();
    cout << "ArbolBAsterisco de cadenas maximo (Despues de remover un elemento,ascendente): " << endl;
    a.remover("Bye");
    a.impresionAscendente();
    cout <<"Checando si esta la cadena 'Hola' " << endl;
    if(a.buscar("Hola")) cout << "Si esta" << endl;
    else cout << "No esta" << endl;
}
