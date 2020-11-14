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
    int fd;
    if (pid < 0) {
        cout << "fork faild.\n";
        exit(1);
    }
    else if (pid == 0) {
        close(p[1]);
        string s = to_string(p[0]);
        char *pchar = &s[0]; 
        char* argv[] = {pchar,NULL};
        execv(arg, argv);
    }
    else {
        if (write(p[1], msg, MSGSIZE) < 0) cout<<"write failed"<<endl;
        close(p[1]);
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

int find_min_or_max(vector<int> prices) {
    vector <int> temp;
    int flag;
    for (int i=0;i<prices.size();i++) {
        if (prices[i] != -1) 
        {
            flag = prices[i]%10;
            temp.push_back(prices[i]);
        }
    }
    if (temp.size() != 0){
        if (flag == 0) return *min_element(prices.begin(), prices.end());
        if (flag == 1) return *max_element(prices.begin(), prices.end());
    }
    return -1;
}

void pass_to_named_pipe(char *name, int price)
{
    int fd = open(name, O_WRONLY);
    string s = to_string(price);
    const char *pchar = s.c_str();
    char kh[100];
    strcpy(kh, pchar);
    if(fd < 0) {
        cout <<"write open error : " << strerror( errno )<< endl;
        exit(0);
    }
    if (write(fd,kh,MSGSIZE) < 0) cout<<"write failed\n";
    close(fd);
}

vector<int> gather_prices(vector<string> fifo_arr, int n)
{
    vector<int> prices;
    for(int i=0; i<n; i++){
        int fd = open(&fifo_arr[i][0],O_RDONLY);
        if(fd < 0) cout << "read open error  : " << strerror( errno )<< endl;
        char str[MSGSIZE];
        int why = read(fd, str, MSGSIZE);
        if (why < 0) cout <<"read error  : " << strerror( errno )<< endl;
        int temp = atoi(str);
        prices.push_back(temp);
        close(fd);
        unlink(&fifo_arr[i][0]);
    }
    return prices;
}


vector<string> create_fifo(vector<char*> input,vector <string> dir,string argc)
{
    vector<string> fifo_arr;
    for(int i=0; i<dir.size(); i++){
        string fifo(input[1]);
        fifo.append(to_string(i));
        char *myfifo = &fifo[0];
        fifo_arr.push_back(fifo);
        mkfifo(myfifo, 0666);

        string msg(input[0]);
        msg.append("#");
        string f(myfifo);
        msg.append(f);
        msg.append("#");
        msg.append(input[2]);
        msg.append("/");
        msg.append(dir[i]);
        char* msg1 = &msg[0];
        
        pass_to_unnamed_pipe(msg1,argc);
    }
    return fifo_arr;
}