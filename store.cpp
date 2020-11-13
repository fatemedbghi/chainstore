#include "main.h"

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

int main() 
{
    string str_obj1("2018/11/10");
    char* char_arr1 = &str_obj1[0];
    string str_obj2("2020/02/14");
    char* char_arr2 = &str_obj2[0];
    string str("PersianShop.csv");
    char* file_name = &str[0];
    cout<< min_or_max(0, char_arr1, char_arr2, file_name,1)<<"\n";      
    return 0; 
}