// ‫‪./StoreCalculator.out‬‬ ‫‪commands.txt‬‬ ‫‪assets‬‬

#include "tools.h"

using namespace std;

int main(int argc, char** argv)
{
    ifstream file(argv[1]);
    string str;
    int i = 0;
    vector<string> command;
    while (getline(file, str))
    {
        command.push_back(str);
        i++;
    }

    for (int j=0; j<i;j++){

        string temp = FIFO;
        temp.append(to_string(j)); 
        char *myfifo = &temp[0];
        mkfifo(myfifo, 0666);

        string msg = command[j];
        msg.append("#");
        msg.append(myfifo);
        msg.append("#");
        msg.append(argv[2]);
        char* msg1 = &msg[0];

        pass_to_unnamed_pipe(msg1,"./assets.out");
    }

    return 0;
}