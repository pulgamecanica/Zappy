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

#include "Player.hpp"
#include "Config.hpp"

namespace Zappy {
	class Server {
		public:
			static constexpr std::string 	VERSION = "42.0";
			Server(const char * toml_file = "conf.toml", const char * default_lang = "en", int players_port = 4242, int spectators_port = 2121);
			Server(const Server&) = delete;
			~Server();
			Server&	operator= (const Server&) = delete; // const for safety... not super nesessary
			void run(int * sig);
			const Config & get_config() const; 
			int total_players() const; 
			int total_spectators() const;
			ssize_t current_timestamp() const;
			const std::string get_creation_date() const;
		private:
			// STATIC VALUES
			static constexpr int					MAX_EPOLL_EVENTS = 64;
			static constexpr int					BACKLOG = 10;
			static constexpr int					RECV_BUFFER = 1024;
			// CLASS FUNCTION MEMBERS
			bool							is_fd_player(int fd);
			int								accept_client(int socket);
			bool							is_server_socket(int fd);
			void							add_client(int socket, int fd);
			void							remove_client(int fd);
			const std::string	handle_client_input_or_disconnect(int fd);
			void							set_config(const std::string lang_acronym);
			// CLASS PARAMS MEMBERS
			const int							players_port_;
			const int 						spectators_port_;
			int										players_socket_;
			int										spectators_socket_;
			int										epoll_fd_;
			sockaddr_in						players_sockaddr_; // man 7 ip to see sockaddr_in struct
			sockaddr_in						spectators_sockaddr_; // '' '' '' '' '' '' '' '' '' ''
			struct epoll_event		events_[MAX_EPOLL_EVENTS];
			std::map<int, Player>	players_;
			std::vector<int>			spectators_;
			std::vector<Config>		configs_;
			Config							* curr_config_;
			struct timeval				created_at_;
			// std::map<int, Spectator> spectators_;
	};

	std::ostream&	operator<<(std::ostream&, const Server&);
}

#endif
