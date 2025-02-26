#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <system_error>
using namespace std;

string green = "\e[0;32m";
string red = "\e[0;31m";

string startsWith(string symbol, string phrase){
    if(phrase.find(symbol) == 0){
        return symbol;
    }else{
        return "";
    }
}

string eraseStartingCharacter(string phrase){
    string new_phrase = phrase.erase(0,1);
    return new_phrase;
}
void format(string color, string icon, string new_phrase){
    cout<<color<< icon << " " << new_phrase<<'\n';
    cout<<"\033[0m";
}

string icons(string symbol, string phrase){
    string starting = startsWith(symbol, phrase);
    string new_phrase = eraseStartingCharacter(phrase);

    if(starting == "/"){
        format(green, "✓", new_phrase);
    }else if(starting == "."){
        format(red, "●",new_phrase);
        return "●"+new_phrase;
    }
    return new_phrase;
}

void write(string fileToWrite, string message){
    ofstream myFile;
    myFile.open(fileToWrite, ios::app);
    myFile << message << '\n';
    myFile.close();
}

void viewFile(string file){
    ifstream inputFile(file);

    if (!inputFile){
        cout<<"Not a file"<<'\n';
        
    }
    string line;

    while(getline(inputFile, line)){
        icons(".", line);
        icons("/", line);
    }
}

void helpinfo(){
    cout<<"Usage:"<<'\n';
    cout<<"  projgo [command]"<<'\n';
    cout<<'\n';
    cout<<"Available Commands:"<<'\n';
    cout<<"  view	view the file"<<'\n';
    cout<<'\n';
    cout<<"Flags:"<<'\n';
    cout<<"  --help, -h	    help for projgo"<<'\n';
}

int main(int argc, char* argv[]){
    int i = 0;
    string help = "--help";
    string view = "view";
    string add  = "add";
    if(argc == 2 and argv[1] == help){
        helpinfo();
    }else if(argc == 2 and argv[1] == view){
        viewFile("test.txt");
    }else if(argc == 3 and argv[1] == add){
        string message = argv[2];

        write("test.txt", message);
    }

}
