#include <iostream>
#include <string>

using namespace std;

bool **duplicate_bool_matrix(bool **source, int rows, int cols) {
    bool **copy = new bool*[rows];

    for (int r = 0; r < rows; r++) {
        copy[r] = new bool[cols];

        for (int c = 0; c < cols; c++) {
            copy[r][c] = source[r][c];
        }
    }

    return copy;
};

class State {
private:
    int R;
    int C;

    bool **visited;
    char **maze;

    void mark_cur_as_visited() {
        this->visited[this->cur_r][this->cur_c] = true;
    };

    void init_visited_matrix(char **maze) {
        // Make new visited matrix
        this->visited = new bool*[this->R];
        for (int r = 0; r < R; r++) {

            this->visited[r] = new bool[this->C];
            for (int c = 0; c < C; c++) {

                // "Visit" all unwalkable cells
                if (maze[r][c] == 'x') {
                    this->visited[r][c] = true;
                } else {
                    this->visited[r][c] = false;
                }
            }
        }

        // Visit starting cell
        this->visited[this->cur_r][this->cur_c] = true;
    }

public:
    int cur_r;
    int cur_c;

    State(int start_r, int start_c, int R, int C, char **maze) {
        this->R = R;
        this->C = C;

        this->cur_r = start_r;
        this->cur_c = start_c;

        // Make all unwalkable cells and starting cell visited
        init_visited_matrix(maze);

        // Reuse (share) maze matrix argument
        this->maze = maze;
    };

    // Destructor frees visited matrix to avoid memory leaks
    ~State() {
        for (int r = 0; r < R; r++) {
            delete[] this->visited[r];
        }
        delete[] this->visited;
    };

    // Copy constructor
    State(const State &source) {
        this->R = source.R;
        this->C = source.C;

        this->cur_r = source.cur_r;
        this->cur_c = source.cur_c;

        // Make own visited matrix; do NOT reuse/share visited matrix argument
        this->visited = duplicate_bool_matrix(source.visited, source.R, source.C);

        // Reuse (share) maze matrix argument
        this->maze = source.maze;
    };

    bool has_visited_all() {
        for (int r = 0; r < this->R; r++) {
            for (int c = 0; c < this->C; c++) {
                if (!this->visited[r][c]) {
                    return false;
                }
            }
        }

        return true;
    };

    bool can_move_up() {
        return (this->cur_r > 0) && !this->visited[cur_r-1][cur_c];
    }

    bool can_move_down() {
        return (this->cur_r + 1 < this->R) && !this->visited[cur_r+1][cur_c];
    }

    bool can_move_left() {
        return (this->cur_c > 0) && !this->visited[cur_r][cur_c-1];
    }

    bool can_move_right() {
        return (this->cur_c + 1 < this->C) && !this->visited[cur_r][cur_c+1];
    }

    void move_up() {
        this->cur_r--;
        this->mark_cur_as_visited();
    }

    void move_down() {
        this->cur_r++;
        this->mark_cur_as_visited();
    }

    void move_left() {
        this->cur_c--;
        this->mark_cur_as_visited();
    }

    void move_right() {
        this->cur_c++;
        this->mark_cur_as_visited();
    }

    void print() {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                cout << maze[i][j];
            }

            cout << '\n';
        }

        cout << '\n';
    }
};

int solutions(State &state) {
    if (state.has_visited_all()) {
        return 1;
    }

    int moves = 0;

    if (state.can_move_up()) {
        // Makes new State object via copy constructor
        State new_state = state;

        new_state.move_up();
        //new_state.print();

        // Recursive call will not affect state of current call
        moves += solutions(new_state);
    }

    if (state.can_move_down()) {
        // Must make new State object for each movement
        State new_state = state;
        new_state.move_down();
        //new_state.print();

        moves += solutions(new_state);
    }

    if (state.can_move_left()) {
        State new_state = state;
        new_state.move_left();
        //new_state.print();

        moves += solutions(new_state);
    }

    if (state.can_move_right()) {
        State new_state = state;
        new_state.move_right();
        //new_state.print();

        moves += solutions(new_state);
    }

    return moves;
}

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int R, C;
        cin >> R >> C;
        cin.ignore(255, '\n');

        char **maze = new char*[R];

        for (int r = 0; r < R; r++) {
            string line;
            getline(cin, line);

            maze[r] = new char[C];

            for (int c = 0; c < C; c++) {
                maze[r][c] = line[c];
            }
        }

        // Make a new State object per test case
        State state(0, 0, R, C, maze);

        cout << solutions(state) << "\n";
    }
}