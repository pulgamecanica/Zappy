//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Resources/Inventory.hpp"

namespace Zappy {
	Inventory::Inventory() {
		int minerals_count = Mineral::TRANTORIAN_MINERALS.size();

		for (int i = 0; i < minerals_count; ++i) {
			resources_[i] = 0;
		}
	}

	Inventory::~Inventory() {
	}

	int Inventory::get_food() const {
		return food_;
	}

	void Inventory::take_food() {
		food_++;
	}

	void Inventory::take_resource(int mineral_index) {
		resources_[mineral_index]--;
	}

	void Inventory::add_food() {
		food_++;
	}

	void Inventory::add_resource(int mineral_index) {
		resources_[mineral_index]++;
	}

	const std::vector<int> Inventory::get_resources() const {
		std::vector<int> vec;

		for (std::map<Mineral, int>::const_iterator i = resources_.begin(); i != resources_.end(); ++i) {
				vec.push_back(i->second);
		}
		return vec;
	}

	std::ostream& operator<<(std::ostream& s, const Inventory& param) {
		const std::vector<int> res = param.get_resources();

		s << param.get_food();
		for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i) {
			s << " " << *i;
		}
		return (s);
	}
}
