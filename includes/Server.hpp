//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SERVER_HPP__
# define __SERVER_HPP__

extern "C" {
	#include <sys/socket.h>
	#include <sys/epoll.h>
	#include <netinet/in.h>
} 

#include <iostream>
#include <map>

#include "Player.hpp"
#include "Spectator.hpp"

namespace Zappy {
	class Server {
		public:
			Server(int players_port = 4242, int spectators_port = 2121);
			Server(const Server&) = delete;
			~Server();
			Server&	operator= (const Server&) = delete; // const for safety... not super nesessary
			void run(int * sig);
		private:
			// STATIC VALUES
			static constexpr std::string 	VERSION = "42.0";
			static constexpr int					MAX_EPOLL_EVENTS = 64;
			static constexpr int					BACKLOG = 10;
			// CLASS MEMBERS
			bool	is_fd_spectator(int fd);
			bool	is_fd_client(int fd);
			int		accept_client(int socket);
			bool	is_server_socket(int fd);
			void	add_client(int socket, int fd);
			const int						players_port_;
			const int 					spectators_port_;
			int									players_socket_;
			int									spectators_socket_;
			int									epoll_fd_;
			sockaddr_in					players_sockaddr_; // man 7 ip to see sockaddr_in struct
			sockaddr_in					spectators_sockaddr_; // '' '' '' '' '' '' '' '' '' ''
			struct epoll_event	events_[MAX_EPOLL_EVENTS];
			std::map<int, Player> players_;
			std::map<int, Spectator> spectators_;
	};

	std::ostream&	operator<<(std::ostream&, const Server&);
}

#endif
