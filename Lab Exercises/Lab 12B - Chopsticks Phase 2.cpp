#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define enable_debug

#ifdef enable_debug
#define D(x) x
#else
#define D(x) 
#endif

using namespace std;

class BodyPart;
class Player;
class Team;
class Game;

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

    static const int max_teams;

    static const int max_players;
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

/// TEAM CONSTANTS

const int Constants::max_teams = 3;

/// GAME CONSTANTS

const int Constants::max_players = 6;



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
    string player_class;
    bool is_skipped;
public:
    Player(int _hands, int _feet, int _fingers, int _toes, const string &_player_class, int _actions_per_turn) {
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

        actions_per_turn = _actions_per_turn;
        player_class = _player_class;
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

    virtual void on_hand_death() {
        
    }

    virtual void on_foot_death() {
        skip_next_turn();
    }

    virtual void on_target(Player &target) {

    }

    virtual void on_player_attack(Player &attacker) {

    }

    virtual void print_player_status() {
        cout << "(";

        for(unsigned int i = 0; i < hands.size(); i++) {
            if(hands[i].is_dead()) cout << "X";
            else cout << hands[i].get_value();
        }

        cout << ":";

        for(unsigned int i = 0; i < feet.size(); i++) {
            if(feet[i].is_dead()) cout << "X";
            else cout << feet[i].get_value();
        }

        cout << ")";
    }
};

class Human: public Player {
private:
public:
    Human()
        : Player(Constants::human_hands, Constants::human_feet, Constants::human_fingers, Constants::human_toes, Constants::human_class, Constants::human_actions) {

    }
};

class Alien: public Player {
private:
public:
    Alien()
        : Player(Constants::alien_hands, Constants::alien_feet, Constants::alien_fingers, Constants::alien_toes, Constants::alien_class, Constants::alien_actions) {

    }

    void on_foot_death(Player &killer) {
        
    }
};

class Zombie: public Player {
private:
    bool can_revive;
public:
    Zombie()
        : Player(Constants::zombie_hands, Constants::zombie_feet, Constants::zombie_fingers, Constants::zombie_toes, Constants::zombie_class, Constants::zombie_actions) {
        can_revive = true;
    }

    void on_hand_death(Player &killer) {
        if(can_revive) {
            Hand hand_new(Constants::initial_fingers, Constants::zombie_fingers);
            hands.push_back(hand_new);
            can_revive = false;
        }
    }
};

class Doggo: public Player {
private:
public:
    Doggo()
        : Player(Constants::doggo_hands, Constants::doggo_feet, Constants::doggo_fingers, Constants::doggo_toes, Constants::doggo_class, Constants::doggo_actions) {

    }

    void on_target(Player &target) {
        if(target.get_player_class() != Constants::doggo_class) {
            target.skip_next_turn();
        }
    }
};



/// ----- TEAMS ----- ///

class Team {
private:
    vector<Player*> players;
    vector<int> player_ids;
    int current_player;
public:
    Team(): current_player(0) {

    }

    void add_player(Player *player, int player_id) {
        players.push_back(player);
        player_ids.push_back(player_id);
    }

    void next_player() {
        if(current_player == -1) current_player = players.size() - 1;

        current_player = (current_player + 1) % players.size();
        while(!can_current_player_act()) {
            players[current_player]->skip();
            current_player = (current_player + 1) % players.size();
        }
    }

    bool can_act() {
        for(unsigned int i = 0; i < players.size(); i++) {
            if(players[i]->can_act()) return true;
        }

        return false;
    }

    bool can_current_player_act() {
        return players[current_player]->can_act();
    }

    void skip() {
        for(unsigned int i = 0; i < players.size(); i++) {
            players[i]->skip();
        }
    }

    bool is_dead() {
        for(unsigned int i = 0; i < get_number_of_players(); i++) {
            if(!players[i]->is_dead()) {
                return false;
            }
        }

        return true;
    }

    int get_current_player() {
        return player_ids[current_player];
    }

    int get_number_of_players() {
        return players.size();
    }

    void print_team_status() {
        for(unsigned int i = 0; i < players.size(); i++) {
            cout << "P" << player_ids[i] << players[i]->get_player_class()[0] << " ";
            players[i]->print_player_status();

            if(i != players.size() - 1) cout << " | ";
        }
    }
};



/// ----- GAME ----- ///
class Game {
private:
    vector<Player*> players;
    vector<Team> teams;

    int current_team;
    int winner;
public:
    Game(int max_players, int max_teams): teams(max_teams), current_team(0) {
        
    }

    ~Game() {
        for(unsigned int i = 0; i < players.size(); i++) {
            delete players[i];
        }
    }

    int get_current_player() {
        return teams[current_team].get_current_player();
    }

    void next_team() {

        current_team = (current_team + 1) % teams.size();

        while(teams[current_team].is_dead() || !teams[current_team].can_act()) {
            if(!teams[current_team].can_act()) {
                teams[current_team].skip();
            }

            current_team = (current_team + 1) % teams.size();
        }

        while(!teams[current_team].can_current_player_act()) {
            teams[current_team].next_player();
        }
    }

    int get_dead_teams() {
        int teams_dead = 0;

        for(int i = 0; i < teams.size(); i++) {
            if(teams[i].is_dead()) teams_dead++;
        }

        return teams_dead;
    }

    bool has_won() {
        if(get_dead_teams() > teams.size() - 2) return true;
        return false;
    }

    int get_winner() {
        if(!has_won()) return -1;

        for(int i = 0; i < teams.size(); i++) {
            if(!teams[i].is_dead()) return i + 1;
        }

        return -1;
    }

    void attack(string player_part_number, int target_id, string target_part_number) {
        int player_value, target_value, player_number, target_number;

        player_number = player_part_number[1] - 'A';
        target_number = target_part_number[1] - 'A';

        if(player_part_number[0] == 'H') player_value = players[get_current_player() - 1]->get_hand_fingers(player_number);
        else if(player_part_number[0] == 'F') player_value = players[get_current_player() - 1]->get_foot_toes(player_number);

        if(target_part_number[0] == 'H') target_value = players[target_id - 1]->get_hand_fingers(target_number);
        else if(target_part_number[0] == 'F') target_value = players[target_id - 1]->get_foot_toes(target_number);

        D(cout << '\n';
        cout << "Attack Status: " << '\n';
        cout << "Player " << get_current_player() << " attacks Player " << target_id << '\n';
        cout << "Body Part " << player_number + 1 << " with value " << player_value << " attacks Body Part " << target_number + 1 << '\n';
        cout << "Old Value: " << target_value << '\n';)

        if(target_part_number[0] == 'H') players[target_id - 1]->set_hand_fingers(target_number, player_value + target_value);
        else if(target_part_number[0] == 'F') players[target_id - 1]->set_foot_toes(target_number, player_value + target_value);

        D(if(target_part_number[0] == 'H') cout << "New Value: " << players[target_id - 1]->get_hand_fingers(target_number) << '\n';
        else if(target_part_number[0] == 'F') cout << "New Value: " << players[target_id - 1]->get_foot_toes(target_number) << '\n';

        cout << '\n';)

        players[target_id - 1]->on_target(*players[get_current_player() - 1]);
        players[get_current_player() - 1]->on_player_attack(*players[target_id - 1]);

    }

    void disthands(vector<int> hands) {
        for(unsigned int i = 0; i < hands.size(); i++) {
            players[get_current_player() - 1]->set_hand_fingers(i, hands[i]);
        }
    }

    void distfeet(vector<int> feet) {
        for(unsigned int i = 0; i < feet.size(); i++) {
            players[get_current_player() - 1]->set_foot_toes(i, feet[i]);
        }
    }

    void run_command(string &input) {
        if(input == "tap") {
            string a, c;
            int b;
            cin >> a >> b >> c;
            attack(a, b, c);
        } else if(input == "disthands") {
            vector<int> hands(players[get_current_player() - 1]->get_number_of_hands());

            for(unsigned int i = 0; i < players[get_current_player() - 1]->get_number_of_hands(); i++) {
                int x;
                cin >> x;
                hands[i] = x;
            }

            disthands(hands);
        } else if(input == "distfeet") {
            vector<int> feet(players[get_current_player() - 1]->get_number_of_feet());

            for(unsigned int i = 0; i < players[get_current_player() - 1]->get_number_of_feet(); i++) {
                int x;
                cin >> x;
                feet[i] = x;
            }

            distfeet(feet);
        }
    }

    void get_input() {
       

        for(int i = 0; i < players[get_current_player() - 1]->get_actions_per_turn(); i++) {
            string command;
            cin >> command;
            run_command(command);
        }

        teams[current_team].next_player();
        next_team();
    }
    

    void print_game_status() {
        for(int i = 0; i < teams.size(); i++) {
            if(teams[i].get_number_of_players() > 0) {
                cout << "Team " << i + 1 << ": ";
                teams[i].print_team_status();
                cout << '\n';
            }
        }

        cout << '\n';
    }

    void print_game_winner() {
        cout << "Team " << get_winner() << " wins!";
    }

    void initialize() {
        int number_players, number_teams;
        cin >> number_players >> number_teams;

        for(int i = 0; i < number_players; i++) {
            string class_name;
            cin >> class_name;
            
            if(class_name == "human") {
                Player *player = new Human;
                players.push_back(player);
            } else if(class_name == "alien") {
                Player *player = new Alien;
                players.push_back(player);
            } else if(class_name == "zombie") {
                Player *player = new Zombie;
                players.push_back(player);
            } else if(class_name == "doggo") {
                Player *player = new Zombie;
                players.push_back(player);
            }

            int team_number;
            cin >> team_number;

            teams[team_number - 1].add_player(players[i], i + 1);
        }
    }

    void run() {
        initialize();

        while(!has_won()) {
            D(cout << "Current Turn: Player " << get_current_player() << '\n';)
            print_game_status();
            get_input();
        }

        print_game_status();
        print_game_winner();
    }
};

void execute_game() {
    Game game(Constants::max_players, Constants::max_teams);
    game.run();
}

int main () {
    execute_game();

    // Human human;
    // cout << human.get_number_of_hands() << '\n';
    // cout << human.get_number_of_feet() << '\n';
    // cout << human.get_hand_fingers(0) << '\n';
    // cout << human.get_foot_toes(0) << '\n';
    // cout << '\n';
    // Zombie zombie;
    // Alien alien;
    // Team team;
    // team.add_player(&human, 1);
    // team.add_player(&zombie, 2);
    // team.add_player(&alien, 4);

    // cout << team.get_current_player() << '\n';
    // team.next_player();
    // cout << team.get_current_player() << '\n';
    // team.next_player();
    // cout << team.get_current_player() << '\n';
    // team.next_player();
    // cout << team.get_current_player() << '\n';
    // team.next_player();
    // cout << team.get_current_player() << '\n';
    // team.next_player();
    // cout << team.get_current_player() << '\n';
    // cout << '\n';

    // cout << human.can_act() << '\n';
    // human.skip_next_turn();
    // cout << human.can_act() << '\n';
    // human.skip();
    // cout << human.can_act() << '\n';
}   