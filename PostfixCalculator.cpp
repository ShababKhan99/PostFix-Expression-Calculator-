//
//  PostFixCalculator.cpp
//  Project7
//
//  Created by Shabab Khan on 11/13/19.
//  Copyright © 2019 Shabab Khan. All rights reserved.
//

#include "PostfixCalculator.hpp"

using namespace std;

//Default constructor
PostfixCalculator::PostfixCalculator(){}

bool PostfixCalculator::checkoperand(char piece){
    if(isdigit(piece))
        return 1;
    else
        return 0;
        
}

bool PostfixCalculator::checkoperator(char piece){
    if(piece == '*')
        return 1;
    if(piece == '+')
        return 1;
    if(piece == '-')
        return 1;
    if(piece == '/')
        return 1;
    else
        return 0;
}

int PostfixCalculator::precedence(char piece){
    if(piece == '*')
        return 2;
    if(piece == '/')
        return 2;
    else
        return 1;
}

string PostfixCalculator::convertToPostfix(string infix_expression){
    stack<char> operators;
    string postfixExp, piece;
    stringstream s(infix_expression);
    while(getline(s, piece, ' ')){
        //cout << piece << endl;
        if(checkoperand(piece[0])){
                postfixExp += piece;
                postfixExp += ' ';
        }
        else if(piece[0] == '('){
                operators.push(piece[0]);
        }
        else if(checkoperator(piece[0])){
            while(!operators.empty() && operators.top() != '(' && precedence(piece[0]) <= precedence(operators.top()))
            {
                postfixExp += operators.top();
                postfixExp += ' ';
                operators.pop();
            }
            operators.push(piece[0]);
        }
        else if(piece[0] == ')'){
            while(!operators.empty() && operators.top() != '(')
            {
                postfixExp += operators.top();
                postfixExp += ' ';
                operators.pop();
            }
            if(operators.empty()){
                throw(PrecondViolatedExcep("Unbalanced parenthesis"));
            }
            
            else{
                operators.pop();
            }
        }
        else{
            throw(PrecondViolatedExcep("Unknown operator"));
        }
    }
    
    while(!operators.empty())
    {
        if(operators.top() == '('){
            throw(PrecondViolatedExcep("Unbalanced parenthesis"));
        }
        else{
            postfixExp += operators.top();
            postfixExp += ' ';
            operators.pop();
        }
    }
    
    return postfixExp;
}

double PostfixCalculator::calculatePostfix(string postfix_expression){
    stack<double> numbers;
    string piece;
    double first, second;
    double answer = 0;
    stringstream s(postfix_expression);
    while(getline(s,piece,' ')){
        if(checkoperand(piece[0]))
            //cout << piece << endl;
            numbers.push(atof(piece.c_str()));
        if(piece[0] == '*'){
            if(!numbers.empty()){
                first = numbers.top();
                numbers.pop();
                second = numbers.top();
                numbers.pop();
                answer = first*second;
                //cout << answer << endl;
                numbers.push(answer);
            }
        }
        if(piece[0] == '-'){
            if(!numbers.empty()){
                first = numbers.top();
                numbers.pop();
                second = numbers.top();
                numbers.pop();
                answer = second-first;
                //cout << answer << endl;
                numbers.push(answer);
            }
        }
        if(piece[0] == '/'){
            if(!numbers.empty()){
                first = numbers.top();
                numbers.pop();
                second = numbers.top();
                numbers.pop();
                answer = second/first;
                //cout << answer << endl;
                numbers.push(answer);
            }
        }
        if(piece[0] == '+'){
            if(!numbers.empty()){
                first = numbers.top();
                numbers.pop();
                second = numbers.top();
                numbers.pop();
                answer = first+second;
                //cout << answer << endl;
                numbers.push(answer);
            }
        }
        
    }
    return answer;
}

void PostfixCalculator::testCalculator(string input_file_name){
    ifstream input(input_file_name);
    ofstream output;
    ofstream resultsfile;
    string infix,postfix,results;
    output.open("postfix.txt");
    resultsfile.open("results.txt");
    while(getline(input,infix)){
        try
        {
            postfix = convertToPostfix(infix);
            output << postfix;
            output << endl;
            auto result = calculatePostfix(postfix);
            resultsfile << result;
            resultsfile << endl;
        }
        catch(PrecondViolatedExcep problem)
        {
            output << problem.what();
            output << endl;
            resultsfile << problem.what();
            resultsfile << endl;
        }
    }
    output.close();
    resultsfile.close();
}
