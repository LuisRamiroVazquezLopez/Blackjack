//Librerias a usar
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>  //para mejor formato
#include <fstream>

using namespace std;

enum Palo{CORAZONES=1, DIAMANTES=2, TREBOLES=3, PICAS=4};

struct Carta{
    int valor;
    Palo palo;
    string nombre; 
};

struct Jugador{
    Carta* manoJugador;
    int totCartas;
    int puntaje;
    string nombre;
};


//funcion para crear la baraja de cartas
Carta* crearBaraja();
void revolverBaraja(Carta* baraja);
void repartirCartas(Jugador* jugador, Carta* baraja);

int main(){
    srand(time(NULL));

    Carta* baraja = crearBaraja();

    
    revolverBaraja(baraja);

    //se crea la instancia para la banca
    Jugador* banca = new Jugador;
    banca->nombre = "Banca";
    repartirCartas(banca, baraja);

    //se crea la instancia para el jugador
    Jugador* jugador = new Jugador;
    cout<<endl<<"Ingresa tu nombre: "<<endl;
    cin>>jugador->nombre;



   

}

Carta* crearBaraja(){
    //declaramos el arreglo que almacenara la baraja
    Carta* baraja = new Carta[52];

    for(int i=0; i<4; i++){
        int contador=2;
        
        
        for(int j=0; j<13;j++){
            //indice para recorrer las 52 cartas
            int indice = i*13+j;
            switch(i){
                case 0:
                    baraja[indice].palo = CORAZONES;
                    break;
                case 1:
                    baraja[indice].palo = DIAMANTES;
                    break;
                case 2:
                    baraja[indice].palo = TREBOLES;
                    break;
                case 3:
                    baraja[indice].palo = PICAS;
                    break;
            }
            if(contador>=2 && contador<=10){
                baraja[indice].valor = contador;
                //pasamos el valor int al nombre con int to ASCII (itoa)
                baraja[indice].nombre = to_string(contador);
                contador++;
            }else if(contador==11){
                baraja[indice].valor = 10;
                baraja[indice].nombre = "J";
                contador++;
            }else if(contador==12){
                baraja[indice].valor = 10;
                baraja[indice].nombre = "Q";
                contador++;
            }else if(contador==13){
                baraja[indice].valor = 10;
                baraja[indice].nombre = "K";
                contador++;
            }else if(contador==14){
                baraja[indice].valor = 11;
                baraja[indice].nombre = "A";
                contador++;
            }
        }   
    }

    return baraja;
}

void revolverBaraja(Carta* baraja){
    

    for (int i = 51; i > 0; --i) {
        int j = rand() % (i + 1);
        // intercambiar
        Carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }
}

void repartirCartas(Jugador* jugador, Carta* baraja){
    int cartaBaraja = 0;

    jugador->manoJugador = new Carta[2];

    for(int i=0; i<2; i++){
        cartaBaraja = rand()%sizeof(baraja);
        //pasar una carta de la baraja a la mano del jugador
        jugador->manoJugador[i] = baraja[cartaBaraja];
        
    }
}












