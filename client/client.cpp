#include <iostream>
#include <boost/asio.hpp>
#include "../common/message.hpp"

using boost::asio::ip::tcp;

using namespace std;

class client {
public:
	client(boost::asio::io_context& io_context,
		const tcp::resolver::results_type& endpoints)
		: io_context_(io_context),
		socket_(io_context) {
	}
	void write(const message& msg) {
	}

	void close() {
		boost::asio::post(io_context_, [this]() { socket_.close(); });
	}

private:
	boost::asio::io_context& io_context_;
	tcp::socket socket_;
};

int main(int argc, char* argv[]) {

	try {
		if (argc != 3) {
			cerr << "Usage: client <host> <port>\n";
			return -1;
		}

		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(argv[1], argv[2]);
		client c(io_context, endpoints);

		thread t([&io_context]() { io_context.run(); });

		char line[message::max_body_length + 1];
		unsigned int type;
		message msg;
		while (true) {
			cout << "Enter type message: ";
			cin >> type;
			if (cin.fail() || !msg.set_type(static_cast<unsigned char>(type))) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Type is from 0 to 9" << endl;
				continue;
			} else
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Enter body message: ";
			cin.getline(line, message::max_body_length + 1);
			if (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Message was truncated" << endl;
			}
			msg.copy(line, strlen(line));
			cout << msg.data() << endl;
			c.write(msg);
		}

		c.close();
		t.join();
	}
	catch (exception& e) {

		cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
