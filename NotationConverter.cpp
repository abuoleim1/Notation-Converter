/* 
Layalie AbuOleim
U60659634
Notation converter 
*/

#include "NotationConverter.hpp"

// Deque functions ///

Deque::Deque(){ 
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
    n = 0;
}

Deque::~Deque(){ 
    while (!empty()) {
        removeBack();
    }
    delete header;
    delete trailer;
}

int Deque::size() { return n; }
bool Deque::empty() { return header->next == trailer; }
std::string Deque::front() { return header->next->elem; }
std::string Deque::back() { return trailer->prev->elem; }

void Deque::insertFront(std::string e){
    Node* u = new Node;
    u->elem = e;
    u->next = header->next;
    u->prev = header;
    header->next->prev = u;
    header->next = u;
    n++;
}

void Deque::insertBack(std::string e){
    Node* u = new Node;
    u->elem = e;
    u->prev = trailer->prev;
    u->next = trailer;
    trailer->prev->next = u;
    trailer->prev = u;
    n++;
}

std::string Deque::removeFront(){ 
    std::string str_out = "";
    if (!empty()) {
        Node* u = header->next;
        str_out = u->elem;
        header->next = u->next;
        u->next->prev = header;
        delete u;
        n--;
    }
    return str_out;
}

std::string Deque::removeBack(){ 
    std::string str_out = "";
    if (!empty()) {
        Node* u = trailer->prev;
        str_out = u->elem;
        trailer->prev = u->prev;
        u->prev->next = trailer;
        delete u;
        n--;
    }
    return str_out;
}

// Notation Converter functions ///

// checks if a char is an operator
bool NotationConverter::isOperator(char a) { 
    return (a == '+' || a == '-' || a == '*' || a == '/'); 
}

// Refined validation function to throw exceptions for invalid characters
bool NotationConverter::requireThrow(std::string str) {
    for (char c : str) {
        if (!isalpha(c) && !isOperator(c) && !isspace(c) && c != '(' && c != ')') {
            return true;
        }
    }
    return false;
}

// Convert prefix to infix with handling for nested expressions
std::string NotationConverter::prefixToInfix(std::string str) { 
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");

    Deque holder; 
    reverse(str.begin(), str.end());

    for (char ch : str) {
        if (isalpha(ch)) { 
            holder.insertBack(std::string(1, ch));
        } else if (isOperator(ch)) { 
            std::string left = holder.removeBack();
            std::string right = holder.removeBack();
            holder.insertBack("(" + left + " " + ch + " " + right + ")");
        }
    }
    return holder.removeBack();
}

// Convert postfix to infix with better handling for nested expressions
std::string NotationConverter::postfixToInfix(std::string str) {
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");

    Deque holder;

    for (char ch : str) {
        if (isalpha(ch)) {
            holder.insertFront(std::string(1, ch));
        } else if (isOperator(ch)) {
            std::string right = holder.removeFront();
            std::string left = holder.removeFront();
            holder.insertFront("(" + left + " " + ch + " " + right + ")");
        }
    }
    return holder.removeFront();
}

// Convert infix to prefix with improved operator and parentheses handling
std::string NotationConverter::infixToPrefix(std::string str) { 
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");

    Deque holder;
    std::string result = "";
    reverse(str.begin(), str.end());

    for (char ch : str) {
        if (isalpha(ch)) {
            result += ch;
            result += " ";
        } else if (isOperator(ch) || ch == ')') {
            holder.insertFront(std::string(1, ch));
        } else if (ch == '(') {
            while (holder.front() != ")") {
                result += holder.removeFront();
                result += " ";
            }
            holder.removeFront(); // pops the ')'
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

// Convert infix to postfix with better ordering
std::string NotationConverter::infixToPostfix(std::string str) {
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");

    std::string result = "";
    Deque holder;

    for (char ch : str) {
        if (isalpha(ch)) {
            result += ch;
            result += " ";
        } else if (isOperator(ch)) {
            holder.insertFront(std::string(1, ch));
        } else if (ch == ')') {
            result += holder.removeFront();
            result += " ";
        }
    }

    result += holder.removeBack(); // final element
    return result;
}

// Convert prefix to postfix by going through infix
std::string NotationConverter::prefixToPostfix(std::string str) {
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");
    return infixToPostfix(prefixToInfix(str));
}

// Convert postfix to prefix by going through infix
std::string NotationConverter::postfixToPrefix(std::string str) {
    if (requireThrow(str)) throw std::invalid_argument("Invalid characters");
    return infixToPrefix(postfixToInfix(str));
}
