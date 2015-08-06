#include <iostream>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#define Dim 10
//typedef ALEGRO_COLOR color;
//#define ALLEGRO_DISPLAY display
//define ALLEGRO_EVENT_QUEUE event
using namespace std;

 ALLEGRO_DISPLAY *display;
 ALLEGRO_EVENT_QUEUE *event_queue;
 ALLEGRO_TIMER *timer;

char tablero_dama[10][10]; // Se modela un tablero_dama de caracteres con su respectiva dimension.
string cuadro_blanco="¦"; // Se van a representar con el siguiente simbolo los cuadrados blancos del tablero_dama.
string cuadro_negro="¦"; // Se van a representar con el siguiente simbolo los cuadrados negros del tablero_dama.
int contador_fichas_x= 9;
int contador_fichas_o= 9;
//int i, j; // Variables que van a permitir poblar_tablero_dama el tablero_dama e imprimirlo para su vizualizacion.
int q;  //  Variable que identifica las coordenadas vertcales.
int turno_jugador=1; // Cuando un jugador mueve una ficha, indica el turno por defecto 1 del jugador y cuando es 0 , turno de la maquina.
int movida ; // Variable que indica hacia donde movera el jugador.
int error ; // Indica error cuando comes una ficha en diagonal que es amiga.
int contador=1; // Variable iniciada en 1 que actua como un contador.
int ficha_o=15; // Cantidad de piezas del jugador o.
int ficha_x=15; // Cantidad de piezas del jugador x.
int finalizar=1; // Variable auxiliar inicializada en 1.
int x,y ; // Variables que actuan como coordenas para mover las piezas del juego.

//estructura para ubicar coordenadas
struct COOR{
   float txi, tyi, txf, tyf;
}cor[][10] = {

(50.0), (50.0), (100.0), (100.0) ,
 (100.0), (50.0), (150.0), (100.0),
 (150.0), (50.0), (200.0), (100.0),
 (200.0), (50.0), (250.0), (100.0),
 (250.0), (50.0), (300.0), (100.0),
 (300.0), (50.0), (350.0), (100.0),
 (350.0), (50.0), (400.0), (100.0),
 (400.0), (50.0), (450.0), (100.0),
 (450.0), (50.0), (500.0), (100.0),
 (500.0), (50.0), (550.0), (100.0),

(50.0), (100.0), (100.0), (150.0),
 (100.0), (100.0), (150.0), (150.0),
 (150.0), (100.0), (200.0), (150.0),
 (200.0), (100.0), (250.0), (150.0),
 (250.0), (100.0), (300.0), (150.0),
 (300.0), (100.0), (350.0), (150.0),
 (350.0), (100.0), (400.0), (150.0),
 (400.0), (100.0), (450.0), (150.0 ),
 (450.0), (100.0), (500.0), (150.0 ),
 (500.0), (100.0), (550.0), (150.0 ),

 (50.0), (150.0), (100.0), (200.0 ),
 (100.0), (150.0), (150.0), (200.0 ),
 (150.0), (150.0), (200.0), (200.0 ),
 (200.0), (150.0), (250.0), (200.0 ),
 (250.0), (150.0), (300.0), (200.0 ),
 (300.0), (150.0), (350.0), (200.0 ),
 (350.0), (150.0), (400.0), (200.0 ),
 (400.0), (150.0), (450.0), (200.0 ),
 (450.0), (150.0), (500.0), (200.0 ),
 (500.0), (150.0), (550.0), (200.0 ),

( 50.0), (200.0), (100.0), (250.0 ),
( 100.0), (200.0), (150.0), (250.0 ),
( 150.0), (200.0), (200.0), (250.0 ),
( 200.0), (200.0), (250.0), (250.0 ),
( 250.0), (200.0), (300.0), (250.0 ),
( 300.0), (200.0), (350.0), (250.0 ),
( 350.0), (200.0), (400.0), (250.0 ),
( 400.0), (200.0), (450.0), (250.0 ),
( 450.0), (200.0), (500.0), (250.0 ),
( 500.0), (200.0), (550.0), (250.0 ),

( 50.0), (250.0), (100.0), (300.0 ),
( 100.0), (250.0), (150.0), (300.0 ),
( 150.0), (250.0), (200.0), (300.0 ),
( 200.0), (250.0), (250.0), (300.0 ),
( 250.0), (250.0), (300.0), (300.0 ),
( 300.0), (250.0), (350.0), (300.0 ),
( 350.0), (250.0), (400.0), (300.0 ),
( 400.0), (250.0), (450.0), (300.0 ),
( 450.0), (250.0), (500.0), (300.0 ),
( 500.0), (250.0), (550.0), (300.0 ),

( 50.0), (300.0), (100.0), (350.0 ),
( 100.0), (300.0), (150.0), (350.0 ),
( 150.0), (300.0), (200.0), (350.0 ),
( 200.0), (300.0), (250.0), (350.0 ),
( 250.0), (300.0), (300.0), (350.0 ),
( 300.0), (300.0), (350.0), (350.0 ),
( 350.0), (300.0), (400.0), (350.0 ),
( 400.0), (300.0), (450.0), (350.0 ),
( 450.0), (300.0), (500.0), (350.0 ),
( 500.0), (300.0), (550.0), (350.0 ),

( 50.0), (350.0), (100.0), (400.0 ),
( 100.0), (350.0), (150.0), (400.0 ),
( 150.0), (350.0), (200.0), (400.0 ),
( 200.0), (350.0), (250.0), (400.0 ),
( 250.0), (350.0), (300.0), (400.0 ),
( 300.0), (350.0), (350.0), (400.0 ),
( 350.0), (350.0), (400.0), (400.0 ),
( 400.0), (350.0), (450.0), (400.0 ),
( 450.0), (350.0), (500.0), (400.0 ),
( 500.0), (350.0), (550.0), (400.0 ),

( 50.0), (400.0), (100.0), (450.0 ),
( 100.0), (400.0), (150.0), (450.0 ),
( 150.0), (400.0), (200.0), (450.0 ),
( 200.0), (400.0), (250.0), (450.0 ),
( 250.0), (400.0), (300.0), (450.0 ),
( 300.0), (400.0), (350.0), (450.0 ),
( 350.0), (400.0), (400.0), (450.0 ),
( 400.0), (400.0), (450.0), (450.0 ),
( 450.0), (400.0), (500.0), (450.0 ),
( 500.0), (400.0), (550.0), (450.0 ),

( 50.0), (450.0), (100.0), (500.0 ),
( 100.0), (450.0), (150.0), (500.0 ),
( 150.0), (450.0), (200.0), (500.0 ),
( 200.0), (450.0), (250.0), (500.0 ),
( 250.0), (450.0), (300.0), (500.0 ),
( 300.0), (450.0), (350.0), (500.0 ),
( 350.0), (450.0), (400.0), (500.0 ),
( 400.0), (450.0), (450.0), (500.0 ),
( 450.0), (450.0), (500.0), (500.0 ),
( 500.0), (450.0), (550.0), (500.0 ),

( 50.0), (500.0), (100.0), (550.0 ),
( 100.0), (500.0), (150.0), (550.0 ),
( 150.0), (500.0), (200.0), (550.0 ),
( 200.0), (500.0), (250.0), (550.0 ),
( 250.0), (500.0), (300.0), (550.0 ),
( 300.0), (500.0), (350.0), (550.0 ),
( 350.0), (500.0), (400.0), (550.0 ),
( 400.0), (500.0), (450.0), (550.0 ),
( 450.0), (500.0), (500.0), (550.0 ),
( 500.0), (500.0), (550.0), (550.0 ),
 };
struct MARCADORES{
   int comer=0, mover=0, sopladita=0, px=0, py=0 , pxf=0, pyf=0, pxf2=0, pyf2=0, a, b,pci1,pci2,pcd1,pcd2;

};
void poblar_tablero_dama(){
int i,j;
    for(i=0;i<Dim;i++){
        for(j=0;j<Dim;j++){
            if(i<=2&&((j+i)%2==1)){  // La sentencia if tiene como funcion dejar las fichas contrarias cuando el elemento del arreglo sea '0'
                tablero_dama[i][j] = 'O';
                //cout<<"FICHA:"<<tablero_dama[i][j]<<endl;
            }
            else if (i>=7&&((j+i)%2==1) ){
                tablero_dama[i][j] = 'X';
                //cout<<"FICHA:"<<tablero_dama[i][j]<<endl;

            }
            else if((j+i)%2==1){
                tablero_dama[i][j] = ' ' ;
                //cout<<"FICHA:"<<tablero_dama[i][j]<<endl;
                }
            else if((j+i)%2 ==0){
               tablero_dama[i][j] == NULL;
            }
        }
    }
}// Termina el procedimiento poblar_tablero_dama

void Dtablero(ALLEGRO_DISPLAY *display){
   int i,j,lin=0,bajar=0,hor=0,ver=0;
   ALLEGRO_COLOR color_crema = al_map_rgb(255, 240, 201);
   ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
   ALLEGRO_COLOR color_blanco = al_map_rgb(255, 255, 255);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   //display *display;
   //int tablero[10][10];
   //vredimensiona(1000,1000);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2==0){
            //color_rgb(255, 240, 201);//color crema
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_crema);
            lin+=50;
            }
        else if((i+j)%2==1){
            //color_rgb(117,75,13);
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_cafe);
            lin+=50;
            //color(BLANCO);
            //circulo_lleno(75+hor,75+ver,15);
            //circulo_lleno(175,75,15);
            //hor+=100;
            }
         if(j==9){
            bajar+=50;
            lin=0;
            //hor=0;
            //ver+=50;
         }

     }
    }
     //refresca();
     al_flip_display();
    //poblado de fichas
    for(i=0;i<10;i++){
       for(j=0;j<10;j++){
          if((i+j)%2==1){
             if(i<3){
                //color(BLANCO);
                if(j%2==1){
                   //circulo_lleno(125+hor,75+ver,15);
                   al_draw_filled_circle(125.0+hor,75.0+ver,15.0,color_blanco);
                   hor+=100;
                }
                else{
                   //circulo_lleno(75+hor,75+ver,15);
                   al_draw_filled_circle(75.0+hor,75.0+ver,15.0,color_blanco);
                   hor+=100;
                }
             }
             else{if(i>6){
                //color(NEGRO);
                if(j%2==1){
                   //circulo_lleno(125+hor,75+ver,15);
                   al_draw_filled_circle(125.0+hor,75.0+ver,15.0,color_negro);
                   hor+=100;
                }
                else{
                   //circulo_lleno(75+hor,75+ver,15);
                   al_draw_filled_circle(75.0+hor,75.0+ver,15.0,color_negro);
                   hor+=100;
                }



             }

             }
            }
          if(j==9){
            hor=0;
            ver+=50;
          }
        }
        if(i==3){
           i+=2;
           ver+=100;
        }
    }

   //circulo_lleno(75,75,15);
   /*color(NEGRO);
   rectangulo_lleno(150,100,200,150);*/
   //refresca();
   al_flip_display();
}
void solotablero(ALLEGRO_DISPLAY *display){
   int i,j,lin=0,bajar=0,hor=0,ver=0;
   ALLEGRO_COLOR color_crema = al_map_rgb(255, 240, 201);
   ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
   ALLEGRO_COLOR color_blanco = al_map_rgb(255, 255, 255);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   //display *display;
   //int tablero[10][10];
   //vredimensiona(1000,1000);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2==0){
            //color_rgb(255, 240, 201);//color crema
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_crema);
            lin+=50;
            }
        else if((i+j)%2==1){
            //color_rgb(117,75,13);
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_cafe);
            lin+=50;
            //color(BLANCO);
            //circulo_lleno(75+hor,75+ver,15);
            //circulo_lleno(175,75,15);
            //hor+=100;
            }
         if(j==9){
            bajar+=50;
            lin=0;
            //hor=0;
            //ver+=50;
         }

     }
    }
     //refresca();
     al_flip_display();
     }

void solofichas(COOR coor[][10]){
   ALLEGRO_COLOR color_blanco = al_map_rgb(255, 255, 255);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
   int i,j;
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2 == 1){
            if(tablero_dama[i][j] == 'O'){
                al_draw_filled_circle(((cor[i][j].txi+cor[i][j].txf)/2),((cor[i][j].tyi+cor[i][j].tyf)/2),15.0,color_blanco);
                /*cout<<"FICHA: "<<tablero_dama[i][j]<<endl;//borrar
                cout<<"CALCULO X: "<<((cor[i][j].txi+cor[i][j].txf)/2)<<endl;//borrar
                cout<<"CALCULO Y: "<<((cor[i][j].tyi+cor[i][j].tyf)/2)<<endl;//borrar
                cout<<"FICHA: "<<tablero_dama[2][9]<<endl;*/
                }
             else if(tablero_dama[i][j] == 'X'){
                 al_draw_filled_circle(((cor[i][j].txi+cor[i][j].txf)/2),((cor[i][j].tyi+cor[i][j].tyf)/2),15.0,color_negro);
             }
             else if(tablero_dama[i][j] == ' '){
                al_draw_filled_rectangle(cor[i][j].txi, cor[i][j].tyi, cor[i][j].txf, cor[i][j].tyf,color_cafe);
             }
             al_flip_display();
             }
            }
         }
  }
void tablerofichas(ALLEGRO_DISPLAY *display, char mcopla[][9], COOR mcor[][9]){
   int i,j,lin=0,bajar=0,hor=0,ver=0;
   ALLEGRO_COLOR color_crema = al_map_rgb(255, 240, 201);
   ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
   ALLEGRO_COLOR color_blanco = al_map_rgb(255, 255, 255);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   //display *display;
   //int tablero[10][10];
   //vredimensiona(1000,1000);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2==0){
            //color_rgb(255, 240, 201);//color crema
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_crema);
            lin+=50;
            }
        else if((i+j)%2==1){
            //color_rgb(117,75,13);
            //rectangulo_lleno(50+lin,50+bajar,100+lin,100+bajar);
            al_draw_filled_rectangle(50+lin,50+bajar,100+lin,100+bajar,color_cafe);
            lin+=50;
            //color(BLANCO);
            //circulo_lleno(75+hor,75+ver,15);
            //circulo_lleno(175,75,15);
            //hor+=100;
            }
         if(j==9){
            bajar+=50;
            lin=0;
            //hor=0;
            //ver+=50;
         }

     }
    }
     //refresca();
     al_flip_display();
     }
void mover2(int x,int y,COOR cor[][10], ALLEGRO_DISPLAY *display)
{
   event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_display_event_source(display));//registra eventos de la pantalla
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_install_mouse();
   ALLEGRO_EVENT e;
   int errorcor=1,aux;
   float px, py;
    do
    {
        do
        {
            do
            {
                do
                {
                    //cout<<"TURNO JUGADOR 1 FICHAS X" <<endl ;
                    /*cout<<x<<endl;
                    cout<<y<<endl;
                    cout<<"ficha:"<<tablero_dama[x][y]<<endl;
                   /if(turno_jugador==1 )
                    {
                        cout<<"INGRESE CORDENADA VERTICAL "<<endl ;
                        cin>> x ;

                        cout<<"INGRESE COORDENADA HORIZONTAL "<<endl ;
                        cin>> y;
                    }//FIN IF TURNO =1*/
                    if  (tablero_dama[x][y]!='X'&&tablero_dama[x][y]!='D')
                    {
                        cout<<"ERROR VUELVA A TIRAR NO HAY FICHA EN LA CASILLA "<<x<<"-"<<y<<endl ;
                        errorcor = 1;
                        }
                }while (tablero_dama[x][y]!='X'&&tablero_dama[x][y]!='D');//VALIDACION PARA EL TIRO DE MOVIMIENTO
                do
                {
                    if (tablero_dama[x][y] == 'X')
                    {
                        {
                            cout<<"SELECCIONE LA NUEVA POSICION DE LA FICHA [1]IZQUIERDA-ARRIBA [2] DERECHA-ARRIBA " ;
                            //cin>>movida ;
                            error=0;
                            if(movida>2||movida<1)
                            {cout<<"ERROR ESCOGA UNA OPCION VALIDA EN movida "<<endl;
                            }
                        }
                        if((y==9&&movida==2)||(y==0&&movida==1))
                        {
                            cout<<"ERROR NO PUEDES SALIRTE DEL tablero_dama "<<endl ;}
                    }//FIN IF DE MOVIMIENTO
                    if (tablero_dama[x][y]=='D')
                    {
                        cout<<"SELECCIONE [1]IZQ-ARRIBA [2]DER-ARRIBA [3]IZQ-ABAJO [4] DER-ABAJO " <<endl ;
                        cin>>movida ;
                        error=0;
                        if(movida>4||movida<1)
                        {cout<<"ERROR ESCOGA UNA OPCION VALIDA EN movida "<<endl;}
                        if((y==9&&movida==2)||(y==0&&movida==1)||(y==9&&movida==4)||(y==0&&movida==3)||(x==0&&movida==1)||(x==0&&movida==2)||(x==9&&movida==3)||(x==9&&movida==4))
                        {
                            cout<<"ERROR NO PUEDES SALIRTE DEL tablero_dama "<<endl ;}
                    }// fin if
                }while (movida>4||movida<1);//VALIDACION DE MOVIMIETNO PARA movida
            }while((y==9&&movida==2)||(y==0&&movida==1)||(y==9&&movida==4)||(y==0&&movida==3)||(x==0&&movida==1)||(x==0&&movida==2)||(x==9&&movida==3)||(x==9&&movida==4));//Vlidacion para no salirte del tablero_dama
            if (movida == 1 && ( tablero_dama[x-1][y-1]== 'X'||tablero_dama[x-1][y-1]== 'D')  ){
                cout<<"ERROR LA CASILLA ESTA OCUPADA POR UNA FICHA AMIGA  "<<endl ;
            }
            else if (movida == 2 && (tablero_dama[x-1][y+1]== 'X'||tablero_dama[x-1][y+1]== 'D') ){
                cout<<"ERROR LA CASILLA ESTA OCUPADA POR UNA FICHA AMIGA "<<endl ;
            }
            else if (movida == 3 && (tablero_dama[x+1][y-1]== 'X'||tablero_dama[x+1][y-1]== 'D') ){
                cout<<"ERROR LA CASILLA ESTA OCUPADA POR UNA FICHA AMIGA "<<endl ;
            }
            else if (movida == 4 && (tablero_dama[x+1][y+1]== 'X'||tablero_dama[x+1][y+1]== 'D') ){
                cout<<"ERROR LA CASILLA ESTA OCUPADA POR UNA FICHA AMIGA "<<endl ;
            }
        }while((movida==1&&(tablero_dama[x-1][y-1]== 'X'||tablero_dama[x-1][y-1]== 'D'))||(movida==2&&(tablero_dama[x-1][y+1]== 'X'||tablero_dama[x-1][y+1]== 'D') )||(movida == 3 && (tablero_dama[x+1][y-1]== 'X'||tablero_dama[x-1][y+1]== 'D') )||(movida == 4 && (tablero_dama[x+1][y+1]== 'X'||tablero_dama[x+1][y+1]== 'D') ));//VALIDACION DE MOVIMIENTO PARA ESPACION OCUPADO POR
        //CASILLA AMIGA
        if (movida==1 && (tablero_dama[x-1][y-1] == 'O'||tablero_dama[x-1][y-1] == 'C') )
        {
            if(y==1)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(x==1)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(tablero_dama[x-2][y-2] == 'X')
            {
                cout<<"NO SE PUEDE COMER LA FICHA YA QUE HAY OTRA FICHA EN LA CASILLA "<<x-2<<"-"<<y-2<<endl;
                error=1;}
            if(tablero_dama[x-2][y-2] == 'O' )
            {
                cout<<"NO SE PUEDE COMER LA FICHA YA QUE HAY OTRA FICHA EN LA CASILLA "<<x-2<<"-"<<y-2<<endl;
                error=1;}
            if(tablero_dama[x-2][y-2] == 'D' )
            {
                cout<<"NO SE PUEDE COMER LA FICHA YA QUE HAY OTRA FICHA EN LA CASILLA "<<x-2<<"-"<<y-2<<endl;
                error=1;}
            if(tablero_dama[x-2][y-2] == 'C' )
            {
                cout<<"NO SE PUEDE COMER LA FICHA YA QUE HAY OTRA FICHA EN LA CASILLA "<<x-2<<"-"<<y-2<<endl;
                error=1;}
        }
        else if (movida==2 && (tablero_dama[x-1][y+1] == 'O'||tablero_dama[x-1][y+1] == 'C'))
        {
            if(y==6)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(x==1)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(tablero_dama[x-2][y+2] == 'X')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x-2][y+2] == 'O')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x-2][y+2] == 'D')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x-2][y+2] == 'C')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
        }
        else if (movida==3 && (tablero_dama[x+1][y-1] == 'O'||tablero_dama[x+1][y-1] == 'C'))
        {
            if(y==1)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;if(y==1)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
                error=1;
            }
            if(x==6)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(tablero_dama[x+2][y-2] == 'X')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x+2][y-2] == 'O')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x-2][y+2] == 'C')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x-2][y+2] == 'D')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
        }
        else if (movida==4 && (tablero_dama[x+1][y+1] == 'O'||tablero_dama[x+1][y+1] == 'C'))
        {
            if(y==6)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(x==6)
            {cout<<"ERROR TE SALES DEL tablero_dama "<<endl ;
                error=1;
            }
            if(tablero_dama[x+2][y+2] == 'X')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x+2][y+2] == 'O')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x+2][y+2] == 'D')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
            if (tablero_dama[x+2][y+2] == 'C')
            {
                cout<<"ERROR NO SE PUEDE COMER UNA FICHA YA QUE LA POSICION ESTA OCUPADA "<<endl;
                error=1;}
        }
    }while(error==1);
    //VALIDACION DE MOVIMIENTO PARA ESPACION OCUPADOS CUANDO SE VA A COMER
    if(tablero_dama[x][y]== 'D' && movida==1 && tablero_dama[x-1][y-1]== ' '  ){
        tablero_dama[x][y]= ' ';
        tablero_dama[x-1][y-1]= 'D';}
    else if (tablero_dama[x][y]=='D'&& movida == 2 && tablero_dama[x-1][y+1]== ' ' ){
        tablero_dama[x][y]=' ' ;
        tablero_dama[x-1][y+1] = 'D' ;
    }
    else if (tablero_dama[x][y]=='D'&& movida == 3 && tablero_dama[x+1][y-1]== ' ' ){
        tablero_dama[x][y]=' ' ;
        tablero_dama[x+1][y-1] = 'D' ;
    }
    else if (tablero_dama[x][y]=='D'&& movida == 4 && tablero_dama[x+1][y+1]== ' ' ){
        tablero_dama[x][y]=' ' ;
        tablero_dama[x+1][y+1] = 'D' ;
    }
    else if(tablero_dama[x][y]=='D'&& movida== 1 &&( tablero_dama [x-1][y-1] == 'O' || tablero_dama [x-1][y-1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama[x-1][y-1]=' ' ;
        tablero_dama[x-2][y-2]= 'D' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA "<<x-1<<"-"<<y-1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;

    }
    else if(tablero_dama[x][y]=='D'&& movida==2 && (tablero_dama [x-1][y+1] == 'O'||tablero_dama [x-1][y+1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama[x-1][y+1]=' ' ;
        tablero_dama[x-2][y+2]= 'D' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA  "<<x-1<<"-"<<y+1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;

    }
    else if(tablero_dama[x][y]=='D'&& movida== 3 && (tablero_dama [x+1][y-1] == 'O'||tablero_dama [x+1][y-1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama[x+1][y-1]=' ' ;
        tablero_dama[x+2][y-2]= 'D' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA "<<x+1<<"-"<<y-1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;

    }
    else if(tablero_dama[x][y]=='D'&& movida== 4 && (tablero_dama [x+1][y+1] == 'O'||tablero_dama [x+1][y-1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama[x+1][y+1]=' ' ;
        tablero_dama[x+2][y+2]= 'D' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA "<<x+1<<"-"<<y+1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;
    }
    else if(tablero_dama[x][y]== 'X' && movida== 1 && tablero_dama [x-1][y-1] == ' ')
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama [x-1][y-1]= 'X' ;
    }//FIN DE ELSE IF
    else if(tablero_dama[x][y]=='X'&& movida== 1 && (tablero_dama [x-1][y-1] == 'O'||tablero_dama [x-1][y-1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama[x-1][y-1]=' ' ;
        tablero_dama[x-2][y-2]= 'X' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA  "<<x-1<<"-"<<y-1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;

    }
    else if(tablero_dama[x][y]== 'X' && movida== 2 && tablero_dama [x-1][y+1] == ' ')
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama [x-1][y+1]= 'X' ;
    }//FIN DE ELSE IF
    else if(tablero_dama[x][y]== 'X' && movida== 2 && (tablero_dama [x-1][y+1] == 'O'||tablero_dama [x-1][y+1] == 'C'))
    {
        tablero_dama[x][y]=' ' ;
        tablero_dama [x-1][y+1]= ' ' ;
        tablero_dama[x-2][y+2]= 'X' ;
        cout<<"\a";
        cout<<"HAS COMIDO A LA FICHA CONTRARIA 'O' EN LA CASILLA "<<x-1<<"-"<<y+1 ;
        ficha_o=ficha_o-1;
        contador_fichas_x= contador_fichas_x+3;

    }//FIN DE ELSE IF
    turno_jugador = 0;
    solofichas(cor);
}//FIN VOI MOVER 2
//guarda coordenadas de casillas
void dibtablero(COOR cor[][10]){
   int i, j;
    ALLEGRO_COLOR color_crema = al_map_rgb(255, 240, 201);
    ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
    ALLEGRO_COLOR color_blanco = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if(((i+j)%2)==0){
            al_draw_filled_rectangle(cor[i][j].txi,cor[i][j].tyi,cor[i][j].txf,cor[i][j].tyf,color_crema);
            //cout<<"posicion"<<"("<<i<<","<<j<<")"<<"coordenada:"<<cor[i][j].txi<<"."<<cor[i][j].tyi<<"."<<cor[i][j].txf<<"."<<cor[i][j].tyf<<endl;
            }
        else if(((i+j)%2)==1){
            al_draw_filled_rectangle(cor[i][j].txi,cor[i][j].tyi,cor[i][j].txf,cor[i][j].tyf,color_cafe);
            //cout<<"posicion"<<"("<<i<<","<<j<<")"<<"coordenada:"<<cor[i][j].txi<<"."<<cor[i][j].tyi<<"."<<cor[i][j].txf<<"."<<cor[i][j].tyf<<endl;
            }

         }
           al_flip_display();
     }

     //al_flip_display();
    }
//funcion transforma coordenadas de pantalla a coordenadas de tablero
int prioridad(vector<MARCADORES> *c){
int i,t=0;
   for(i=0;i<(*c).size();i++){
       if((*c)[i].comer > 0 && (*c)[i].comer < 4){
          t = 1;
       }else if((*c)[i].mover > 0 && (*c)[i].mover <  4 && t!=1){
          t =  2;
       }
   }
   return t;
}
/*void check(vector<marcadores> *c,pos[4]){
   if(prioridad(c) && movida == 1){

   }
}*/
vector<int> moverficha(int pos[4], COOR cor[][10], vector<MARCADORES> *c){
   int i, j, aux, e1=0,e2=0 , rpos[4];//borrar variable aux
   vector<int> movp(3);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if(pos[1]>cor[i][j].tyi && pos[1]<cor[i][j].tyf){
            if(pos[0]>cor[i][j].txi && pos[0]<cor[i][j].txf){
                cout<<"posicion mouse x"<<i<<endl;
                cout<<"posicion mouse y"<<j<<endl;
                e1 = 1;
                rpos[0] = i;
                rpos[1] = j;
                }else{
                   rpos[0] = -1;
                   rpos[1] = -1;
                }
         }
          if(pos[3]>cor[i][j].tyi && pos[3]<cor[i][j].tyf){
            if(pos[2]>cor[i][j].txi && pos[2]<cor[i][j].txf){
                cout<<"posicion mouse x"<<i<<endl;
                cout<<"posicion mouse y"<<j<<endl;
                e2 = 1;
                rpos[2] = i;
                rpos[3] = j;
                }
                else{
                   rpos[2] = -1;
                   rpos[3] = -1;
                }

         }
      }
   }
   for(i=0;i<(*c).size();i++){
      if(rpos[0] == (*c)[i].a && rpos[1] == (*c)[i].b){
         if(prioridad(c) == 1){
            if(rpos[2] == (*c)[i].a-2 && rpos[3] == (*c)[i].b-2){
               movp[0] = i;
               movp[1] = 1;
               cout<<"hola1"<<endl;
               return movp;

               }
               else if(rpos[2] == (*c)[i].a-2 && rpos[3] == (*c)[i].b+2){
                  movp[0] = i;
                  movp[1] = 2;
                  cout<<"hola2"<<endl;
                  return movp;

               }
         }
         else if(prioridad(c) == 2){
            if(rpos[2] == (*c)[i].a-1 && rpos[3] == (*c)[i].b-1){
                movp[0] = i;
                movp[1] = 1;
                cout<<"hola3"<<endl;
                return movp;
            }
            else if(rpos[2] == (*c)[i].a-1 && rpos[3] == (*c)[i].b+1){
                movp[0] = i;
                movp[1] = 2;
                cout<<"hola4"<<endl;
                return movp;
            }
         }
      }
   }
 }


void cpu (COOR cor[][10])
{
int aux;
   cout<<"TURNO COMPUTADORA PENSANDO JUGADA...." <<endl ;
    do{
        do{
           do{
               do{
                    srand(time(NULL));
                    x=rand() % 9+0 ;
                    y=rand() % 9+0 ;
                    cout<<"pieza:"<<"("<<x<<","<<y<<")"<<"---->Ficha: "<<tablero_dama[x][y]<<endl;
                  }while (tablero_dama[x][y]!='O'&&tablero_dama[x][y]!='C');//VALIDACION PARA EL TIRO DE MOVIMIENTO
                    do
                    {
                    cout<<"buscando movidas"<<endl;
                        if (tablero_dama[x][y]=='C') // Estos if van a permitir el movimiento de las piezas.
                       {
                            movida=rand()% 4+1 ;
                            error=0;
                            cout<<"hola"<<endl;
                            }
                          if (tablero_dama[x][y] == 'O')
                          {
                            movida=rand() % 2+1 ;
                            cout<<"movida:--->"<<movida<<endl;
                            error=0;
                          }
                        //cout<<"movida: ---->"<<movida<<" error: "<<error<<endl;
                        cout<<rand()%2+1<<endl;
                        cout<<"FICHA---> "<<tablero_dama[x][y]<<endl;
                     }while (movida>4||movida<1);
             }while ((y==9&&movida==2)||(y==0&&movida==1)||(y==9&&movida==4)||(y==0&&movida==3)||(x==0&&movida==4)||(x==0&&movida==3)||(x==9&&movida==1)||(x==9&&movida==2));
           }while((movida == 1 &&( tablero_dama[x+1][y-1]== 'O'||tablero_dama[x+1][y-1]== 'C') )||(movida == 2 && (tablero_dama[x+1][y+1]== 'O' || tablero_dama[x+1][y+1]== 'C') )|| (movida == 3 && (tablero_dama[x-1][y-1]== 'O' || tablero_dama[x-1][y-1]== 'C') )||(movida == 4 && (tablero_dama[x-1][y+1]== 'O' || tablero_dama[x-1][y+1]== 'C') ));//VALIDACION PARA CASILLA OCUPADA POR UNA AMIGA
            if (movida==1 &&( tablero_dama[x+1][y-1] == 'X' || tablero_dama[x+1][y-1] == 'D') )
             {
                if(y==1)
                {
                  error=1;
                }
                if(x==6)
                {
                  error=1;
                }
                if(tablero_dama[x+2][y-2] == 'X')
                {
                  error=1;
                }
                if(tablero_dama[x+2][y-2] == 'O')
                {
                  error=1;
                }
                if(tablero_dama[x+2][y-2] == 'C')
                {
                  error=1;
                }
                if(tablero_dama[x+2][y-2] == 'D')
                {
                 error=1;}
              }
             if (movida==2 && (tablero_dama[x+1][y+1] == 'X'||tablero_dama[x+1][y+1] == 'D'))
              {
                if(y==6)
                {
                   error=1;
                }
                if(x==6)
                {
                   error=1;
                }
                if(tablero_dama[x+2][y+2] == 'X')
                {
                   error=1;
                }
                if( tablero_dama[x+2][y+2] == 'O')
                {
                   error=1;
                }
                if( tablero_dama[x+2][y+2] == 'C')
                {
                   error=1;
                }
                if( tablero_dama[x+2][y+2] == 'D')
                {
                   error=1;
                }
              }
             if (movida==3 && (tablero_dama[x-1][y-1] == 'X'||tablero_dama[x-1][y-1] == 'D'))
              {
                if(y==1)
                { error=1;
                }
                if(x==1)
                { error=1;
                }
                if(tablero_dama[x-2][y-2] == 'X')
                {
                  error=1;}
                if( tablero_dama[x-2][y-2] == 'O')
                {
                 error=1;}
                 if( tablero_dama[x-2][y-2] == 'C')
                {
                 error=1;}
                if( tablero_dama[x-2][y-2] == 'D')
                {
                 error=1;
                }
              }
             if (movida==4 && (tablero_dama[x-1][y+1] == 'X'||tablero_dama[x-1][y+1] == 'D'))
              {
                if(y==6)
                {
                    error=1;
                }
                if(x==1)
                {
                    error=1;
                }
                if(tablero_dama[x-2][y+2] == 'X')
                {
                    error=1;
                }
                if( tablero_dama[x-2][y+2] == 'O')
                {
                    error=1;
                }
                if( tablero_dama[x-2][y+2] == 'D')
                {
                    error=1;
                }
                 if( tablero_dama[x-2][y+2] == 'C')
                {
                    error=1;
                }
             }
     }while(error==1);//VALIDACION DE MOVIMIENTO PARA ESPACION OCUPADOS
        if (tablero_dama[x][y]=='C' && movida == 1 && tablero_dama[x+1][y-1]== ' ' ){
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y-1] = 'C' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x+1<<"-"<<y-1 ;

          }
        else if (tablero_dama[x][y]=='C' && movida == 2 && tablero_dama[x+1][y+1]== ' '  )
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y+1] = 'C' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x+1<<"-"<<y+1 ;

        }
        else if (tablero_dama[x][y]=='C' && movida == 3 && tablero_dama[x-1][y-1]== ' '  )
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x-1][y-1] = 'C' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x-1<<"-"<<y-1 ;

        }
        else if (tablero_dama[x][y]=='C' && movida == 4 && tablero_dama[x-1][y+1]== ' '  )
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x-1][y+1] = 'C' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x-1<<"-"<<y+1 ;

        }
        else if(tablero_dama[x][y]=='C' && movida== 1 && (tablero_dama [x+1][y-1] == 'X'||tablero_dama [x+1][y-1] == 'D'))
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y-1]=' ' ;
            tablero_dama[x+2][y-2]= 'C' ;
             cout<<"\a";
             cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA   "<<x+1<<"-"<<y-1 ;
             ficha_x=ficha_x-1;
             contador_fichas_o= contador_fichas_o+3;

        }
        else if(tablero_dama[x][y]=='C' && movida== 2 && (tablero_dama [x+1][y+1] == 'X'||tablero_dama [x+1][y+1] == 'D'))
        {
                tablero_dama[x][y]=' ' ;
                tablero_dama[x+1][y+1]=' ' ;
                tablero_dama[x+2][y+2]= 'C' ;
                 cout<<"\a";
                 cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA   "<<x+1<<"-"<<y+1 ;
                 ficha_x=ficha_x-1;
                 contador_fichas_o= contador_fichas_o+3;

         }
        else if(tablero_dama[x][y]=='C' && movida== 3 && (tablero_dama [x-1][y-1] == 'X'||tablero_dama [x-1][y-1] == 'D'))
        {
                tablero_dama[x][y]=' ' ;
                tablero_dama[x-1][y-1]=' ' ;
                tablero_dama[x-2][y-2]= 'C' ;
                 cout<<"\a";
                 cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA   "<<x-1<<"-"<<y-1 ;
                 ficha_x=ficha_x-1;
                 contador_fichas_o= contador_fichas_o+3;

        }
        else if(tablero_dama[x][y]=='C' && movida== 4 && (tablero_dama [x-1][y+1] == 'X'||tablero_dama [x-1][y+1] == 'D'))
        {
                tablero_dama[x][y]=' ' ;
                tablero_dama[x-1][y+1]=' ' ;
                tablero_dama[x-2][y+2]= 'C' ;
                 cout<<"\a";
                 cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA   "<<x-1<<"-"<<y+1 ;
                 ficha_x=ficha_x-1;
                 contador_fichas_o= contador_fichas_o+3;

        }
        else if (tablero_dama[x][y]=='O' && movida == 1 && tablero_dama[x+1][y-1]== ' ' )
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y-1] = 'O' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x+1<<"-"<<y-1 ;

        }
        if (tablero_dama[x][y]=='O' && movida == 2 && tablero_dama[x+1][y+1]== ' ' )
         {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y+1] = 'O' ;
            cout<<"LA COMPUTADORA A MOVIDO UNA FICHA A LA CASILLA "<<x+1<<"-"<<y+1 ;

         }
        else if(tablero_dama[x][y]=='O'&& movida== 1 && (tablero_dama [x+1][y-1] == 'X'||tablero_dama [x+1][y-1] == 'D'))
         {
            tablero_dama[x][y]=' ' ;
            tablero_dama [x+1][y-1]= ' ' ;
            tablero_dama[x+2][y-2]= 'O' ;
            cout<<"\a";
            cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA  "<<x+1<<"-"<<y-1 ;
            ficha_x=ficha_x-1;
            contador_fichas_o= contador_fichas_o+3;

         }
        else if(tablero_dama[x][y]=='O'&& movida== 2 && ( tablero_dama [x+1][y+1] == 'X'|| tablero_dama [x+1][y+1] == 'D'))
        {
            tablero_dama[x][y]=' ' ;
            tablero_dama[x+1][y+1]=' ' ;
            tablero_dama[x+2][y+2]= 'O' ;
            cout<<"\a";
            cout<<"HAS COMIDO A LA FICHA CONTRARIA 'X' EN LA CASILLA   "<<x+1<<"-"<<y+1 ;
            ficha_x=ficha_x-1;
            contador_fichas_o= contador_fichas_o+3;

         }
           turno_jugador = 1 ;
           cout<<"pensando dibujar"<<endl;
           solofichas(cor);
           cout<<"dibujado"<<endl;
           //cin>>aux;
}

/*void brain(COOR cor[][10],MARCADORES marc){
int i=0, j=1, k=0, l=0, m=0, n=0, iaux=0, jaux=0;
   for(i=0;i<=7;j+=2){
      //iaux=i;
      //jaux=j;
         for(l=j;l<=10-j;l++){
            k=l-1;//posicion de fila a partir de columna
            if(k<9 || l<9){//RECORDAR; colocar else para coronar y tambien cuando se haga el branch izquierdo restriccion espejo
               if(tablero_dama[k][l] == 'O' && tablero_dama[k+1][l+1] != 'O'){//RECORDAR:falta regla si hubiera una dama
                  if(k<8 || l<8){//limites para columna y fila
                     if(tablero_dama[k+1][l+1] == 'X' && tablero_dama[k+2][l+2] == ' '){
                        marc[k][l].comer = 1; //comer va en la estructura
                        //iaux++;
                        if(k+3<){
                           iaux=k+2;
                           jaux=k+3;
                           while(tablero_dama[iaux][jaux] == 'X' && tablero_dama[iaux+1][jaux+1] == ' ' && ){
                              marc[k][l].comer++;
                              iaux++;
                              jaux++;
                            }
                          }
                        }
                        //ablero_dama[i][j] ==
                     }
               }
          }
      }
   }

}*/
/*oid movnegras(COOR cor[10][10],MARCADORES marc2[10][10]){
int i=0, j=1, k=0, l=0, m=0, n=0, iaux=0, jaux=0;
   for(i=0;i<=7;j+=2){
      //iaux=i;
      //jaux=j;
         for(l=j;l<=10-j;l++){
            k=l-1;//posicion de fila a partir de columna
            if(k<9){//RECORDAR; colocar else para coronar y tambien cuando se haga el branch izquierdo restriccion espejo
               if(tablero_dama[k][l] == 'X' && tablero_dama[k-1][l+1] != 'X'){//RECORDAR:falta regla si hubiera una dama
                  if(k<8 && l<8){//limites para columna y fila
                     if(tablero_dama[k+1][l+1] == 'X' && tablero_dama[k+2][l+2] == ' '){
                        marc[k][l].comer = 1; //comer va en la estructura
                        //iaux++;
                        if(k+3<){
                           iaux=k+2;
                           jaux=k+3;
                           while((iaux+1)<8 && (jaux+1)<8){
                              marc[k][l].comer++;
                              iaux+=2;
                              jaux+=2;
                            }
                          }
                        }
                        //ablero_dama[i][j] ==
                     }
               }
          }
      }
   }
}*/
void mov(COOR cor[][10],vector<MARCADORES> c){
int i=0,j=0;
MARCADORES aux;
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2 == 1 && tablero_dama[i][j] == 'X'){
            cout<<"prueba de ejecucion:"<<endl;
            if(j>1 && i>1){//if de comer izquierda
               if((i-2)>=0 && (j-2)>=0){//verifica que la siguiente ficha no este fuera de los limites
                  if(tablero_dama[i-1][j-1] == 'O' && tablero_dama[i-2][j-2] == ' '){
                     aux.comer = 1;
                     aux.px = i;
                     aux.py = j;
                     aux.pxf = i-2;
                     aux.pyf = j-2;
                     //c.push_back(aux);
                  }
               }
            }
            if(j<8 && i<8){//if de comer derecha
                if((i-2)>=0 && (j+2)>=0){//verifica que la siguiente ficha no este fuera de los limites
                  if(tablero_dama[i-1][j+1] == 'O' && tablero_dama[i-2][j+2] == ' '){
                     if(aux.comer == 1){//si ya come derecha tres come rama izquierda y derecha
                        aux.comer = 3;
                     }
                     else if(aux.comer == 0){
                        aux.comer = 2;
                     }
                     aux.px = i;
                     aux.py = j;
                     aux.pxf2 = i-2;
                     aux.pyf2 = j+2;
                     //c.push_back(aux);
                  }
               }
            }
            if(aux.comer >0 || aux.mover >0){
               c.resize(1);
               c.push_back(aux);
            }
        }
     }
   }
}
void marcartablero(vector<MARCADORES> c,COOR cor[][10]){
int i,ax,ay, pause;
   ALLEGRO_COLOR color_cafe = al_map_rgb(117, 75, 13);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
//   c=
   for (i=0;i<c.size();i++){
      if(c[i].comer == 3){
         ax = c[i].pxf;
         ay =c[i].pyf;
         al_draw_filled_circle(((cor[ax][ay].txi+cor[ax][ay].txf)/2),((cor[ax][ay].tyi+cor[ax][ay].tyf)/2),5.0,color_rojo);
         al_draw_filled_circle(((cor[ax][ay+4].txi+cor[ax][ay+4].txf)/2),((cor[ax][ay+4].tyi+cor[ax][ay+4].tyf)/2),5.0,color_rojo);
      }
      else if(c[i].comer == 2){
         ax = c[i].pxf;
         ay =c[i].pyf;
         al_draw_filled_circle(((cor[ax][ay+4].txi+cor[ax][ay+4].txf)/2),((cor[ax][ay+4].tyi+cor[ax][ay+4].tyf)/2),5.0,color_rojo);
      }
      else if(c[i].comer == 1){
         ax = c[i].pxf;
         ay =c[i].pyf;
         al_draw_filled_circle(((cor[ax][ay].txi+cor[ax][ay].txf)/2),((cor[ax][ay].tyi+cor[ax][ay].tyf)/2),5.0,color_rojo);

      }
      al_flip_display();
      cout<<"largo del vector:"<<c.size()<<endl;
      cin>>pause;

      //al_draw_filled_circle(((cor[i][j].txi+cor[i][j].txf)/2),((cor[i][j].tyi+cor[i][j].tyf)/2),5.0,color_rojo);
   }
}
/*void movv(COOR cor[][10],vector<MARCADORES> *c){
   int i,j;
   //c.resize(15);
   MARCADORES aux;
   //vector <MARCADORES> c(15);
   //ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2 == 1 && tablero_dama[i][j] == ' '){
            cout<<"(i,j): "<<i<<" , "<<j<<endl;
            //al_draw_filled_circle(((cor[i][j].txi+cor[i][j].txf)/2),((cor[i][j].tyi+cor[i][j].tyf)/2),5.0,color_rojo);
            aux.a =i;
            aux.b = j;
            cout<<"pushbackvector: "<<aux.a<<","<<aux.b<<endl;
            (*c).push_back(aux);
            //al_flip_display();

         }
      }
   }
   //*d=c;
}*/
bool limite(char s,int pi,int pj){
   if(s == 'i'  && (pi-1 >= 0 && pj-1 >=0)){// limite izquierdo
      return true;
   }
   else if(s == 'd' && (pi-1 >= 0 && pj+1 <=9)){//limite derecho
      return true;
   }
   else if(s == 'a'){
           if((pi-1 >= 0 && pj-1 >=0) || (pi-1 >= 0 && pj+1 <=9)){
              return true;
           }
           else{
              return false;
           }
   }
   else if(s == 'ci' && (pi-2 >= 0 && pj-2 >=0)){
      return true;
   }
   else if(s == 'cd' && (pi-2 >= 0 && pj+2 <=9)){
      return true;
   }
   else if(s == 'ca'){
           if((pi-2 >= 0 && pj-2 >=0) || (pi-2 >= 0 && pj+2 <=9)){
              return true;
           }
           else{
              return false;
           }
   }
   else{
      return false;
   }

}
bool limiteb(char s,int pi,int pj){
   if(s == 'i'  && (pi+1 <=9  && pj+1 <=9)){// limite izquierdo
      return true;
   }
   else if(s == 'd' && (pi+1 <=9  && pj-1 >=9)){//limite derecho
      return true;
   }
   else if(s == 'a'){
           if((pi+1 <=9  && pj+1 <=9) || (pi+1 <=9  && pj-1>=9)){
              return true;
           }
           else{
              return false;
           }
   }
   else if(s == 'ci' && (pi+2 <=9  && pj+2 <=9)){
      return true;
   }
   else if(s == 'cd' && (pi+2 <=9 && pj-2>=9)){
      return true;
   }
   else if(s == 'ca'){
           if((pi+2 <=9  && pj+2 <=9) || (pi+2 <=9  && pj-2>=9)){
              return true;
           }
           else{
              return false;
           }
   }
   else{
      return false;
   }

}
bool checkn(char o,int i,int j){
   if(o == 'Oi' && tablero_dama[i-1][j-1] == 'O' && tablero_dama[i-2][j-2] == ' '){
      return true;
   }
   else if(o =='Od' && tablero_dama[i-1][j+1] == 'O' && tablero_dama[i-2][i+2] == ' '){
      return true;
   }
   else {
      return false;
   }
}
bool ramas(char r,int i,int j){
   if(r == 'i' && limite('ci',i,j) && checkn('Oi',i,j)){
      return true;
   }
   else if(r == 'd' && limite('cd',i,j) && checkn('Od',i,j)){
      return true;
   }
   else{
      return false;
   }
}

int comerdobleomas(int i,int j){
int cpd=0, cpi=0,check1,check2,check3,check4,check5;//variable contador de piezas comidas
   if(ramas('d',i,j)){
      if(ramas('i',i,j)){
         check1 = 1;
      }else{
         check1 =0;
      }
      if(ramas('d',i,j)){
         check2 = 1;
      }else{
         check2 = 0;
      }
      if(check1 && check2){
         if(ramas('i',i-2,j-2)){
            check3 = 1;
         }else{
            check3 = 0;
         }
         if(ramas('d',i-2,j-2)){
            check4 = 1;
         }else{
            check4 = 0;
         }
         if(ramas('d',i-2,j+2)){
            check5 = 1;
         }
         if(check3 && check4 && check5){
            return 6;
         }else if(check3 && !check4 && !check5){
            return 3;
         }
         else if(check4 && !check3 && !check5){
            return 4;
         }
         else if(check5 && !check4 && !check3){
            return 5;
         }

      }else if(check1 && !check2){
         if(ramas('i',i-2,j-2)){
            check3 = 1;
         }else{
            check3 = 0;
         }
         if(ramas('d',i-2,j-2)){
            check4 = 1;
         }else{
            check4 = 0;
      }
      if(check3 && check4){
         return 7;
      }else if(check3 && !check4){
         return 3;
      }else if(check4 && !check3){
         return 4;
      }
     }else if(check2 && !check1){
        if(ramas(i,i-2,j+2)){
           check4 = 1;
        }else{
           check4 = 0;
        }
        if(ramas('d',i-2,j+2)){
            check5 = 1;
        }else{
           check5=0;
        }
        if(check4 && !check5){
           return 4;
        }else if(check5 && !check4){
           return 5;
        }else if(check4 && check5){
           return 9;
        }
     }
   }else {
      return 0;
   }
}

void movv(COOR cor[][10],vector<MARCADORES> *c){
   int i,j,lim,seg ,cd;
   //c.resize(15);
   MARCADORES aux;
   //vector <MARCADORES> c(15);
   //ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2 == 1 && tablero_dama[i][j] == 'X' && limite('ca',i,j)){
            if(limite('ci',i,j)){
               if(tablero_dama[i-1][j-1] == 'O' && tablero_dama[i-2][j-2] == ' '){
                  aux.comer = 1;
               }
            }
            if(limite('cd',i,j)){
               if(tablero_dama[i-1][j+1] == 'O' && tablero_dama[i-2][j+2] == ' '){
                  if(aux.comer == 1){
                     aux.comer = 3;
                  }else if(aux.comer == 0){
                     aux.comer = 2;
                  }
               }
            }
         }
         /*if(aux.comer > 0 && aux.comer < 4){
            cd = comerdobleomas(i-2,j+2);
            if(aux.comer == 2){
               cout<<"COMIDA DOBLE ES: "<<cd<<endl;
            }
         }*/
         if((i+j)%2 == 1 && tablero_dama[i][j] == 'X' && limite('d',i,j)){
             if(limite('i',i,j)){
                if(tablero_dama[i-1][j-1] == ' '){
                   cout<<"(i,j): "<<i-1<<" , "<<j-1<<endl;
                   aux.mover = 1;
                   //cout<<"check iz ok"<<endl;
                }
                //cout<<"(i,j): "<<i-1<<" , "<<j-1<<endl;
             }
             if(limite('d',i,j)){
                if(tablero_dama[i-1][j+1] == ' '){
                   //cout<<"(i,j): "<<i-1<<" , "<<j+1<<endl;
                   if(aux.mover == 1 ){
                      aux.mover = 3;
                   }else if(aux.mover == 0){
                      aux.mover = 2;
                   }
                }
                //cout<<"check der ok"<<endl;
             }
        }
        if((aux.mover > 0 && aux.mover < 4) || (aux.comer >0 && aux.comer < 4)){
                  aux.a = i;
                  aux.b = j;
                  (*c).push_back(aux);
                  aux.mover=0;
                  aux.comer=0;
              }
      }
   }
   //*d=c;
}
void normalizar(COOR cor[][10],vector<MARCADORES> *c){
   int i,j,k;
   ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
   ALLEGRO_COLOR color_verde = al_map_rgb(0,128,0);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   if(prioridad(c) == 1){
      for(i=0;i<(*c).size();i++){
          //for(j=0;j<10;j++){
          //if((i+j)%2 == 1 && tablero_dama[i][j] == ' '){
          k = (*c)[i].a;//coordenadas de fichas dentro del vector
          j = (*c)[i].b;
          //al_draw_filled_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),5.0,color_rojo);
          if((*c)[i].comer == 1){
             al_draw_filled_circle(((cor[k-2][j-2].txi+cor[k-2][j-2].txf)/2),((cor[k-2][j-2].tyi+cor[k-2][j-2].tyf)/2),5.0,color_rojo);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          else if((*c)[i].comer == 2){
               al_draw_filled_circle(((cor[k-2][j+2].txi+cor[k-2][j+2].txf)/2),((cor[k-2][j+2].tyi+cor[k-2][j+2].tyf)/2),5.0,color_rojo);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          else if((*c)[i].comer == 3){
             al_draw_filled_circle(((cor[k-2][j-2].txi+cor[k-2][j-2].txf)/2),((cor[k-2][j-2].tyi+cor[k-2][j-2].tyf)/2),5.0,color_rojo);
             al_draw_filled_circle(((cor[k-2][j+2].txi+cor[k-2][j+2].txf)/2),((cor[k-2][j+2].tyi+cor[k-2][j+2].tyf)/2),5.0,color_rojo);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          //c.push_back(aux);
          al_flip_display();
          //cout<<"cantidad de vectores: "<<(*c)[i].a<<endl;
          //cout<<"hola"<<endl;

         //}
      //}
      }
    }else if(prioridad(c) == 2){
    for(i=0;i<(*c).size();i++){
      //for(j=0;j<10;j++){
         //if((i+j)%2 == 1 && tablero_dama[i][j] == ' '){
            k = (*c)[i].a;//coordenadas de fichas dentro del vector
            j = (*c)[i].b;
            //al_draw_filled_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),5.0,color_rojo);
            if((*c)[i].mover == 1){
               al_draw_filled_circle(((cor[k-1][j-1].txi+cor[k-1][j-1].txf)/2),((cor[k-1][j-1].tyi+cor[k-1][j-1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);

            }
            else if((*c)[i].mover == 2){
               al_draw_filled_circle(((cor[k-1][j+1].txi+cor[k-1][j+1].txf)/2),((cor[k-1][j+1].tyi+cor[k-1][j+1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
            }
            else if((*c)[i].mover == 3){
               al_draw_filled_circle(((cor[k-1][j-1].txi+cor[k-1][j-1].txf)/2),((cor[k-1][j-1].tyi+cor[k-1][j-1].tyf)/2),5.0,color_verde);
               al_draw_filled_circle(((cor[k-1][j+1].txi+cor[k-1][j+1].txf)/2),((cor[k-1][j+1].tyi+cor[k-1][j+1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
            }
            //c.push_back(aux);
            al_flip_display();
            //cout<<"cantidad de vectores: "<<(*c)[i].a<<endl;
            //cout<<"hola"<<endl;

         //}
      //}
   }
}
   //*d=c;
}
void dibrojos(COOR cor[][10],vector<MARCADORES> *c){
   int i,j,k;
   //c.resize(15);
   //MARCADORES aux;
   //vector <MARCADORES> c(15);
   //c = *d;
   ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
   ALLEGRO_COLOR color_verde = al_map_rgb(0,128,0);
   ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
   if(prioridad(c) == 1){
      for(i=0;i<(*c).size();i++){
          //for(j=0;j<10;j++){
          //if((i+j)%2 == 1 && tablero_dama[i][j] == ' '){
          k = (*c)[i].a;//coordenadas de fichas dentro del vector
          j = (*c)[i].b;
          //al_draw_filled_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),5.0,color_rojo);
          if((*c)[i].comer == 1){
             al_draw_filled_circle(((cor[k-2][j-2].txi+cor[k-2][j-2].txf)/2),((cor[k-2][j-2].tyi+cor[k-2][j-2].tyf)/2),5.0,color_rojo);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          else if((*c)[i].comer == 2){
               al_draw_filled_circle(((cor[k-2][j+2].txi+cor[k-2][j+2].txf)/2),((cor[k-2][j+2].tyi+cor[k-2][j+2].tyf)/2),5.0,color_rojo);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          else if((*c)[i].comer == 3){
             al_draw_filled_circle(((cor[k-2][j-2].txi+cor[k-2][j-2].txf)/2),((cor[k-2][j-2].tyi+cor[k-2][j-2].tyf)/2),5.0,color_rojo);
             al_draw_filled_circle(((cor[k-2][j+2].txi+cor[k-2][j+2].txf)/2),((cor[k-2][j+2].tyi+cor[k-2][j+2].tyf)/2),5.0,color_rojo);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
             //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_rojo);
             al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),15.0,color_rojo,3.0);
            }
          //c.push_back(aux);
          al_flip_display();
          //cout<<"cantidad de vectores: "<<(*c)[i].a<<endl;
          //cout<<"hola"<<endl;

         //}
      //}
      }
    }else if(prioridad(c) == 2){
    for(i=0;i<(*c).size();i++){
      //for(j=0;j<10;j++){
         //if((i+j)%2 == 1 && tablero_dama[i][j] == ' '){
            k = (*c)[i].a;//coordenadas de fichas dentro del vector
            j = (*c)[i].b;
            //al_draw_filled_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),5.0,color_rojo);
            if((*c)[i].mover == 1){
               al_draw_filled_circle(((cor[k-1][j-1].txi+cor[k-1][j-1].txf)/2),((cor[k-1][j-1].tyi+cor[k-1][j-1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);

            }
            else if((*c)[i].mover == 2){
               al_draw_filled_circle(((cor[k-1][j+1].txi+cor[k-1][j+1].txf)/2),((cor[k-1][j+1].tyi+cor[k-1][j+1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
            }
            else if((*c)[i].mover == 3){
               al_draw_filled_circle(((cor[k-1][j-1].txi+cor[k-1][j-1].txf)/2),((cor[k-1][j-1].tyi+cor[k-1][j-1].tyf)/2),5.0,color_verde);
               al_draw_filled_circle(((cor[k-1][j+1].txi+cor[k-1][j+1].txf)/2),((cor[k-1][j+1].tyi+cor[k-1][j+1].tyf)/2),5.0,color_verde);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
               //al_draw_filled_rectangle(cor[k][j].txi,cor[k][j].tyi,cor[k][j].txf,cor[k][j].tyf,color_verde);
               al_draw_circle(((cor[k][j].txi+cor[k][j].txf)/2),((cor[k][j].tyi+cor[k][j].tyf)/2),16.0,color_verde,3.0);
            }
            //c.push_back(aux);
            al_flip_display();
            //cout<<"cantidad de vectores: "<<(*c)[i].a<<endl;
            //cout<<"hola"<<endl;

         //}
      //}
   }
}
   //*d=c;
}
int check(vector<MARCADORES> *c,int pos[1],int p){
int i;
   if(p == 1){
      for(i=0;i<(*c).size();i++){
         if(pos[0] == (*c)[i].a && pos[1] == (*c)[i].b){
            return i;
         }
         else{
            return -1;
         }
      }
    }
    else if(p == 2){
       for(i=0;i<(*c).size();i++){
         if(pos[0] == (*c)[i].a && pos[1] == (*c)[i].b){
            return i;
         }
         else{
            return -1;
         }
      }

    }
}
void heuristica(vector<MARCADORES> *h){

}
void brainmachine(COOR cor[][10],vector<MARCADORES> *c){
      int i,j,lim,seg;
   //c.resize(15);
   MARCADORES aux;
   //vector <MARCADORES> c(15);
   //ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
   for(i=0;i<10;i++){
      for(j=0;j<10;j++){
         if((i+j)%2 == 1 && tablero_dama[i][j] == 'O' && limiteb('ca',i,j)){
            if(limiteb('ci',i,j)){
               if(tablero_dama[i+1][j+1] == 'O' && tablero_dama[i+2][j+2] == ' '){
                  aux.comer = 1;
               }
            }
            if(limiteb('cd',i,j)){
               if(tablero_dama[i+1][j-1] == 'O' && tablero_dama[i+2][j-2] == ' '){
                  if(aux.comer == 1){
                     aux.comer = 3;
                  }else if(aux.comer == 0){
                     aux.comer = 2;
                  }
               }
            }

         }
         //if(aux.comer > 0 && aux.comer < 4 && ){
            //if(comerdobleomas())
         }
         if((i+j)%2 == 1 && tablero_dama[i][j] == 'X' && limiteb('d',i,j)){
             if(limiteb('i',i,j)){
                if(tablero_dama[i-1][j-1] == ' '){
                   cout<<"(i,j): "<<i-1<<" , "<<j-1<<endl;
                   aux.mover = 1;
                   //cout<<"check iz ok"<<endl;
                }
                //cout<<"(i,j): "<<i-1<<" , "<<j-1<<endl;
             }
             if(limiteb('d',i,j)){
                if(tablero_dama[i-1][j+1] == ' '){
                   //cout<<"(i,j): "<<i-1<<" , "<<j+1<<endl;
                   if(aux.mover == 1 ){
                      aux.mover = 3;
                   }else if(aux.mover == 0){
                      aux.mover = 2;
                   }
                }
                //cout<<"check der ok"<<endl;
             }
        }
        if((aux.mover > 0 && aux.mover < 4) || (aux.comer >0 && aux.comer < 4)){
                  aux.a = i;
                  aux.b = j;
                  (*c).push_back(aux);
                  aux.mover=0;
                  aux.comer=0;
              }
      }
   }
   //*d=c;

int main(){
   if(!al_init()){
        cerr << "fallo al iniciar allegro!" << endl;
        return -1;
    }
    //cout<<cor[0][0].txi<<endl;
    //cout<<cor[0][0].tyi<<endl;
    bool done = false,ok=true;
    int redraw = 1, pos[4];
    float pos_x,pos_y,pos2_x,pos2_y;
    MARCADORES marc[10][10], marc2[10][10];
    vector<MARCADORES> c;
    vector<int> Mad;
    ALLEGRO_COLOR color_negro = al_map_rgb(0, 0, 0);
    display = al_create_display(700,700);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 30.0);
    al_install_mouse();//drivers mouse
    al_register_event_source(event_queue, al_get_display_event_source(display));//registra eventos de la pantalla
    al_register_event_source(event_queue, al_get_mouse_event_source());//registra eventos del mouse
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    //Dtablero(display);
    //Coordenadas(cor);
    dibtablero(cor);
    poblar_tablero_dama();
    solofichas(cor);
    cout<<"tamaño vector: "<<c.size()<<endl;
    //ALLEGRO_COLOR color_rojo = al_map_rgb(231,37,18);
    //al_draw_filled_circle(175,175.0,10,color_rojo);
    while(!done){
       ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);
       if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE
          done = true;
       }else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
          //pos_x = ev.mouse.x;
          //pos_y = ev.mouse.y;
          //redraw =1;
       }
       else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
           //cout<<"funcion button down";
             if(ev.mouse.button &1){
                //moverficha(display, pos_x, pos_y, cor);
                //al_draw_filled_circle(pos_x,pos_y,15.0,color_negro);
                //done = true;
                pos[0] = ev.mouse.x;
                pos[1] = ev.mouse.y;
                //cout<<pos_x<<endl;
                //cout<<pos_y<<endl;
                }
          }
          if(turno_jugador ==1 && ok){
                 movv(cor,&c);
                 dibrojos(cor,&c);
                 ok=false;
              }
       else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
           if(ev.mouse.button &1){
              cout<<"tamaño vector: "<<c.size()<<endl;
              pos[2] = ev.mouse.x;
              pos[3] = ev.mouse.y;
              //moverficha(display, pos_x, pos_y, pos2_x, pos2_y, cor);
              if(turno_jugador==0){
              cpu(cor);
              }
              else if(turno_jugador==1){
                 //mov(cor,c);
                 //cout<<"tamaño vector: "<<c.size()<<endl;
                 //marcartablero(c,cor);
                 Mad = moverficha(pos, cor,&c);
                 cout<<"señor mad: "<<Mad[1]<<endl;
                 c.clear();
                 ok =true;
              }
              //cout<<pos2_x<<endl;
              //cout<<pos2_y<<endl;
              }
              //cout<<ev.mouse.x<<endl;
              //cout<<ev.mouse.y<<endl;

           }


      /* else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
          if(ev.mouse.button & 1){
             redraw = !redraw;
          }
       }*/
       if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = 1;
        }
       if(redraw){
           //dibtablero(cor);
           //solofichas(cor);
          //Dtablero(display);
          //solotablero(display);
          //al_draw_filled_circle(pos_x,pos_y,15.0,color_negro);
          //al_flip_display();
          //redraw = 0;
       }
       //moverficha(display);
    }
    //al_rest(5);
   return 0;
}
