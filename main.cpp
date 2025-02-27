#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <system_error>
using namespace std;


string help = "--help";
string view = "view";
string add  = "add";

string green = "\e[0;32m";
string red = "\e[0;31m";
string blue = "\e[0;34m";
string underlinePurple = "\e[4;35m";



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
    }else if(starting == "*"){
        format(blue,"💡", new_phrase);
        return "💡"+new_phrase;
    }else if(starting == "#"){
        format(underlinePurple, "", new_phrase);
        return new_phrase; 
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
        icons("*", line);
        icons("#", line);
    }
}

void helpInfoFormat(string command, string details){
    cout<<command+"      "+details<<'\n';
}

void helpinfo(){

    cout<<"Usage:"<<'\n';
    cout<<'\n'<<"proj [command]"<<'\n';
    cout<<"proj"<<'\n';
    cout<<'\n';
    cout<<"Available Commands:"<<'\n';
    helpInfoFormat("view", "views the file");
    helpInfoFormat("add", "writes to the file. Start the lines with flags. (.to do, /complete, *idea, #heading)");
    cout<<'\n';
    cout<<"Flags:"<<'\n';
    cout<<"  --help, -h	    help for projgo"<<'\n';
}

void runMode(){
    int i = 0;
    while(i < 1){
        string command;
        cout<<"Enter Command: ";
        cin >> command;

        if(command == help){
            helpinfo();
        }else if(command == view){
            viewFile("proj.txt");
        }else if(command == add){
            string message;
            cout<<"What would you like to write?";
            getline(cin, message);
            write("test.txt", message);
        }
    }
}

int main(int argc, char* argv[]){
    int i = 0;
    if(argc == 2 and argv[1] == help){
        helpinfo();
    }else if(argc == 2 and argv[1] == view){
        viewFile("test.txt");
    }else if(argc == 3 and argv[1] == add){
        string message = argv[2];
        write("test.txt", message);
    }else if(argc == 1){
        runMode();
    }
}
