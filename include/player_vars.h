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

inline EquipType slot_to_equip_type(int slot) {
	switch (slot) {
		case 0:
			return EquipType::WEAPON;
			break;
		case 1:
			return EquipType::GUN;
			break;
		case 2:
			return EquipType::BULLET;
			break;
		case 3:
			return EquipType::HELMET;
			break;
		case 4:
			return EquipType::BODY;
			break;
		case 5:
			return EquipType::GLOVES;
			break;
		case 6:
			return EquipType::LEGS;
			break;
		default:
			return EquipType::NONE;
			break;
	}
}

inline std::vector<int> get_equippable_ids(int slot) {
	std::vector<int> list;
	EquipType target_type = slot_to_equip_type(slot);

	for (const auto& inv_slot : inventory) {
		Item item = get_item_by_id(inv_slot.item_id);
		if (item.type == ItemType::EQUIP && item.equip_type == target_type) {
			list.push_back(item.id);
		}
	}
	return list;
}


inline void equip_item_on_char(int char_idx, int slot, int new_item_id) {
	Character& c = party[char_idx];
	std::string old_name = "None";

	switch (slot) {
		case 0: 
			old_name = c.get_weapon();
			break;
		case 1:
			old_name = c.get_gun();
			break;
		case 2:
			old_name = c.get_bullet();
			break;
		case 3:
			old_name = c.get_head();
			break;
		case 4:
			old_name = c.get_body();
			break;
		case 5:
			old_name = c.get_gloves();
			break;
		case 6:
			old_name = c.get_legs();
			break;
	}

	if (old_name != "None") {
		Item old_item = get_item_by_name(old_name);
		if (old_item.id != 0) {
			c.set_attack(c.get_attack() - old_item.attack_boost);
			c.set_defense(c.get_defense() - old_item.defense_boost);
			c.set_magic_attack(c.get_magic_attack() - old_item.magic_attack_boost);
            c.set_magic_resistance(c.get_magic_resistance() - old_item.magic_resistance_boost);
            c.set_speed(c.get_speed() - old_item.speed_boost);
            c.set_luck(c.get_luck() - old_item.luck_boost);
            add_item(old_item.id, 1);
		}
	}

	std::string new_name = "None";
	if (new_item_id != 0) {
		Item new_item = get_item_by_id(new_item_id);
		new_name = new_item.name;
		c.set_attack(c.get_attack() + new_item.attack_boost);
        c.set_defense(c.get_defense() + new_item.defense_boost);
        c.set_magic_attack(c.get_magic_attack() + new_item.magic_attack_boost);
        c.set_magic_resistance(c.get_magic_resistance() + new_item.magic_resistance_boost);
        c.set_speed(c.get_speed() + new_item.speed_boost);
        c.set_luck(c.get_luck() + new_item.luck_boost);
        use_item(new_item_id);
	}

	switch (slot) {
		case 0:
			c.set_weapon(new_name);
			break;
		case 1:
			c.set_gun(new_name);
			break;
		case 2:
			c.set_bullet(new_name);
			break;
		case 3:
			c.set_head(new_name);
			break;
		case 4:
			c.set_body(new_name);
			break;
		case 5:
			c.set_gloves(new_name);
			break;
		case 6:
			c.set_legs(new_name);
			break;
	}
}
