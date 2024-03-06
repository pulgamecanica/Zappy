//***************************//
//*Template by pulgamecanica*//
//***************************//
	
extern "C" {
	#include <signal.h>
	#include <string.h>
	#include <fcntl.h>
}

#include "Zappy.inc"
#include "Server.hpp"

int g_stop_sig = 42;

static void sighandler(int signal) {
	std::cout << "Signal Received: [" << RED << signal << ENDC ":" << BLUE << strsignal(signal) << ENDC << "]" << std::endl;
	g_stop_sig = 0;
}

static void setup_signals() {
	struct sigaction sigIntHandler;
	// SETUP SIGNALE
	sigIntHandler.sa_handler = sighandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGTERM, &sigIntHandler, NULL);
	sigaction(SIGSTOP, &sigIntHandler, NULL);
	sigaction(SIGINT, &sigIntHandler, NULL);
	sigaction(SIGKILL, &sigIntHandler, NULL);
	sigaction(SIGQUIT, &sigIntHandler, NULL);
}

void setnonblocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 01) {
		perror("fcntl()");
		exit(EXIT_FAILURE);		
	}
}

int	main(void)
{
	Zappy::Server s;
	
	setup_signals();
	try {
		s.run(&g_stop_sig);
	} catch (std::exception &e) {
		std::cerr << RED << e.what() << ENDC << std::endl;
	}
	std::cout << YELLOW << "Thank you for using the " << GREEN "Zappy Server" << ENDC << " :)" << std::endl;
	return (0);
}
