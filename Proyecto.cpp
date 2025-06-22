#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream> 

using namespace std;

struct Carta{
    char figura[10];
    char valor[3];
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
void turnoJugador(Jugador* jugador, Jugador* banca);
void turnoBanca(Jugador* banca);
void Ganador(Jugador* jugador, Jugador* banca);
void liberarMemoria(Jugador* jugador);
void guardar(const char* nombre, const char* resultado, int total);
void historial();

int main(){
    srand(time(0));
    Jugador jugador, banca;
    cout << " ____  _        _    ____ _  __   _   _    ____ _  __" << endl;
    cout << "| __ )| |      / \\  / ___| |/ /  | | / \\  / ___| |/ /" << endl;
    cout << "|  _ \\| |     / _ \\| |   | ' /_  | |/ _ \\| |   | ' / " << endl;
    cout << "| |_) | |___ / ___ \\ |___| . \\ |_| / ___ \\ |___| . \\ " << endl;
    cout << "|____/|_____/_/   \\_\\____|_|\\_\\___/_/   \\_\\____|_|\\_\\" << endl;
    char nombre[50];
    cout<<endl<<endl;
    cout << "=================================================================" << endl;
    cout << "Introduce tu nombre: ";
    cin.getline(nombre, 50);
    cout << "=================================================================" << endl;
    char opc;
    do{
        cout<<endl<<endl;
        cout << " _____                                         _              _ " << endl;
        cout << "| ____|_ __ ___  _ __   ___ ______ _ _ __   __| | ___     ___| |" << endl;
        cout << "|  _| | '_ ` _ \\| '_ \\ / _ \\_  / _` | '_ \\ / _` |/ _ \\   / _ \\ |" << endl;
        cout << "| |___| | | | | | |_) |  __// / (_| | | | | (_| | (_) | |  __/ |" << endl;
        cout << "|_____|_| |_| |_| .__/ \\___/___\\__,_|_| |_|\\__,_|\\___/   \\___|_|" << endl;
        cout << "  (_)_   _  ___ |_| _  ___                                      " << endl;
        cout << "  | | | | |/ _ \\/ _` |/ _ \\                                     " << endl;
        cout << "  | | |_| |  __/ (_| | (_) |                                    " << endl;
        cout << " _/ |\\__,_|\\___|\\__, |\\___/                                     " << endl;
        cout << "|__/            |___/                                           " << endl;
        cout<<endl<<endl;
        crearJugador(&jugador, nombre);
        crearJugador(&banca, (char*)"Banca");
        turnoJugador(&jugador, &banca);
        cout << "=================================================================" << endl;
        cout << "  ____ _        _    ____ ___ _____ ___ ____    _    ____ ___ ___  _   _ " << endl;
        cout << " / ___| |      / \\  / ___|_ _|  ___|_ _/ ___|  / \\  / ___|_ _/ _ \\| \\ | |" << endl;
        cout << "| |   | |     / _ \\ \\___ \\| || |_   | | |     / _ \\| |    | | | | |  \\| |" << endl;
        cout << "| |___| |___ / ___ \\ ___) | ||  _|  | | |___ / ___ \\ |___ | | |_| | |\\  |" << endl;
        cout << " \\____|_____/_/   \\_\\____/___|_|   |___\\____/_/   \\_\\____|___\\___/|_| \\_|" << endl;
        mostrarMano(&jugador);
        cout<<endl;
        mostrarMano(&banca);
        Ganador(&jugador, &banca);

        char op;
        cout<<endl<<"ver historial: |s|n|: ";
        cin>>op;
        if(op=='s'){
            cout << "_   _ ___ ____ _____ ___  ____  ___    _    _    " << endl;
            cout << "| | | |_ _/ ___|_   _/ _ \\|  _ \\|_ _|  / \\  | |   " << endl;
            cout << "| |_| || |\\___ \\ | || | | | |_) || |  / _ \\ | |   " << endl;
            cout << "|  _  || | ___) || || |_| |  _ < | | / ___ \\| |___" << endl;
            cout << "|_| |_|___|____/ |_| \\___/|_| \\_\\___/_/   \\_\\_____|" << endl;
            historial();
        }
        cout<<"jugar de nuevo: |s|n|: ";
        cin>>opc;
        cout<<endl;
    }while(opc=='s');
    cout<<endl<<endl;
    cout << "    _    ____ ___ ___  ____  " << endl;
    cout << "   / \\  |  _ \\_ _/ _ \\/ ___| " << endl;
    cout << "  / _ \\ | | | | | | | \\___ \\ " << endl;
    cout << " / ___ \\| |_| | | |_| |___) |" << endl;
    cout << "/_/   \\_\\____/___\\___/|____/ " << endl;

    liberarMemoria(&jugador);
    liberarMemoria(&banca);
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
        if(jugador->total<10||jugador->numDeCar<=1){
            return 11;
        }else{
            return 1;
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
    strncpy(carta.valor, valores[rand() % 13], 3);
    carta.puntos = valorCarta(carta.valor, jugador);
    return carta;
}
void agregarCarta(Jugador* jugador, Carta carta){
    jugador->juego[jugador->numDeCar] = carta;
    jugador->total += carta.puntos;
    jugador->numDeCar++;
}
void mostrarMano(Jugador* jugador){
    cout<<"juego de"<<" ";
    cout << jugador->nombre << ": "<<endl;
    for (int i = 0; i < jugador->numDeCar; i++){
        cout<<"["<<jugador->juego[i].valor<<" | "<<jugador->juego[i].figura<<"]"<<"   ";
    }
    cout<<endl;
    cout<<"total: "<<jugador->total<<endl;
}
void turnoJugador(Jugador* jugador, Jugador* banca){
    char op;
    do{
        turnoBanca(banca);
        Carta c = generarCarta(jugador);
        agregarCarta(jugador, c);
        mostrarMano(jugador);
        if (jugador->total > 21){
            return;
        }else if(banca->total > 21){
            return;
        }else{
            cout << "otra? |s/n|  ";
            cin >> op;
        }
    }while(op=='s');
    while(banca->total<17){
        turnoBanca(banca);
        mostrarMano(jugador);
    }
}
void turnoBanca(Jugador* banca){
    if (banca->total < 17)
    {
        Carta c = generarCarta(banca);
        agregarCarta(banca, c);
    }
    mostrarMano(banca);
}
void Ganador(Jugador* jugador, Jugador* banca){
    cout<<endl;
    if(jugador->total >21){
        cout << " ____  _____ ____  ____ ___ ____ _____ _____ " << endl;
        cout << "|  _ \\| ____|  _ \\|  _ \\_ _/ ___|_   _| ____|" << endl;
        cout << "| |_) |  _| | |_) | | | | |\\___ \\ | | |  _|  " << endl;
        cout << "|  __/| |___|  _ <| |_| | | ___) || | | |___ " << endl;
        cout << "|_|   |_____|_| \\_\\____/___|____/ |_| |_____|" << endl;
        guardar(jugador->nombre, "PERDISTE", jugador->total);
    }else if(banca->total>21){
        cout << "  ____    _    _   _    _    ____ _____ _____ " << endl;
        cout << " / ___|  / \\  | \\ | |  / \\  / ___|_   _| ____|" << endl;
        cout << "| |  _  / _ \\ |  \\| | / _ \\ \\___ \\ | | |  _|  " << endl;
        cout << "| |_| |/ ___ \\| |\\  |/ ___ \\ ___) || | | |___ " << endl;
        cout << " \\____/_/   \\_\\_| \\_/_/   \\_\\____/ |_| |_____|" << endl;
        guardar(jugador->nombre, "GANASTE", jugador->total);
    }else if(jugador->total>banca->total){
        cout << "  ____    _    _   _    _    ____ _____ _____ " << endl;
        cout << " / ___|  / \\  | \\ | |  / \\  / ___|_   _| ____|" << endl;
        cout << "| |  _  / _ \\ |  \\| | / _ \\ \\___ \\ | | |  _|  " << endl;
        cout << "| |_| |/ ___ \\| |\\  |/ ___ \\ ___) || | | |___ " << endl;
        cout << " \\____/_/   \\_\\_| \\_/_/   \\_\\____/ |_| |_____|" << endl;
        guardar(jugador->nombre, "GANASTE", jugador->total);
    }else if(jugador->total==banca->total){
        cout << " _____ __  __ ____   _  _____ _____    ____    _    _   _    _    " << endl;
        cout << "| ____|  \\/  |  _ \\ / \\|_   _| ____|  / ___|  / \\  | \\ | |  / \\   " << endl;
        cout << "|  _| | |\\/| | |_) / _ \\ | | |  _|   | |  _  / _ \\ |  \\| | / _ \\  " << endl;
        cout << "| |___| |  | |  __/ ___ \\| | | |___  | |_| |/ ___ \\| |\\  |/ ___ \\ " << endl;
        cout << "|_____|_|  |_|_| /_/   \\_\\_| |_____|  \\____/_/   \\_\\_| \\_/_/   \\_\\" << endl;
        cout << "| |      / \\    | __ )  / \\  | \\ | |/ ___|  / \\                   " << endl;
        cout << "| |     / _ \\   |  _ \\ / _ \\ |  \\| | |     / _ \\                  " << endl;
        cout << "| |___ / ___ \\  | |_) / ___ \\| |\\  | |___ / ___ \\                 " << endl;
        cout << "|_____/_/   \\_\\ |____/_/   \\_\\_| \\_|\\____/_/   \\_\\                " << endl;
        guardar(jugador->nombre, "EMPATE,PERDISTE", jugador->total);
    }else{
        cout << " ____  _____ ____  ____ ___ ____ _____ _____ " << endl;
        cout << "|  _ \\| ____|  _ \\|  _ \\_ _/ ___|_   _| ____|" << endl;
        cout << "| |_) |  _| | |_) | | | | |\\___ \\ | | |  _|  " << endl;
        cout << "|  __/| |___|  _ <| |_| | | ___) || | | |___ " << endl;
        cout << "|_|   |_____|_| \\_\\____/___|____/ |_| |_____|" << endl;
        guardar(jugador->nombre, "PERDISTE", jugador->total);
    }
}
void liberarMemoria(Jugador* jugador){
    free(jugador->juego);
    jugador->juego = NULL;
    jugador->numDeCar = 0;
    jugador->total = 0;
}
void guardar(const char* nombre, const char* resultado, int total){
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);
    ofstream archivo("historial.txt", ios::app);
    if(!archivo){
        cout<<"error"<<endl;
        return;
    }

    archivo<<"nombre: "<<nombre<<endl;
    archivo<<"puntos: "<<total<<endl;
    archivo<<"resultado: "<<resultado<<endl;
    archivo << "fecha: " << tiempo->tm_mday << "/" << (tiempo->tm_mon + 1) << "/" << (tiempo->tm_year + 1900) << " a las " << tiempo->tm_hour << ":" << tiempo->tm_min << endl;
    archivo << "================================================================="<<endl<<endl;

    archivo.close();
}
void historial(){
    ifstream archivo("historial.txt");
    if(!archivo){
        cout<<"error"<<endl;
        return;
    }
    string linea;
    while(getline(archivo, linea)){
        cout<<linea<<endl;
    }

    archivo.close();
}
