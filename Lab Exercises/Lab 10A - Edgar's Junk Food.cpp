#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Top-Down Approach

int *cache;

float take(float base_price, vector<int> *promo_bags, vector<float> *promo_cost, int bags) {
    if(bags < 1) return 0.0f;
    if(cache[bags - 1] != -1) return cache[bags - 1];

    float min_cost = numeric_limits<float>::max();

    for(unsigned int i = 0; i < promo_bags->size(); i++) {
        min_cost = min(min_cost, promo_cost->at(i) + take(base_price, promo_bags, promo_cost, bags - promo_bags->at(i)));
    }

    cache[bags - 1] = min_cost;

    return min_cost;
}

// Failed Bottom-up Approach

// float take(float base_price, vector<int> promo_bags, vector<float> promo_cost, int bags) {
//     vector<float> cache(bags);
//     fill(cache.begin(), cache.end(), -1);

//     int max_promo_bags = *max_element(promo_bags.begin(), promo_bags.end());
//     float min_price = *min_element(promo_cost.begin(), promo_cost.end());

//     for(int i = 1; i <= bags; i++) {
//         if(base_price * i < min_price ) {
//             cache[i - 1] = base_price * i;
//             continue;
//         }

//         float min_cost = base_price * i;

//         for(unsigned int j = 0; j < promo_bags.size(); j++) {
//             if(i > max_promo_bags) {
//                 min_cost = min(min_cost, promo_cost[j] + cache[i - promo_bags[j]]);
//             } else {
                
//             }
//         }

//         if(i > max_promo_bags) {
//             for(unsigned int j = 0; j < promo_bags.size(); j++) {
//                 min_cost = min(min_cost, promo_cost[j] + cache[i - promo_bags[j]]);
//             }
//         } else {
            
//         }

        

//         cache[i - 1] = min_cost;
//     }

//     return cache[bags - 1];
// }

int main() {
    cout << fixed << setprecision(2);

    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        float u;
        int n, q;
        cin >> u >> n;
        vector<int> i(n);
        vector<float> c(n);

        for(int j = 0; j < n; j++) {
            int ii;
            float ic;
            cin >> ii >> ic;
            i[j] = ii;
            c[j] = ic;
        }

        i.push_back(1);
        c.push_back(u);

        cin >> q;

        for(int j = 0; j < q; j++) {
            int a;
            cin >> a;
            cache = new int[a];
            fill(cache, cache + a, -1);
            cout << "Buy " << a << " for " << take(u, &i, &c, a) << '\n';
            delete cache;
        }
    }   
}