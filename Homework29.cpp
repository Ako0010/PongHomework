#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#include "pongg.h"

int main() {
    PongGame game(40, 20);
    game.run();
    return 0;
}
