#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// make the code complicated, coz why not?
// all -> is satisfying though
// of course, this aint gonna get through the HOCE

struct Point {
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    bool const operator < (const Point &p) {
        if(x == p.x) return y < p.y;
        return x < p.x;
    }
};

double get_distance(Point *p1, Point *p2) {
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
}

void print_vector(vector<Point*> *arr) {
    for(int i = 0; i < arr->size(); i++) {
        cout << "Point: ";
        cout << arr->at(i)->x;
        cout << ',';
        cout << arr->at(i)->y;
        cout << '\n';
    }
}

double closest_pair(vector<Point*> *arr) {
    if(arr->size() == 2) {
        return get_distance(arr->at(0), arr->at(1));
    }

    if(arr->size() == 3) {
        return min(get_distance(arr->at(0), arr->at(1)),
                min(get_distance(arr->at(1), arr->at(2)),
                    get_distance(arr->at(0), arr->at(2))));
    }

    int mid = (arr->size() - 1) / 2;

    vector<Point*> *left = new vector<Point*>;
    vector<Point*> *right = new vector<Point*>;

    for(int i = 0; i < arr->size(); i++) {
        if(i <= mid) {
            left->push_back(arr->at(i));
        } else {
            right->push_back(arr->at(i));
        }
    }

    double min_distance = min(closest_pair(left), closest_pair(right));

    vector<Point*> *strip = new vector<Point*>;
    for(int i = 0; i < arr->size(); i++) {
        if(arr->at(i)->x > (arr->at(mid)->x - min_distance) && arr->at(i)->x < (arr->at(mid)->x + min_distance)) {
            strip->push_back(arr->at(i));
        }
    }

    for(int i = 0; i < strip->size(); i++) {
        for(int j = i + 1; j < strip->size() && strip->at(j)->y - strip->at(i)->y < min_distance; j++) {
            if(get_distance(strip->at(j), strip->at(i)) < min_distance) {
                min_distance = get_distance(strip->at(j), strip->at(i));
            }
        }
    }

    delete left;
    delete right;
    delete strip;

    return min_distance;
}

bool pointsort(Point *p1, Point *p2) {
    return *p1 < *p2;
}

int main() {
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        int n;
        cin >> n;
        vector<Point*> *arr = new vector<Point*>;

        for(int i = 0; i < n; i++) {
            double x;
            double y;

            cin >> x >> y;

            Point *point = new Point(x, y);
            arr->push_back(point);
        }

        sort(arr->begin(), arr->end(), [](Point *p1, Point* p2) { return *p1 < *p2; });

        double dist = closest_pair(arr);

        cout << dist << '\n';

        for(int i = 0; i < arr->size(); i++) {
            delete arr->at(i);
        }

        delete arr;
    }

    return 0;
}