NAME 		=	minishell
CC = cc

CFLAGS =	-Wall \
			-Wextra \
			-g3 \
			#-fsanitize=address

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

.PHONY: all clean fclean re libft mac clone_libft clone_tester tester

all: clone_libft libft $(NAME)


$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(CC) $(CFLAGS) \$$(OBJ) $(LIBS) -o $(NAME)"
	@echo "\n$(GREEN)\t$(NAME) compiled successfully$(RESET)\n"

libft:
	echo "Start LibFT"
	@$(MAKE) all -C ./libft
	echo "End LibFT"

mac: clone_libft libft $(OBJ_MAC)
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

leaks: mac
	clear
	leaks --atExit -- ./$(NAME)

valgrind: all
	clear
	$(VALGRIND) ./$(NAME)

project_re:
	rm -f $(OBJ)
	rm -f $(NAME)
	clear
	make $(NAME) -j

tester: clone_tester all
	cd tester
	./tester
	cd ..

REPO_URL_LIB := https://github.com/Saliinger/libft.git
CLONE_DIR_LIB := libft

# Clone target
clone_libft:
	@if [ ! -d "$(CLONE_DIR_LIB)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL_LIB) $(CLONE_DIR_LIB); \
	else \
		echo "Repository already cloned."; \
	fi

REPO_URL_TESTER := https://github.com/LucasKuhn/minishell_tester.git
CLONE_DIR_TESTER := tester

clone_tester:
	@if [ ! -d "$(CLONE_DIR_TESTER)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL_TESTER) $(CLONE_DIR_TESTER); \
	else \
		echo "Repository already cloned."; \
	fi
