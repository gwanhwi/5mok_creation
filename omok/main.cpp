#include "OmokUI.h"
#include "filefunc.h"
#include "login.h"
#include "replay.h"

int main() {
    int play = 27;
    int cont = 0;
    string user1 = "";
    string user2 = "";
    while (play != -1) {
        OmokUI *omokGame = new OmokUI();
        Login *login = new Login();
        if (play == 27) {
            play = omokGame->startUI();
            if (play == -1) {
                delete omokGame;
                delete login;
                break;
            }
        }
        if (play == 0) {
            play = login->startLogin();
            if (play == 27) {
                delete omokGame;
                delete login;
                continue;
            }
            user1 = login->getUser1();
            user2 = login->getUser2();
        }
        omokGame->setUsername(user1, user2);
        userfilecreate(user1, user2);

        cont = scoreboard(user1, user2);
        if (cont == -1) {
            play = 0;
            delete omokGame;
            delete login;
            continue;
        }
        omokGame->run();

        play = omokGame->isreplay;
        int result = omokGame->getWinner();
        userfilesave(user1, user2, result);
        delete omokGame;
        delete login;
    }
    finishUI();
    return 0;
}
