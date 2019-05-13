#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Top-Down Approach

double *cache;

double take(vector<int> *promo_bags, vector<double> *promo_costs, int bags) {
    if(bags < 1) return 0.0f;
    if(cache[bags - 1] != -1) return cache[bags - 1];

    double min_cost = numeric_limits<double>::max();

    for(unsigned int i = 0; i < promo_bags->size(); i++) {
        min_cost = min(min_cost, promo_costs->at(i) + take(promo_bags, promo_costs, bags - promo_bags->at(i)));
    }

    cache[bags - 1] = min_cost;

    return min_cost;
}

// Bottom-up Approach

double take_bu(vector<int> *promo_bags, vector<double> *promo_costs, int bags) {
    vector<double> cache(bags);

    for(unsigned int i = 1; i <= bags; i++) {
        double min_cost = numeric_limits<double>::max();

        for(unsigned int j = 0; j < promo_bags->size(); j++) {
            int bags_tmp = i - promo_bags->at(j);
            
            if(bags_tmp < 1) {
                min_cost = min(min_cost, promo_costs->at(j));
            } else {
                min_cost = min(min_cost, promo_costs->at(j) + cache[bags_tmp - 1]);
            }
        }

        cache[i - 1] = min_cost;
    }

    return cache[bags - 1];
}

int main() {
    cout << fixed << setprecision(2);

    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        double base_price;
        int num_promos, queries;
        cin >> base_price >> num_promos;
        vector<int> promo_bags(num_promos + 1);
        vector<double> promo_costs(num_promos + 1);

        for(int j = 0; j < num_promos; j++) {
            int promo_bag;
            double promo_cost;
            cin >> promo_bag >> promo_cost;
            promo_bags[j] = promo_bag;
            promo_costs[j] = promo_cost;
        }

        promo_bags[num_promos] = 1;
        promo_costs[num_promos] = base_price;

        cin >> queries;

        for(int j = 0; j < queries; j++) {
            int query;
            cin >> query;
            cache = new double[query];
            fill(cache, cache + query, -1);
            cout << "Buy " << query << " for " << take_bu(&promo_bags, &promo_costs, query) << '\n';
            delete cache;
        }
    }   
}