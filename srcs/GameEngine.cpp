//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "GameEngine.hpp"

namespace Zappy {
	GameEngine::GameEngine(): Server(), t_(4), current_frame_(0) {
		set_game_delay();
		updated_at_ms_ = (created_at_.tv_sec * 1000) + (created_at_.tv_usec / 1000);
	}

	void GameEngine::set_game_delay() {
		/**
		 * Probably should limit t_ to be a maximum amount of 1000
		 * Else it can be problematic, also 1000 would be a frame of 1ms
		 * Which means 1000 iterations in 1 second, which seams so many
		 **/
		frame_delay_ = 1000 / t_;
	}

	void GameEngine::start(int * sig) {
		std::cout << get_config().get("welcome_to_server") << std::endl;
		write(1, "$> ", 3);
		while (*sig && check_health(ServerHealth::Running))
			update();
	}

	inline unsigned int GameEngine::frame() {return current_frame_;}

	inline bool GameEngine::is_time_to_update() {
		ssize_t now_ms; 
		struct timeval tv;

		if(gettimeofday(&tv, NULL) == -1) {
			perror("gettimeofday()");
			exit(EXIT_FAILURE);
		}
		now_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (now_ms - updated_at_ms_ >= frame_delay_)
			return true;
		return false;
	}

	inline void GameEngine::update_time() {
		updated_at_ms_ += frame_delay_;
	}

	// The game engine is running an underlying Server, who is also in charge of all managing the fds
	void GameEngine::update() {
		Server::update();
		if (is_time_to_update()) {
			current_frame_++;
			update_time();
		}
	}

	GameEngine::~GameEngine() {
		if (DEBUG)
			std::cout << "GameEngine destroyed | Total: [" << current_frame_ << "]frames" << std::endl;
	}

	std::ostream& operator<<(std::ostream& s, const GameEngine& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}