#pragma once
#include <ncurses.h>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;

class Queue {
  private:
    queue<pair<int, int>> queue_xy;
    queue<char> queue_player;
    WINDOW *win;
    vector<vector<char>> checkerboard;

  public:
    void push_xy(pair<int, int> p);
    void push_player(bool &player);
    void pop_queue();
    int print_replay();
    int run_test();
    void printCheckerboard();
    void drawCheckerboard();
};
