#include<iostream>
#include <cstdlib>
#include<vector>
#include<string>
#include <utility>

#define ERROR std::cout << "ERROR" << std::endl

std::vector<std::pair<std::string, int> > variables;
std::string Var;
bool hasVar;

bool isVariable(std::string x)
{
	if (( (x[0] >= 'A') and (x[0] <= 'Z')) or
		( (x[0] >= 'a') and (x[0] <= 'z')))
		return true;

	return false;
}

int Value(std::string x)
{
	for (int i = 0; i < variables.size(); ++i)
		if (variables[i].first == x)
			return variables[i].second;
	ERROR;
}

void Save(std::string x, int y)
{
	for (int i = 0; i < variables.size(); ++i)
		if (variables[i].first == x)
		{
			variables[i].second = y;
			return;
		}
	variables.push_back(make_pair(x, y));
}

int main(){



while (true)
{
	Var = '~';
	hasVar = false;


	std::string input;
	std::getline(std::cin, input);
	input.push_back(' ');

	std::vector<std::string> elements;
	std::string temp;
	for(std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (not isspace(*it)) {
			temp.push_back(*it);
		} else {
			if (temp != "")
				elements.push_back(temp);
			temp = "";
		}
	}

	if (elements.size() == 1)
	{
		if (isVariable(elements[0]))
			std::cout << Value(elements[0]) << std:: endl;
		else
			std::cout << elements[0] << std::endl;
		continue;
	}

	if (elements[1] == "=")
	{
		Var = elements[0];
		hasVar = true;
		if (not isVariable(Var)) {ERROR; continue;}
	}

	char operation = '~'; //No operation
	char tmpOperation = '~';
	int num;
	int result = 0;
	bool wait_for_number = true, error = false;
	for ( std::vector<std::string>::iterator it = elements.begin() + ((int)hasVar)*2 ; it != elements.end(); ++it ) {
		bool is_number = true;
		tmpOperation = '~';
		num = 0;

		if (isVariable(*it))
		{
			num = Value(*it);
			goto hell;
			is_number = true;
		}

		for ( std::string::iterator cit = it->begin(); cit != it->end(); ++cit)
		{
		//	std::cout << " here cit: " << *cit << ' ';
			if (not isdigit(*cit))
			{
				if (cit == it->begin() and (it->size() > 1))  //First character could be + or -
				{
					tmpOperation = *cit;
					if (tmpOperation != '-' and tmpOperation != '+')
						return ERROR, 0;
					continue;
				}
				is_number = false;
			}
		//	std::cout << " num : " << num << ' ';
			num*=10;
			num+= std::atoi(it->c_str());
		}

		hell:
		if (is_number) {
			if (wait_for_number) {
				if (operation == '+' or operation == '~')
					result += num;
				if (operation == '-')
					result -= num;
				operation = '~';


				wait_for_number = false;
			} else {
				ERROR;
				return -1;
			}
		} else {
			if (wait_for_number) {
				ERROR;
				return -1;
			} else {
				operation = (*it)[0];
				if ((*it) == "+")
					wait_for_number = true;
				else if ((*it) == "-")
					wait_for_number = true;
				else {
					ERROR;
					return -1;
				}
			}
		}
	}
	if (!hasVar)
		std::cout << result << std::endl;
	if (hasVar)
		Save(Var, result);

}

}
