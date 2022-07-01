#include <bits/stdc++.h>
using namespace std;
int main(){
    ifstream file ;
    file.open("Data.txt");
    vector<string> names ;
    while(! file.eof()){
        string str1 = "daily problem solved";
        string str ;
        getline(file, str);
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        size_t found = str.find(str1);
    if (found != string::npos)
        {
            int pos1 = str.find(']'), pos2 ;
            for(int i = pos1+1 ; i < str.size(); i++){
                if(str[i] == ':'){
                    pos2 = i ;
                    break;
                }
            }
            cout << pos1 << "  " << pos2 << endl ;
            names.push_back(str.substr(pos1+2, pos2-pos1-2));

        }
    }
    file.close();
    for(string n : names){
        cout << n << endl ;
    }
}