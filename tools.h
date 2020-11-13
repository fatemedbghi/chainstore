#ifndef TOOLS_H
#define TOOLS_H

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
#include <dirent.h> 
#include<sys/wait.h> 

#define FIFO "fifo"
#define MSGSIZE 100

using namespace std;

vector<string> subdire_or_files(char* path);

#endif