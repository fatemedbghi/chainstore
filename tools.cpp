#include "tools.h"

using namespace std;

vector<string> subdire_or_files(char* path)
{
    struct dirent *de;
    DIR *dr = opendir(path); 
  
    if (dr == NULL) 
    { 
        printf("Could not open current directory" ); 
        exit(1); 
    } 
    
    vector <string> dir;
    while ((de = readdir(dr)) != NULL)
    {
        string str(de->d_name);
        if (str.compare("..") != 0 && str.compare(".") != 0)
            dir.push_back(str);
    }
    
    closedir(dr);

    return dir;
}

void pass_to_unnamed_pipe(char *msg,string argc)
{
    char* arg = &argc[0];
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
        execv(arg, argv);
    }
    else {
        // close(p[0]);
        if (write(p[1], msg, MSGSIZE) < 0) cout<<"write failed"<<endl;
        close(p[1]);
        // wait(NULL);
    }
}

vector<char*> split(char inbuf[MSGSIZE]){
    char *token;
    char *rest = inbuf;
    vector<char*> input;
    while ((token = strtok_r(rest, "#", &rest))) 
    {
        input.push_back(token);
    }
    return input;
}