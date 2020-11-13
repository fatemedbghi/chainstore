// ‫‪./StoreCalculator.out‬‬ ‫‪commands.txt‬‬ ‫‪assets‬‬

#include<iostream>
#include <string> 
#include <stdio.h> 
#include <string.h> 
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>

#define FIFO "fifo"
#define MSGSIZE 100


using namespace std;

int main(int argc, char** argv)
{
    ifstream file(argv[1]);
    string str;
    int i = 0;
    vector<string> fifo;
    vector<string> command;
    while (getline(file, str))
    {
        command.push_back(str);
        string temp = FIFO;
        temp.append(to_string(i)); 
        string str_obj(temp);
        char *myfifo = &str_obj[0];
        fifo.push_back(&str_obj[0]);
        mkfifo(myfifo, 0666);
        i++;
    }

    for (int j=0; j<i;j++){
        int p[2];
        if (pipe(p) < 0) cout<<"pipe faild\n";
        pid_t pid = fork();
        if (pid < 0) {
            cout << "fork faild.\n";
            exit(1);
        }
        else if (pid == 0) {
            // close(p[0]);
            close(p[1]);
            string s = to_string(p[0]);
            char *pchar = &s[0]; 
            char* argv[] = {pchar,NULL};
            execv("./assets.out", argv);
        }
        else {
            // close(p[0]);
            string msg = command[j];
            msg.append("#");
            msg.append(fifo[j]);
            msg.append("#");
            msg.append(argv[2]);
            char* msg1 = &msg[0];
            if (write(p[1], msg1, MSGSIZE) < 0) cout<<"write failed"<<j<<endl;
            close(p[1]);
            wait(NULL);
        }
    }

    return 0;
}