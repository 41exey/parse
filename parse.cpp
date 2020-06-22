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
	cout << " 1. 127.0.0.1 - Windows 64" << endl;
	cout << " 2. 132.32.78.154 - Linux x32_64" << endl;
	cout << " 3. all" << endl;
	cout << endl;
}

void payload(unsigned int num) {
	cout << "For target " << num << " will be try load pay" << endl;
	cout << endl;
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
			if (regex_match(command, regex("^payload\\s\\d+$"))) {
				static std::regex e("\\d+");
				std::sregex_token_iterator i(command.begin(), command.end(), e);
				std::sregex_token_iterator end;

				std::string result;
				while (i != end)
					result += i->str() + " ",
					++i;

				cout << result << endl;
				payload(stoi(result));
			} else {
				cout << "Required parameter lost" << endl;
				cout << endl;
			}
		else
			error();
	}
	return EXIT_SUCCESS;
}