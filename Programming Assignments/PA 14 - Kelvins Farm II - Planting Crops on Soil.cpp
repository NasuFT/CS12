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

class FarmCell {
private:
    Crop *crop;
    const CropDetails *details;
    bool tilled;
    int watered;
public:
    FarmCell() {
        crop = nullptr;
        details = nullptr;
        tilled = false;
        watered = 0;
    }

    ~FarmCell() {
        delete crop;
    }

    bool till() {
        if(tilled) return false;
        return tilled = true;
    }

    bool is_tilled() {
        return tilled;
    }

    bool is_untilled() {
        return !tilled;
    }

    bool plant(const CropDetails *details) {
        if(!tilled || crop != nullptr) return false;
        crop = new Crop(details);
        this->details = details;
        return true;
    }

    bool has_crop() {
        return crop != nullptr;
    }

    Crop *get_crop() {
        return crop;
    }

    bool clear() {
        if(crop != nullptr) {
            delete crop;
            crop = nullptr;
            details = nullptr;
            return true;
        }

        return false;
    }

    bool water() {
        return watered++ == 0; 
    }

    bool is_unwatered() {
        return watered == 0;
    }

    bool is_watered() {
        return watered == 1;
    }

    bool is_overwatered() {
        return watered > 1;
    }

    bool will_wilt() {
        return ((!crop->is_wilted() && watered == 0) || (!crop->is_wilted() && watered > 1)) ;
    }

    const CropDetails *harvest() {
        if(crop == nullptr) return nullptr;
        crop->harvest();
        return details;
    }

    bool can_harvest() {
        return (crop->is_harvestable() && !crop->was_harvested());
    }

    void end_day() {
        if(crop != nullptr && (watered == 0 || watered > 1)) {
            crop->wilt();
        } else {
            if(!crop->is_wilted() && watered == 1) {
                crop->grow();
            }
        }

        watered = 0;
    }
};

int main() {
    
}