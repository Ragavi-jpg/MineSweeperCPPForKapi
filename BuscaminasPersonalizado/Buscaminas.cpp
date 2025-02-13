#include <iostream>
#include <stdio.h>
#include <locale.h>

using namespace std;

const int DIMENSIONX = 10;
const int DIMENSIONY = 11;

const int hubicacionBombas[DIMENSIONX][DIMENSIONY] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,0,0,0,1,0},
    {0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,1,0,0,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0}
};


int contarBombas()
{
    int n = 0;
    for(int i = 0; i<DIMENSIONX; i++){
        for(int j = 0; j<DIMENSIONY; j++){
            if(hubicacionBombas[i][j] == 1) n++;
        }
    }
    return n;
}

void imprimir(char matriz[DIMENSIONX+1][DIMENSIONY+1])
{
    for(int i = 0; i<DIMENSIONX+1; i++){
        for(int j = 0; j<DIMENSIONY+1; j++){
            cout<<matriz[i][j]<<' '
            ;
        }
        cout<<'\n';
    }
    cout<<endl;
}

void jugar(char matriz[DIMENSIONX+1][DIMENSIONY+1])
{
    int ganarOPerder = 0; //ganar = 1, perder = -1
    int fila;
    int columna;
    bool hubicacionCorrecta;
    char colocarBandera;

    while(ganarOPerder == 0){
        do{
            imprimir(matriz);
            if(!hubicacionCorrecta) cout<<"Casilla incorrecta, prueba otra vez"<<'\n';
            hubicacionCorrecta = true;
            cout<<"Colocar bandera?(Y/N): ";
            cin>>colocarBandera;
            if(colocarBandera == 'Y' || colocarBandera == 'y'){
                cout<<"Escoge N�mero de fila: ";
                cin>>fila;
                cout<<"Escoge N�mero de columna: ";
                cin>>columna;
                system("cls");
                if(fila<0 || fila>=DIMENSIONX-2 || columna<0 || columna>=DIMENSIONY-2) hubicacionCorrecta = false;
                if(hubicacionCorrecta) matriz[fila+1][columna+1] = 'O';
            }else{
                cout<<"Escoge N�mero de fila: ";
                cin>>fila;
                cout<<"Escoge N�mero de columna: ";
                cin>>columna;
                system("cls");
                if(fila<0 || fila>=DIMENSIONX-2 || columna<0 || columna>=DIMENSIONY-2) hubicacionCorrecta = false;
            }
        }while(!hubicacionCorrecta);
        if(hubicacionBombas[fila+1][columna+1] == 1 && !(colocarBandera == 'y' || colocarBandera == 'Y')){
            matriz[fila+1][columna+1] = 'X';
            ganarOPerder = -1;
        }
    }
    if(ganarOPerder == 1){
        imprimir(matriz);
        cout<<"[ ��GANASTE!! ]"<<endl;
    }else{
        imprimir(matriz);
        cout<<"[ PERDISTE D: ]"<<endl;
    }
}

int main()
{
    int nBombas = contarBombas();
    char m = '#', e = '.', b = ' ';
    char tablero[DIMENSIONX+1][DIMENSIONY+1] = {
    {m,m,m,m,m,m,m,m,m,m,m,'F'},
    {m,e,e,e,e,e,e,e,e,e,m,'0'},
    {m,e,e,e,e,e,e,e,e,e,m,'1'},
    {m,e,e,e,e,e,e,e,e,e,m,'2'},
    {m,e,e,e,e,e,e,e,e,e,m,'3'},
    {m,e,e,e,e,e,e,e,e,e,m,'4'},
    {m,e,e,e,e,e,e,e,e,e,m,'5'},
    {m,e,e,e,e,e,e,e,e,e,m,'6'},
    {m,e,e,e,e,e,e,e,e,e,m,'7'},
    {m,m,m,m,m,m,m,m,m,m,m,b},
    {'C','0','1','2','3','4','5','6','7','8',b,b}
    };

    setlocale(LC_ALL, "");
    jugar(tablero);
    return 0;
}

/*
    cosas por hacer:
        {
        -Funci�n que calcule las casillas contiguas libres cuando excaves una
        -Funci�n que ponga en blanco las casillas libres cuando excaves una
        -Funci�n que muestre los n�meros de las minas cuando excaves casillas libres
        }
        -Funci�n que calcule los n�meros O Actualizar la hubicaci�n de las minas para que tambi�n tengan los n�meros
*/
