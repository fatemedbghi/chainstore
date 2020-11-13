
#include "tools.h"

#define MSGSIZE 100

using namespace std;

int main(int argc, char** argv)
{
    char inbuf[MSGSIZE]; 
    if (read(atoi(argv[0]), inbuf, MSGSIZE) < 0)  cout<<"read failed"<<endl;
    close(atoi(argv[0]));

    char *token;
    char *rest = inbuf;
    int i = 0;
    vector<char*> input;
    while ((token = strtok_r(rest, "#", &rest))) 
    {
        input.push_back(token);
    }

    
    return 0;
}