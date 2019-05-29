#include <iostream>
#include <string>

using namespace std;

struct Counter {
    int x, o, draw;

    Counter(): x(0), o(0), draw(0) {

    }
};

bool isWinner(string &state, char player) {
    if(state[0] == player && state[1] == player && state[2] == player) return true;    
    if(state[3] == player && state[4] == player && state[5] == player) return true;
    if(state[6] == player && state[7] == player && state[8] == player) return true;
    if(state[0] == player && state[3] == player && state[6] == player) return true;
    if(state[1] == player && state[4] == player && state[7] == player) return true;
    if(state[2] == player && state[5] == player && state[8] == player) return true;
    if(state[0] == player && state[4] == player && state[8] == player) return true;
    if(state[2] == player && state[4] == player && state[6] == player) return true;

    return false;
}

bool isGameDraw(string &state) {
    return (state.find('_') == string::npos);
}

Counter count(string state, char player) {
    Counter counter;

    for(int i = 0; i < 9; i++) {
        if(state[i] == 'x') state[i] = 'X';
        if(state[i] == 'o') state[i] = 'O';
    }

    if(player == 'x') player = 'X';
    if(player == 'o') player = 'O';

    if(isWinner(state, 'X')) {
        counter.x++;
        return counter;
    }

    if(isWinner(state, 'O')) {
        counter.o++;
        return counter;
    }

    if(isGameDraw(state)) {
        counter.draw++;
        return counter;
    }

    for(int i = 0; i < 9; i++) {
        if(state[i] == '_') {
            string new_state = state;
            new_state[i] = player;
            char new_player = (player == 'X' ? 'O' : 'X');
            Counter new_counter = count(new_state, new_player);
            counter.x += new_counter.x;
            counter.o += new_counter.o;
            counter.draw += new_counter.draw;
        }
    } 

    return counter;
}

int main() {
    string state = "_________";
    Counter counter = count(state, 'O');
    cout << counter.x << ' ' << counter.o << ' ' << counter.draw << ' ' << counter.o + counter.x + counter.draw;
}