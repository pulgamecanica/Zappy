//***************************//
//*Template by pulgamecanica*//
//***************************//
	
extern "C" {
	#include <signal.h>
	#include <string.h>
	#include <fcntl.h>
}

#include <toml++/toml.hpp>

#include "Zappy.inc"
#include "GameEngine.hpp"

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
	// Using en language as a default, can be changed by using parameters
	// main parameters:
	// --default-language=<name> // default en
	// --toml-file=<path> // default conf.toml
	// --players-port=0000 // default 4242
	// --viewers-port=0000 // default 2121
	setup_signals();
	try {
		Zappy::GameEngine trantor;
		trantor.start(&g_stop_sig);
		// Zappy::Server s;
	} catch (const toml::parse_error& err) {
    std::cerr
        << "Error parsing file '" << *err.source().path
        << "':\n" << RED << err.description() << ENDC
        << "\n\t(" << err.source().begin << ")\n";
    return (1);
	} catch (std::exception &e) {
		std::cerr << RED << e.what() << ENDC << std::endl;
		return (1);
	}
	std::cout << YELLOW << "Thank you for using the " << GREEN "Zappy Server" << ENDC << " :)" << std::endl;
	return (0);
}
