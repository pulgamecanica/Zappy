# Makefile created automatically from script\n
# C++ Zappy [Thu Feb 15 07:45:39 PM CET 2024]\n
#MAKEFLAGS += --silent  # Silence makefile [Commented by default]\n
NAME  = Zappy

.RECIPEPREFIX = >

SRC = $(wildcard srcs/*.cpp)

# Add the Command srcs
SRC += srcs/Commands/HelpServer.cpp \
  srcs/Commands/StatusServer.cpp \
  srcs/Commands/ExitServer.cpp \
  srcs/Commands/LangServer.cpp \
  srcs/Commands/ClearServer.cpp \
  srcs/Commands/PlayersServer.cpp \
  srcs/Commands/Advance.cpp \
  srcs/Commands/Right.cpp \
  srcs/Commands/Left.cpp \
  srcs/Commands/MapSize.cpp \
  srcs/Commands/Join.cpp \
  srcs/Commands/BlockContentTile.cpp \
  srcs/Commands/MapContentTile.cpp \
  srcs/Commands/TeamsNames.cpp \
  srcs/Commands/PlayerPosition.cpp \
  srcs/Commands/PlayerLevel.cpp \

# Add The Geometry srcs
SRC += srcs/Geometry/Point.cpp \
  srcs/Geometry/Direction.cpp \

CFLAGS  = -Wall -Wextra -Werror -std=c++20 #-fsanitize=leak
# CFLAGS  = -O3 -g -Wall -Wextra -Werror -std=c++20 -pedantic #-fsanitize=leak

INC = -I includes -I tomlplusplus/include

OBJS_D  = objs

OBJS_DIRS = ${OBJS_D}/Commands ${OBJS_D}/Geometry 

DEBUG_OBJS_D  = debug_objs

DEBUG_OBJS_DIRS = ${DEBUG_OBJS_D}/Commands ${DEBUG_OBJS_D}/Geometry 

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
