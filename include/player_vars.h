#pragma once
#include <vector>
#include <string>
#include <items.h>

struct InventorySlot {
    int item_id;
    int quantity;
};

inline std::vector<InventorySlot> inventory;

inline void add_item(int item_id, int qty) {
    for (auto& slot : inventory) {
        if (slot.item_id == item_id) {
            slot.quantity += qty;
            return;
        }
    }
    inventory.push_back({item_id, qty});
}
