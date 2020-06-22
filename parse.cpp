#include <iostream>
#include <string>

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

	}
	return EXIT_SUCCESS;
}