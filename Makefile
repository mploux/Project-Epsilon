NAME = renderer
CC = g++
FILES =\
main.cpp\
material.cpp\
light.cpp\
mesh_renderer.cpp\
skybox.cpp

SRC = srcs/
DIRS =		bin

SYSTEM = $(shell uname -s)

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

OBJS = $(addprefix bin/,$(FILES:.cpp=.o))

DEPS = -L deps/liblz/ -L deps/glfw/build/src/ -L deps/glew/lib/
INCLUDES = -I includes/ -I deps/liblz/includes/ -I deps/glfw/include/ -I deps/glew/include/

ifeq (SYSTEM, Darwin)
	DEPSFLAGS = -llz -lglfw3 -lGLEW -framework Cocoa -framework OpenGL\
				-framework IOKit -framework CoreVideo
else
	DEPSFLAGS = -llz -lglfw3 -lGL -lm -lGLU -lGLEW -lXrandr -lXi -lX11\
				-lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lrt
endif

CXXFLAGS =	-Wall -Wextra -std=c++11
FLAGS = $(CXXFLAGS) $(INCLUDES)

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

$(NAME): $(DIRS) $(OBJS)
	@printf "\r$(GREEN)Compiling sources: DONE !                      $(NO_COLOR)\n";
	@printf "Building liblz...\r"
	@make --no-print-directory -C deps/liblz/ > /dev/null
	@printf "\r$(GREEN)Building liblz: DONE !$(NO_COLOR)\n";

	@printf "Building libGLFW...\r"
	@$(MKDIR) deps/glfw/build > /dev/null
	@cd deps/glfw/build && cmake .. > /dev/null
	@make -C deps/glfw/build/ > /dev/null
	@printf "\r$(GREEN)Building libGLFW: DONE !$(NO_COLOR)\n";

	@printf "Building libGLEW...\r"
	@make -C deps/glew/ > /dev/null
	@rm -f deps/glew/lib/libGLEW.so
	@rm -f deps/glew/lib/libGLEW.2.0.0.dylib
	@printf "\r$(GREEN)Building libGLEW: DONE !$(NO_COLOR)\n";

	@printf "Building objects...\r"
	@$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Building objects: DONE !$(NO_COLOR)\n";
	@printf "\n$(GREEN)Building done: $(GREEN_BG)$(NAME)$(NO_COLOR)\n"

$(DIRS):
	@$(MKDIR) $(DIRS)

bin/%.o: srcs/%.cpp
	@printf "\rCompiling sources: $^                          \r";
	@$(CC) -MMD -c $^ -o $@ $(CXXFLAGS) $(INCLUDES)

.PHONY: all clean clean-libs fclean-libs fclean re

all: $(NAME)

clean:
	@printf "Cleaning objects..."
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objects: DONE !$(NO_COLOR)\n";

clean-libs: clean
	@printf "Cleaning liblz..."
	@make fclean -C deps/liblz > /dev/null
	@printf "\r$(GREEN)Cleaning liblz: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLFW..."
	@$(RMDIR) deps/glfw/build
	@printf "\r$(GREEN)Cleaning libGLFW: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLEW..."
	@make clean -C deps/glew > /dev/null
	@printf "\r$(GREEN)Cleaning libGLEW: DONE !$(NO_COLOR)\n";

fclean-libs: clean-libs
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
