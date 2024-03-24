//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <math.h>
}

#include "Resource.hpp"

namespace Zappy {

	enum Resource::ResourceType Resource::get_random_resource() {
		return ((Resource::ResourceType)(rand() % 7));
	}

 int Resource::get_next_id() {
    static int global_id_count = 1;

    return global_id_count++;
  }

	Resource::Resource(enum ResourceType type): id_(get_next_id()), type_(type) {
	}

	Resource::~Resource() {
		// std::cout << "Resource" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	enum Resource::ResourceType	Resource::get_resource_type() const {
		return (type_);
	}

	bool	Resource::check_resource_type(enum ResourceType type) const {
		return (type == type_);
	}

	std::ostream& operator<<(std::ostream& s, const Resource& res) {
		s << Resource::RESOURCE_TYPES_STR[res.get_resource_type()];
		return (s);
	}

}