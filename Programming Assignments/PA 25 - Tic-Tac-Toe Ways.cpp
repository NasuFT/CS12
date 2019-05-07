#include <iostream>
#include <string>

using namespace std;

struct Counter {
    int x;
    int o;
    int draw;

    Counter() {
        x = 0;
        o = 0;
        draw = 0;
    }
};

bool isWinner(string &state, char player) {
    if(state[0] == state[3] && state[3] == state[6] && state[0] == player) return true;
    if(state[1] == state[4] && state[4] == state[7] && state[1] == player) return true;
    if(state[2] == state[5] && state[5] == state[8] && state[2] == player) return true;
    if(state[0] == state[1] && state[1] == state[2] && state[0] == player) return true;
    if(state[3] == state[4] && state[4] == state[5] && state[3] == player) return true;
    if(state[6] == state[7] && state[7] == state[8] && state[6] == player) return true;
    if(state[0] == state[4] && state[4] == state[8] && state[0] == player) return true;
    if(state[2] == state[4] && state[4] == state[6] && state[2] == player) return true;

    return false;
}

bool isOutOfMoves(string &state) {
    return state.find('_') == string::npos;
}

Counter count(string state, char player) {
    Counter counter;

    if(isWinner(state, 'X')) {
        counter.x = 1;
        return counter;
    }

    if(isWinner(state, 'O')) {
        counter.o = 1;
        return counter;
    }

    if(isOutOfMoves(state)) {
        counter.draw = 1;
        return counter;
    }

    for(int i = 0; i < 9; i++) {
        if(state[i] == '_') {
            string new_state = state;
            new_state[i] = player;

            Counter new_counter = count(new_state, (player == 'X') ? 'O' : 'X');
            counter.o += new_counter.o;
            counter.x += new_counter.x;
            counter.draw += new_counter.draw;
        }
    }

    return counter;
}

void print_counter(Counter &counter) {
    cout << "X WINS: " << counter.x << '\n';
    cout << "O WINS: " << counter.o << '\n';
    cout << "DRAWS: " << counter.draw << '\n';
    cout << "TOTAL: " << counter.x + counter.o + counter.draw << '\n';
}

int main() {
    string str = "_________";
    Counter counter = count(str, 'X');
    print_counter(counter);
}