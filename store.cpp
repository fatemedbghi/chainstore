#include "tools.h"

using namespace std; 

int date_to_int(char* date){
    int int_date = 0;
    char *token;
    char *rest = date;

    int i = 0;
    while ((token = strtok_r(rest, "/", &rest))) 
    {
        if (i==0) int_date += stoi(token)*10000;
        if (i==1) int_date += stoi(token)*100;
        if (i==2) int_date += stoi(token);
        date += stoi(token);
        i++;
    }
    return int_date;
}

int min_or_max(int id, char* start_date, char* end_date, char* file_name, int flag){

    int start = date_to_int(start_date);
    int end = date_to_int(end_date);
    vector<int> price;

    fstream fin; 
    fin.open(file_name, ios::in);   
    string line, word; 
    int i = 0;
    while (fin.good()){
        vector<string> row;
        row.clear();
        getline(fin, line); 

        stringstream l(line); 
        string token; 
        int j = 0;
        int date;
        int id_;
        int price_;
        while(getline(l, token, ',') && i != 0) 
        {
            if (j == 0) date = date_to_int(&token[0]);
            if (j == 1) id_ = stoi(token);
            if (j == 2) {
                price_ = stoi(token);
                if (id == id_ && date >= start && date <= end) price.push_back(price_);
            }
            j++;
        } 
        i++;
    }
    if (!price.empty()) 
    {
        if (flag == 0) return *min_element(price.begin(), price.end());
        if (flag == 1) return *max_element(price.begin(), price.end());
    }
    return -1;
}

int command(vector<char*> input) {
    char *token, *start_date, *end_date;
    char *rest = input[0];
    int i = 0, flag, id;
    while ((token = strtok_r(rest, " ", &rest))) 
    {
        if (i==0){
            if (strcmp("MAX", token) == 0) flag = MAX;
            else flag = MIN;
        }
        if (i==1) id = stoi(token);
        if (i==2) start_date = token;
        if (i==3) end_date = token;
        i++;
    }
    char* file_name = input[2];
    return min_or_max(id, start_date, end_date, file_name, flag);
}

int main(int argc, char** argv) 
{
    char inbuf[MSGSIZE]; 
    if (read(atoi(argv[0]), inbuf, MSGSIZE) < 0)  cout<<"read failed"<<endl;
    close(atoi(argv[0]));

    vector<char*> input = split(inbuf);
    cout<<input[1]<<endl;

    cout << command(input) << endl;
   
    return 0; 
}