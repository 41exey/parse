#include <iostream>
#include <string>
#include <regex>
#include <thread>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class session {
public:
	session(tcp::socket socket)
		: socket_(move(socket)) {
	}

	void start() {
		do_read_header();
	}
	~session() {
		cout << "Destructor session" << endl;
	}
private:
	void do_read_header() {
		cout << "read header" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		do_read_body();
	}

	void do_read_body() {
		cout << "read body" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		socket_.close();
//		do_read_header();
	}

	tcp::socket socket_;
};

class server {
public:
	server(boost::asio::io_context& io_context,
		const tcp::endpoint& endpoint)
		: acceptor_(io_context, endpoint), count_participiant(3) {

		do_accept();
	}
	~server() {
		cout << "Destructor server" << endl;
	}
	unsigned int get_count_participiant() {
		return count_participiant;
	}
private:
	void do_accept() {
		acceptor_.async_accept(
			[this](boost::system::error_code ec, tcp::socket socket) {
				if (!ec) {
					make_shared<session>(move(socket))->start();
				}
				do_accept();
			});
	}
	unsigned int count_participiant;
	tcp::acceptor acceptor_;
};


class dialog {
public:
	dialog() {

//		cout << server_.get_count_participiant() << endl;
	}
	void detach(server *server_) {
		thread t(dialog::menu, server_);
		t.detach();
	}

private:
	static void command_help(server *server_) {
		cout << endl;
		cout << "This will be enough today" << endl;
		cout << endl;
	}

	static void command_list(server *server_) {
		auto num = server_->get_count_participiant();
		cout << " 1. 127.0.0.1 - Windows 64" << endl;
		cout << " 2. 132.32.78.154 - Linux x32_64" << endl;
		cout << " 3. all" << endl;
//		cout << num << endl;
		cout << endl;
	}

	static void command_payload(server *server_, unsigned int num) {
		cout << "For target " << num << " will be try load pay" << endl;
		cout << endl;
	}

	static void error() {
		cout << "Command not found" << endl;
		cout << endl;
	}

	static void menu(server *server_) {

		cout << "Welcome to Payload System" << endl;
		string command;

		while (true) {
			cout << ">";
			getline(cin, command);
			if (command == "help")
				dialog::command_help(server_);
			else if (command == "list")
				dialog::command_list(server_);
			else if (static_cast<int>(command.find("payload")) > -1)
				if (regex_match(command, regex("^payload\\s\\d+$"))) {
					static std::regex e("\\d+");
					std::sregex_token_iterator i(command.begin(), command.end(), e);
					std::sregex_token_iterator end;

					std::string result;
					while (i != end)
						result += i->str() + " ",
						++i;

//					cout << result << endl;
					dialog::command_payload(server_, stoi(result));
				}
				else {
					cout << "Required parameter lost" << endl;
					cout << endl;
				}
			else
				dialog::error();
		}

	}

};

int main(int argc, char *argv[]) {

	try {
		if (argc < 2) {
			cerr << "Usage: server <port>\n";
			return -1;
		}
		
		boost::asio::io_context io_context;
		tcp::endpoint endpoint(tcp::v4(), atoi(argv[1]));
		server server_(io_context, endpoint);

		dialog dialog_;
		dialog_.detach(&server_);

		io_context.run();

	} catch(exception & e) {
		cerr << "Exception: " << e.what() << endl;
	}

	return EXIT_SUCCESS;
}
