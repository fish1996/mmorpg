#ifndef SERVER_H
#define SERVER_H

#include <fstream>

class server
{
private:
    std::ofstream out;
public:
    server();
    void start();
};


#endif // SERVER_H
