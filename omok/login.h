#pragma once
#include "OmokUI.h"
#include "filefunc.h"
#include "replay.h"

using namespace std;

class Login {
  private:
    string user1;
    string user2;

  public:
    Login();
    int startLogin();
    string getUser1();
    string getUser2();
};
