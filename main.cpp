#include <iostream>
#include "Engine/Engine.cpp"

int main(int argc, char *argv[]){
    Engine engine = Engine();
    
    engine.XInnit();
    engine.XCreate_Window("X-Base Engine", 800,600);
    engine.Xwindow_clear(255,255,255,255);

    return 0;
}