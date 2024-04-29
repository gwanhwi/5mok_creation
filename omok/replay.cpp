#include "replay.h"
#include "OmokUI.h"
#include <ncurses.h>
#include <string.h>
#include <vector>
using namespace std;
int Queue::run_test() {
    int isreplay = 0;
    wclear(win);
    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return false;
    } else {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    }
    refresh();
    win = newwin(80, 80, 0, 0);

    wbkgd(win, COLOR_PAIR(1));
    drawCheckerboard();
    wmove(win, 0, 0);

    isreplay = print_replay();

    // getch();
    endwin();
    return isreplay;
}
void Queue::push_xy(pair<int, int> p) {
    queue_xy.push(p); // push xy
}

void Queue::push_player(bool &player) {
    if (player) {
        queue_player.push('O'); // player 1
    } else {
        queue_player.push('X'); // player 2
    }
}

void Queue::pop_queue() {
    queue_xy.pop();
    queue_player.pop();
}

int Queue::print_replay() {
    int isreplay = 0;
    while (1) {
        int c;
        keypad(win, TRUE);
        noecho();
        c = wgetch(win);

        if (c == 10) {
            int x = queue_xy.front().first;
            int y = queue_xy.front().second;

            checkerboard[x][y] = queue_player.front();
            printCheckerboard();
            wprintw(win, "Press ENTER KEY to see next..\n");
            wprintw(win, "Press ESC KEY to go to login page\n");

            pop_queue();

            if (queue_xy.empty() == true && queue_player.empty() == true) {
                wrefresh(win);
                wprintw(win,
                        "do you want to play again? or go to login page?\n");
                wprintw(win, "(play again : y / go to login page : ESC)\n");

                int d;
                keypad(win, TRUE);
                noecho();
                d = wgetch(win);
                while (d != 89 && d != 121 && d != 27) {
                    d = wgetch(win);
                }
                if (d == 89 || d == 121) {
                    isreplay = 1;

                    break;
                }
                if (d == 27) {
                    isreplay = 0;
                    break;
                }
            }
        } else if (c == 27) {
            isreplay = 0;
            break;
        } else {
            wprintw(win, "Wrong Command!\n");
        }
    }

    // login();
    // for test, if press esc, shutdown.
    endwin();
    wclear(win);
    return isreplay;
}
void Queue::drawCheckerboard() {
    vector<char> row1;
    vector<char> row2;
    row1.push_back('+');
    row2.push_back('|');
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 3; j++) {
            row1.push_back('-');
            row2.push_back(' ');
        }
        row1.push_back('+');
        row2.push_back('|');
    }
    for (int i = 0; i < 18; i++) {
        checkerboard.push_back(row1);
        checkerboard.push_back(row2);
    }
    checkerboard.push_back(row1);

    printCheckerboard();
    wprintw(win, "Press ENTER KEY to see next..\n");
}

void Queue::printCheckerboard() {
    wclear(win);
    for (int i = 0; i < checkerboard.size(); i++) {
        for (int j = 0; j < checkerboard[i].size(); j++) {
            wprintw(win, "%c", checkerboard[i][j]);
        }
        wprintw(win, "\n");
    }
    wrefresh(win);
}
