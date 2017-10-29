#include "include/Engine.h"
#include <iostream>

#include "include/BaseBlockHeader/BaseBlock.h"
#include "include/BaseBlockHeader/BaseBlockMulti.h"

using namespace std;

int main()
{
    srand(time(0));
    Engine engine;
    engine.run();
}

