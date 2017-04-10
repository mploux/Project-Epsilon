NAME = renderer
CC = g++
FILES =		main.cpp

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

DIRS =		bin

SRC = src/
OBJS = $(addprefix bin/,$(FILES:.cpp=.o))

DEPS = -L deps/liblz/ -L deps/glfw/build/src/ -L deps/glew/lib/
INCLUDES = -I deps/liblz/includes/ -I deps/glfw/include/ -I deps/glew/include/

# DEPSFLAGS = -llz -lglfw3 -lGL -lm -lGLU -lGLEW -lXrandr -lXi -lX11\
# -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lrt

DEPSFLAGS = -llz -lglfw3 -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

CXXFLAGS =	-Wall -Wextra -std=c++11
FLAGS = $(CXXFLAGS) $(INCLUDES)

# LIBLZ = deps/liblz/liblz.a
# GLFW = deps/glfw/build/src/libglfw3.a
# GLEW = deps/glew/lib/libGLEW.a

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

$(NAME): deps $(DIRS) $(OBJS)
	@echo "Making liblz..."
	@make --no-print-directory -C deps/liblz/ > /dev/null
	@printf "\r$(GREEN)Compiling liblz: DONE !$(NO_COLOR)\n";
	@echo "Making libGLFW..."
	@make -C deps/glfw/build/ > /dev/null
	@printf "\r$(GREEN)Compiling libGLFW: DONE !$(NO_COLOR)\n";
	@echo "Making libGLEW..."
	@make -C deps/glew/ > /dev/null
	@rm -f deps/glew/lib/libGLEW.so
	@rm -f deps/glew/lib/libGLEW.2.0.0.dylib
	@printf "$(GREEN)Compiling libGLEW: DONE !$(NO_COLOR)\n";
	@echo "Making planet..."
	@$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Compiling planet: DONE !$(NO_COLOR)\n";
	@echo "\n$(GREEN)Compilation done: $(GREEN_BG)$(NAME)$(NO_COLOR)"

all: $(NAME)

$(DIRS):
	@$(MKDIR) $(DIRS)

bin/%.o: src/%.cpp
	@$(CC) -c $^ -o $@ $(CXXFLAGS) $(INCLUDES)

clean:
	@printf "Cleaning objs..."
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objs: DONE !$(NO_COLOR)\n";

clean-libs: clean
	@printf "Cleaning liblz..."
	@make fclean -C deps/liblz > /dev/null
	@printf "\r$(GREEN)Cleaning liblz: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLFW..."
	@make clean -C deps/glfw/build > /dev/null
	@printf "\r$(GREEN)Cleaning libGLFW: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLEW..."
	@make clean -C deps/glew > /dev/null
	@printf "\r$(GREEN)Cleaning libGLEW: DONE !$(NO_COLOR)\n";

fclean-libs: clean-libs
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
