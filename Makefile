NAME 		=	minishell
CC = cc

CFLAGS =	-Wall \
			-Wextra \
			-g3 \
			#-fsanitize=address

LIBFT_A		=	libft/libft/libft.a
PRINTF_A	=	libft/printf/libprintf.a
LIBS = -L./libft/compiled -lft -lprintf -lreadline

VALGRIND = valgrind					\
--trace-children=yes				\
--track-fds=yes						\
--leak-check=full					\
--show-leak-kinds=all				\
--suppressions="./.valgrind.supp"	\
--track-origins=yes					\
-s									\

#--gen-suppressions=yes 

INCLUDE_MAC = -I/opt/homebrew/opt/readline/include
LIBS_MAC = -L/opt/homebrew/opt/readline/lib -lreadline -L./libft/compiled -lft -lprintf

GREEN = \033[0;32m
RESET = \033[0m

SRCD = ./src
UTILSD = ./src/utils
PARSD = ./src/parsing
SIGD = ./src/signals
EXED = ./src/exec
BINS = ./src/builtins

SRC =	$(wildcard $(SRCD)/*.c)				\
		$(wildcard $(UTILSD)/*.c)			\
		$(wildcard $(UTILSD)/*/*.c)			\
		$(wildcard $(PARSD)/*.c)			\
		$(wildcard $(PARSD)/*/*.c)			\
		$(wildcard $(SIGD)/*.c)				\
		$(wildcard $(EXED)/*.c)				\
		$(wildcard $(EXED)/*/*.c)			\
    	$(wildcard $(EXED)/*/*/*.c)	   		\
		$(wildcard $(BINS)/*.c)				\
		$(wildcard $(BINS)/*/*.c)			\
		$(wildcard $(SRCD)/export_list/*.c)

OBJ = $(SRC:.c=.o)

OBJ_MAC = $(SRC:.c=.mac.o)  # macOS-specific object files


# Rule to compile macOS-specific .mac.o files
%.mac.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_MAC)

.PHONY: all clean fclean re libft mac clone

all: clone $(LIBFT_A) $(PRINTF_A) $(NAME)


$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(CC) $(CFLAGS) \$$(OBJ) $(LIBS) -o $(NAME)"
	@echo "\n$(GREEN)\t$(NAME) compiled successfully$(RESET)\n"

$(LIBFT_A):
	echo "test"
	@$(MAKE) all -C ./libft

$(PRINTF_A):
	echo "test2"
	@$(MAKE) all -C ./libft

mac: $(LIBFT_A) $(PRINTF_A) $(OBJ_MAC)
	@$(CC) $(CFLAGS) $(OBJ_MAC) -o $(NAME) $(LIBS_MAC)
	@echo "$(CC) $(CFLAGS_MAC) \$$(OBJ_MAC) -o $(NAME) $(LIBS_MAC)"
	@echo "\n$(GREEN)\t$(NAME) compiled successfully on macOS$(RESET)\n"


clean:
	@$(MAKE) -C ./libft clean
	rm -f $(OBJ) $(OBJ_MAC)
	clear

fclean: clean
	@$(MAKE) -C ./libft fclean
	rm -f $(NAME)
	clear

re: fclean all

project_re:
	rm -f $(OBJ)
	rm -f $(NAME)
	clear
	make $(NAME) -j

exec_re: 
	rm -f $(EXED)/*.o
	rm -f $(EXED)/*/*.o
	rm -f $(EXED)/*/*/*.o
	rm -f $(EXED)/*/*/*/*.o
	rm -f $(NAME)
	clear
	make $(NAME) -j

utils_re:
	rm -f $(UTILSD)/*.o
	rm -f $(UTILSD)/*/*.o
	rm -f $(NAME)
	clear
	make $(NAME) -j

parsing_re:
	rm -f $(PARSD)/*.o
	rm -f $(NAME)
	clear
	make $(NAME) -j

builtins_re:
	rm -f $(BINS)/*/*.o
	rm -f $(NAME)
	clear
	make $(NAME) -j

test: project_re
	clear
	./$(NAME) || lldb $(NAME)

lldb: all
	lldb $(NAME)

valgrind: all
	clear
	$(VALGRIND) ./$(NAME)


REPO_URL := https://github.com/Saliinger/libft.git
CLONE_DIR := libft

# Clone target
clone:
	@if [ ! -d "$(CLONE_DIR)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL) $(CLONE_DIR); \
	else \
		echo "Repository already cloned."; \
	fi