
#include "tools.h"

#define MSGSIZE 100

using namespace std;

int main(int argc, char** argv)
{
    char inbuf[MSGSIZE]; 
    if (read(atoi(argv[0]), inbuf, MSGSIZE) < 0)  cout<<"read failed"<<endl;
    close(atoi(argv[0]));

    vector<char*> input = split(inbuf);
    vector <string> dir = subdire_or_files(input[2]);
    vector<char*> fifo_arr;
    
    for(int i=0; i<dir.size(); i++){
        string fifo(input[1]);
        fifo.append(to_string(i));
        char *myfifo = &fifo[0];
        fifo_arr.push_back(myfifo);
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
        
        pass_to_unnamed_pipe(msg1,"./store.out");

    }

    for(int i=0; i<dir.size(); i++){
        // mkfifo(fifo_arr[i], 0666);
        
        int fd = open(fifo_arr[i],O_RDONLY);
        if(fd < 0) cout << "error open province : " << strerror( errno )<< endl;
        char str[MSGSIZE];
        if (read(fd, str, MSGSIZE)<0) cout<<"read failed"<<i<<"\n";
        cout<<str<<endl;
        close(fd);
    }

    return 0;
}