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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    string line;
    ifstream source;
    source.open(filename);
    while (getline(source, line)) {
        char name[100];
        int score1, score2, score3;
        const char *Z=line.c_str();
        sscanf(Z, "%[^:]: %d %d %d", name, &score1, &score2, &score3);
        int totalScore = score1 + score2 + score3;
        names.push_back(string(name));
        scores.push_back(totalScore);
        grades.push_back(score2grade(int(totalScore)));
    }
}

void getCommand(string &command, string &arguments) {
    string input;
    cout << "Please input your command: ";
    getline(cin, input);

    unsigned int Pos = input.find_first_of(' ');
    if (Pos != 999999999) {
        command = input.substr(0, Pos);
        arguments = input.substr(Pos + 1);
    } else {
        command = input;
        arguments = "";
    }
}


void searchName(vector<string> names, vector<int> scores, vector<char> grades, string searchName) {
    bool found = false;
    cout << "---------------------------------" << "\n";
    for (int index = 0; index < int(names.size()); index++) {
        if (toUpperStr(names.at(index)) == toUpperStr(searchName)) {
            cout << names.at(index) << "'s score = " << scores.at(index) << "\n";  
            cout << names.at(index) << "'s grade = " << grades.at(index) << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found." << "\n";
    }
    cout << "---------------------------------" << "\n";
}


void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string targetGrade) {
    bool found = false;
    cout << "---------------------------------" << "\n";
    for (int index = 0; index < int(names.size()); index++) {
        if (grades.at(index) == targetGrade[0]) {
            cout << names.at(index) << " (" << scores.at(index) << ")" << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found." << "\n";
    }
    cout << "---------------------------------" << "\n";
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
