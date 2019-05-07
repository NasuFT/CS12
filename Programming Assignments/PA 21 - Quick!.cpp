#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<int> arr) {
    cout << '[';

    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i];

        if(i < arr.size() - 1) cout << ' ';
    }

    cout << "]\n";
}

int median(int a, int b, int c) {
    vector<int> ret;
    ret.push_back(a);
    ret.push_back(b);
    ret.push_back(c);
    sort(ret.begin(), ret.end());
    return ret[1];
}

vector<int> merge(vector<int> &v1, vector<int> &v2, vector<int> &v3) {
    vector<int> ret;

    for(int i = 0; i < v1.size(); i++) {
        ret.push_back(v1[i]);
    }

    for(int i = 0; i < v2.size(); i++) {
        ret.push_back(v2[i]);
    }

    for(int i = 0; i < v3.size(); i++) {
        ret.push_back(v3[i]);
    }

    return ret;
}

vector<int> quicksort(vector<int> arr) {
    if(arr.size() < 2) return arr;
    int pivot = median(arr[0], arr[arr.size() - 1], arr[arr.size() / 2]);
    vector<int> less;
    vector<int> pivotlist;
    vector<int> gt;
    vector<int> ret;

    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] < pivot) less.push_back(arr[i]);
        else if(arr[i] > pivot) gt.push_back(arr[i]);
        else pivotlist.push_back(arr[i]);
    }

    cout << pivot << '\n';
    print_vector(less);
    print_vector(gt);

    less = quicksort(less);
    gt = quicksort(gt);
    return merge(less, pivotlist, gt);
}

int main() {
    vector<int> arr = {5, 9, 3, 2, 7, 1, 4, 6, 8};
    vector<int> sorted_arr = quicksort(arr);
}