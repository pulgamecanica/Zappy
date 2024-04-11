//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __INVENTORY_HPP__
# define __INVENTORY_HPP__

#include <iostream>
#include <vector>
#include <map>

#include "Resources/Mineral.hpp"

namespace Zappy {
	class Inventory {
		public:
			Inventory();
			Inventory(const Inventory&) = default;
			Inventory&	operator= (const Inventory&) = default;
			~Inventory();
			int get_food() const;
			const std::vector<int> get_resources() const;
			
			void take_food();
			void take_resource(int mineral_index);
			void add_food();
			void add_resource(int mineral_index);
		private:
			int food_;
			std::map<Mineral, int> resources_;
	};

	std::ostream&	operator<<(std::ostream&, const Inventory&);
}
#endif

