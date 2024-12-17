################################################################################
#                                     CONFIG                                   #
################################################################################

NAME	:= minishell
CC		:= cc
FLAGS	:= -Wall -Wextra -Werror 
LIBS	= -L./libft/compiled -lft -lprintf -lreadline
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      src/builtins/cd/change_pwd.c \
                          src/builtins/cd/get_current_path.c \
                          src/builtins/cd/get_home.c \
                          src/builtins/cd/get_path.c \
                          src/builtins/cd/path_constructor.c \
                          src/builtins/cd/path_handler.c \
                          src/builtins/cd/ft_cd.c \
                          src/builtins/echo/check_flag.c \
                          src/builtins/echo/echo_print.c \
                          src/builtins/echo/ft_echo.c \
                          src/builtins/env/ft_env.c \
                          src/builtins/exit/ft_exit.c \
                          src/builtins/export/print_export_list.c \
                          src/builtins/export/ft_export.c \
                          src/builtins/pwd/ft_pwd.c \
                          src/builtins/unset/ft_unset.c \
                          src/exec/ft_exec.c \
                          src/exec/ft_exec_builtins.c \
                          src/exec/ft_exec_extern.c \
                          src/exec/redir/handle_redir.c \
                          src/exec/redir/preprocess_heredocs.c \
                          src/exec/get_cmd_path.c \
                          src/exec/get_exit_status.c \
                          src/exec/utils.c \
                          src/exec/exec_fork_loop.c \
                          src/exec/exec_processor.c \
                          src/export_list/add_node.c \
                          src/export_list/delete_node.c \
                          src/export_list/find_export_node.c \
                          src/export_list/init_list.c \
                          src/export_list/modify_value.c \
                          src/export_list/sort_list.c \
                          src/ft_minishell.c \
                          src/main.c \
                          src/parsing/0_base/split_element.c \
                          src/parsing/0_base/split_element_extend.c \
                          src/parsing/1_redirection/clean_arg.c \
                          src/parsing/1_redirection/utils.c \
                          src/parsing/1_redirection/move_redir.c \
                          src/parsing/1_redirection/lexer.c \
                          src/parsing/1_redirection/relexer_handle_cases.c \
                          src/parsing/2_expand/expand_in.c \
                          src/parsing/2_expand/tiny_expand.c \
                          src/parsing/2_expand/utils.c \
                          src/parsing/3_quotes/remove_quote.c \
                          src/parsing/command.c \
                          src/parsing/divider.c \
                          src/parsing/input_chequer/check_access.c \
                          src/parsing/input_chequer/input_checker.c \
                          src/parsing/parsing.c \
                          src/parsing/trimmer.c \
                          src/signals/handlers.c \
                          src/signals/setters.c \
                          src/utils/env_utility/get_env.c \
                          src/utils/garbage_collector/ft_itoa_safe.c \
                          src/utils/garbage_collector/ft_split_safe.c \
                          src/utils/garbage_collector/ft_strjoin_safe.c \
                          src/utils/garbage_collector/safe_fd.c \
                          src/utils/garbage_collector/safe_malloc.c \
                          src/utils/init_no_env.c \
                          src/utils/manage_var.c \
                          src/utils/printerr/ft_countdigit.c \
                          src/utils/printerr/ft_decimal.c \
                          src/utils/printerr/ft_hex.c \
                          src/utils/printerr/ft_pointeurhex.c \
                          src/utils/printerr/ft_printchar.c \
                          src/utils/printerr/ft_putnbr_u.c \
                          src/utils/printerr/ft_putstr.c \
                          src/utils/printerr/ft_selector.c \
                          src/utils/printerr/ft_string.c \
                          src/utils/printerr/ft_uint.c \
                          src/utils/printerr/printerr.c \
                          src/utils/printerr/utils.c \
                          src/utils/nuclear_exit.c \
                          src/utils/utils.c \
                          src/utils/utils2.c \
           
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
RESET		:= \033[0m



all:		clone_libft libft ${NAME}

libft:
	echo "Start LibFT"
	@$(MAKE) all -C ./libft
	echo "End LibFT"

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

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} $(LIBS)
			@echo "$(GREEN)$(NAME) created $(RESET)"

bonus:		all

clean:
			@$(MAKE) -C ./libft clean
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs"

fclean:		clean
			@$(MAKE) -C ./libft fclean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary"

re:			fclean all

.PHONY:		all clean fclean re clone_libft libft


