NAME = philo

COMPILER = cc

FLAGS = -Wall -Werror -Wextra -I ./include

SRC_PATH = ./src
SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/initialize.c \
	$(SRC_PATH)/threads_manager.c\
	$(SRC_PATH)/one_thread.c \
	$(SRC_PATH)/utils.c \
	$(SRC_PATH)/utils2.c

OBJ_DIR = obj
OBJECTS = $(SRC:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJECTS)
	$(COMPILER) $(FLAGS) $(OBJECTS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
