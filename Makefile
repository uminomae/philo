NAME		:= philo
CC			:= cc
# CC			:= clang
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O
# CFLAGS		:= -O
DFLAGS		:= -MMD -MP
SRCS		:= 	ph_main.c \
				ph_time.c \
				ph_init_mutex.c \
				ph_begin_is_valid.c \
				ph_begin_build.c \
				ph_begin_list_fork.c \
				ph_begin_list_pthread.c \
				ph_error_flag.c \
				ph_error_check.c \
				ph_malloc.c \
				ph_run_parallel.c \
				ph_run_philo_func.c \
				ph_run_eating.c \
				ph_run_flag_ate.c \
				ph_run_flag_died.c \
				ph_finish.c \
				ph_finish_free.c \
				ph_util_libft.c \
				ph_util_atoi.c \
				ph_util_mutex.c

# B_SRCS	:= 

# LIBFT		= $(LIBDIR)libft.a
INCLUDE		= -I$(INCDIR)
DEPENDS		= $(OBJECTS:.o=.d)
OBJS		= $(SRCS:%.c=%.o)
OBJECTS		= $(addprefix $(OBJDIR)/, $(OBJS))

# B_OBJS		= $(B_SRCS:%.c=%.o)
# B_OBJECTS   = $(addprefix $(OBJDIR)/, $(B_OBJS))
# ifdef WITH_BONUS
# 	OBJS += $(B_OBJECTS)
# endif

INCDIR		= include/
# LIBDIR		= libft/
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR	= .
endif
# SRCDIR    = src/
# ifeq "$(strip $(SRCDIR))" ""
#   SRCDIR  = .
# endif


$(NAME): $(OBJECTS) $(LIBFT)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)

$(OBJDIR)/%.o: %.c
	@echo $(SKYBLUE) "make .o" $(RESET)
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

# $(LIBFT): FORCE
# 	$(MAKE) -C $(LIBDIR)
# 	@echo $(GREEN)"----- $(LIBFT) $(CC) done-----"$(RESET)
# FORCE:

all: $(NAME) 

clean:
# $(MAKE) clean -C $(LIBDIR)
	@echo $(YELLOW)"----- $(LIBFT) clean done-----"$(RESET)
	$(RM) $(OBJECTS) $(DEPENDS)
	@echo $(YELLOW)"----- $(NAME) clean done-----"$(RESET)

fclean:	clean
# $(MAKE) fclean -C $(LIBDIR)
	@echo $(RED)"----- $(LIBFT) fclean done-----"$(RESET)
	$(RM) $(NAME)
	@echo $(RED)"----- $(NAME) fclean done-----"$(RESET)

re: fclean all

-include $(DEPENDS)

# bonus: 
# 	make WITH_BONUS=1

sani: CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
sani: re

sani2: CFLAGS +=  -g  -fsanitize=thread 
sani2: re

run: 
	make sani2
	bash test.sh










#	./philo 5 300 100 100 2 > out
# valgrind --leak-check=full ./philo 5 300 100 100 2
#	./philo 200 410 200 200  >out2


# ./philo 200 410 200 200 | awk '{print $1}' | tee act | sort -n > exp; diff -u exp act

# タイムスタンプに前後がないか確認するコマンド
.PHONY: all clean fclean re bonus sani

RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"