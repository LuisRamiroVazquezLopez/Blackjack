#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Carta{
    char figura[10];
    char valor[2];
    int puntos;
};

struct Jugador{
    Carta* juego;
    int numDeCar;
    int total;
    char nombre[30];
};
void crearJugador(Jugador* jugador, const char* nombre);
int valorCarta(const char* valor, Jugador* jugador);
Carta generarCarta(Jugador* jugador);
void agregarCarta(Jugador* jugador, Carta carta);
void mostrarMano(Jugador* jugador);
void turnoJugador(Jugador* jugador);

int main(){
    srand(time(0));
    Jugador jugador, banca;
    cout<<"¦¦¦¦¦¦+ ¦¦+      ¦¦¦¦¦+  ¦¦¦¦¦¦+¦¦+  ¦¦+     ¦¦+ ¦¦¦¦¦+  ¦¦¦¦¦¦+¦¦+  ¦¦+"<<endl;
    cout<<"¦¦+--¦¦+¦¦¦     ¦¦+--¦¦+¦¦+----+¦¦¦ ¦¦++     ¦¦¦¦¦+--¦¦+¦¦+----+¦¦¦ ¦¦++"<<endl;
    cout<<"¦¦¦¦¦¦++¦¦¦     ¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦++      ¦¦¦¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦++ "<<endl;
    cout<<"¦¦+--¦¦+¦¦¦     ¦¦+--¦¦¦¦¦¦     ¦¦+-¦¦+ ¦¦   ¦¦¦¦¦+--¦¦¦¦¦¦     ¦¦+-¦¦+ "<<endl;
    cout<<"¦¦¦¦¦¦++¦¦¦¦¦¦¦+¦¦¦  ¦¦¦+¦¦¦¦¦¦+¦¦¦  ¦¦++¦¦¦¦¦++¦¦¦  ¦¦¦+¦¦¦¦¦¦+¦¦¦  ¦¦+"<<endl;
    cout<<"+-----+ +------++-+  +-+ +-----++-+  +-+ +----+ +-+  +-+ +-----++-+  +-+"<<endl;
    char nombre[50];
    cout<<endl;
    cout<<"======================================================================="<<endl;
    cout<<"||"<< "nombre: ";
    cin.getline(nombre, 50);
    crearJugador(&jugador, nombre);
    crearJugador(&banca, (char*)"Banca");
    cout<<endl<<"tu turno:"<<endl;
    turnoJugador(&jugador);
}

void crearJugador(Jugador* jugador, const char* nombre){
    jugador->total = 0;
    jugador->numDeCar = 0;
    jugador->juego = (Carta*) malloc(10 * sizeof(Carta));

    strncpy(jugador->nombre, nombre, sizeof(jugador->nombre) - 1);
    jugador->nombre[sizeof(jugador->nombre) - 1] = '\0';

    for (int i = 0; i < 1; i++) {
        Carta carta = generarCarta(jugador);
        agregarCarta(jugador, carta); 
    }
}
int valorCarta(const char* valor, Jugador* jugador){
    if (strcmp(valor, "A") == 0){
        if(jugador->total<10||jugador->numDeCar<=2){
            return 1;
        }else{
            return 11;
        }
    } 
    if (strcmp(valor, "J") == 0 || strcmp(valor, "Q") == 0 || strcmp(valor, "K") == 0) return 10;
    return atoi(valor);
}

Carta generarCarta(Jugador* jugador){
    const char* figuras[]= {"Corazon", "Diamante", "Trebol", "Pica"};
    const char* valores[]= {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    Carta carta;
    strncpy(carta.figura, figuras[rand() % 4], 10);
    strncpy(carta.valor, valores[rand() % 13], 2);
    carta.puntos = valorCarta(carta.valor, jugador);
    return carta;
}
void agregarCarta(Jugador* jugador, Carta carta){
    jugador->juego[jugador->numDeCar] = carta;
    jugador->total += carta.puntos;
    jugador->numDeCar++;
}
void mostrarMano(Jugador* jugador){
    cout<<"juego de"<<endl;
    cout << jugador->nombre << ": ";
    for (int i = 0; i < jugador->numDeCar; i++){
        cout<<"["<<jugador->juego[i].valor<<" | "<<jugador->juego[i].figura<<"]"<<"   ";
    }
    cout<<endl;
    cout<<"total: "<<jugador->total<<endl;
}
void turnoJugador(Jugador* jugador){
    char op;
    do{
        Carta c = generarCarta(jugador);
        agregarCarta(jugador, c);
        mostrarMano(jugador);
        if (jugador->total > 21){
            cout << "perdisteeeee jajajajajajaja"<<endl;
            return;
        }else{
            cout << "otra? |s/n|  ";
            cin >> op;
        }
    }while(op == 's');
}
