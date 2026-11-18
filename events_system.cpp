#include "include/maps.h"
#include "include/player_vars.h"

int check_event(int event_id) {
    if (event_id > 200) {
        return 0;           // person
    }
    else {
        return 1;           // chest
    }
}

bool check_opened_chest(int chest_id) {
    for (auto& chest : chests) {
        if (chest_id == chest.id) {
            return chest.is_open;
        }
    }
    return false;
}

int check_event_present(int map_id, int p_x, int p_y) {
    // insert map_id
    return sample_map[p_x][p_y];
}

std::string get_chest_item(int chest_id) {
    for (auto& chest : chests) {
        if (chest_id == chest.id && !chest.is_open) {
            chest.is_open = true;
            inventory.push_back(chest.loot);
            return chest.loot;
        }
    }
    return "Nothing";
}
