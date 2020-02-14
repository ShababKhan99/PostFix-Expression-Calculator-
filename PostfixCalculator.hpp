//
//  PostfixCalculator.hpp
//  Project7
//
//  Created by Shabab Khan on 11/13/19.
//  Copyright © 2019 Shabab Khan. All rights reserved.
//

#ifndef PostfixCalculator_hpp
#define PostfixCalculator_hpp

#include <stdio.h>
#include <stack>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include "PrecondViolatedExcep.hpp"

using namespace std;

class PostfixCalculator{
  
public:
    
    PostfixCalculator(); //default constructor
    
    bool checkoperand(char piece);
    
    bool checkoperator(char piece);
    
    //checks precedence
    int precedence(char piece);
    
    //takes in a algebraic equation, and returns a postfix function that can then be calculated by the calcualte function in this class.
    string convertToPostfix(string infix_expression);
    
    
    //takes in a postfix function, and calculates the function, and returns a numerical value.
    double calculatePostfix(string postfix_expression);
    
    //takes in an input file name, and outputs onto two different files, postfix results onto postfix.txt and true algebraic results onto results.txt.
    void testCalculator(string input_file_name);
    
};

#endif /* PostFixCalculator_hpp */
