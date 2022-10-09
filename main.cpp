#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    string input;

    while(true){
        cout << ">> ";
        getline(cin, input);
        if(input == "q" || input == "quit")
            break;

        string num1, num2;
        if(input.find('+') != string::npos){
            num1 = input.substr(0,input.find('+') - 1);
            num2 = input.substr(input.find('+') + 2);

            cout << endl << "ans =" << endl << endl << "    ";
            cout << add(num1, num2) << endl << endl;
        }
        else if(input.find('*') != string::npos){
            num1 = input.substr(0,input.find('*') - 1);
            num2 = input.substr(input.find('*') + 2);

            cout << endl << "ans =" << endl << endl << "    ";
            cout << multiply(num1, num2) << endl << endl;
        }        
    }
    cout << endl << "farvel!" << endl << endl;
}

