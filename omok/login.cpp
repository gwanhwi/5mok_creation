#include "login.h"
#include <ctype.h>
#include <curses.h>
#include <fcntl.h>
#include <form.h>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
Login::Login() {
    user1 = "";
    user2 = "";
}
int Login::startLogin() {
    FIELD *field[3]; // for input user name
    FORM *my_form;   // making field
    clear();
    int ch;

    initscr();
    cbreak();
    noecho();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    keypad(stdscr, TRUE);
    field[0] =
        new_field(1, 10, 12, 38, 0, 0); // make a file in a proper location
    field[1] = new_field(1, 10, 14, 38, 0, 0);
    field[2] = NULL;

    set_field_back(field[0], A_UNDERLINE); // show underline
    field_opts_off(field[0], O_AUTOSKIP);

    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    my_form = new_form(field);
    post_form(my_form);
    refresh();

    attron(COLOR_PAIR(1));

    mvprintw(12, 35, "P1:");
    mvprintw(14, 35, "P2:");
    mvprintw(1, 1, "Start press F1.");                  // show manual
    mvprintw(2, 1, "Press ESC if you want to go back"); // show manual
    refresh();                                          // show!!
    while (1) { // repeat untill pressed f1key
        while ((ch = getch()) != KEY_F(1)) {
            switch (ch) {
            case '\n':     // when press enter, down key
            case KEY_DOWN: // move under field
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP: // when press key up
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;                              // move top field
            case KEY_BACKSPACE:                     // when press key backspace
                form_driver(my_form, REQ_DEL_PREV); // remove
                break;
            case 27:      // esc key
                endwin(); // exit --> back to menu window
                return 27;
            default:
                form_driver(my_form, ch); // input string
                break;
            }
        }

        /* char usr1[30],usr2[30];

         strcpy(usr1, field_buffer(field[0], 0)); // make user1 name
         strcpy(usr2, field_buffer(field[1], 0)); // make user2 name
         if (isspace(usr1[0]) || isspace(usr2[0])) {
             // if the name begins with a blank space, show error message
             mvprintw(16, 20, "please remove the spaces in the first letter");
             continue;
         }
                 mvprintw(20,20,"%s %s",usr1,usr2);
                 refresh();

         char u1[30];
         char u2[30];

         for (int i = 0; i < sizeof(usr1); i++) {
             u1[i] = usr1[i];
         }
         for (int i = 0; i < sizeof(usr2); i++) {
             u2[i] = usr2[i];
         }*/

        string name1(field_buffer(field[0], 0));
        string name2(field_buffer(field[1], 0));

        mvprintw(20, 35, "%s%s", name1.c_str(), name2.c_str());
        refresh();

        // delete blank
        for (int i = 0; i < name1.length(); i++) {
            if (name1.at(i) != ' ') {
                user1 += name1.at(i);
            }
        }
        for (int i = 0; i < name2.length(); i++) {
            if (name2.at(i) != ' ') {
                user2 += name2.at(i);
            }
        }
        //   user1 = name1;
        // user2 = name2;

        unpost_form(my_form);
        free_form(my_form); // end use form
        free_field(field[0]);
        free_field(field[1]);
        free_field(field[2]);
        endwin();
        break;
    }
    attroff(COLOR_PAIR(1));
    return 0;
}
string Login::getUser1() { return user1; }
string Login::getUser2() { return user2; }
