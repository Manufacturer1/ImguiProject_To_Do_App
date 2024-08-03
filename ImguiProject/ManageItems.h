#pragma once

#include "UseImgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <map>


using namespace std;


 struct Item {
	string name;
	string time_posted;
	string selected_priority;
	bool checked = false;
};


class ManageItems {
private:

	map<string, int> priority_map = {
	   {"High", 3},
	   {"Medium", 2},
	   {"Low", 1}
	};
	vector<Item> item_list;


private:
	

	string GetCurrentTime() {
		auto now = chrono::system_clock::now();
		auto now_time_t = chrono::system_clock::to_time_t(now);

		stringstream ss;

		ss << put_time(localtime(&now_time_t), "%d.%m.%Y %H:%M");
		return ss.str();

	}
	string getPriorityName(int value) {
		for (const auto& pair : priority_map) {
			if (pair.second == value) {
				return pair.first;
			}
		}
		return "High"; 
	}

public:

	ManageItems() = default;



	void sort_items_by_priority() {
		auto compare_priority = [this](const Item& a, const Item& b) {
			return priority_map[a.selected_priority] > priority_map[b.selected_priority];
			};

		sort(item_list.begin(), item_list.end(), compare_priority);
	}
	
	void changePriority(Item& item) {
		auto it = find_if(item_list.begin(), item_list.end(), [&item](const Item& i) {return i.name == item.name;});
		if (it != item_list.end()) {
			int current_value_map = priority_map[it->selected_priority];
			int new_pr_value = (current_value_map % 3) + 1;
			it->selected_priority = getPriorityName(new_pr_value);
		}
		sort_items_by_priority();
		
	}

	Item find_item(Item& item) {
		auto it = find_if(item_list.begin(), item_list.end(), [&item](const Item& i) {return i.name == item.name;});
		if (it != item_list.end()) {
			return *it;
		}
	}
	void add_new_item(string& text) {

		Item item;
		item.name = text;
		item.time_posted = GetCurrentTime();
		item_list.push_back(item);

	}

	void updateItemCheckedState(const std::string& itemName, bool checked) {
		for (auto& item : item_list) {
			if (item.name == itemName) {
				item.checked = checked;
				break;
			}
		}
	}


	bool remove_item_from_list(const string& text) {
		auto it = remove_if(item_list.begin(), item_list.end(), [&text](const Item& i) { return i.name == text; });
		if (it != item_list.end()) {
			item_list.erase(it, item_list.end());
			return true;
		}
		return false;
	}
	const vector<Item>& getItems() const {
		return item_list;
	}
	
	void setPriority(string name,string priority) {

		auto it = find_if(item_list.begin(), item_list.end(), [&name](const Item& i) { return i.name == name; });
		if (it != item_list.end()) {
			it->selected_priority = priority;
		}
		
	}

};