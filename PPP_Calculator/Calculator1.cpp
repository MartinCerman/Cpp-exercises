﻿// Program: Simple Calculator
//
// Purpose:	Simple Calculator can calculate a single expression of varying lenght.
//			First version will let user to enter and expression consisting of numbers
//			and operators '+', '-', '/', '*'.
//			User will end the expression with '=' and receives a result after enter.
//
// Method:	1. Convert input stream into tokens consisting of a symbol ( '+', '-', '/',
//			'*', '(', ')' or 'd' for doubles) and a value, only 'd' uses the value.
//			2. Token stream class will handle reading input and has putback() function for
//				storing tokens  
//			3. Read tokens 1 by 1 by functions, if the function can't handle it, it returns
//				read Token to the Token stream and calls a function that can. There is one
// 				function for each rule from the grammar below.
//
// Grammar: Expression	: term
//						| term + term | term - term
//			Term		: number
//						| number * number | number / number
//			Number		: double
//						| ( expression )
//						| { expression }
//
// Classes:	Token;
//			Token_stream;
//  
// Functions:	double number(); // Reads a token and returs its value, if it finds
//									parentheses, calculate the expression inside and
//									 return it's value.
//				double term(); // Handles multiplication and returns result, if there
//								is no need for multiplication, returns a single number.
//				double expression(); // First and final step, calls term() and adds up
//										results from term(), returns if it finds an
//										ending character '=' or closed parentheses.
//				Token Token_stream::get(); // Returns a token created from cin or returns
//											an already stored Token.
//				void Token_stream::putback(Token) // Stores an unused Token for future reading.
// 
// Changes: Version01:	Support for parentheses and braces.
//						Modulo % operator added.
//						User can now enter expressions repeatedly.
//						

#include "../std_lib_facilities.h"

double expression();

class Token
{
public:
	char symbol;
	double value;
};

class Token_stream
{
	Token token{};
	bool full{ false };

public:
	Token get_token();
	void putback(Token);
};

#pragma warning(suppress:4715)
Token Token_stream::get_token()
{
	if (full) {
		full = false;
		return token;
	}
	else {
		Token t{};
		char temp{};
		cin >> temp;
		switch (temp) {
		case '*':case '/':case '+':case '-':case '=':
		case '(':case ')':case '{':case '}':case '%':
			t.symbol = temp; return t;
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':{
			t.symbol = 'd';
			cin.putback(temp);
			cin >> t.value; return t;
		}
		default: error("unknown symbol ", string(1,temp));
		}
	}
}

void Token_stream::putback(Token t)
//pre-condition: full must be false (class cannot hold more than 1 Token)
{
	if (full)
		error("Token_stream already full");
	token.symbol = t.symbol;
	token.value = t.value;
	full = true;
}

Token_stream ts{};

#pragma warning(suppress:4715)
double number()
//pre-condition: Token must either be 'd' symbol or '-'. In case of '-'
//				get next number and return negative value.
{
	Token temp = ts.get_token();
	switch (temp.symbol) 
	{
	case '(': case '{':
		return expression();
	case 'd': return temp.value;
	case '-': return -number();
	case '+': return number();
	default:
		error("expected a number but received ", string(1, temp.symbol));
	}
}

//Reads a number, uses it as left side, if next token is * or /, reads another number
//for right side of the term and returns the result, otherwise put Token back and
//return left side.
double term()
{
	double left_side{ number() };
	Token t{ ts.get_token() };
	while (t.symbol == '*' || t.symbol == '/' || t.symbol == '%')
	{
		switch (t.symbol)
		{
		case '*': left_side *= number(); break;
		case '/': left_side /= number(); break;
		case '%': left_side = fmod(left_side, number());
		}
		t = ts.get_token();
	}
	ts.putback(t);
	return left_side;
}

//Left side number is a term, then read a Token and do an operation with the next
//term. Repeats until it finds '=' symbol.
double expression()
{
	double left_side{ term() };
	Token t{};
	while (t.symbol != '=' && t.symbol != ')' && t.symbol != '}')
	{
		t = ts.get_token();
		switch (t.symbol) {
		case '+': left_side += term(); break;
		case '-': left_side -= term(); break;
		case '=': case ')': case '}':
			break;
		default:
			error("expected '+', '-' or '=' but received ", string(1,t.symbol));
		}
	}
	return left_side;
}

int main()
{
	cout << "Simple calculator.\n";
	cout << "Please enter an expression using doubles and operators '+', '-', '/', '*' or '%' followed by '='.\n"
		<< "You can also use parentheses and braces('q' for quit):\n";
	while (true)
	{

		try
		{
			char ch{};
			cin >> ch;
			if (ch == 'q') break;
			cin.putback(ch);
			cout << expression() << '\n';
		}
		catch (exception e)
		{
			cerr << "Error: " << e.what() << '\n';
		}
	}
}