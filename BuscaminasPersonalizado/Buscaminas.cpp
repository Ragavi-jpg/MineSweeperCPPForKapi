#include <iostream>
#include <stdio.h>
#include <cstdio>


using namespace std;

const int DIMENSIONX = 12;
const int DIMENSIONY = 12;

const int hubicacionBombas[DIMENSIONX][DIMENSIONY] = {
    {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
    {-2, 0, 0, 0, 0, 1,-1, 1, 0, 0, 0,-2},
    {-2, 0, 0, 1, 1, 2, 1, 1, 0, 1, 1,-2},
    {-2, 0, 0, 1,-1, 1, 0, 0, 0, 2,-1,-2},
    {-2, 0, 0, 1, 1, 1, 0, 0, 0, 3,-1,-2},
    {-2, 1, 1, 1, 0, 0, 0, 0, 0, 2,-1,-2},
    {-2, 2,-1, 1, 0, 0, 0, 0, 0, 1, 1,-2},
    {-2,-1, 3, 1, 0, 0, 0, 0, 0, 0, 0,-2},
    {-2,-1, 2, 0, 0, 1, 1, 1, 0, 0, 0,-2},
    {-2, 1, 1, 0, 0, 1,-1, 2, 1, 0, 0,-2},
    {-2, 0, 0, 0, 0, 1, 2,-1, 1, 0, 0,-2},
    {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2}
}; //minas = -1, Muros = -2, Casillas libres = 0


int contarBombas()
{
    int n = 0;
    for(int i = 0; i<DIMENSIONX; i++){
        for(int j = 0; j<DIMENSIONY; j++){
            if(hubicacionBombas[i][j] == -1) n++;
        }
    }
    return n;
}

void imprimir(char matriz[DIMENSIONX+1][DIMENSIONY+1])
{
    for(int i = 0; i<DIMENSIONX+1; i++){
        for(int j = 0; j<DIMENSIONY+1; j++){
            cout<<matriz[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<endl;
}

void calcularCasillasVacias(char matriz[DIMENSIONX+1][DIMENSIONY+1], int& casillasPorLimpiar, int fila, int columna)
{
    if(matriz[fila][columna] == '.' || matriz[fila][columna] == 'P'){
        if(hubicacionBombas[fila][columna] == 0){
            casillasPorLimpiar--;
            matriz[fila][columna] = ' ';
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila-1,columna-1);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila-1,columna);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila-1,columna+1);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila,columna-1);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila,columna+1);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila+1,columna-1);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila+1,columna);
            calcularCasillasVacias(matriz, casillasPorLimpiar, fila+1,columna+1);
        }else{
            casillasPorLimpiar--;
            matriz[fila][columna] = hubicacionBombas[fila][columna]+'0';
        }
    }
    return;
}

void procesarCasillaSegura(char matriz[DIMENSIONX+1][DIMENSIONY+1], int& casillasPorLimpiar, int fila, int columna)
{
    if(hubicacionBombas[fila+1][columna+1] != 0){
        matriz[fila+1][columna+1] = hubicacionBombas[fila+1][columna+1]+'0';
        casillasPorLimpiar--;
    }else{
        calcularCasillasVacias(matriz,casillasPorLimpiar,fila+1,columna+1);
    }
}

void alterarMatriz(char matriz[DIMENSIONX+1][DIMENSIONY+1]){
    for(int i = 0; i<DIMENSIONX; i++){
        for(int j = 0; j<DIMENSIONY; j++){
            if(hubicacionBombas[i][j] != -2) matriz[i][j] = ' ';
            if(hubicacionBombas[i][j] == -1) matriz[i][j] = 'P';
        }
    }
}

void jugar(char matriz[DIMENSIONX+1][DIMENSIONY+1], int bombas, int& casillasPorLimpiar)
{
    int ganarOPerder = 0; //ganar = 1, perder = -1
    int fila;
    int columna;
    bool hubicacionCorrecta;
    char colocarBandera;

    while(ganarOPerder == 0){
        do{
            cout<<"BOMBAS: "<<bombas<<'\n'<<"CASILLAS PARA GANAR: "<<casillasPorLimpiar<<endl;
            imprimir(matriz);
            if(!hubicacionCorrecta) cout<<"Casilla incorrecta, prueba otra vez"<<'\n';
            hubicacionCorrecta = true;
            cout<<"Colocar bandera?(Y/N): ";
            cin>>colocarBandera;
            if(colocarBandera == 'Y' || colocarBandera == 'y'){
                cout<<"Escoge Numero de fila: ";
                cin>>fila;
                cout<<"Escoge Numero de columna: ";
                cin>>columna;
                system("cls");
                if(fila<0 || fila>=DIMENSIONX-2 || columna<0 || columna>=DIMENSIONY-2 || matriz[fila+1][columna+1] != '.') hubicacionCorrecta = false;
                if(hubicacionCorrecta) matriz[fila+1][columna+1] = 'P';
            }else{
                cout<<"Escoge Numero de fila: ";
                cin>>fila;
                cout<<"Escoge Numero de columna: ";
                cin>>columna;
                system("cls");
                if(fila<0 || fila>=DIMENSIONX-2 || columna<0 || columna>=DIMENSIONY-2) hubicacionCorrecta = false;
            }
        }while(!hubicacionCorrecta);
        if(hubicacionBombas[fila+1][columna+1] == -1 && !(colocarBandera == 'y' || colocarBandera == 'Y')){
            matriz[fila+1][columna+1] = 'X';
            ganarOPerder = -1;
        }else{
            if(!(colocarBandera == 'y' || colocarBandera == 'Y')) procesarCasillaSegura(matriz, casillasPorLimpiar, fila, columna);
        }
        if(casillasPorLimpiar == 0) ganarOPerder = 1;
    }
    if(ganarOPerder == 1){
        alterarMatriz(matriz);
        imprimir(matriz);
        cout<<"[ !!GANASTE!! ]"<<'\n'<<'\n'<<"  - GAME OVER -"<<'\n'<<'\n'<<"LA PISTA ES: [OBJECTIVE-C]"<<'\n'<<endl;
    }else{
        imprimir(matriz);
        cout<<"[ OH NO! CAVASTE DONDE HAY UNA MINA! ]"<<'\n'<<'\n'<<"  - GAME OVER -"<<endl;
    }
}

int main()
{
    int nBombas = contarBombas();
    int nCasillasPorLimpiar = (DIMENSIONX-2)*(DIMENSIONY-2) - contarBombas();
    char m = '#', e = '.', b = ' ';
    char tablero[DIMENSIONX+1][DIMENSIONY+1] = {
    { m , m , m , m , m , m , m , m , m , m , m , m ,'F'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'0'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'1'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'2'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'3'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'4'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'5'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'6'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'7'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'8'},
    { m , e , e , e , e , e , e , e , e , e , e , m ,'9'},
    { m , m , m , m , m , m , m , m , m , m , m , m , b },
    {'C','0','1','2','3','4','5','6','7','8','9', b , b }
    };

    jugar(tablero, nBombas, nCasillasPorLimpiar);
    system("pause");
    return 0;
}

/*
    cosas por hacer:
        {
        -Función que calcule las casillas contiguas libres cuando excaves una
        -Función que ponga en blanco las casillas libres cuando excaves una
        -Función que muestre los números de las minas cuando excaves casillas libres
        }
        -Función que calcule los números O Actualizar la hubicación de las minas para que también tengan los números
*/
