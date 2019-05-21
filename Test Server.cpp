#include "socketstream/socketstream.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace swoope;

int main() {
	socketstream server, client;
	server.open("10984", 1);
	server.accept(client);
	
	string str = "DASJIDDSAIDAD\n\n\naOJSDIANDLSIDA";
	
	client << str << endl;
}