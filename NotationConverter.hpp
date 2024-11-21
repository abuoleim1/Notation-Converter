/* 
Layalie AbuOleim
U60659634
header files
*/

#ifndef __NotationConverter_H_
#define __NotationConverter_H_

//includes 
#include<iostream>
#include<string>
#include<algorithm>
#include "NotationConverterInterface.hpp"

//create node class
class Node {

    public:
        Node* prev;
        Node* next;
        std::string elem;

    friend class Deque;
};

//deque class and attributes
class Deque {
    public:
        Deque();
        ~Deque();

        int size();
        bool empty();

        std::string front(); //
        std::string back();

        void insertFront(std::string e);
        void insertBack(std::string e);

        std::string removeFront();
        std::string removeBack();
        
    private:
        Node* header;
        Node* trailer;
        int n; //size of deque
};

//converter class
class NotationConverter: public NotationConverterInterface{
    public:
        std::string postfixToInfix(std::string inStr);
        std::string postfixToPrefix(std::string inStr);
        std::string infixToPostfix(std::string inStr);
        std::string infixToPrefix(std::string inStr);
        std::string prefixToInfix(std::string inStr);
        std::string prefixToPostfix(std::string inStr);

        // two helper functions in order to make the code easier
        bool isOperator(char a);
        bool requireThrow(std::string inStr);
};

#endif
