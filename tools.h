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
#include<errno.h>

#define FIFO "fifo/fifo"
#define MSGSIZE 100
#define MAX 1
#define MIN 0

extern int errno;

using namespace std;

vector<string> subdire_or_files(char* path);
void pass_to_unnamed_pipe(char *msg,string argc);
vector<char*> split(char inbuf[MSGSIZE]);
int find_min_or_max(vector<int> prices);
void pass_to_named_pipe(char *name, int price);
vector<int> gather_prices(vector<string> fifo_arr, int n);

#endif