//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "GameEngine.hpp"

namespace Zappy {
	GameEngine::GameEngine(): Server(), t_(100), current_frame_(0) {
		frame_delay_ = 1000 / t_;
		updated_at_ms_ = (created_at_.tv_sec * 1000) + (created_at_.tv_usec / 1000);
	}

	void GameEngine::start(int * sig) {
		std::cout << get_config().get("welcome_to_server") << std::endl;
		write(1, "$> ", 3);
		while (*sig && check_health(ServerHealth::Running))
			update();
		std::cout << "Finished[" << current_frame_ << "]" << std::endl; 
	}

	inline unsigned int GameEngine::frame() {return current_frame_;}

	inline bool GameEngine::is_time_to_update() {
		ssize_t now_ms;//, now_s, updated_at_s; 
		struct timeval tv;

		if(gettimeofday(&tv, NULL) == -1) {
			perror("gettimeofday()");
			exit(EXIT_FAILURE);
		}
		now_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		// now_s = now_ms / 1000;
		// updated_at_s = updated_at_ms_ / 1000;
		// std::cout << "\033[H\033[2J" << std::endl
		// 	 << "Frame[" << current_frame_ << "] | Frame delay: " << frame_delay_ << " | Outdated(ms): " << (now_ms - updated_at_ms_) << std::endl
		// 	 << "Now:" << ctime(&now_s) << "Last Update:" << ctime(&updated_at_s);
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
			// std::cout << "Update [" << GREEN << current_frame_ << ENDC << "]" << std::endl;
			current_frame_++;
			update_time();
		}
	}

	GameEngine::~GameEngine() {
		// std::cout << "GameEngine" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	std::ostream& operator<<(std::ostream& s, const GameEngine& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}