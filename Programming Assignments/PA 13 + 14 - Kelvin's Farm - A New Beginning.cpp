#include <iostream>
#include <string>

using namespace std;

struct CropDetails {
    string name;
    int selling_price;
    int days_grow;
    int days_regrow;
};

enum class Cell {
    EMPTY,
    TILLED,
    PLANTED,
    WILTED,
    READY
};

struct FarmCell{
    CropDetails cropdetails;
    Cell cell;
    int water;
    int daysToGrow;

    FarmCell() {
        cell = Cell::EMPTY;
        water = 0;
        daysToGrow = 0;
    }
};

class Farm {
    private:
        FarmCell **farm;
        int days;
        int rows;
        int cols;
        const CropDetails *current_crop;

        int profit;
        int total_profit;
        int harvested;
        int wilted;
        int growing;
        int unharvested;
        int tilled;
        int untilled;
        int watered;
        int unwatered;
        int overwatered;
    public:
        Farm(int rows, int cols) {
            this->rows = rows;
            this->cols = cols;
            days = 1;
            total_profit = 0;
            resetDay();

            farm = new FarmCell*[rows];
            for(int i = 0; i < rows; i++) {
                farm[i] = new FarmCell[cols];
            }
        }

        ~Farm() {
            for(int i = 0; i < rows; i++) {
                delete [] farm[i];
            }

            delete [] farm;
        }

        void resetDay() {
            profit = 0;
            harvested = 0;
            wilted = 0;
            growing = 0;
            unharvested = 0;
            tilled = 0;
            untilled = 0;
            watered = 0;
            unwatered = 0;
            overwatered = 0;
        }

        bool isInBounds(int x, int y) {
            if(0 <= x && x < rows && 0 <= y && y < cols) return true;
            return false;
        }

        void copyCrop(const CropDetails &deets, int x, int y) {
            farm[x][y].cropdetails.name = deets.name;
            farm[x][y].cropdetails.selling_price = deets.selling_price;
            farm[x][y].cropdetails.days_grow = deets.days_grow;
            farm[x][y].cropdetails.days_regrow = deets.days_regrow;
        }

        bool till(int x, int y) {
            if(farm[x][y].cell != Cell::EMPTY) return false;

            farm[x][y].cell = Cell::TILLED;
            return true;
        }

        bool plant(const CropDetails &deets, int x, int y) {
            if(farm[x][y].cell != Cell::TILLED) return false;

            current_crop = &deets;
            farm[x][y].cell = Cell::PLANTED;
            copyCrop(deets, x, y);
            farm[x][y].daysToGrow = deets.days_grow;
            return true;
        }

        int scatter_seeds(const CropDetails &deets, int x, int y) {
            int count = 0;
            current_crop = &deets;

            for(int i = x - 1; i < x + 2; i++) {
                for(int j = y - 1; j < y + 2; j++) {
                    if(isInBounds(x, y) && plant(deets, x, y)) {
                        count++;
                    }
                }
            }

            return count;
        }

        bool water(int x, int y) {
            if(farm[x][y].cell != Cell::EMPTY) {
                farm[x][y].water++;

                if(farm[x][y].water == 1) return true;
            }

            return false;
        }

        const CropDetails *harvest(int x, int y) {
            if(farm[x][y].cell == Cell::EMPTY ||
                farm[x][y].cell == Cell::TILLED) return nullptr;

            if(farm[x][y].cell == Cell::READY) {
                profit += farm[x][y].cropdetails.selling_price;
                harvested++;
                if(farm[x][y].cropdetails.days_regrow == 0) {
                    clear(x, y);
                } else {
                    farm[x][y].daysToGrow = farm[x][y].cropdetails.days_regrow;
                }
            }

            return current_crop;
        }

        bool clear(int x, int y) {
            if(farm[x][y].cell == Cell::EMPTY || farm[x][y].cell == Cell::TILLED) return false;

            farm[x][y].cell = Cell::TILLED;
            return true;
        }

        int clear_all() {
            int count = 0;
            for(int x = 0; x < rows; x++) {
                for(int y = 0; y < cols; y++) {
                    if(clear(x, y)) count++;
                }
            }
            return count;
        }

        void examine(int x, int y) {
            cout << x << " " << y << " ";
            
            if(farm[x][y].cell == Cell::EMPTY) {
                cout << "untilled\n";
            } else if(farm[x][y].cell == Cell::TILLED) {
                cout << "empty\n";
            } else {
                cout << farm[x][y].cropdetails.name << " ";

                if(farm[x][y].cell == Cell::WILTED) {
                    cout << "wilted ";
                } else if(farm[x][y].cell == Cell::READY) {
                    cout << "ready ";
                } else {
                    cout << farm[x][y].daysToGrow << " ";
                }

                if(farm[x][y].water < 1) {
                    cout << "unwatered\n";
                } else if(farm[x][y].water == 1) {
                    cout << "watered\n";
                } else {
                    cout << "overwatered\n";
                }
            }
        }

        void print() {
            cout << "Day #" << days << "\n";
            cout << "Total Profit: " << total_profit << "\n";
            cout << "Earned Today: " << profit << "\n";
            cout << "Harvested Today: " << harvested << "\n";
            cout << "Wilted Today: " << wilted << "\n";
            cout << "Still Growing: " << growing << "\n";
            cout << "Unharvested: " << unharvested << "\n";
            cout << "Tilled Cells: " << tilled << "\n";
            cout << "Untilled Cells: " << untilled << "\n";
            cout << "Watered Cells: " << watered << "\n";
            cout << "Unwatered Cells: " << unwatered << "\n";
            cout << "Overwatered Cells: " << overwatered << "\n";
        }

        void end_day() {
            total_profit += profit;

            for(int x = 0; x < rows; x++) {
                for(int y = 0; y < cols; y++) {
                    if(farm[x][y].water != 1) {
                        farm[x][y].cell = Cell::WILTED;
                        if(farm[x][y].water < 1) {
                            unwatered++;
                        } else {
                            overwatered++;
                        }
                    } else {
                        farm[x][y].daysToGrow--;
                        watered++;
                    }

                    farm[x][y].water = 0;

                    if(farm[x][y].cell == Cell::EMPTY) {
                        untilled++;
                    } else if(farm[x][y].cell == Cell::TILLED) {
                        tilled++;
                    } else if(farm[x][y].cell == Cell::PLANTED) {
                        farm[x][y].daysToGrow--;
                        if(farm[x][y].daysToGrow == 0) {
                            farm[x][y].cell = Cell::READY;
                        } else {
                            growing++;
                        }
                    } else if(farm[x][y].cell == Cell::READY) {
                        unharvested++;
                        wilted++;
                        farm[x][y].cell = Cell::WILTED;
                    }
                }
            }

            print();
            resetDay();
            days++;
        }
};

int main() {
    int x;

    return 0;
}