#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_stuff(int max_depth, vector<int> *arr) {
    cout << "max_depth: " << max_depth << "; ";
    cout << "array: ";

    for(int i = 0; i < arr->size(); i++) {
        if(i != 0) cout << ',';
        cout << arr->at(i);
    }

    cout << '\n';
}

int bucket_sort(vector<int> *arr, int k, int depth = 0) {
    if(arr->size() > 1) {
        vector<vector<int>> buckets(k + 1);
        int minimum = *min_element(arr->begin(), arr->end());
        int maximum = *max_element(arr->begin(), arr->end());
        int element_range = maximum - minimum;
        int max_depth = depth;
        if(element_range == 0) {
            return max_depth;
        }

        for(int i = 0; i < arr->size(); i++) {
            int index = int((float(arr->at(i) - minimum) / float(element_range)) * k);
            buckets[index].push_back(arr->at(i));
        }

        for(int i = 0; i < buckets.size(); i++) {
            int depth_tmp = bucket_sort(&buckets[i], k, depth + 1);
            if(max_depth < depth_tmp) max_depth = depth_tmp;
        }

        int index = 0;
        for(int i = 0; i < buckets.size(); i++) {
            for(int j = 0; j < buckets[i].size(); j++) {
                *(arr->begin() + index++) = buckets[i][j];
            }
        }

        return max_depth;
    }

    return depth;
}

int main() {
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        vector<int> arr;

        for(int i = 0; i < n; i++) {
            int n;
            cin >> n;
            arr.push_back(n);
        }

        int max_depth = bucket_sort(&arr, k);

        print_stuff(max_depth, &arr);
    }

    return 0;
}