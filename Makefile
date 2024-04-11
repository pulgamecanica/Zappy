# Makefile created automatically from script\n
# C++ Zappy [Thu Feb 15 07:45:39 PM CET 2024]\n
#MAKEFLAGS += --silent  # Silence makefile [Commented by default]\n
NAME  = Zappy

.RECIPEPREFIX = >

SRC = $(wildcard srcs/*.cpp)

# Add Player Commands
SRC += srcs/Commands/PlayerClientCommands/Advance.cpp \
  srcs/Commands/PlayerClientCommands/Join.cpp \
  srcs/Commands/PlayerClientCommands/Right.cpp \
  srcs/Commands/PlayerClientCommands/Left.cpp \

# Add Spectator Commands
SRC += srcs/Commands/SpectatorClientCommands/MapSize.cpp \
  srcs/Commands/SpectatorClientCommands/BoxContentTile.cpp \
  srcs/Commands/SpectatorClientCommands/MapContentTile.cpp \
  srcs/Commands/SpectatorClientCommands/TeamsNames.cpp \
  srcs/Commands/SpectatorClientCommands/Players.cpp \
  srcs/Commands/SpectatorClientCommands/PlayerPosition.cpp \
  srcs/Commands/SpectatorClientCommands/PlayerLevel.cpp \
  srcs/Commands/SpectatorClientCommands/GetTimeUnit.cpp \
  srcs/Commands/SpectatorClientCommands/SetTimeUnit.cpp \

# Add Server Commands
SRC += srcs/Commands/ServerCommands/HelpServer.cpp \
srcs/Commands/ServerCommands/StatusServer.cpp \
  srcs/Commands/ServerCommands/ExitServer.cpp \
  srcs/Commands/ServerCommands/LangServer.cpp \
  srcs/Commands/ServerCommands/ClearServer.cpp \
  srcs/Commands/ServerCommands/PlayersServer.cpp \

# Add The Geometry srcs
SRC += srcs/Geometry/Point.cpp \
  srcs/Geometry/Direction.cpp \

# Add The Resources srcs
SRC += srcs/Resources/Mineral.cpp \
  srcs/Resources/Inventory.cpp \


CFLAGS  = -Wall -Wextra -Werror -std=c++20 #-fsanitize=leak
#CFLAGS  = -O3 -g -Wall -Wextra -Werror -std=c++20 -pedantic -fsanitize=leak

INC = -I includes -I tomlplusplus/include

DEPS = Command Commands/PlayerClientCommand Geometry Resources

OBJS_D  = objs

OBJS_DIRS = ${OBJS_D}/Commands \
  ${OBJS_D}/Commands/SpectatorClientCommands \
  ${OBJS_D}/Commands/PlayerClientCommands \
  ${OBJS_D}/Commands/ServerCommands \
  ${OBJS_D}/Resources \
  ${OBJS_D}/Geometry \

DEBUG_OBJS_D  = debug_objs

DEBUG_OBJS_DIRS = ${DEBUG_OBJS_D}/Commands \
  ${DEBUG_OBJS_D}/Commands/SpectatorClientCommands \
  ${DEBUG_OBJS_D}/Commands/PlayerClientCommands \
  ${DEBUG_OBJS_D}/Commands/ServerCommands \
  ${DEBUG_OBJS_D}/Resources \
  ${DEBUG_OBJS_D}/Geometry \

OBJ = $(SRC:srcs/%.cpp=$(OBJS_D)/%.o)

DEBUG_OBJ = $(SRC:srcs/%.cpp=$(DEBUG_OBJS_D)/%.o)

UNAME :=  $(shell uname)

RM    = rm -rf

ifeq ($(UNAME), Darwin)
  CC = g++
else ifeq ($(UNAME), FreeBSD)
  CC = clang++
else
  CC  = g++
  CFLAGS += -D LINUX
endif

$(NAME):$(OBJ)
> @printf "Compiling $(C_YELLOW)$(NAME)$(C_END) ... \n"
> $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
> @printf "$(C_GREEN)DONE$(C_END)\n"

$(OBJS_D)/%.o:srcs/%.cpp
> @mkdir -p $(OBJS_D) ${OBJS_DIRS}
> $(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(DEBUG_OBJS_D)/%.o:srcs/%.cpp
> @mkdir -p $(DEBUG_OBJS_D) ${DEBUG_OBJS_DIRS}
> $(CC) $(CFLAGS) -D DEBUG=1 $(INC) -o $@ -c $<

test:   re
> @printf "$(C_BLUE)Testing $(C_YELLOW)$(NAME)$(C_END)\n"
> @printf "\n$(C_BLUE)********************************************$(C_END)\n"
> @./$(NAME)
> @printf "\n$(C_BLUE)********************************************$(C_END)\n"
> @printf "\n$(C_BLUE)Finished Test...$(C_END)\n"
> @$(MAKE) show
> @$(MAKE) fclean

all:$(NAME)

debug: $(DEBUG_OBJ)
> @printf "Compiling DEBUG $(C_YELLOW)debug_$(NAME)$(C_END) ...\n"
> $(CC) $(CFLAGS) $(DEBUG_OBJ) -o debug_$(NAME)
> @printf "$(C_GREEN)DONE$(C_END)\n"

clean:
> $(RM) $(OBJS_D) $(DEBUG_OBJS_D)
> @printf "$(C_RED)Cleaning objs$(C_END)\n"

fclean:   clean
> $(RM) $(NAME) debug_$(NAME)
> @printf "$(C_RED)Deleted Everything$(C_END)\n"

re:fclean all

show:
> @printf "$(C_GREEN)"
> @printf "UNAME    : $(UNAME)\n"
> @printf "NAME     : $(C_YELLOW)$(NAME)$(C_GREEN)\n"
> @printf "CC   : $(CC)\n"
> @printf "CFLAGS   : $(CFLAGS)\n"
> @printf "INCLUDES : $(INC)\n"
> @printf "SRC    : $(C_YELLOW)$(SRC)$(C_GREEN)\n"
> @printf "OBJ    : $(C_YELLOW)[$(OBJS_D)] --> $(OBJ)$(C_END)\n"

.PHONY: all test re

C_BLACK   = \033[0;30m
C_RED   = \033[0;31m
C_GREEN   = \033[0;32m
C_YELLOW  = \033[0;33m
C_BLUE    = \033[0;34m
C_WHITE   = \033[0;37m
C_END   = \033[0m
