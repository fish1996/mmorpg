#include <iostream>
#include "server.h"
using namespace std;

int main(int argc, char *argv[])
{
    server s;
    cout << "Hello World!" << endl;
    s.start();

    return 0;
}
