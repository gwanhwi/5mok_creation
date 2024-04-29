#ifndef FILEFUNC_H
#define FILEFUNC_H

#include <fcntl.h>
#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using std::string;
typedef struct Userdata {
    char name[31];
    int score;
    int win;
    int lose;
} User;

void userfilecreate(string username1,string username2);
void userfilesave(string username1, string username2,int result);
int scoreboard(string username1,string username2);

#endif