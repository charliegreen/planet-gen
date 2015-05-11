#include "Main.hpp"

Main*Main::_instance = NULL;

Main::Main() {
    _instance = this;
}

void Main::main() {
    srand(time(NULL));
}

Main*Main::getInstance(){
    return _instance ? _instance : _instance=new Main();
}

int main(int argc, char*argv[]){
    Main::getInstance()->main();
    return 0;
}
