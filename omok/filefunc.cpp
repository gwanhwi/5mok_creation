#include "filefunc.h"
#include <curses.h>
#include <fcntl.h>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void userfilesave(string username1, string username2, int result) {

    // loginname= received username from login (changeable)
    // result = win(1) or lose(0) from last game (changeable)

    string a;

    a = username1;
    string b;
    b = username2;
    char loginname1[30];
    char loginname2[30];
    strcpy(loginname1, a.c_str());
    strcpy(loginname2, b.c_str());

    char filename1[30] = "./"; // path fix
    char filename2[30] = "./";
    char dat[] = ".dat";
    strcat(filename1, loginname1); // making the './name.dat' form
    strcat(filename1, dat);

    strcat(filename2, loginname2);
    strcat(filename2, dat);

    // printf("filename1 : %s\n", filename1);
    // printf("filename2 : %s\n", filename2);
    char *pathname2 = filename2;
    char *pathname1 = filename1; // convert to pointer

    int fd1;
    int fd2;
    ssize_t wsize = 0;
    ssize_t readsize = 0;

    if (access(pathname1, F_OK) != -1) {

        User *olduser1 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser1->name, '\0', 31);

        olduser1->win = 0;
        olduser1->lose = 0;
        olduser1->score = 0;

        fd1 = open(pathname1, O_RDWR, 0666); // open

        if (fd1 == -1) {
            // perror("open error");
            exit(-1);
        }

        readsize = read(fd1, (User *)olduser1, sizeof(User)); // read

        if (readsize == -1) {
            // perror("read error");
            exit(-2);
        }
        // printf("fd1 : %d , rsize: %ld\n", fd1, readsize);

        if (result == 0) { // if player 1 last game lost
            olduser1->lose = olduser1->lose + 1;
            olduser1->score = olduser1->score - 1;

        } else if (result == 1) { // if last game won
            olduser1->win = olduser1->win + 1;
            olduser1->score = olduser1->score + 3;
        }
        lseek(fd1, 0, SEEK_SET);
        wsize = (write(fd1, (User *)olduser1, sizeof(User)));
        if (wsize == -1) {
            // perror("write name error");
            exit(-2);
        }
        // 이부분에 mvprintw 를 통해 원하는 좌표에 사용자의 최신화된 정보 출력
        // printf("%s's scoreboard\nWin %d times\nLose %d times\nYour score now
        // : "
        //"%d\n",
        // olduser1->name, olduser1->win, olduser1->lose, olduser1->score);

        close(fd1);
        free(olduser1);

    } else { // ONLY first time login
        // perror("file does not exists");
        exit(-3);
    }

    //  ------------------------------ now user2
    if (access(pathname2, F_OK) != -1) {

        User *olduser2 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser2->name, '\0', 31);

        olduser2->win = 0;
        olduser2->lose = 0;
        olduser2->score = 0;

        fd2 = open(pathname2, O_RDWR, 0666); // open

        if (fd2 == -1) {
            // perror("open error");
            exit(-1);
        }

        readsize = read(fd2, (User *)olduser2, sizeof(User)); // read

        if (readsize == -1) {
            // perror("read error");
            exit(-2);
        }
        // printf("fd2 : %d , rsize: %ld\n", fd2, readsize);

        if (result == 1) { // if player 2 last game lost
            olduser2->lose = olduser2->lose + 1;
            olduser2->score = olduser2->score - 1;

        } else if (result == 0) { // if player2 last game won
            olduser2->win = olduser2->win + 1;
            olduser2->score = olduser2->score + 3;
        }
        lseek(fd2, 0, SEEK_SET);
        wsize = (write(fd2, (User *)olduser2, sizeof(User)));
        if (wsize == -1) {
            // perror("write name error");
            exit(-2);
        }
        // 이부분에 mvprintw 를 통해 원하는 좌표에 사용자의 최신화된 정보 출력
        // printf("%s's scoreboard\nWin %d times\nLose %d times\nYour score now
        // : "
        //"%d\n",
        // olduser2->name, olduser2->win, olduser2->lose, olduser2->score);

        close(fd2);
        free(olduser2);

    } else { // ONLY first time login
        perror("file does not exists");
        exit(-3);
    }
}

void userfilecreate(
    string username1,
    string username2) { // user file first time create, one time per one user
    // cout << username1 << " " << username2 << endl;
    string a;
    a = username1;
    string b;
    b = username2;
    char newusername1[30];
    char newusername2[30];
    strcpy(newusername1, a.c_str());
    strcpy(newusername2, b.c_str());

    char newfilename1[30] = "./";
    char newfilename2[30] = "./";
    char newdat[6] = ".dat";
    strcat(newfilename1, newusername1);
    strcat(newfilename1, newdat);
    strcat(newfilename2, newusername2);
    strcat(newfilename2, newdat);
    // printf("newfilename1: %s\n", newfilename1);
    // printf("newfilename2: %s\n",newfilename2);
    char *newpathname1 = newfilename1;
    char *newpathname2 = newfilename2;
    int fd1;
    int fd2;
    ssize_t wsize1 = 0;
    ssize_t wsize2 = 0;
    if (access(newpathname1, F_OK) == 0 &&
        access(newpathname2, F_OK) == 0) { // already file exists
        return;
    } else if (access(newpathname1, F_OK) == 0 &&
               access(newpathname2, F_OK) != 0) {
        User *user2 = (User *)malloc(sizeof(User));
        memset(user2->name, '\0', 31);
        strcpy(user2->name, newusername2);
        user2->win = 0;
        user2->lose = 0;
        user2->score = 100;

        fd2 = open(newpathname2, O_CREAT | O_RDWR, 0666); // open

        if (fd2 == -1) {
            // perror("open error");
            exit(-1);
        }
        wsize2 = write(fd2, (User *)user2, sizeof(User)); // write

        if (wsize2 == -1) {
            // perror("write name error");
            exit(-2);
        }

        // printf("fd2 : %d , wsize2: %ld\n", fd2, wsize2);

        close(fd2);
        free(user2);

    } else if (access(newpathname1, F_OK) != 0 &&
               access(newpathname2, F_OK) == 0) {
        User *user1 = (User *)malloc(sizeof(User));
        memset(user1->name, '\0', 31);
        strcpy(user1->name, newusername1);

        user1->win = 0;
        user1->lose = 0;
        user1->score = 100;

        fd1 = open(newpathname1, O_CREAT | O_RDWR, 0666); // open

        if (fd1 == -1) {
            // perror("open error");
            exit(-1);
        }

        wsize1 = write(fd1, (User *)user1, sizeof(User)); // write

        if (wsize1 == -1) {
            // perror("write name error");
            exit(-2);
        }

        // printf("fd1 : %d , wsize1: %ld\n", fd1, wsize1);

        close(fd1);
        free(user1);

    } else { // first time login
        User *user1 = (User *)malloc(sizeof(User));
        memset(user1->name, '\0', 31);
        strcpy(user1->name, newusername1);
        user1->win = 0;
        user1->lose = 0;
        user1->score = 100;

        fd1 = open(newpathname1, O_CREAT | O_RDWR, 0666); // open

        if (fd1 == -1) {
            // perror("open error");
            exit(-1);
        }

        wsize1 = write(fd1, (User *)user1, sizeof(User)); // write

        if (wsize1 == -1) {
            // perror("write name error");
            exit(-2);
        }

        // printf("fd1 : %d , wsize1: %ld\n", fd1, wsize1);

        close(fd1);
        free(user1);

        User *user2 = (User *)malloc(sizeof(User));
        memset(user2->name, '\0', 31);
        strcpy(user2->name, newusername2);

        user2->win = 0;
        user2->lose = 0;
        user2->score = 100;

        fd2 = open(newpathname2, O_CREAT | O_RDWR, 0666); // open

        if (fd2 == -1) {
            // perror("open error");
            exit(-1);
        }

        wsize2 = write(fd2, (User *)user2, sizeof(User)); // write

        if (wsize2 == -1) {
            // perror("write name error");
            exit(-2);
        }

        // printf("fd2 : %d , wsize2: %ld\n", fd2, wsize2);

        close(fd2);
        free(user2);
    }
}

int scoreboard(string username1, string username2) {
    string a;
    a = username1;
    string b;
    b = username2;
    char loginname1[30];
    char loginname2[30];
    strcpy(loginname1, a.c_str());
    strcpy(loginname2, b.c_str());

    char filename1[30] = "./"; // path fix
    char filename2[30] = "./";
    char dat[] = ".dat";
    strcat(filename1, loginname1); // making the './name.dat' form
    strcat(filename1, dat);
    strcat(filename2, loginname2);
    strcat(filename2, dat);

    // printf("filename1 : %s\n", filename1);
    // printf("filename2 : %s\n", filename2);
    char *pathname2 = filename2;
    char *pathname1 = filename1; // convert to pointer

    int fd1;
    int fd2;
    ssize_t readsize1 = 0;
    ssize_t readsize2 = 0;

    if (access(pathname1, F_OK) == 0 && access(pathname2, F_OK) == 0) {
        User *olduser1 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser1->name, '\0', 31);

        olduser1->win = 0;
        olduser1->lose = 0;
        olduser1->score = 0;

        fd1 = open(pathname1, O_RDWR, 0666); // open

        if (fd1 == -1) {
            // perror("open error");
            exit(-1);
        }
        readsize1 = read(fd1, (User *)olduser1, sizeof(User)); // read

        if (readsize1 == -1) {
            // perror("read error");
            exit(-2);
        }
        // printf("fd1 : %d , rsize: %ld\n", fd1, readsize);
        User *olduser2 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser2->name, '\0', 31);

        olduser2->win = 0;
        olduser2->lose = 0;
        olduser2->score = 0;

        fd2 = open(pathname2, O_RDWR, 0666); // open

        if (fd2 == -1) {
            // perror("open error");
            exit(-1);
        }

        readsize2 = read(fd2, (User *)olduser2, sizeof(User)); // read

        if (readsize2 == -1) {
            // perror("read error");
            exit(-2);
        }

        initscr();
        noecho();
        clear();
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "Press q to leave");
        mvprintw(1, 0, "Press Enter to game start");

        mvprintw(15, 10, "[%s's scoreboard]", olduser1->name);
        mvprintw(16, 10, "Win %d times", olduser1->win);
        mvprintw(17, 10, "Lose %d times", olduser1->lose);
        mvprintw(18, 10, "Your score now : %d", olduser1->score);

        mvprintw(15, 35, "[%s's scoreboard]", olduser2->name);
        mvprintw(16, 35, "Win %d times", olduser2->win);
        mvprintw(17, 35, "Lose %d times", olduser2->lose);
        mvprintw(18, 35, "Your score now : %d", olduser2->score);

        refresh();
        attroff(COLOR_PAIR(1));
        char ch = getch();
        while (ch != 'q' && ch != 10) {
            ch = getch();
        }
        if (ch == 10) {
            close(fd1);
            close(fd2);
            free(olduser1);
            free(olduser2);
            endwin();
            return 1;
        }
        if (ch == 'q') {

            close(fd1);
            close(fd2);
            free(olduser1);
            free(olduser2);
            endwin();
            return -1;
        }

    } else {
        // perror("File not exists");
        exit(-4);
    }
    return -1;
}
