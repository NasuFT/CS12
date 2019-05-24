//Merlin, Santiago

#include "socketstream/socketstream.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#ifdef enable_debug
#define DEBUG(x) x
#else
#define DEBUG(x) 
#endif

using namespace std;
using namespace swoope;

class BodyPart;
class Player;
class Team;
class Game;
class Server;
class GameHandler;

// TO DO:

/// ----- PROGRAM CONSTANTS ----- ///

class Constants {
public:
    static const bool hand_rollover;
    static const bool foot_rollover;
    static const int initial_fingers;
    static const int initial_toes;

    static const string human_class;
    static const int human_hands;
    static const int human_feet;
    static const int human_fingers;
    static const int human_toes;
    static const int human_actions;
    
    static const string alien_class;
    static const int alien_hands;
    static const int alien_feet;
    static const int alien_fingers;
    static const int alien_toes;
    static const int alien_actions;

    static const string zombie_class;
    static const int zombie_hands;
    static const int zombie_feet;
    static const int zombie_fingers;
    static const int zombie_toes;
    static const int zombie_actions;

    static const string doggo_class;
    static const int doggo_hands;
    static const int doggo_feet;
    static const int doggo_fingers;
    static const int doggo_toes;
    static const int doggo_actions;

    static const int min_teams;
    static const int max_teams;

    static const int min_players;
    static const int max_players;

    static const int min_port;
    static const int max_port;

    static const string port_out_of_range_msg;
    static const string players_out_of_range_msg;
    static const string teams_out_of_range_msg;
    static const string start_game_msg;
};

/// BODY PART CONSTANTS

const bool Constants::hand_rollover = true;
const bool Constants::foot_rollover = false;
const int Constants::initial_fingers = 1;
const int Constants::initial_toes = 1;

/// PLAYER & PLAYER CLASS CONSTANTS

const string Constants::human_class = "human";
const int Constants::human_hands = 2;
const int Constants::human_feet = 2;
const int Constants::human_fingers = 5;
const int Constants::human_toes = 5;
const int Constants::human_actions = 1;

const string Constants::alien_class = "alien";
const int Constants::alien_hands = 4;
const int Constants::alien_feet = 2;
const int Constants::alien_fingers = 3;
const int Constants::alien_toes = 2;
const int Constants::alien_actions = 1;

const string Constants::zombie_class = "zombie";
const int Constants::zombie_hands = 1;
const int Constants::zombie_feet = 0;
const int Constants::zombie_fingers = 4;
const int Constants::zombie_toes = 0;
const int Constants::zombie_actions = 2;

const string Constants::doggo_class = "doggo";
const int Constants::doggo_hands = 0;
const int Constants::doggo_feet = 4;
const int Constants::doggo_fingers = 0;
const int Constants::doggo_toes = 4;
const int Constants::doggo_actions = 1;

/// GAME CONSTANTS

const int Constants::min_players = 2;
const int Constants::max_players = 6;

/// TEAM CONSTANTS

const int Constants::min_teams = 2;
const int Constants::max_teams = Constants::max_players;

/// SERVER CONSTANTS

const int Constants::min_port = 1024;
const int Constants::max_port = 65535;

/// MESSAGES
const string Constants::port_out_of_range_msg = "Invalid Port! Valid Ports Range: (" + to_string(Constants::min_port) + "-" + to_string(Constants::max_port) + ")";
const string Constants::players_out_of_range_msg = "Invalid Number of Players! Valid Number of Players Range: (" + to_string(Constants::min_players) + "-" + to_string(Constants::max_players) + ")";
const string Constants::teams_out_of_range_msg = "Invalid Number of Teams! Valid Number of Teams Range: (" + to_string(Constants::min_teams) + "-" + to_string(Constants::max_teams) + ")";
const string Constants::start_game_msg = "Ready. Let the game start!!!";

/// HELPER FUNCTIONS
bool is_number(string &str) {
    if(str.empty()) return false;
    for(unsigned int i = 0; i < str.size(); i++) {
        if(!isdigit(str[i])) return false;
    }

    return true;
}

int get_sum(vector<int> &vec) {
    int sum = 0;

    for(unsigned int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }

    return sum;
}



/// ----- BODY PARTS ----- ///

class BodyPart {
protected:
    int value;
    int rollover_value;
    bool rollover_enabled;
    bool dead;

    Player *owner;
public:
    BodyPart(int value, bool rollover_enabled, int rollover_value) {
        this->value = value;
        this->rollover_enabled = rollover_enabled;
        this->rollover_value = rollover_value;
        this->dead = false;
    }

    virtual bool can_rollover() {
        return rollover_enabled;
    }

    virtual int get_value() {
        return value;
    }

    virtual void set_value(int x) {
        value = x;
        if(can_rollover()) roll_over();
    }

    virtual void roll_over() {
        while(value > rollover_value) {
            value -= rollover_value;
        }
    }

    virtual void set_owner(Player *player) {
        owner = player;
    }

    virtual bool is_dead() {
        return false;
    }

    virtual bool trigger_death_flag() {
        if(is_dead() && !dead) {
            dead = true;
            return true;
        }

        return false;
    }
};

class Hand: public BodyPart {
private:
public:
    Hand(int value, int rollover_value)
        : BodyPart(value, Constants::hand_rollover, rollover_value) {
    }

    bool is_dead() {
        return value == rollover_value;
    }
};

class Foot: public BodyPart {
private:
public:
    Foot(int value, int rollover_value)
        : BodyPart(value, Constants::foot_rollover, rollover_value) {
    }

    bool is_dead() {
        return value >= rollover_value;
    }
};



/// ----- PLAYER CLASSES ----- ///

class Player {
protected:
    vector<Hand> hands;
    vector<Foot> feet;

    int actions_per_turn;
    int player_id;
    int team_number;
    string player_class;
    string player_name;
    bool is_skipped;
    int max_fingers, max_toes;
public:
    Player(int _hands, int _feet, int _fingers, int _toes, const string &_player_class, int _actions_per_turn, const string &_player_name, int _player_id) {
        for(int i = 0; i < _hands; i++) {
            Hand hand(Constants::initial_fingers, _fingers);
            hands.push_back(hand);
            hands[i].set_owner(this);
        }

        for(int i = 0; i < _feet; i++) {
            Foot foot(Constants::initial_toes, _toes);
            feet.push_back(foot);
            feet[i].set_owner(this);
        }

        max_fingers = _fingers;
        max_toes = _toes;
        actions_per_turn = _actions_per_turn;
        player_class = _player_class;
        player_name = _player_name;
        player_id = _player_id;
        is_skipped = false;
    }

    virtual bool is_dead() {
        for(unsigned int i = 0; i < hands.size(); i++) {
            if(!hands[i].is_dead()) return false;
        }

        for(unsigned int i = 0; i< feet.size(); i++) {
            if(!feet[i].is_dead()) return false;
        }

        return true;
    }

    virtual bool is_hand_dead(int i) {
        return hands[i].is_dead();
    }

    virtual bool is_foot_dead(int i) {
        return feet[i].is_dead();
    }

    virtual bool can_act() {
        return !is_skipped;
    }

    virtual void skip() {
        is_skipped = false;
    }

    virtual void skip_next_turn() {
        is_skipped = true;
    }

    virtual void add_hand(int hand_number, int value) {
        hands[hand_number].set_value(hands[hand_number].get_value() + value);
        if(hands[hand_number].trigger_death_flag()) on_hand_death();
    }

    virtual void add_toe(int toe_number, int value) {
        feet[toe_number].set_value(feet[toe_number].get_value() + value);
        if(feet[toe_number].trigger_death_flag()) on_foot_death();
    }

    virtual int get_hand_fingers(int hand_number) {
        return hands[hand_number].get_value();
    }

    virtual int get_foot_toes(int foot_number) {
        return feet[foot_number].get_value();
    }

    virtual int get_number_of_hands() {
        return hands.size();
    }

    virtual int get_number_of_feet() {
        return feet.size();
    }

    virtual int get_alive_hands() {
        int alive = 0;

        for(unsigned int i = 0; i < hands.size(); i++) {
            if(!hands[i].is_dead()) alive++;
        }

        return alive;
    }

    virtual int get_alive_feet() {
        int alive = 0;

        for(unsigned int i = 0; i < feet.size(); i++) {
            if(!feet[i].is_dead()) alive++;
        }

        return alive;
    }

    virtual void set_hand_fingers(int hand_number, int value) {
        hands[hand_number].set_value(value);
        if(hands[hand_number].trigger_death_flag()) on_hand_death();
    }

    virtual void set_foot_toes(int toe_number, int value) {
        feet[toe_number].set_value(value);
        if(feet[toe_number].trigger_death_flag()) on_foot_death();
    }

    virtual int get_actions_per_turn() {
        return actions_per_turn;
    }

    virtual string get_player_class() {
        return player_class;
    }

    virtual string get_player_name() {
        return player_name;
    }

    virtual int get_player_id() {
        return player_id;
    }

    virtual void set_team_number(int team_number) {
        this->team_number = team_number;
    }

    virtual int get_team_number() {
        return team_number;
    }

    virtual int get_max_fingers() {
        return max_fingers;
    }

    virtual int get_max_toes() {
        return max_toes;
    }

    virtual void on_hand_death() {
        
    }

    virtual void on_foot_death() {
        skip_next_turn();
    }

    virtual void on_target(Player *target) {

    }

    virtual void on_player_attack(Player *attacker) {

    }

    virtual string get_player_status() {
        string str;

        str += "(";

        for(unsigned int i = 0; i < hands.size(); i++) {
            if(hands[i].is_dead()) str += "X";
            else str += to_string(hands[i].get_value());
        }

        str += ":";

        for(unsigned int i = 0; i < feet.size(); i++) {
            if(feet[i].is_dead()) str += "X";
            else str += to_string(feet[i].get_value());
        }

        str += ":";

        if(is_dead()) str += "dead";
        else if(!can_act()) str += "skip";

        str += ")";

        return str;
    }
};

class Human: public Player {
private:
public:
    Human(string player_name, int player_id)
        : Player(Constants::human_hands, Constants::human_feet, Constants::human_fingers, Constants::human_toes, Constants::human_class, Constants::human_actions, player_name, player_id) {

    }
};

class Alien: public Player {
private:
public:
    Alien(string player_name, int player_id)
        : Player(Constants::alien_hands, Constants::alien_feet, Constants::alien_fingers, Constants::alien_toes, Constants::alien_class, Constants::alien_actions, player_name, player_id) {

    }

    void on_foot_death() {
        
    }
};

class Zombie: public Player {
private:
    bool can_revive;
public:
    Zombie(string player_name, int player_id)
        : Player(Constants::zombie_hands, Constants::zombie_feet, Constants::zombie_fingers, Constants::zombie_toes, Constants::zombie_class, Constants::zombie_actions, player_name, player_id) {
        can_revive = true;
    }

    void on_hand_death() {
        if(can_revive) {
            Hand hand_new(Constants::initial_fingers, Constants::zombie_fingers);
            hand_new.set_owner(this);
            hands.push_back(hand_new);
            can_revive = false;
        }
    }
};

class Doggo: public Player {
private:
public:
    Doggo(string player_name, int player_id)
        : Player(Constants::doggo_hands, Constants::doggo_feet, Constants::doggo_fingers, Constants::doggo_toes, Constants::doggo_class, Constants::doggo_actions, player_name, player_id) {

    }

    void on_target(Player *target) {
        if(target->get_player_class() != Constants::doggo_class) {
            target->skip_next_turn();
        }
    }
};



/// ----- TEAM CLASS ----- ///

class Team {
private:
    vector<Player*> players;
    int current_player;
    int next_player_number;
public:
    Team(): current_player(0), next_player_number(0) {

    }

    void add_player(Player *player) {
        players.push_back(player);
    }

    Player* get_current_player() {
        return players[current_player];
    }

    Player* get_player(int i) {
        return players[i];
    }

    int get_number_of_players() {
        return players.size();
    }

    bool is_dead() {
        for(unsigned int i = 0; i < players.size(); i++) {
            if(!players[i]->is_dead()) return false;
        }

        return true;
    }

    bool can_act() {
        for(unsigned int i = 0; i < players.size(); i++) {
            if(players[i]->can_act() && !players[i]->is_dead()) return true;
        }

        return false;
    }

    void skip() {
        for(unsigned int i = 0; i < players.size(); i++) {
            players[i]->skip();
        }
    }

    void next_player() {
        current_player = (current_player + 1) % players.size();
    }

    string telegraph_next_player() {
        if(!can_act()) return get_current_player()->get_player_name();

        int next_player = current_player;

        while(get_player(next_player)->is_dead() || !get_player(next_player)->can_act()) {
            next_player = (next_player + 1) % players.size();
        }

        return get_player(next_player)->get_player_name();
    }

    string get_team_status() {
        string str;

        for(unsigned int i = 0; i < players.size(); i++) {
            str += "P" + to_string(players[i]->get_player_id() + 1) + players[i]->get_player_class()[0] + " ";
            str += players[i]->get_player_status();

            if(i != players.size() - 1) str += " | ";
        }

        str += " | Next Player: " + telegraph_next_player();

        return str;
    }
};



/// --- GAME CLASS --- ///

class Game {
private:
    vector<Player*> players;
    vector<Team> teams;

    vector<string> skipped_players;
    vector<string> skipped_teams;

    int current_team;
    int winner;
public:
    Game(int max_players, int max_teams)
        : teams(max_teams), current_team(0) {
        
    }

    ~Game() {
        for(unsigned int i = 0; i < players.size(); i++) {
            delete players[i];
        }
    }

    void add_player(Player* player, int team_number) {
        players.push_back(player);
        teams[team_number].add_player(player);
        player->set_team_number(team_number);
    }

    Player* get_current_player() {
        return teams[current_team].get_current_player();
    }

    Player* get_player(int player_id) {
        return players[player_id];
    }

    int get_dead_teams() {
        int dead_teams = 0;

        for(unsigned int i = 0; i < teams.size(); i++) {
            if(teams[i].is_dead()) dead_teams++;
        }

        return dead_teams;
    }

    bool is_game_over() {
        if(teams.size() - get_dead_teams() <= 1) return true;
        return false;
    }

    int get_winning_team() {
        if(!is_game_over()) return -1;

        for(unsigned int i = 0; i < teams.size(); i++) {
            if(!teams[i].is_dead()) return i;
        }

        return -1;
    }

    void next_team() {
        current_team = (current_team + 1) % teams.size();
    }

    void end_turn() {
        teams[current_team].next_player();
        next_team();

        skipped_teams.clear();
        skipped_players.clear();

        while(teams[current_team].is_dead() || !teams[current_team].can_act()) {
            if(!teams[current_team].can_act() && !teams[current_team].is_dead()) {
                teams[current_team].skip();
                string str = "Team " + to_string(current_team + 1) + " has been skipped.";
                skipped_teams.push_back(str);
            }

            next_team();
        }

        while(get_current_player()->is_dead() || !get_current_player()->can_act()) {
            if(!get_current_player()->can_act() && !get_current_player()->is_dead()) {
                get_current_player()->skip();
                string str = "Player " + to_string(get_current_player()->get_player_id() + 1) + " has been skipped.";
                skipped_players.push_back(str);
            }

            teams[current_team].next_player();
        }
    }

    int get_active_teams() {
        int active_teams;

        for(unsigned int i = 0; i < teams.size(); i++) {
            if(teams[i].get_number_of_players() > 0) active_teams++;
        }
    }

    vector<string> &get_skipped_players_msg() {
        return skipped_players;
    }

    vector<string> &get_skipped_teams_msg() {
        return skipped_teams;
    }

    void tap(string &player_body_part, int player_body_number, int target_id, string &target_body_part, int target_body_number) {
        int player_value, target_value;

        if(player_body_part == "hand") player_value = get_current_player()->get_hand_fingers(player_body_number);
        else if(player_body_part == "foot") player_value = get_current_player()->get_foot_toes(player_body_number);

        if(target_body_part == "hand") {
            target_value = players[target_id]->get_hand_fingers(target_body_number);
            players[target_id]->set_hand_fingers(target_body_number, player_value + target_value);
        }
        else if(target_body_part == "foot") {
            target_value = players[target_id]->get_foot_toes(target_body_number);
            players[target_id]->set_foot_toes(target_body_number, player_value + target_value);
        }

        get_current_player()->on_player_attack(players[target_id]);
        players[target_id]->on_target(get_current_player());
    }

    void disthands(vector<int> &hands) {
        for(unsigned int i = 0; i < get_current_player()->get_number_of_hands(); i++) {
            get_current_player()->set_hand_fingers(i, hands[i]);
        }
    }

    void distfeet(vector<int> &feet) {
        for(unsigned int i = 0; i < get_current_player()->get_number_of_feet(); i++) {
            get_current_player()->set_foot_toes(i, feet[i]);
        }
    }

    vector<string> get_game_status() {
        vector<string> game_status;

        for(unsigned int i = 0; i < teams.size(); i++) {
            if(teams[i].get_number_of_players() > 0) {
                string str;
                str += "Team " + to_string(i + 1) + ": ";
                str += teams[i].get_team_status();
                game_status.push_back(str);
            }
        }

        string team_str = "Current Team: " + to_string(current_team + 1);
        game_status.push_back(team_str);
        string str = "Current Player: " + get_current_player()->get_player_name();
        game_status.push_back(str);

        return game_status;
    }
};



/// ----- SERVER CLASS ----- ///

class Server {
    socketstream server;
    vector<socketstream> *clients;
    int current_clients;
    vector<int> client_ids;
    int port;
public:
    Server(string port) {
        if(!check_port_validity(port)) {
            cout << Constants::port_out_of_range_msg << endl;
            throw out_of_range(Constants::port_out_of_range_msg + " - Port Received: " + port);
        }

        this->port = atoi(port.c_str());
        current_clients = 0;
    }

    ~Server() {
        for(unsigned int i = 0; i < clients->size(); i++) {
            clients->at(i).close();
        }

        delete clients;
    }

    void open(int connections) {
        server.open(to_string(port), connections);
    }

    void wait_connections(int connections) {
        clients = new vector<socketstream>(connections);
        for(int i = 0; i < connections; i++) {
            string waiting_msg = "Waiting for " + to_string(connections - i) + " more player" + (connections - i == 1 ? "" : "s") + " to connect...";
            cout << waiting_msg << endl;
            send_all_clients(waiting_msg);

            server.accept(clients->at(i));
            client_ids.push_back(client_ids.size());
            current_clients++;

            string join_msg = "You have joined the game as: Player " + to_string(i + 2);
            send_client(i, join_msg);
            send_client(i, connections - i - 1);
            send_client(i, i);
        }

        string all_connected = "All players connected!";
        cout << all_connected << '\n';
        send_all_clients(all_connected);
    }

    void send_client(int i, string str) {
        clients->at(i) << str << endl;
    }

    void send_all_clients(string str) {
        for(unsigned int i = 0; i < current_clients; i++) {
            send_client(i, str);
        }
    }

    void send_client(int i, int data) {
        clients->at(i) << data << endl;
    }

    void send_all_clients(int data) {
        for(unsigned int i = 0; i < current_clients; i++) {
            send_client(i, data);
        }
    }

    void send_client(int i, bool data) {
        clients->at(i) << data << endl;
    }

    void send_all_clients(bool data) {
        for(unsigned int i = 0; i < current_clients; i++) {
            send_client(i, data);
        }
    }

    void send_client(int i, vector<string> &vec) {
        int vec_size = vec.size();
        send_client(i, vec_size);

        for(int j = 0; j < vec_size; j++) {
            send_client(i, vec[j]);
        }
    }

    void send_all_clients(vector<string> &vec) {
        for(unsigned int i = 0; i < current_clients; i++) {
            send_client(i, vec);
        }
    }

    string get_client_string(int i) {
        string str;
        getline(clients->at(i), str);
        return str;
    }

    int get_client_int(int i) {
        int data;
        clients->at(i) >> data;
        clients->at(i).ignore(1024, '\n');
        return data;
    }

    bool get_client_bool(int i) {
        bool data;
        clients->at(i) >> data;
        clients->at(i).ignore(1024, '\n');
        return data;
    }

    int get_number_of_clients() {
        return clients->size();
    }

    bool check_port_validity(string &port) {
        return (is_number(port) && Constants::min_port <= atoi(port.c_str()) && atoi(port.c_str()) <= Constants::max_port);
    }

    socketstream* get_socket() {
        return &server;
    }
};

/// ----- GAME HANDLER CLASS ----- ///

class GameHandler {
private:
    Game *game;
    Server *server;
    int number_of_players;
    int number_of_teams;
public:
    GameHandler(Game* game, Server *server) {
        this->game = game;
        this->server = server;
    }

    void send_game_status_all() {
        vector<string> status = game->get_game_status();
        server->send_all_clients(status);
        
        for(unsigned int i = 0; i < status.size(); i++) {
            cout << status[i] << '\n';
        }
    }

    void print_game_status() {
        send_game_status_all();
        cout << '\n';
    }

    void print_game_winner() {
        int winning_team = game->get_winning_team();

        string win_msg = "Congratulations! Team " + to_string(winning_team + 1) + " wins!";
        string lose_msg = "You lose! Team " + to_string(winning_team + 1) + " wins!";

        for(int i = 0; i < number_of_players; i++) {
            if(i == 0) {
                if(game->get_player(0)->get_team_number() == winning_team) {
                    cout << win_msg << '\n';
                } else {
                    cout << lose_msg << '\n';
                }
            } else {
                if(game->get_player(i)->get_team_number() == winning_team) {
                    server->send_client(i - 1, win_msg);
                } else {
                    server->send_client(i - 1, lose_msg);
                }
            }
        }
    }

    void run() {
        initialize_server();
        initialize_game();

        server->send_all_clients(game->is_game_over());
        while(!game->is_game_over()) {
            print_game_status();
            input();
            game->end_turn();
            print_skipped();
            server->send_all_clients(game->is_game_over());
        }

        print_game_status();
        print_game_winner();
    }

    void print_skipped() {
        vector<string> skipped_teams = game->get_skipped_teams_msg();
        vector<string> skipped_players = game->get_skipped_players_msg();

        server->send_all_clients(skipped_teams);
        server->send_all_clients(skipped_players);

        for(unsigned int i = 0; i < skipped_teams.size(); i++) {
            cout << skipped_teams[i] << '\n';
        }

        for(unsigned int i = 0; i < skipped_players.size(); i++) {
            cout << skipped_players[i] << '\n';
        }
    }

    void initialize_server() {
        string str;
        cout << "How many players will play? (" << Constants::min_players << "-" << Constants::max_players << " players): ";

        while(!is_number(str) || atoi(str.c_str()) < Constants::min_players || atoi(str.c_str()) > Constants::max_players) {
            getline(cin, str);

            if(!is_number(str) || atoi(str.c_str()) < Constants::min_players || atoi(str.c_str()) > Constants::max_players) {
                cout << "Invalid input! Try again (" << Constants::min_players << "-" << Constants::max_players << " players): ";
            }
        }

        number_of_players = atoi(str.c_str());
        str.clear();

        cout << "How many teams will play? (" << Constants::min_teams << "-" << number_of_players << " teams): ";
        while(!is_number(str) || atoi(str.c_str()) < Constants::min_teams || atoi(str.c_str()) > number_of_players) {
            getline(cin, str);

            if(!is_number(str) || atoi(str.c_str()) < Constants::min_teams || atoi(str.c_str()) > number_of_players) {
                cout << "Invalid input! Try again (" << Constants::min_teams << "-" << number_of_players << " teams): ";
            }
        }

        number_of_teams = atoi(str.c_str());

        server->open(number_of_players - 1);
        server->wait_connections(number_of_players - 1);
        server->send_all_clients(number_of_players);
        server->send_all_clients(number_of_teams);
        str = "";
        server->send_all_clients(str);
        cout << str << '\n';
    }

    void initialize_game() {
        vector<string> player_classes = ask_players_player_class();
        vector<int> team_numbers = ask_players_team_numbers();

        process_data(player_classes, team_numbers);

        string start_game_msg = Constants::start_game_msg;
        cout << start_game_msg << '\n';
        server->send_all_clients(start_game_msg);
    }

    vector<string> ask_players_player_class() {
        vector<string> player_classes(number_of_players);

        string wait_msg = "Waiting for Player 1 to pick Player Type...";
        server->send_all_clients(wait_msg);

        string player_class;

        cout << "Choose[type] your class: \"human\", \"alien\", \"zombie\", \"doggo\": ";
        while(!is_valid_player_class(player_class)) {
            getline(cin, player_class);

            if(!is_valid_player_class(player_class)) {
                cout << "Invalid player class!\n";
                cout << "Choose[type] your class: \"human\", \"alien\", \"zombie\", \"doggo\": ";
            }
        }

        player_classes[0] = player_class;

        for(int i = 0; i < server->get_number_of_clients(); i++) {
            string player_class;
            wait_msg = "Waiting for Player " + to_string(i + 2) + " to pick Player Type...";
            cout << wait_msg << '\n';
            for(int j = 0; j < server->get_number_of_clients(); j++) {
                if(i != j) {
                    server->send_client(j, wait_msg);
                }
            }

            string msg = "Choose[type] your class: \"human\", \"alien\", \"zombie\", \"doggo\": ";

            server->send_client(i, is_valid_player_class(player_class));
            server->send_client(i, msg);

            while(!is_valid_player_class(player_class)) {
                player_class = server->get_client_string(i);

                server->send_client(i, is_valid_player_class(player_class));
                if(!is_valid_player_class(player_class)) {
                    vector<string> invalid_player_class_msg(2);
                    invalid_player_class_msg[0] = "Invalid player class!";
                    invalid_player_class_msg[1] = "Choose[type] your class: \"human\", \"alien\", \"zombie\", \"doggo\": ";
                    server->send_client(i, invalid_player_class_msg);
                }
            }

            player_classes[i + 1] = player_class;
        }

        return player_classes;
    }

    vector<int> ask_players_team_numbers() {
        vector<int> team_numbers(number_of_players);
        fill(team_numbers.begin(), team_numbers.end(), 0);

        server->send_all_clients(is_valid_team_grouping(team_numbers));
        while(!is_valid_team_grouping(team_numbers)) {
            string wait_msg = "Waiting for Player 1 to pick Team Number...";
            server->send_all_clients(wait_msg);

            string team_number;

            cout << "Choose[type] your team number: (1-" << to_string(number_of_teams) << "): ";
            while(!is_valid_team_number(team_number)) {
                getline(cin, team_number);

                if(!is_valid_team_number(team_number)) {
                    cout << "Invalid team number!\n";
                    cout << "Choose[type] your team number: (1-" << to_string(number_of_teams) << "): ";
                }
            }

            team_numbers[0] = atoi(team_number.c_str());

            for(int i = 0; i < server->get_number_of_clients(); i++) {
                string team_number;
                wait_msg = "Waiting for Player " + to_string(i + 2) + " to pick Team Number...";
                cout << wait_msg << '\n';
                for(int j = 0; j < server->get_number_of_clients(); j++) {
                    if(i != j) {
                        server->send_client(j, wait_msg);
                    }
                }

                string msg = "Choose[type] your team number: (1-" + to_string(number_of_teams) +"): ";

                server->send_client(i, is_valid_team_number(team_number));
                server->send_client(i, msg);

                while(!is_valid_team_number(team_number)) {
                    team_number = server->get_client_string(i);

                    server->send_client(i, is_valid_team_number(team_number));
                    if(!is_valid_team_number(team_number)) {
                        vector<string> invalid_team_number_msg(2);
                        invalid_team_number_msg[0] = "Invalid team number";
                        invalid_team_number_msg[1] = "Choose[type] your team number: (1-" + to_string(number_of_teams) +"): ";
                        server->send_client(i, invalid_team_number_msg);
                    }
                }

                team_numbers[i + 1] = atoi(team_number.c_str());
            }

            server->send_all_clients(is_valid_team_grouping(team_numbers));
            if(!is_valid_team_grouping(team_numbers)) {
                string invalid_team_grouping_msg = "Invalid team grouping detected! Team " + to_string(get_no_player_team(team_numbers)) + " has no members! Team numbers will be asked again from all players.";
                cout << invalid_team_grouping_msg << '\n';
                server->send_all_clients(invalid_team_grouping_msg);
            }
        }

        return team_numbers;
    }

    bool is_valid_player_class(string str) {
        if(str == "doggo" || str == "human" || str == "alien" || str == "zombie") return true;
        return false;
    }

    bool is_valid_team_grouping(vector<int> &team_numbers) {
        int max_team_number = *max_element(team_numbers.begin(), team_numbers.end());
        if(max_team_number < Constants::min_teams) return false;

        for(int i = max_team_number; i > 1; i--) {
            if(find(team_numbers.begin(), team_numbers.end(), i - 1) == team_numbers.end()) {
                return false;
            } 
        }

        return true;
    }

    bool is_valid_team_number(string &team_number) {
        return (is_number(team_number) && 0 < atoi(team_number.c_str()) && atoi(team_number.c_str()) <= number_of_teams);
    }

    int get_no_player_team(vector<int> &team_numbers) {
        int max_team_number = *max_element(team_numbers.begin(), team_numbers.end());
        for(int team_number = max_team_number; team_number > 1; team_number--) {
            if(find(team_numbers.begin(), team_numbers.end(), team_number - 1) == team_numbers.end()) {
                return team_number - 1;
            }
        }

        int active_teams = 0;

        for(int team_number = max_team_number; team_number > 1; team_number--) {
            if(find(team_numbers.begin(), team_numbers.end(), team_number) != team_numbers.end()) {
                active_teams++;
            }
        }

        if(active_teams < 2) return 2;

        return -1;
    }

    void process_data(vector<string> &player_classes, vector<int> &team_numbers) {
        for(unsigned int i = 0; i < player_classes.size(); i++) {
            Player *player;
            string player_name = "Player " + to_string(i + 1);

            if(player_classes[i] == "human") player = new Human(player_name, i);
            if(player_classes[i] == "alien") player = new Alien(player_name, i);
            if(player_classes[i] == "zombie") player = new Zombie(player_name, i);
            if(player_classes[i] == "doggo") player = new Doggo(player_name, i);

            game->add_player(player, team_numbers[i] - 1);
        }
    }

    void input() {
        for(int i = 0; i < server->get_number_of_clients(); i++) {
            bool is_player_i_turn;
            is_player_i_turn = (game->get_current_player()->get_player_id() == i + 1);

            server->send_client(i, is_player_i_turn);
        }

        server->send_all_clients(game->get_current_player()->get_actions_per_turn());
        server->send_all_clients(game->is_game_over());
        
        for(int j = 0; j < game->get_current_player()->get_actions_per_turn() && !game->is_game_over(); j++) {
            string hold_msg = "Waiting for " + game->get_current_player()->get_player_name() + ": Action " + to_string(j + 1) + "...";

            if(game->get_current_player()->get_player_id() == 0) {
                server->send_all_clients(hold_msg);
            } else {
                cout << hold_msg << '\n';
                for(int k = 0; k < server->get_number_of_clients(); k++) {
                    if(game->get_current_player()->get_player_id() != k + 1) server->send_client(k, hold_msg);
                }
            }

            string command = ask_current_player_command(game->get_current_player()->get_player_id(), j);
            execute_command(command, j);
            if(command == "help") j--;
            server->send_all_clients(j);
            server->send_all_clients(game->is_game_over());
        }
    }

    string ask_current_player_command(int player_id, int action_number) {
        string command;

        if(player_id != 0) server->send_client(player_id - 1, is_valid_command(command));

        string instruction_msg = "Your turn: Type \"help\" for available commands. Input: ";
        if(player_id == 0) cout << instruction_msg;
        else server->send_client(player_id - 1, instruction_msg);

        while(!is_valid_command(command)) {
            if(player_id == 0) {
                getline(cin, command);
            } else {
                command = server->get_client_string(player_id - 1);
            }

            if(player_id != 0) server->send_client(player_id - 1, is_valid_command(command));

            if(!is_valid_command(command)) {
                string error_msg = "Invalid command! Please try again: ";
                if(player_id == 0) cout << error_msg;
                else server->send_client(player_id - 1, error_msg);
            }
        }

        return command;
    }

    void execute_command(string &command, int action_number) {
        string str;
        stringstream ss(command);
        ss >> str;

        if(str == "tap") {
            string player_body_part, target_body_part;
            int target_id, player_body_part_number, target_body_part_number;

            str.clear();
            ss >> str;

            if(str[0] == 'H') player_body_part = "hand";
            else if(str[0] == 'F') player_body_part = "foot";

            player_body_part_number = str[1] - 'A';

            str.clear();
            ss >> str;

            target_id = atoi(str.c_str()) - 1;

            str.clear();
            ss >> str;

            if(str[0] == 'H') target_body_part = "hand";
            else if(str[0] == 'F') target_body_part = "foot";

            target_body_part_number = str[1] - 'A';

            game->tap(player_body_part, player_body_part_number, target_id, target_body_part, target_body_part_number);
        } else if(str == "disthands") {
            vector<int> hands;

            for(int i = 0; i < game->get_current_player()->get_number_of_hands(); i++) {
                if(!game->get_current_player()->is_hand_dead(i)) {
                    str.clear();
                    ss >> str;
                    hands.push_back(atoi(str.c_str()));
                } else {
                    hands.push_back(game->get_current_player()->get_max_fingers());
                }
            }

            game->disthands(hands);
        } else if(str == "distfeet") {
            vector<int> feet;

            for(int i = 0; i < game->get_current_player()->get_number_of_feet(); i++) {
                if(!game->get_current_player()->is_foot_dead(i)) {
                    str.clear();
                    ss >> str;
                    feet.push_back(atoi(str.c_str()));
                } else {
                    feet.push_back(game->get_current_player()->get_max_toes());
                }
            }

            game->distfeet(feet);
        } else if(str == "help") {
            int player_id = game->get_current_player()->get_player_id();

            vector<string> command_msg(4);
            command_msg[0] = "Please choose from the following actions: ";
            command_msg[1] = "--- tap H/F[body_letter] [target_player] H/F[target_body_letter]: e.g. \"tap HA 2 FB\"";
            command_msg[2] = "--- disthands [hand_1_fingers] [hand_2_fingers] ...: e.g. \"disthands 3 2 3\"";
            command_msg[3] = "--- distfeet [feet_1_toes] [feet_2_toes] ...: e.g. \"distfeet 1 3 1\"";

            if(player_id == 0) {
                for(int i = 0; i < 4; i++) {
                    cout << command_msg[i] << '\n';
                }
            } else {
                server->send_client(player_id - 1, command_msg);
            }
        }
    }

    bool is_valid_command(string &command) {
        stringstream ss(command);
        string str;

        ss >> str;
        
        if(str == "tap") {
            str.clear();
            ss >> str;
            if(str.length() != 2) return false;

            if(str[0] != 'H' && str[0] != 'F') return false;
            int body_number = str[1] - 'A';
            if(str[0] == 'H') {
                if(!(0 <= body_number && body_number < game->get_current_player()->get_number_of_hands() && !game->get_current_player()->is_hand_dead(body_number))) {
                    return false;
                }
            } else if(str[0] == 'F') {
                if(!(0 <= body_number && body_number < game->get_current_player()->get_number_of_feet() && !game->get_current_player()->is_foot_dead(body_number))) {
                    return false;
                }
            }

            str.clear();
            ss >> str;
            if(!(is_number(str) && 0 < atoi(str.c_str()) && atoi(str.c_str()) <= number_of_players && game->get_current_player()->get_team_number() != game->get_player(atoi(str.c_str()) - 1)->get_team_number() && !game->get_player(atoi(str.c_str()) - 1)->is_dead())) {
                return false;
            }
            int target_id = atoi(str.c_str()) - 1;

            str.clear();
            ss >> str;
            if(str.length() != 2) return false;
            if(str[0] != 'H' && str[0] != 'F') return false;
            body_number = str[1] - 'A';
            if(str[0] == 'H') {
                if(!(0 <= body_number && body_number < game->get_player(target_id)->get_number_of_hands() && !game->get_player(target_id)->is_hand_dead(body_number))) {
                    return false;
                }
            } else if(str[0] == 'F') {
                if(!(0 <= body_number && body_number < game->get_player(target_id)->get_number_of_feet() && !game->get_player(target_id)->is_foot_dead(body_number))) {
                    return false;
                }
            }

            str.clear();
            ss >> str;
            if(str != "") return false;
            return true;
        } else if(str == "disthands") {
            if(game->get_current_player()->get_alive_hands() <= 1) return false;
            vector<int> hands;

            while(ss) {
                str.clear();
                ss >> str;
                if(str == "") break;
                if(is_number(str) && 0 <= atoi(str.c_str()) && atoi(str.c_str()) < game->get_current_player()->get_max_fingers()) {
                    hands.push_back(atoi(str.c_str()));
                } else {
                    return false;
                }
            }

            if(hands.size() != game->get_current_player()->get_alive_hands()) return false;

            for(int i = 0; i < game->get_current_player()->get_number_of_hands(); i++) {
                if(!game->get_current_player()->is_hand_dead(i)) {
                    if(game->get_current_player()->get_hand_fingers(i) != hands[i]) {
                        return true;
                    }
                }
            }

            vector<int> current_hands;

            for(int i = 0; i < game->get_current_player()->get_number_of_hands(); i++) {
                if(!game->get_current_player()->is_hand_dead(i)) {
                    current_hands.push_back(game->get_current_player()->get_hand_fingers(i));
                }
            }

            if(get_sum(current_hands) != get_sum(hands)) return false;

            return false;
        } else if(str == "distfeet") {
            if(game->get_current_player()->get_alive_feet() <= 1) return false;
            vector<int> feet;

            while(ss) {
                str.clear();
                ss >> str;
                if(str == "") break;
                if(is_number(str) && 0 < atoi(str.c_str()) && atoi(str.c_str()) < game->get_current_player()->get_max_toes()) {
                    feet.push_back(atoi(str.c_str()));
                } else {
                    return false;
                }
            }

            if(feet.size() != game->get_current_player()->get_alive_feet()) return false;

            for(int i = 0; i < game->get_current_player()->get_number_of_feet(); i++) {
                if(!game->get_current_player()->is_foot_dead(i)) {
                    if(game->get_current_player()->get_foot_toes(i) != feet[i]) {
                        return true;
                    }
                }
            }

            vector<int> current_feet;

            for(int i = 0; i < game->get_current_player()->get_number_of_feet(); i++) {
                if(!game->get_current_player()->is_foot_dead(i)) {
                    current_feet.push_back(game->get_current_player()->get_foot_toes(i));
                }
            }

            if(get_sum(current_feet) != get_sum(feet)) return false;

            return false;
        } else if(str == "help") return true;

        return false;
    }
};

void execute_server(string port) {
    Game *game = new Game(Constants::max_players, Constants::max_teams);
    Server server(port);

    GameHandler gamehandler(game, &server);
    gamehandler.run();
    delete game;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        string launch_err_msg = "Invalid number of arguments! Please enter a port (Range: " + to_string(Constants::min_port) + "-" + to_string(Constants::max_port) + ")";

        cout << launch_err_msg << '\n';
        throw invalid_argument(launch_err_msg);
    }
    execute_server(argv[1]);
}
