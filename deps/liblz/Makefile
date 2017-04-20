PROG = liblz
NAME = liblz.a
CC = g++
FILES =		graphics/display.cpp\
			maths/vec3.cpp\
			maths/mat4.cpp\
			maths/quat.cpp\
			graphics/shader.cpp\
			utils/error.cpp\
			utils/string_utils.cpp\
			utils/file_utils.cpp\
			maths/transform.cpp\
			graphics/camera.cpp\
			inputs/input.cpp\
			utils/timer.cpp\
			graphics/mesh.cpp\
			graphics/obj_loader.cpp\
			utils/resources.cpp\
			graphics/textures/texture.cpp\
			graphics/textures/texture_dds.cpp\
			graphics/textures/texture_bmp.cpp\
			graphics/cubemap.cpp\
			graphics/image.cpp

WHITE = \033[7;49;39m
BAR_COLOR = \033[48;5;
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

DIRS = $(addprefix bin/,$(dir $(FILES)))

SRC = src/
BIN = bin/
OBJS = $(addprefix bin/,$(FILES:.cpp=.o))

INCLUDES = -I includes/LZ/ -I ../glfw/include/ -I ../glew/include/
# GLFLAGS = 	-lglfw3 -lGL -lm -lGLU -lglew -lXrandr -lXi -lX11 -lXxf86vm \
# 			-lpthread -ldl -lXinerama -lXcursor -lrt
GLFLAGS =
FLAGS = -std=c++11 $(GLFLAGS) $(INCLUDES) -pedantic -W -Wall -Wextra

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

$(NAME): $(BIN) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "$(NO_COLOR)\r%*b" "$(WIDTH)";
	@printf "\r$(GREEN)Compiling $(PROG): DONE !$(NO_COLOR)\n";

all: $(NAME)

$(BIN):
	@$(MKDIR) $(BIN)
	@$(MKDIR) $(DIRS)

bin/%.o: src/%.cpp $(COUNT) $(WIDTH)
	$(CC) -MMD -c $^ -o $@ $(FLAGS)

clean:
	@$(RMDIR) bin

fclean: clean
	@$(RM) $(NAME)

re: fclean all
