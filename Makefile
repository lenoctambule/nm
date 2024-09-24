CC		= gcc
FLAGS	= -Wall -Wextra -Werror -MMD -g
INCS	= -I./libft -I./includes
SRC_DIR = ./src
SRC		+= $(addprefix $(SRC_DIR)/, \
						main.c)
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = ./obj
NAME	= nm
DEPS	= $(OBJ:%.o=%.d)

all : libft/libft.a $(NAME) 

show:
	echo $(SRC)
	echo $(OBJ)

-include $(DEPS)
$(OBJ_DIR) : 
	@mkdir -p $(OBJ_DIR)

$(NAME):  $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) $(INCS) $(OBJ) libft/libft.a  -o $(NAME)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(INCS) -o $@ -c $<

libft/libft.a :
	make -C ./libft

clean :
	rm -rf ./obj
	make -C ./libft fclean

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY:
	all clean fclean re