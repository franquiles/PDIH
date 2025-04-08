#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 40000

typedef struct{int x, y, goals, size;} Paddle;

void mostrarPantallaInicio(int screen_y, int screen_x) {
    WINDOW *window = newwin(screen_y, screen_x, 0, 0);
    init_pair(4, COLOR_YELLOW, COLOR_BLUE);
    wbkgd(window, COLOR_PAIR(4));
    box(window, '|', '-');

    int mid_x = screen_x / 2;

    mvwprintw(window, 2, mid_x - 18, "=== PONG - ncurses Edition ===");
    mvwprintw(window, 4, mid_x - 18, "Hecho por: Francisco Quiles Ramírez");

    mvwprintw(window, 7, mid_x - 18, "Controles del juego:");
    mvwprintw(window, 8, mid_x - 18, "Jugador Izquierdo: W (subir), S (bajar)");
    mvwprintw(window, 9, mid_x - 18, "Jugador Derecho:  KEY_UP (subir), KEY_DOWN (bajar)");

    mvwprintw(window, 11, mid_x - 18, "El primero que llegue a 7 puntos gana!");
    mvwprintw(window, 13, mid_x - 18, "Presione una tecla para comenzar...");
    mvwprintw(window, 14, mid_x - 18, "(Q para salir en cualquier momento)");


    wrefresh(window);
    getch();
    endwin();
}


int mostrarResumen(WINDOW *window, int izquierda, int derecha) {
    int screen_y, screen_x;
    getmaxyx(window, screen_y, screen_x);
    int mid_x = screen_x / 2;

    werase(window);
    wbkgd(window, COLOR_PAIR(4));
    box(window, '|', '-');

    mvwprintw(window, 2, mid_x - 12, "=== FIN DE LA PARTIDA ===");
    mvwprintw(window, 6, mid_x - 12, "Jugador Izquierdo: %d", izquierda);
    mvwprintw(window, 7, mid_x - 12, "Jugador Derecho : %d", derecha);

    if (izquierda > derecha) {
        mvwprintw(window, 4, mid_x - 12, "GANADOR: Jugador Izquierdo!!!");
    } else {
        mvwprintw(window, 4, mid_x - 12, "GANADOR: Jugador Derecho!!!");
    }

    mvwprintw(window, 9, mid_x - 12, "Si desea jugar otra vez: Pulsa [r]");
    mvwprintw(window, 10, mid_x - 12, "SI desea salir: Pulsa [q]");

    wrefresh(window);

    int ch;
    while (1) {
        ch = getch();
        if (ch == 'r' || ch == 'R') return 1; // Repetir partida
        if (ch == 'q' || ch == 'Q') return 0; // Salir del juego
    }
}

int main(int argc, char *argv[]) {
    int x = 0, y = 0;
    int next_x = 0, next_y = 0;
    int direction_x = 1, direction_y = 1;
    int screen_y, screen_x;
    int i;
    bool quit = false;
    Paddle right_paddle, left_paddle;

    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    clear();

    refresh();

    getmaxyx(stdscr, screen_y, screen_x);
    mostrarPantallaInicio(screen_y, screen_x);

    initscr();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    keypad(stdscr, true);

    right_paddle.size = 7;
    right_paddle.x = screen_x - 2;
    right_paddle.y = screen_y / 2 - right_paddle.size / 2;
    right_paddle.goals = 0;

    left_paddle.size = 7;
    left_paddle.x = 2;
    left_paddle.y = screen_y / 2 - left_paddle.size / 2;
    left_paddle.goals = 0;

    while(!quit) {
        clear();
        attron(COLOR_PAIR(5));
        mvprintw(y, x, "o");
        attroff(COLOR_PAIR(5));
        for(i = 0 ; i < screen_y; ++i) {
            mvprintw(i, screen_x/2, "|");
        }

        for(i = 0 ; i < right_paddle.size; ++i) {
            mvprintw(right_paddle.y + i, right_paddle.x, "|");
        }

        for(i = 0 ; i < left_paddle.size; ++i) {
            mvprintw(left_paddle.y + i, left_paddle.x , "|");
        }
        attron(COLOR_PAIR(6));
        mvprintw(0, screen_x/4 , "%i", left_paddle.goals);
        mvprintw(0, screen_x - screen_x/4 , "%i", right_paddle.goals);
        attroff(COLOR_PAIR(6));
        switch(getch()){
            case 'w':
                if(left_paddle.y > 0)
                    left_paddle.y--;
                break;
            case 's':
                if(left_paddle.y+left_paddle.size < screen_y)
                    left_paddle.y++;
                break;
            case KEY_UP:
                if(right_paddle.y > 0)
                    right_paddle.y--;
                break;
            case KEY_DOWN:
                if(right_paddle.y+right_paddle.size < screen_y)
                    right_paddle.y++;
                break;
            case 'q':
                quit = true;
                break;
        }

        refresh();

        usleep(DELAY);

        next_x = x + direction_x;
        next_y = y + direction_y;


        if(right_paddle.x == x){
            for (i = 0; i < right_paddle.size; ++i) {
                if((right_paddle.y + i) == y){
                    direction_x*= -1;
                    x+= direction_x;
                }
            }
        }


        if(left_paddle.x == x){
            for (i = 0; i < left_paddle.size; ++i) {
                if((left_paddle.y + i) == y){
                    direction_x*= -1;
                    x+= direction_x;
                }
            }
        }

        if (next_x >= screen_x) {
            left_paddle.goals++;
            x = screen_x/4;
            y = screen_y/2;
            direction_y*= -1;
        }else if (next_x < 0) {
            right_paddle.goals++;
            x = screen_x - screen_x/4;
            y = screen_y/2;
            direction_y*= -1;

        }else {
            x+= direction_x;
        }

        if (next_y >= screen_y || next_y < 0) {
            direction_y*= -1;
        } else {
            y+= direction_y;
        }
        if(left_paddle.goals == 7 || right_paddle.goals == 7) {

            quit = true;


            WINDOW *resumen = newwin(screen_y, screen_x, 0, 0);
            int repetir = mostrarResumen(resumen, left_paddle.goals, right_paddle.goals);
            delwin(resumen);

            if (repetir) {
                left_paddle.goals = 0;
                right_paddle.goals = 0;
                left_paddle.y = screen_y / 2 - left_paddle.size / 2;
                right_paddle.y = screen_y / 2 - right_paddle.size / 2;
                x = screen_x / 2;
                y = screen_y / 2;
                direction_x = 1;
                direction_y = 1;
                quit = false;
            }

        }



    }

    endwin();

}
