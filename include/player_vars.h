#pragma once
#include <vector>
#include <string>
#include <items.h>
#include <character.h>
struct InventorySlot {
    int item_id;
    int quantity;
};

inline std::vector<InventorySlot> inventory;
inline std::vector<Character> party;
inline void add_item(int item_id, int qty) {
    for (auto& slot : inventory) {
        if (slot.item_id == item_id) {
            slot.quantity += qty;
            return;
        }
    }
    inventory.push_back({item_id, qty});
}

inline void use_item(int id) {
    for (int i = 0; i < (int)inventory.size(); i++) {
        if (inventory[i].item_id == id) {
            if (inventory[i].quantity > 1) {
                inventory[i].quantity--;
            } else {
                inventory.erase(inventory.begin() + i);
            }
            return;
        }
    }
}
