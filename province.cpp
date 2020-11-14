// MIN 0 2018/01/01 2020/01/01#fifo32#assets/Isfahan
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
        
        pass_to_unnamed_pipe(msg1,"./city.out");
    }
   
    vector<int> prices = gather_prices(fifo_arr, dir.size());
    int price = find_min_or_max(prices);
    pass_to_named_pipe(input[1], price);
    return 0;
}