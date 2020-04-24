// Jameson O'Malley
// CIS2542-002 Lab #10
// File: expressionTree.h
// Desc: header file expressionTree class

#include <iostream>
#include <stack>
#include <string>
#include <cassert>

// necessary struct per instructions
struct expTreeNode {
	double number;
	char op;
	expTreeNode* left_field;
	expTreeNode* right_field;
};

class expressionTree
{
public:
	// default constructor
	expressionTree() {
		root_ptr = new expTreeNode;
		root_ptr->number = 0;
		root_ptr->op = ' ';
		root_ptr->left_field = nullptr;
		root_ptr->right_field = nullptr;
	}

	// parameterized constructor
	expressionTree(std::string& input) {
		root_ptr = new expTreeNode;
		root_ptr->number = 0;
		root_ptr->op = ' ';
		root_ptr->left_field = nullptr;
		root_ptr->right_field = nullptr;
		createStack(input);
	}

	// destructor
	~expressionTree() {
		tree_clear(root_ptr);
	}

	// accessor method
	expTreeNode* get_root() {
		return root_ptr;
	}

	// clear method for destructor
	void tree_clear(expTreeNode*& root_ptr) {
		expTreeNode* temp = new expTreeNode;
		if (root_ptr != nullptr) {
			// clear left
			temp = root_ptr->left_field;
			tree_clear(temp);
			// clear right
			temp = root_ptr->right_field;
			tree_clear(temp);
			// clear root
			delete root_ptr;
			root_ptr = nullptr;
		}
	}

	void generate(expTreeNode* root_ptr, std::stack<std::string>& treestack) {
		std::string plus = "+";
		std::string minus = "-";
		std::string multiply = "*";
		std::string divide = "/";
		std::string value;

		if (root_ptr->op != '+' && root_ptr->op != '-' && root_ptr->op != '*' && root_ptr->op != '/') {
			value = treestack.top();
			treestack.pop();
			if (value == plus || value == minus || value == multiply || value == divide) {
				if (value == plus) {
					root_ptr->op = '+';
				}
				else if (value == minus) {
					root_ptr->op = '-';
				}
				else if (value == multiply) {
					root_ptr->op = '*';
				}
				else if (value == divide) {
					root_ptr->op = '/';
				}
			}

			else {
				// this will then be a number and make the string into a double. 
				// sets root_ptr as this double value
				root_ptr->number = stod(value);
			}
		}

		// right side
		value = treestack.top();
		treestack.pop();
		if (value == plus || value == minus || value == multiply || value == divide) {
			root_ptr->right_field = new expTreeNode();
			if (value == plus) root_ptr->right_field->op = '+';
			else if (value == minus) root_ptr->right_field->op = '-';
			else if (value == multiply) root_ptr->right_field->op = '*';
			else if (value == divide) root_ptr->right_field->op = '/';
			if (treestack.size() != 0) {
				generate(root_ptr->right_field, treestack);
			}
		}

		else {
			root_ptr->right_field = new expTreeNode();
			root_ptr->right_field->number = stod(value);
		}

		// left side
		value = treestack.top();
		treestack.pop();
		if (value == plus || value == minus || value == multiply || value == divide) {
			root_ptr->left_field = new expTreeNode();
			if (value == plus) root_ptr->left_field->op = '+';
			else if (value == minus) root_ptr->left_field->op = '-';
			else if (value == multiply) root_ptr->left_field->op = '*';
			else if (value == divide) root_ptr->left_field->op = '/';
			if (treestack.size() != 0) {
				generate(root_ptr->left_field, treestack);
			}
		}

		else {
			root_ptr->left_field = new expTreeNode();
			root_ptr->left_field->number = stod(value);
		}
	}

	void createStack(std::string input) {
		std::string fullNum;
		std::string num;
		std::stack<std::string> expression;
		int i = 0;
		do
		{
			if (isdigit(input[i]) || input[i] == '.' || input[i] == ' ')
			{
				// add the digit into a string and then another final string
				// in case a decimal is coming
				if (input[i] != ' ') {
					num = input[i];
					fullNum += num;
				}
				// put together decimal numbers, but just goes through if a normal digit without decimals
				if (!fullNum.empty() && input[i] == ' ') {
					expression.push(fullNum);
					fullNum.clear();
				}
			}

			// checks for operand and also if the next input is not NULL
			else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' && input[i] != NULL)
			{
				std::string s(1, input[i]);
				expression.push(s);
			}

			else {
			}

			i++;
		} while (i <= input.length());
		generate(root_ptr, expression);
	}

private:
	expTreeNode* root_ptr;
};

// evaluation method for getting the correct answers
double evaluate(expTreeNode* root_ptr) {
	if (root_ptr->number == 0) {
		expTreeNode* cursor = root_ptr;
		double op1, op2;

		if (root_ptr->left_field->op == '+' || root_ptr->left_field->op == '-' || root_ptr->left_field->op == '*' || root_ptr->left_field->op == '/') {
			evaluate(root_ptr->left_field);
		}

		else if (root_ptr->right_field->op == '+' || root_ptr->right_field->op == '-' || root_ptr->right_field->op == '*' || root_ptr->right_field->op == '/') {
			evaluate(root_ptr->right_field);
		}

		else {
		}

		op1 = root_ptr->left_field->number;
		op2 = root_ptr->right_field->number;
		// check which operator root_ptr contains
		switch (root_ptr->op)
		{
		case '+': root_ptr->number = (op1 + op2);
			break;
		case '-': root_ptr->number = (op1 - op2);
			break;
		case '*': root_ptr->number = (op1 * op2);
			break;
		case '/':
			assert(op2 != 0);
			root_ptr->number = (op1 / op2);
			break;
		}
	}
	return root_ptr->number;
}

/*
					/
						0.25 [leaf]
						0.5 [leaf]
Postfix expression: .5 .25 /

		==> evaluates to 2
		==> correct answer is 2
					*
						8.5 [leaf]
						+
							3.7 [leaf]
							2.5 [leaf]
Postfix expression: 2.5 3.7 + 8.5 *

		==> evaluates to 52.7
		==> correct answer is 52.7
					+
						5 [leaf]
						-
							4 [leaf]
							+
								*
									2 [leaf]
									3.1 [leaf]
								5 [leaf]
Postfix expression: 5 3.1 2 * + 4 - 5 +

		==> evaluates to 12.2
		==> correct answer is 12.2
					/
						5 [leaf]
						+
							*
								5 [leaf]
								347.8 [leaf]
							25 [leaf]
Postfix expression: 25 347.8 5 * + 5 /

		==> evaluates to 352.8
		==> correct answer is 352.8
					/
						3 [leaf]
						2 [leaf]
Postfix expression: 2 3 /

		==> evaluates to 0.666667
		==> correct answer is 0.666667

C:\Users\paren\Desktop\Project1\Debug\Project1.exe (process 4884) exited with code 0.
Press any key to close this window . . .
*/