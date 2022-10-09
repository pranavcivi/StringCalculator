#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;


//convert a character to an integer
unsigned int digit_to_decimal(char digit) {
    if(digit < 48 || digit > 57){
        cout << "error occurred because of " << digit << endl;
        throw std::invalid_argument("invalid argument number 1");
    }
    return digit - '0';
}

//convert an integer to a character
char decimal_to_digit(unsigned int decimal) {
    if(decimal > 9)
        throw std::invalid_argument("invalid argument 2");
    return '0' + decimal;
}

//remove leading zeroes of a string
string trim_leading_zeros(string num) {
    long unsigned int i;
    for(i = 0; i < num.length(); i++){
        if(num[i] != '0' && num[i] != '-'){
            if(num[0] == '-')
                return "-" + num.substr(i);
            else
                return num.substr(i);
        }
    }
    return "0";
}

//add two strings together as though they were integers. 
string add(string lhs, string rhs) {
    //checking if the sum should be positive or negative
    bool negative = false;
    if(lhs[0] == '-' || rhs[0] == '-'){
        negative = true;
        lhs = lhs.substr(1);
        rhs = rhs.substr(1);
    }

    //removing leading zeroes from user input
    string left = trim_leading_zeros(lhs);
    string right = trim_leading_zeros(rhs);
    string out = "";

    //make both strings have the same length by adding leading 0s to the smaller length string
    if (left.length() < right.length()){
        int diff = right.length() - left.length();
        for(int i = 0; i < diff; i++){
            left.insert(0, 1, '0');
        }
    }
    if(left.length() > right.length()){
        int diff = left.length() - right.length();
        for(int i = 0; i < diff; i++){
            right.insert(0, 1, '0');
        }
    }
    
    // start at the end of the string. Add the two numbers together and add it to the ouput string.
    int carry = 0;
    for(int i = left.length()-1; i >= 0; i--){
        int up = digit_to_decimal(left[i]);
        int down = digit_to_decimal(right[i]);
        int sum = up + down + carry;
        carry = 0;

        // if the sum of the digits is > 9, add the second digit of the sum to the total sum and carry over the first digit of the sum. 
        if(sum > 9 && i != 0){
            carry = sum / 10;
            sum = sum % 10;
            out.insert(0, 1, decimal_to_digit(sum));
        }
        // if the sum of the digits is > 9, and the program is at the first digit of the two numbers, 
        // then add both digits of the sum to the final sum string
        else if(i == 0 && sum > 9){
            out.insert(0, 1, decimal_to_digit(sum % 10));
            sum /= 10;
            out.insert(0,1,decimal_to_digit(sum));
        }
        // if the sum of the digits is <= 9, just add that digit to the final sum string
        else{
            out.insert(0, 1, decimal_to_digit(sum));
        }
    }
    // add a negative sign if the sum should be negative
    if(negative){
        out.insert(0, 1, '-');
    }
    return out;
}

// multiply two integers as though they were integers. 
string multiply(string lhs, string rhs) {
    bool negative = false;
    string left, right;
    string out = "0";
    // checking if the product should be positive or negative
    if(lhs[0] == '-'){
        negative = !negative;
        lhs = lhs.substr(1);
    }
    if(rhs[0] == '-'){
        negative = !negative;
        rhs = rhs.substr(1);
    }
    
    // start by removing leading zeroes
    left = trim_leading_zeros(lhs);
    right = trim_leading_zeros(rhs);

    // add leading zeroes so both arguments are the same length
    if (left.length() < right.length()){
        int diff = right.length() - left.length();
        for(int i = 0; i < diff; i++){
            left.insert(0, 1, '0');
        }
    }
    if(left.length() > right.length()){
        int diff = left.length() - right.length();
        for(int i = 0; i < diff; i++){
            right.insert(0, 1, '0');
        }
    }

    //loop through the second number's digits
    int place = 0;
    for(int i = right.length()-1; i >= 0; i--){
        string temp = "";
        int carry = 0;
        //loop through the first number's digits
        for(int k = left.length()-1; k >= 0; k--){
            int up = digit_to_decimal(left[k]);
            int down = digit_to_decimal(right[i]);
            int prod = (up * down) + carry;
            carry = 0;
            // if there needs to be carry over 
            if(prod > 9 && k != 0){
                carry = prod / 10;
                prod = prod % 10;
                temp.insert(0, 1, decimal_to_digit(prod));
            }
            // if the sum is > 9 and the program is on the first digits
            else if(k == 0 && prod > 9){
                temp.insert(0, 1, decimal_to_digit(prod % 10));
                prod /= 10;
                temp.insert(0,1,decimal_to_digit(prod));
            }
            // if the sum is <= 9, then just add the product to the output string
            else{
                temp.insert(0, 1, decimal_to_digit(prod));
            }
        }
        // add a 0 to the temp product for multiple digit multiplication
        for(int i = 0; i < place; i++){
            temp.push_back('0');
        }
        place++;
        
        out = add(out, temp);
        temp = "";
    }
    if(negative)
        out.insert(0, 1, '-');
    return out;
}
