#include <iostream>
#include <string>
#include <regex>
#include <thread>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

void command_help() {
	cout << endl;
	cout << "This will be enough today" << endl;
	cout << endl;
}

void command_list() {
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

void dialog() {

	cout << "Welcome to Payload System" << endl;
	string command;

	while(true) {
		cout << ">";
		getline(cin, command);
		if (command == "help")
			command_help();
		else if (command == "list")
			command_list();
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
}

int main() {

	thread dialog(dialog);
	dialog.join();

	return EXIT_SUCCESS;
}