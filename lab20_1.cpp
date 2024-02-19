#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f, vector<string> &a , vector<int> &b , vector<char> &c){
    ifstream file(f);
    string text;
    char name[100];
    char format[] = "%[^:]: %d %d %d";
    int u,v,w;
    while(getline(file,text)){
        sscanf(text.c_str(),format,name,&u,&v,&w);
        a.push_back(name);
        b.push_back(u+v+w);
        c.push_back(score2grade(u+v+w));
    }
}

void getCommand(string &command, string &key){
    cout <<"Please input your command: ";
    cin >> command;
    if(toUpperStr(command)=="GRADE"|| toUpperStr(command)=="NAME"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string>name, vector<int> score, vector<char> grade, string key){
    int x = 0;

    cout << "---------------------------------"<<endl;
    
    for(unsigned int i = 0 ; i < name.size() ;i++){
        if(key == toUpperStr(name[i])){
        cout << name[i] << "'s score = "<< score[i]<<endl;
        cout << name[i] << "'s grade = "<< grade[i]<<endl;
        x++; 
        }else if(i == name.size()-1 && x==0){
        cout <<"Cannot found."<<endl;
        }   
    }
    cout << "---------------------------------"<< endl;

}

void searchGrade(vector<string> name, vector<int> score ,vector<char>grade,string key){
    int i = 0;
    cout << "---------------------------------"<<endl;

    for(unsigned int j = 0 ; j < name.size();j++){
        if(*key.c_str() == grade[j]){
            cout << name[j] <<" ("<< score[j] <<")" << endl;
            i++;
        }else if(j == name.size()-1 && i == 0){
            cout <<"Cannot found."<<endl;
        }
    }
        cout << "---------------------------------"<<endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
