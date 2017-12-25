#include "include/Engine.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    Engine engine;
    engine.run();
}

