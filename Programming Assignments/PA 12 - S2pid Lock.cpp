#include <iostream>

using namespace std;

class CombinationLock {
    private:
        int num_discs;
        int *code;
        bool state;
    public:
        CombinationLock(int num_discs, int *code) {
            this->num_discs = num_discs;
            this->code = new int[num_discs];

            for(int i = 0; i < num_discs; i++) {
                this->code[i] = code[i];
            }
        }

        int get_num_discs() {
            return num_discs;
        }

        void rotate(int i) {
            code[i] = ++code[i] % 10;
        }

        int view(int i) {
            return code[i];
        }

        bool unlock() {
            return state;
        }

        ~CombinationLock() {
            delete [] code;
        }
};

int* break_lock(CombinationLock *cl) {
    int disc = cl->get_num_discs();

    int *arr = new int[disc];

    for(int i = 0; i < disc; i++) {
        arr[i] = cl->view(i);
    }

    for(int i = 0; i < disc; i++) {
        for(int j = 0; j < 10; j++) {
            if(cl->unlock()) break;

            cl->rotate(i);

            if(arr[i] == cl->view(i)) {
                for(int k = i - 1; k >= 0; k--) {
                    cl->rotate(k);

                    if(arr[k] != cl->view(k)) {
                        i--;
                        break;
                    }
                }
            }
        }

        if(cl->unlock()) break;
    }

    for(int i = 0; i < disc; i++) {
        arr[i] = cl->view(i);
    }

    return arr;
}

int main() {
    return 0;
}