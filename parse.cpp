#include <iostream>
#include <string>
#include <regex>

using namespace std;

void help() {
	cout << endl;
	cout << "This will be enough today" << endl;
	cout << endl;
}

void list() {
	cout << endl;
	cout << " 1. 127.0.0.1 - Windows 64" << endl;
	cout << " 2. 132.32.78.154 - Linux x32_64" << endl;
	cout << " 3. all" << endl;
}

void payload() {
	cout << endl;
	cout << "This load pay" << endl;
}

void error() {
	cout << "Command not found" << endl;
	cout << endl;
}

int main() {
	cout << "Welcome to Payload System" << endl;
	string command;

	while(true) {
		cout << ">";
		getline(cin, command);
		if (command == "help")
			help();
		else if (command == "list")
			list();
		else if ((int) command.find("payload") > -1)
			if (regex_match(command, regex("^payload\\s\\d+$")))
				payload();
			else {
				cout << "Required parameter lost" << endl;
				cout << endl;
			}
		else
			error();
	}
	return EXIT_SUCCESS;
}