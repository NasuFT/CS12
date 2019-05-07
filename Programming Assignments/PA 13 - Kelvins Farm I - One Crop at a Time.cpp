#include <iostream>
#include <string>

using namespace std;

struct CropDetails {
    string name;
    int selling_price;
    int days_grow;
    int days_regrow;
};

class Crop {
    bool wilted;
    bool harvested;
    bool flag;
    int days;

    const CropDetails *crop;

    public:
        Crop(const CropDetails *details) {
            crop = details;
            wilted = false;
            harvested = false;
            flag = false;
            days = details->days_grow;
        }
        
        void wilt() {
            wilted = true;
        }

        bool is_harvestable() {
            return days < 1 && !wilted && !harvested;
        }

        bool harvest() {
            if(!is_harvestable()) return false;

            harvested = true;
            flag = true;
            if(crop->days_regrow > 0) days = crop->days_regrow;

            return true;
        }        

        bool was_harvested() {            
            return flag && harvested;
        }

        bool can_regrow() {
            return crop->days_regrow > 0;
        }

        bool is_growing() {
            return days > 0 && !wilted;
        }

        bool is_wilted() {
            return wilted;
        }

        void grow() {
            if(wilted || days < 1) return;
            days--;
            harvested = false;
            if(crop->days_regrow > 0 && !wilted) flag = false;
        }
};

int main() {
    CropDetails details;
    details.days_grow = 2;
    details.days_regrow = 1;
    details.name = string("LMAO");
    details.selling_price = 19;

    Crop crop(&details);

    crop.grow();
    cout << crop.is_harvestable() << endl;
    crop.grow();
    cout << crop.is_harvestable() << endl;
    cout << crop.harvest() << endl;
    cout << crop.was_harvested() << endl;

    return 0;
}