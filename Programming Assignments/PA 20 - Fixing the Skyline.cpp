#include <iostream>
#include <vector>

using namespace std;

struct Building {
    int left;
    int height;
    int right;
};


struct KeyPoint {
    int x;
    int height;

    KeyPoint(int x, int height) {
        this->x = x;
        this->height = height;
    };
};


int max(int a, int b) {
    return (a > b) ? a : b;
}


class Skyline {
private:
    vector<KeyPoint*> *points;

public:
    Skyline() {
        points = new vector<KeyPoint*>();
    };

    Skyline *merge(Skyline *that) {
        Skyline *merged_skyline = new Skyline();

        int recent_height_from_this = 0;
        int recent_height_from_that = 0;

        // Incrementing an index means "removing" a key point
        int this_index = 0;
        int that_index = 0;

        while (this_index < this->size() && that_index < that->size()) {
            KeyPoint *this_point = this->at(this_index);
            KeyPoint *that_point = that->at(that_index);

            int x;

            if (this_point->x < that_point->x) {
                x = this_point->x;
                recent_height_from_this = this_point->height;

                this_index++;

            } else if (this_point->x > that_point->x) {
                x = that_point->x;
                recent_height_from_that = that_point->height;

                that_index++;

            } else {
                x = this_point->x;
                recent_height_from_this = this_point->height;
                recent_height_from_that = that_point->height;

                this_index++;
                that_index++;
            }

            int max_height = max(recent_height_from_this, recent_height_from_that);
            KeyPoint *adjusted_point = new KeyPoint(x, max_height);

            merged_skyline->try_to_add(adjusted_point);
        }

        while (this_index < this->size()) {
            merged_skyline->try_to_add(this->at(this_index));
            this_index++;
        }

        while (that_index < that->size()) {
            merged_skyline->try_to_add(that->at(that_index));
            that_index++;
        }

        return merged_skyline;
    };

    int size() {
        return this->points->size();
    };

    KeyPoint *at(int index) {
        return this->points->at(index);
    }

    void try_to_add(KeyPoint *to_add) {
        if (this->size() == 0 || to_add->height != this->latest_point()->height) {
            this->points->push_back(to_add);
        }
    };

    KeyPoint *latest_point() {
        int size = this->size();

        if (size == 0) {
            return nullptr;
        }

        return this->points->at(size-1);
    };

    void print() {
        for (int i = 0; i < this->size(); i++) {
            KeyPoint *p = this->points->at(i);

            cout << "(" << p->x << " " << p->height << ") ";
        }
        cout << "\n";
    };
};


Skyline *get_skyline(Building buildings[], int left_index, int right_index) {
    // Base case
    if (left_index == right_index) {
        Skyline *skyline = new Skyline();
        Building &b = buildings[left_index];

        skyline->try_to_add(new KeyPoint(b.left, b.height));
        skyline->try_to_add(new KeyPoint(b.right, 0));

        return skyline;
    }

    int middle_index = left_index + (right_index - left_index) / 2;

    Skyline *left_skyline = get_skyline(buildings, left_index, middle_index);
    Skyline *right_skyline = get_skyline(buildings, middle_index + 1, right_index);
    Skyline *merged_skyline = left_skyline->merge(right_skyline);

    delete left_skyline;
    delete right_skyline;

    return merged_skyline;
}


int main() {
    Building buildings[] = {{2, 10, 9}, {3, 15, 7}, {5, 12, 12}, {15, 10, 20}, {19, 8, 24}};

    int n = sizeof(buildings) / sizeof(buildings[0]);

    Skyline *skyline = get_skyline(buildings, 0, n - 1);

    skyline->print();

    return 0;
}