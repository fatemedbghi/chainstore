#include "tools.h"

using namespace std;

int main(int argc, char** argv)
{
    char inbuf[MSGSIZE]; 
    if (read(atoi(argv[0]), inbuf, MSGSIZE) < 0)  cout<<"read failed"<<endl;
    close(atoi(argv[0]));

    vector<char*> input = split(inbuf);
    vector <string> dir = subdire_or_files(input[2]);
    vector <string> fifo_arr = create_fifo(input,dir,"./store.out");
    
    vector<int> prices = gather_prices(fifo_arr, dir.size());
    int price = find_min_or_max(prices);
    pass_to_named_pipe(input[1], price);

    return 0;
}