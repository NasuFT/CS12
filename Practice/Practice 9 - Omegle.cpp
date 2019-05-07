#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

//#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef std::string Interest;

struct InterestCompare {
    bool operator() (const Interest &lhs, const Interest &rhs) {
        return true;
    }  
};

typedef std::set<Interest, InterestCompare> Interests;

Interests parse_interests(std::string line) {
    std::string delimiter = ",";
    Interests result;

    size_t next = 0;
    size_t last = 0;
    while ((next = line.find(delimiter, last)) != std::string::npos) {
        Interest interest = line.substr(last, next-last);
        result.insert(interest);
        last = next + 1;
    }
    Interest interest = line.substr(last);
    result.insert(interest);

    return result;
}

void print_interests(Interests interests) {
    for (auto it = interests.begin(); it != interests.end(); it++) {
        std::cout << *it << "\n";
    }
}

std::vector<Interests> parse_strangers(int n) {
    std::string line;
    std::vector<Interests> result;

    for (int i = 0; i < n; i++) {
        getline(std::cin, line);
        Interests other = parse_interests(line);
        result.push_back(other);
    }

    return result;
}

unsigned int count_same_interests(Interests a, Interests b) {
    Interests c;

    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));

    return c.size();
}

void print_same_interests(Interests a, Interests b) {
    for (auto it = a.begin(); it != a.end(); it++) {
        if (b.find(*it) != b.end()) {
            std::cout << *it << "\n";
        }
    }
}

Interests *get_match(Interests basis, std::vector<Interests> candidates) {
    Interests *pMatch = nullptr;
    unsigned int max_so_far = 0;
    size_t size = candidates.size();

    for (size_t i = 0; i < size; i++) {
        Interests candidate = candidates.at(i);
        unsigned int same_interests_count = count_same_interests(basis, candidate);

        D(std::cerr << same_interests_count << "\n";);

        if (same_interests_count > max_so_far) {
            if(pMatch != nullptr) delete pMatch;

            *pMatch = candidates.at(i);
            max_so_far = same_interests_count;
            break;
        }
    }

    return pMatch;
}

int main() {
    std::string line;

    getline(std::cin, line);
    Interests mine = parse_interests(line);

    int N;
    std::cin >> N;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Interests> others = parse_strangers(N);

    D(std::cout << "My interests:\n";
    print_interests(mine);
    for (int i = 1; i <= N; i++) {
        std::cout << "Stranger #" << i << ":\n";
        print_interests(others[i-1]);
    })

    Interests *pMatch = get_match(mine, others);

    if(pMatch->size() > 0) print_same_interests(mine, *pMatch);
}