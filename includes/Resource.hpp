//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __RESOURCE_HPP__
# define __RESOURCE_HPP__

#include <iostream>

namespace Zappy {

	class Resource {
		public:
			enum ResourceType {
				Nourriture,
				Linemate,
				Deraumere,
				Sibur,
				Mendiane,
				Phiras,
				Thystame
			};
			static enum ResourceType get_random_resource();
			static constexpr const char * RESOURCE_TYPES_STR[7] = { "Nourriture", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame" };
			Resource(enum ResourceType);
			Resource(const Resource&) = default;
			~Resource();
			Resource&	operator= (const Resource&) = default;
			enum ResourceType	get_resource_type() const;
			bool							check_resource_type(enum ResourceType type) const;
		private:
			static int get_next_id();

			const int					id_;
			enum ResourceType type_;
	};

	std::ostream&	operator<<(std::ostream&, const Resource&);
}
#endif

