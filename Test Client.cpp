#include "socketstream/socketstream.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace swoope;

int main() {
	socketstream server;
	server.open("127.0.0.1", "10984");
	
	string str;
	server >> str;
	cout << str;
}	