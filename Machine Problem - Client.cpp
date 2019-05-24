#include "socketstream/socketstream.hh"

#include <iostream>
#include <vector>
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

bool is_number(string &str) {
    if(str.empty()) return false;
    for(unsigned int i = 0; i < str.size(); i++) {
        if(!isdigit(str[i])) return false;
    }

    return true;
}


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
        getline(server, str);
        return str;
    }

    int get_server_int() {
        int data;
        server >> data;
        server.ignore(1024, '\n');
        return data;
    }

    bool get_server_bool() {
        bool data;
        server >> data;
        server.ignore(1024, '\n');
        return data;
    }

    vector<string> get_server_vector_string() {
        int vec_size = get_server_int();
        vector<string> vec(vec_size);

        for(int i = 0; i < vec_size; i++) {
            vec[i] = get_server_string();
        }

        return vec;
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

    int number_of_players, number_of_teams, conn_id, team_number;
    string player_class;
public:
    GameClient(Client *client) {
        this->client = client;
    }

    void run() {
        initialize_connection();
        initialize_game();

        bool is_game_over = client->get_server_bool();
        while(!is_game_over) {
            print_game_status();
            input();
            print_skipped();

            is_game_over = client->get_server_bool();
        }

        print_game_status();
        print_game_winner();
    }

    void print_game_winner() {
        string msg = client->get_server_string();

        cout << msg << '\n';
    }

    void print_skipped() {
        vector<string> skipped_teams = client->get_server_vector_string();
        vector<string> skipped_players = client->get_server_vector_string();

        for(unsigned int i = 0; i < skipped_teams.size(); i++) {
            cout << skipped_teams[i] << '\n';
        }

        for(unsigned int i = 0; i < skipped_players.size(); i++) {
            cout << skipped_players[i] << '\n';
        }
    }

    void input() {
        bool is_turn = client->get_server_bool();
        int actions = client->get_server_int();
        
        if(!is_turn) {
            string wait_msg = client->get_server_string();
            cout << wait_msg << '\n';
        } else {
            for(int i = 0; i < actions; i++) {
                bool is_valid = client->get_server_bool();
                string command;

                while(!is_valid) {
                    getline(cin, command);
                    client->send_server_string(command);

                    if(command == "help") {
                        vector<string> help_msg = client->get_server_vector_string();
                        for(unsigned int i = 0; i < help_msg.size(); i++) {
                            cout << help_msg[i] << '\n';
                        }
                        i--;
                    }

                    is_valid = client->get_server_bool();

                    if(!is_valid) {
                        string error_msg = client->get_server_string();
                    }
                }
            }
        }
    }

    void print_game_status() {
        vector<string> game_status = client->get_server_vector_string();

        for(unsigned int i = 0; i < game_status.size(); i++) {
            cout << game_status[i] << '\n';
        }

        cout << '\n';
    }

    void initialize_connection() {
        string welcome_msg;
        int connections_left;

        client->open();
        
        welcome_msg = client->get_server_string();
        cout << welcome_msg << '\n';
        connections_left = client->get_server_int();
        conn_id = client->get_server_int();

        for(int i = 0; i < connections_left; i++) {
            string wait_msg = client->get_server_string();
            cout << wait_msg << '\n';
        }

        string all_connected_msg = client->get_server_string();
        cout << all_connected_msg << '\n';

        number_of_players = client->get_server_int();
        number_of_teams = client->get_server_int();
    }

    void initialize_game() {
        ask_players_player_class();
        ask_players_team_number();
        string start_game_msg = client->get_server_string();
        cout << start_game_msg << '\n';
    }

    void ask_players_player_class() {
        string wait_msg;
        wait_msg = client->get_server_string();
        cout << wait_msg << '\n';

        for(int i = 0; i < number_of_players - 1; i++) {
            if(i == conn_id) {
                player_class = ask_player_class();
            } else {
                wait_msg = client->get_server_string();
                cout << wait_msg << '\n';
            }
        }
    }

    void ask_players_team_number() {
        bool is_valid_grouping = client->get_server_bool();
        while(!is_valid_grouping) {
            string wait_msg = client->get_server_string();
            int team_number;
            cout << wait_msg << '\n';

            for(int i = 0; i < number_of_players - 1; i++) {
                if(i == conn_id) {
                    team_number = ask_player_team_number();
                } else {
                    wait_msg = client->get_server_string();
                    cout << wait_msg;
                }
            }

            is_valid_grouping = client->get_server_bool();
            if(!is_valid_grouping) {
                string invalid_team_grouping_msg = client->get_server_string();
                cout << invalid_team_grouping_msg << '\n';
            }
        }
    }

    int ask_player_team_number() {
        bool is_valid = client->get_server_bool();
        string msg = client->get_server_string();
        cout << msg;
        string team_number;

        while(!is_valid) {
            getline(cin, team_number);
            client->send_server_string(team_number);
            is_valid = client->get_server_bool();
            if(!is_valid) {
                string invalid_team_number_msg = client->get_server_string();
                cout << invalid_team_number_msg << '\n';
            }
        }

        return atoi(team_number.c_str());
    }

    string ask_player_class() {
        bool is_valid = client->get_server_bool();
        string msg = client->get_server_string();
        cout << msg;
        string player_class;

        while(!is_valid) {
            getline(cin, player_class);
            client->send_server_string(player_class);

            is_valid = client->get_server_bool();
            if(!is_valid) {
                string error_msg = client->get_server_string();
                cout << error_msg << '\n';
            }
        }

        return player_class;
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
    gameclient->run();
}

int main(int argc, char *argv[]) {
    execute_client(argv[1], argv[2]);
}