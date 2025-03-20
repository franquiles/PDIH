#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char
BYTE MODOTEXTO = 3;
//BYTE MODOVIDEO = 4;
BYTE MODOGRAFICO = 4;

unsigned char bcolor = 0;
unsigned char tcolor = 1;

//aux
void mi_pausa(){
   union REGS inregs, outregs;
 inregs.h.ah = 0x00;
 int86(0x16, &inregs, &outregs);
}
//Ej 1
void gotoxy(int x, int y) {
 union REGS inregs, outregs;
 inregs.h.ah = 0x02; // Indicamos que queremos cambiar la pos del cursor
 inregs.h.dh = y; // Fila
 inregs.h.dl = x; // Columna
 inregs.h.bh = 0x00; // (En la ventana actual)
 int86(0x10, &inregs, &outregs);
}
//Ej 2
void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}
//Ej3
void setvideomode(BYTE modo){
 union REGS inregs, outregs;
 inregs.h.al = modo;
 inregs.h.ah = 0x00;
 int86(0x10, &inregs, &outregs);
}

//Ej4
int getvideomode() {

    int mode;
    union REGS inregs, outregs;
    inregs.h.ah = 15;
    int86(0x10, &inregs, &outregs);
    mode = outregs.h.al;
    return mode;
}

// EJ 5
void textcolor(unsigned char color) {
	tcolor = color;
}
// EJ 6
void textbackground(unsigned char color) {
	bcolor = color;
}

// EJ 7
void clrscr() {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


//Ej 8
void cputchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 0x09;
     inregs.h.al = c;
     inregs.h.bl = (bcolor << 4) | tcolor;  // Se establece el color
     inregs.h.bh = 0x00;
     inregs.x.cx = 1;
     int86(0x10, &inregs, &outregs);

}

//Ej 9
int getche(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

//Ej 10
void pixel(int x, int y, BYTE C){
 union REGS inregs, outregs;
 inregs.x.cx = x;
 inregs.x.dx = y;
 inregs.h.al = C;
 inregs.h.ah = 0x0C;
 int86(0x10, &inregs, &outregs);
}

//Ej extra 1 dibujar cuadrado
void dibujarcuadrado(int xsi, int ysi, int xid, int yid, unsigned char text1, unsigned char bg1, unsigned char text2, unsigned char bg2) {

 int i;

 clrscr();
 printf("\nEjercicio extra: Pintar cuadrado");

 textcolor(text1);
 textbackground(bg1);
  //Arriba
 for (i = xsi; i <= xid; ++i) {
   gotoxy(i, ysi);
   cputchar(' ');
 }
 //Abajo
 for (i = xsi; i <= xid; ++i) {
   gotoxy(i, yid);
   cputchar(' ');
 }
 //Izquierda
 for (i = ysi; i <= yid; ++i) {
   gotoxy(ysi, i);
   cputchar(' ');
 }
 //Derecha
 for (i = ysi; i <= yid; ++i) {
   gotoxy(yid, i);
   cputchar(' ');
 }

 textcolor(text2);
    textbackground(bg2);

    // Arriba
    for (i = xsi + 2; i <= xid - 2; ++i) {
        gotoxy(i, ysi + 2);
        cputchar(' ');
    }
    // Abajo
    for (i = xsi + 2; i <= xid - 2; ++i) {
        gotoxy(i, yid - 2);
        cputchar(' ');
    }
    // Izquierda
    for (i = ysi + 2; i <= yid - 2; ++i) {
        gotoxy(xsi + 2, i);
        cputchar(' ');
    }
    // Derecha
    for (i = ysi + 2; i <= yid - 2; ++i) {
        gotoxy(xid - 2, i);
        cputchar(' ');
    }

    gotoxy(xsi, yid + 2);


}

//Ejercicio extra 2, modo grafico
void rectangulo(int x1, int y1, int x2, int y2, BYTE C){
    int i;
    printf("\nEjercicio extra2: Cuadrado");

    // Línea superior e inferior
    for (i = x1; i <= x2; i++) {
        pixel(i, y1, C);
        pixel(i, y2, C);
    }
    // Línea izquierda y derecha
    for (i = y1; i <= y2; i++) {
        pixel(x1, i, C);
        pixel(x2, i, C);
    }
}






//Ejercicio extra 3: art ascii
void dibujarPatos(){
    //pato1
    gotoxy(10, 5); printf("_");
    gotoxy(11, 5); printf("_");
    gotoxy(12, 5); printf("(");
    gotoxy(13, 5); printf(".");
    gotoxy(14, 5); printf(")");
    gotoxy(15, 5); printf("<");

    gotoxy(13, 4); printf("_");

    gotoxy(10, 6); printf("\\");
    gotoxy(11, 6); printf("_");
    gotoxy(12, 6); printf("_");
    gotoxy(13, 6); printf("_");
    gotoxy(14, 6); printf(")");


    //pato2
    gotoxy(17, 5); printf("_");
    gotoxy(18, 5); printf("_");
    gotoxy(19, 5); printf("(");
    gotoxy(20, 5); printf(".");
    gotoxy(21, 5); printf(")");
    gotoxy(22, 5); printf(">");

    gotoxy(20, 4); printf("_");

    gotoxy(17, 6); printf("\\");
    gotoxy(18, 6); printf("_");
    gotoxy(19, 6); printf("_");
    gotoxy(20, 6); printf("_");
    gotoxy(21, 6); printf(")");

    //pato3

    gotoxy(24, 5); printf("_");
    gotoxy(25, 5); printf("_");
    gotoxy(26, 5); printf("(");
    gotoxy(27, 5); printf(".");
    gotoxy(28, 5); printf(")");
    gotoxy(29, 5); printf("=");

    gotoxy(27, 4); printf("_");

    gotoxy(24, 6); printf("\\");
    gotoxy(25, 6); printf("_");
    gotoxy(26, 6); printf("_");
    gotoxy(27, 6); printf("_");
    gotoxy(28, 6); printf(")");







}






int main(){
	int tmp;
	int video_mode;
	clrscr();
	printf("\nEjercicio 7: Se ha limpiado la pantalla.");

	//EJ 1 Gotoxy
    printf("\nEjercicio 1: Pulsa una tecla (GOTOXY 20,20): ");
    gotoxy(20,20);
    mi_pausa();
    printf("\n");

    //Ej 2
	printf("\nEjercicio 2: Cursor invisible: ");
   	setcursortype(0);
   	mi_pausa();
   	printf("\nEjercicio 2: Cursor grueso: ");
   	setcursortype(2);
   	mi_pausa();
   	printf("\nEjercicio 2: Cursor normal: ");
   	setcursortype(1);
   	mi_pausa();

   	//Ej 3 y 4
   	printf("\nEjercicio 3 y 4: Pulsa una tecla (setVideo): ");
    setvideomode(MODOGRAFICO);
    video_mode = getvideomode();
    printf("\nEjercicio 3 y 4: Pulsa una tecla (MODO GRAFICO 4): %i", video_mode);
    mi_pausa();
    printf("\nEjercicio 3 y 4: Pulsa una tecla (MODO TEXTO 3): ");
    setvideomode(MODOTEXTO);
    video_mode = getvideomode();
    printf("\nEjercicio 3 y 4: (MODO TEXTO 3) video mode: %i", video_mode);
    mi_pausa();
    printf("\n");



    //Ejs: 5 6 8 y 9
    printf("\nEjercicios 5, 6, 8 y 9: Introduce una tecla: (GETCHE)");
    tmp = getche();
    mi_pausa();
    printf("\nEjercicios 5, 6, 8 y 9: Pulsa una tecla: ( TEXTCOLOR 1 (azul oscuro) y background 3 (cian) )\n");
    mi_pausa();
    textcolor(1);
    textbackground(3);
    cputchar((char)tmp);
    mi_pausa();
    printf("\n");

    //Ej 10
   	printf("\nEjercicio 10: Pixel: ");
   	setvideomode(MODOGRAFICO); //gráfico
    pixel(10,40,0);
    pixel(10,50,1);
    pixel(15,60,2);
    pixel(20,70,3);
    mi_pausa();
    setvideomode(MODOTEXTO); //texto

    //Ej extra1
    mi_pausa();
    dibujarcuadrado(1,1,10,10,1,3,14,4);
    mi_pausa();
    printf("\n");

    //Ej extra2

    setvideomode(MODOGRAFICO);
    rectangulo(80,80,180,140,3);
    mi_pausa();
    setvideomode(MODOTEXTO);

    //Ej extra3
    printf("\nEjercicio extra3: ");
    dibujarPatos();


	return 0;
}
