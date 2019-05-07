//CS 12 S - Merlin, Santiago

#include <iostream>
#include <string>
#include <vector>

class Hand;
class Player;
class Game;
class Interface;

class Hand {
private:
    int fingers;
public:
    Hand(int x): fingers(x) {
    }

    int get_fingers() {
        return fingers;
    }

    bool is_dead() {
        return (fingers == 5);
    }

    void add_fingers(int x) {
        fingers += x;
        if(fingers > 5) fingers -= 5;
    }

    void set_fingers(int x) {
        fingers = x;
    }
};

class Player {
private:
    Hand hand1;
    Hand hand2;
public:
    Player(): hand1(1), hand2(1) {
    }

    bool both_hands_dead() {
        return hand1.is_dead() && hand2.is_dead();
    }

    void add_left_hand_fingers(int x) {
        hand1.add_fingers(x);
    }

    void add_right_hand_fingers(int x) {
        hand2.add_fingers(x);
    }

    int get_left_hand_fingers() {
        return hand1.get_fingers();
    }

    int get_right_hand_fingers() {
        return hand2.get_fingers();
    }

    void set_left_hand_fingers(int x) {
        hand1.set_fingers(x);
    }

    void set_right_hand_fingers(int x) {
        hand2.set_fingers(x);
    }
};

class Game {
private:
    Player p1;
    Player p2;

    Player *current_turn;
    Player *winner;

    Interface *interface;
public:
    Game(): current_turn(&p1) {
    }

    Player *player_turn() {
        return current_turn;
    }

    Player *opponent_turn() {
        return (current_turn == &p1 ? &p2 : &p1);
    }

    void switch_turn() {
        current_turn = (current_turn == &p1 ? &p2 : &p1);
    }

    void attack(char attacker, char opponent) {
        int finger_count;

        if(attacker == 'L') finger_count = player_turn()->get_left_hand_fingers();
        else finger_count = player_turn()->get_right_hand_fingers();

        if(opponent == 'L') opponent_turn()->add_left_hand_fingers(finger_count);
        else opponent_turn()->add_right_hand_fingers(finger_count);
    }

    void change(int x, int y) {
        player_turn()->set_left_hand_fingers(x);
        player_turn()->set_right_hand_fingers(y);
    }

    bool has_won() {
        if(p1.both_hands_dead() || p2.both_hands_dead()) {
            if(p1.both_hands_dead()) winner = &p2;
            if(p2.both_hands_dead()) winner = &p1;
            return true;
        }

        return false;
    }

    int get_winner() {
        if(!has_won()) return 0;
        else {
            if(winner == &p1) return 1;
            else return 2;
        }
    }

    std::vector<int> get_p1_status() {
        std::vector<int> status(2);
        status[0] = p1.get_left_hand_fingers();
        status[1] = p1.get_right_hand_fingers();
        return status;
    }

    std::vector<int> get_p2_status() {
        std::vector<int> status(2);
        status[0] = p2.get_left_hand_fingers();
        status[1] = p2.get_right_hand_fingers();
        return status;
    }

    void set_interface(Interface *interface) {
        this->interface = interface;
    }
};

class Interface {
protected:
    Game *current_game;
public:
};

class CMDInterface: public Interface {
private:
public:
    CMDInterface() {
    }

    CMDInterface(Game *game) {
        current_game = game;
        current_game->set_interface(this);
    }

    void get_input() {
        std::string command;
        std::cin >> command;
        run_command(command);
    }

    void run_command(std::string &command) {
        if(command == "attack") {
            char player, opponent;
            std::cin >> player >> opponent;
            current_game->attack(player, opponent);
        } else if(command == "change") {
            int left, right;
            std::cin >> left >> right;
            current_game->change(left, right);
        }
    }

    void set_game(Game *game) {
        current_game = game;
        current_game->set_interface(this);
    }

    void print_game_status() {
        std::vector<int> p1_status = current_game->get_p1_status();
        std::vector<int> p2_status = current_game->get_p2_status();

        std::cout << "P1 L:" << p1_status[0] << " R:" << p1_status[1];
        std::cout << " | ";
        std::cout << "P2 L:" << p2_status[0] << " R:" << p2_status[1];
        std::cout << '\n';
    }

    void print_game_winner() {
        std::cout << "Player " << current_game->get_winner() << " wins";
    }

    void run() {
        if(current_game == nullptr) {
            std::cout << "No game set! Set game by method set_game(Game *game).\n";
            return;
        }

        while(!current_game->has_won()) {
            print_game_status();
            get_input();
            current_game->switch_turn();
        }

        print_game_status();
        print_game_winner();
    }
};

void execute_game() {
    Game game;
    CMDInterface interface(&game);
    interface.run();
}

int main() {
    execute_game();
    return 0;
}