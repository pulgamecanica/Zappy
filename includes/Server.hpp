//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SERVER_HPP__
# define __SERVER_HPP__

extern "C" {
	#include <sys/time.h>
	#include <sys/socket.h>
	#include <sys/epoll.h>
	#include <netinet/in.h>
} 

#include <iostream>
#include <map>
#include <vector>

#include "Config.hpp"

// typedef class Player Player;
#include "Client.hpp"

namespace Zappy {

	// Implement enum to represent the server health
	// Booting
	// Running 
	// Error
	// End Of Life
	class GameEngine;

	enum ServerHealth
	{
		Booting,
		Running,
		EndOfLife
	};
	class Server {
		public:
			static constexpr std::string 	VERSION = "42.0";
			Server(const Server&) = delete;
			~Server();
			Server&													operator= (const Server&) = delete; // const for safety... not super nesessary
			const Config &									get_config() const; 
			int 														total_players() const; 
			int 														total_spectators() const;
			ssize_t													current_timestamp() const;
			const std::string								get_creation_date() const;
			void 														stop_server();
			void														set_config(const std::string lang_acronym);
			const std::vector<std::string>	get_list_of_supported_languages() const;
			const std::map<int, Client *> & get_clients() const;
		protected:
			Server(GameEngine *trantor, std::string toml_file, std::string default_lang, int players_port, int spectators_port);
			void									update();
			bool									check_health(enum ServerHealth check) const;
			ssize_t								created_at_ms_;
		private:
			// STATIC VALUES
			static constexpr int					MAX_EPOLL_EVENTS = 64;
			static constexpr int					BACKLOG = 10;
			static constexpr int					RECV_BUFFER = 1024;
			// CLASS FUNCTION MEMBERS
			bool							is_client(int fd);
			int								accept_client(int socket);
			bool							is_server_socket(int fd);
			bool							is_stdin(int fd);
			void							add_client(int socket, int fd);
			void							remove_client(int fd);
			void							handle_stdin(const std::string & cmd);
			void							handle_client(int fd, const std::string & cmd);
			const std::string	handle_client_input_or_disconnect(int fd);
			// CLASS PARAMS MEMBERS
			GameEngine 						*trantor_;
			const int							players_port_;
			const int 						spectators_port_;
			// const int							connection_timeout_; // Players will time out after X seconds, spectators never timeout
			int										players_socket_;
			int										spectators_socket_;
			int										epoll_fd_;
			sockaddr_in						players_sockaddr_; // man 7 ip to see sockaddr_in struct
			sockaddr_in						spectators_sockaddr_; // '' '' '' '' '' '' '' '' '' ''
			struct epoll_event		events_[MAX_EPOLL_EVENTS];
			std::map<int, Client *>	clients_;
			std::vector<int>			spectators_;
			std::vector<Config>		configs_;
			Config							* curr_config_;
			enum ServerHealth			health_;
			// std::map<int, Spectator> spectators_;
	};

	std::ostream&	operator<<(std::ostream&, const Server&);
}

#endif
