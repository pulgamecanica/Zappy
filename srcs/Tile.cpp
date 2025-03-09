//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <math.h>
}

#include <sstream>
#include <map>

#include "Zappy.inc"

#include "Tile.hpp"

namespace Zappy {
	Tile::Tile(const Point& pos): pos_(pos) {
		// std::cout << "Constructed Tile from (pos) [" << pos_ << "]" << std::endl;
		for (int i = 0; i < 7; ++i)
			resources_[(Resource::ResourceType)i] = 0;
		for (int i = 0; i < rand() % 10; ++i) {
			add_new_resource(Resource::get_random_resource());
		}
	}

	void Tile::add_new_resource(Resource res) {
		resources_[res.get_resource_type()]++;
	}

	// Tile::Tile(const Tile& param) {
	// 	// TODO (copy constructor)
	// 	(void)param;
	// }

	Tile::~Tile() {
		// std::cout << "Tile" << " destroyed" << std::endl;
		// TODO (destructor)
	}


	/**
	 *****************
	 *   0 1 2 3 4   *
	 * 0 a . . . e 0 *
	 * 1 . g . . . 1 *
	 * 2 . . m n . 2 *
	 * 3 . . . s t 3 *
	 * 4 u v . . . 4 *
	 *   0 1 2 3 4   *
	 *****************
	 * In the 5x5 map presented above we can `identify`
	 * each tile by using coordinates, their value, or their index
	 * It goes as follows:
	 * | Value | Coordinate | Index | coord -> index                       | index -> coord                                                       |
	 * | ----- | ---------- | ----- | ------------------------------------ | -------------------------------------------------------------------- |
	 * |  'a'  |   [0, 0]   |   0   | ((y * width) + x) = (0 * 5) + 0 = 0  | [y = (i / width), x = (i % width)] = [y = 0 / 5, x = 0 % 5] = [0, 0] |
	 * |  'b'  |   [1, 0]   |   1   | ((y * width) + x) = (0 * 5) + 1 = 1  | [y = (i / width), x = (i % width)] = [y = 0 / 5, x = 1 % 5] = [0, 1] |
	 * |  'c'  |   [2, 0]   |   2   | ((y * width) + x) = (0 * 5) + 2 = 2  | [y = (i / width), x = (i % width)] = [y = 0 / 5, x = 2 % 5] = [0, 2] |
	 * |  'd'  |   [3, 0]   |   3   | ((y * width) + x) = (0 * 5) + 3 = 3  | [y = (i / width), x = (i % width)] = [y = 0 / 5, x = 3 % 5] = [0, 3] |
	 * |  'e'  |   [4, 0]   |   4   | ((y * width) + x) = (0 * 5) + 4 = 4  | [y = (i / width), x = (i % width)] = [y = 0 / 5, x = 4 % 5] = [0, 4] |
	 * |  'f'  |   [0, 1]   |   5   | ((y * width) + x) = (1 * 5) + 0 = 5  | [y = (i / width), x = (i % width)] = [y = 1 / 5, x = 0 % 5] = [1, 0] |
	 * |  'g'  |   [1, 1]   |   6   | ((y * width) + x) = (1 * 5) + 1 = 6  | [y = (i / width), x = (i % width)] = [y = 1 / 5, x = 1 % 5] = [1, 1] |
	 * |  'h'  |   [2, 1]   |   7   | ((y * width) + x) = (1 * 5) + 2 = 7  | [y = (i / width), x = (i % width)] = [y = 1 / 5, x = 2 % 5] = [1, 2] |
	 * |  'i'  |   [3, 1]   |   8   | ((y * width) + x) = (1 * 5) + 3 = 8  | [y = (i / width), x = (i % width)] = [y = 1 / 5, x = 3 % 5] = [1, 3] |
	 * |  'j'  |   [4, 1]   |   9   | ((y * width) + x) = (1 * 5) + 4 = 9  | [y = (i / width), x = (i % width)] = [y = 1 / 5, x = 4 % 5] = [1, 4] |
	 * |  'k'  |   [0, 2]   |   10  | ((y * width) + x) = (2 * 5) + 0 = 10 | [y = (i / width), x = (i % width)] = [y = 2 / 5, x = 0 % 5] = [2, 0] |
	 * |  'l'  |   [1, 2]   |   11  | ((y * width) + x) = (2 * 5) + 1 = 11 | [y = (i / width), x = (i % width)] = [y = 2 / 5, x = 1 % 5] = [2, 1] |
	 * |  'm'  |   [2, 2]   |   12  | ((y * width) + x) = (2 * 5) + 2 = 12 | [y = (i / width), x = (i % width)] = [y = 2 / 5, x = 2 % 5] = [2, 2] |
	 * |  'n'  |   [3, 2]   |   13  | ((y * width) + x) = (2 * 5) + 3 = 13 | [y = (i / width), x = (i % width)] = [y = 2 / 5, x = 3 % 5] = [2, 3] |
	 * |  'o'  |   [4, 2]   |   14  | ((y * width) + x) = (2 * 5) + 4 = 14 | [y = (i / width), x = (i % width)] = [y = 2 / 5, x = 4 % 5] = [2, 4] |
	 * |  'p'  |   [0, 3]   |   15  | ((y * width) + x) = (3 * 5) + 0 = 15 | [y = (i / width), x = (i % width)] = [y = 3 / 5, x = 0 % 5] = [3, 0] |
	 * |  'q'  |   [1, 3]   |   16  | ((y * width) + x) = (3 * 5) + 1 = 16 | [y = (i / width), x = (i % width)] = [y = 3 / 5, x = 1 % 5] = [3, 1] |
	 * |  'r'  |   [2, 3]   |   17  | ((y * width) + x) = (3 * 5) + 2 = 17 | [y = (i / width), x = (i % width)] = [y = 3 / 5, x = 2 % 5] = [3, 2] |
	 * |  's'  |   [3, 3]   |   18  | ((y * width) + x) = (3 * 5) + 3 = 18 | [y = (i / width), x = (i % width)] = [y = 3 / 5, x = 3 % 5] = [3, 3] |
	 * |  't'  |   [4, 3]   |   19  | ((y * width) + x) = (3 * 5) + 4 = 19 | [y = (i / width), x = (i % width)] = [y = 3 / 5, x = 4 % 5] = [3, 4] |
	 * |  'u'  |   [0, 4]   |   20  | ((y * width) + x) = (4 * 5) + 0 = 20 | [y = (i / width), x = (i % width)] = [y = 4 / 5, x = 0 % 5] = [4, 0] |
	 * |  'v'  |   [1, 4]   |   21  | ((y * width) + x) = (4 * 5) + 1 = 21 | [y = (i / width), x = (i % width)] = [y = 4 / 5, x = 1 % 5] = [4, 1] |
	 * |  'w'  |   [2, 4]   |   22  | ((y * width) + x) = (4 * 5) + 2 = 22 | [y = (i / width), x = (i % width)] = [y = 4 / 5, x = 2 % 5] = [4, 2] |
	 * |  'x'  |   [3, 4]   |   23  | ((y * width) + x) = (4 * 5) + 3 = 23 | [y = (i / width), x = (i % width)] = [y = 4 / 5, x = 3 % 5] = [4, 3] |
	 * |  'y'  |   [4, 4]   |   24  | ((y * width) + x) = (4 * 5) + 4 = 24 | [y = (i / width), x = (i % width)] = [y = 4 / 5, x = 4 % 5] = [4, 4] |
	 **/
	inline int Tile::get_index(int width) const {
		return ((pos_.y() * width) + pos_.x());
	}

	bool	Tile::operator==(const Point& p) const {
		return (pos_.y() == p.y() && pos_.x() && p.x());
	}


	bool	Tile::operator== (const Tile& t) const {
		return (pos_.y() == t.pos_.y() && pos_.x() && t.pos_.x());
	}

	bool	Tile::operator< (const Tile& t) const {
		if (pos_.y() == t.pos_.y())
			return (pos_.x() < t.pos_.x());
		return (pos_.y() < t.pos_.y());

	}

	bool	Tile::operator> (const Tile& t) const {
		if (pos_.y() == t.pos_.y())
			return (pos_.x() > t.pos_.x());
		return (pos_.y() > t.pos_.y());
	}

	
	const Point & Tile::get_pos() const {
		return (pos_);
	}

	Tile::operator std::string() const {
		std::stringstream ss;

		ss << std::string(pos_);
		for (std::map<Resource::ResourceType, int>::const_iterator i = resources_.begin(); i != resources_.end(); ++i) {
			ss << " " << i->second;
		}
    return ss.str();
	}

	bool Tile::has_resources() const {
		return resources_.size() > 0;
	}

	std::ostream& operator<<(std::ostream& s, const Tile& tile) {
		s << tile.get_pos();
		return (s);
	}

}
