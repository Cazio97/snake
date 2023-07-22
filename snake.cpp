#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;
 
#define ARRIBA 72  //numeros asociados a las flechas
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

int cuerpo[200][2]; //j i matriz para las coordenadas x 2 y 200 
int n = 1, tam = 10, dir = 3; // ,forma en que guardaa el cuerpo
int x = 10, y = 12; //posicion inical
int xc = 30, yc = 15; //comiida
int velocidad = 120, h =1;// entre mas el valor mas lento
int score = 0;
char tecla;

void gotoxy(int x, int y) //funcion que posiciona el cursor
{ 
 HANDLE hCon;
 COORD dwPos; 
 
 dwPos.X = x; 
 dwPos.Y = y; 
 hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
 SetConsoleCursorPosition(hCon,dwPos); 
}

void portada(){
        system("cls");
        int c=24,f=79,r;
        char t=178;
        for(int i=0 ; i<f ; i++){
                gotoxy(i,0);
                cout<<t;
                gotoxy(i,c);
                cout<<t;
        }
        for(int i=0 ; i<=c ; i++){
                gotoxy(0,i);
                cout<<t;
                gotoxy(f,i);
                cout<<t;
        }
        string snkd[]={"         ....oooooo....    ","     .',;;:o:000000',0. ","    .:  ......ldl````````dloo:.",
                " .,  ,ldd, ;c  dl  okxxo:  ';l:.",".,  ;dxkx, cd  dl  dOkxxxl..'l;",";  ;dxkkk, cx  ko  x0Okkxxooocl",
                ";  ,:cclx; ;c  kd  xK0kxl00000l",",      :d; .,,:0d  xK0Oo,     o ",";  ;ddxkk, l0KKXo  x0Okkddl  ,0",
                ",'  oxxkx, l0K00o  dOOkxxd;  0"," ,'  ldxd, cOOOOl  okkxxo;  :0","  ,'   lo, ckkxkc  okxo:   :o",
                "    ..   .......,,,......:::","      ```'oooooooooooo:::","......';;',;:cc:,'..."};
                
        r=2;
        for(int i=0;i<14;i++){
                gotoxy(20,r);
                r++;
                cout<<snkd[i]<<endl;
        }
        
        string snkl[]={"                     __     ","   _________  ____ _/ /_____","  / ___/ __ \\/ __ `/ //_/ _ \\",
        " (__  ) / / / /_/ / ,< /  __/","/____/_/ /_/\\__,_/_/|_|\\___/"};
        for(int i=0;i<5;i++){
                gotoxy(22,r);
                r++;
                cout<<snkl[i]<<endl;
        }
        gotoxy(23,23);
        cout<<"Precione ENTER para empezar";
        system("pause>dsdsd");
}
 



void OcultaCursor() {
 CONSOLE_CURSOR_INFO cci = {100, FALSE};
 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void pintar(){ //lineas horizontales
 for(int i=2; i < 78; i++){ //limites marco eje x
 gotoxy (i, 3); printf ("%c", 205); //caracter char codigo asci
 gotoxy(i, 23); printf ("%c", 205); 
 }
 for(int v=4; v < 23; v++){ //lineas verticaless
 gotoxy (2,v); printf ("%c", 186);
 gotoxy(77,v); printf ("%c", 186); 
 }
 //esquinas 
 gotoxy (2,3); printf ("%c", 201);
 gotoxy (2,23); printf ("%c", 200);
 gotoxy (77,3); printf ("%c", 187);
 gotoxy(77,23); printf ("%c", 188); 
 } 
void guardar_posicion(){ // guarda cada paso en la matriz 
 cuerpo[n][0] = x;
 cuerpo[n][1] = y;
 n++;
 if(n == tam) n = 1;//vueelve a reexcribir poniendo las coordenadas actuales
}
void dibujar_cuerpo(){ //espacios con datos lo uso como coordenas y lo imprime en pantalla
 for(int i = 1; i < tam; i++){
 gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("*");
 }
}
void borrar_cuerpo(){
 gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");//
 }
void teclear(){
 if(kbhit()){
 tecla = getch();
 switch(tecla){
 case ARRIBA : if(dir != 2) dir = 1; break;
 case ABAJO : if(dir != 1) dir = 2; break;
 case DERECHA : if(dir != 4) dir = 3; break;
 case IZQUIERDA : if(dir != 3) dir = 4; break;
 }
 }
}
void comida()
{
 if(x == xc && y == yc)
 {
 xc = (rand() % 73) + 4;
 yc = (rand() % 19) + 4;
 
 tam++;
 score +=10;
 gotoxy(xc, yc); printf("%c", 4);
 }
}
bool game_over()
{
 if(y == 3 || y == 23 || x == 2 || x == 77) return false;
 for(int j = tam - 1; j > 0; j--){
 if(cuerpo[j][0] == x && cuerpo[j][1] == y)
 return false;
 }
 return true;
}


void puntos(){
   gotoxy(3,1);printf("score %d",score);

}
void cambiar_velocidad(){
    if(score == h*20){
        velocidad -=10;
        h++;
    }
}




int main()
{
 OcultaCursor();

 portada();
 
 pintar();
 gotoxy(xc, yc); printf("%c", 4);

 
 while(tecla != ESC && game_over())
 {
 borrar_cuerpo();
 guardar_posicion();
 dibujar_cuerpo();
 comida();
 puntos();
 cambiar_velocidad();
 teclear();
 teclear();
 
 if(dir == 1) y--;
 if(dir == 2) y++;
 if(dir == 3) x++;
 if(dir == 4) x--;
 
 Sleep(velocidad);
 }
 pintar();
 return 0;
}
