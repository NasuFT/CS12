#include "socketstream/socketstream.hh"

#include <iostream>
#include <string>

using namespace std;
using namespace swoope;

class Client;
class GameClient;

class Constants {
public:
    static const int min_teams;

    static const int min_port;
    static const int max_port;

    static const string port_out_of_range_msg;
};

const int Constants::min_teams = 2;

const int Constants::min_port = 1024;
const int Constants::max_port = 65535;

const string Constants::port_out_of_range_msg = "Invalid Port! Valid Ports Range: (" + to_string(Constants::min_port) + "-" + to_string(Constants::max_port) + ")";

class Client {
    string server_ip_address;
    int server_port;
    socketstream server;
public:
    Client(string &server_ip_address, string &server_port) {
        this->server_ip_address = server_ip_address;
        this->server_port = atoi(server_port.c_str());

        if(!check_port_validity(this->server_port)) {
            cout << Constants::port_out_of_range_msg << endl;
            throw out_of_range(Constants::port_out_of_range_msg + " - Port Received: " + server_port);
        }
    }

    void open() {
        server.open(server_ip_address, to_string(server_port));
    }

    string get_server_string() {
        string str;
        server.ignore(1024, '\n');
        getline(server, str);
        return str;
    }

    int get_server_int() {
        int data;
        server >> data;
        return data;
    }

    bool get_server_bool() {
        bool data;
        server >> data;
        return data;
    }

    void send_server_string(string &str) {
        server << str << endl;
    }

    void send_server_int(int data) {
        server << data << endl;
    }

    void send_server_bool(bool data) {
        server << data << endl;
    }

    bool check_port_validity(int port) {
        return (Constants::min_port <= port && port <= Constants::max_port);
    }
};

class GameClient {
    Client *client;

    int number_of_players, number_of_teams, conn_id;
public:
    GameClient(Client *client) {
        this->client = client;
    }

    void run() {
        initialize_connection();
        initialize_game();
    }

    void initialize_connection() {
        string welcome_msg;
        int connections_left;

        client->open();
        
        welcome_msg = client->get_server_string();
        cout << welcome_msg << '\n';
        connections_left = client->get_server_int();
        conn_id = client->get_server_int();

        for(int i = connections_left; i > 0; i--) {
            string wait_msg = client->get_server_string();
            cout << wait_msg << '\n';
        }

        string all_connected_msg = client->get_server_string();
        cout << all_connected_msg << '\n';

        number_of_players = client->get_server_int();
        number_of_teams = client->get_server_int();
    }

    void initialize_game() {
        
    }

    bool is_valid_player_class(string str) {
        if(str == "doggo" || str == "human" || str == "alien" || str == "zombie") return true;
        return false;
    }

    bool is_valid_team_number(int team_number) {
        return (Constants::min_teams <= team_number && team_number <= number_of_teams);
    }
};

void execute_client(string server_ip_address, string server_port) {
    Client *client = new Client(server_ip_address, server_port);
    GameClient *gameclient = new GameClient(client);
}

int main(int argc, char *argv[]) {
    execute_client(argv[1], argv[2]);
}