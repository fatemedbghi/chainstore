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