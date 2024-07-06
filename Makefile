CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = philo

DIR_SRCS	=	srcs
DIR_OBJS	=	.objs

LST_SRCS =	main.c \
			init.c \
			alive.c \
			utils.c \
			actions.c \

LST_OBJS = $(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS		=	$(addprefix $(DIR_OBJS)/, $(LST_OBJS))

ERASE		=	\033[2K\r
BLUE		=	\033[34m
YELLOW		=	\033[33m
GREEN		=	\033[32m
END			=	\033[0m

all : $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	@mkdir -p .objs
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(BLUE) > Compilation :$(END) $<\n"


$(NAME) :   $(OBJS)
	@printf "$(GREEN).c are compiled\n$(END)"
	@printf "$(BLUE) > Libft Compilation ...\n$(END)"
	@$(MAKE) -C libft
	@printf "$(ERASE)$(GREEN)Libft made !\n$(END)"
	@$(CC) $(CFLAGS) $(OBJS) -L./libft/ -lft -o $(NAME)
	@printf "$(ERASE)$(GREEN)$(NAME) made !\n$(END)"

clean   :
	@printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@make clean -C libft
	@rm -rdf $(DIR_OBJS)

fclean  :   clean
	@printf "$(YELLOW)$(NAME) removed$(END)\n"
	@make fclean -C libft
	@rm -f $(NAME)

re      :   fclean all
