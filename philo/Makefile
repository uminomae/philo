
#=============================
#flags
#=============================
NAME		:= philo
CC			:= cc
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O
DFLAGS		:= -MMD -MP
#=============================
#src
#=============================
SRCDIR    = srcs
# SRCS_LIST		:= $(wiledcard $(SRCDIR)/*.c)
SRCS_LIST	:= 	\
ph_main.c \
ph_begin_is_valid.c \
ph_begin_build.c \
ph_begin_list_fork.c \
ph_begin_list_philo.c \
ph_run_1_parallel.c \
ph_run_2_philo_main.c \
ph_run_2_philo_eating.c \
ph_run_3_die.c \
ph_run_3_err.c \
ph_run_3_hungry.c \
ph_run_flag.c \
ph_run_put.c \
ph_run_util.c \
ph_finish.c \
ph_util_atoi.c \
ph_util_error.c \
ph_util_free.c \
ph_util_libft.c \
ph_util_malloc.c \
ph_util_mutex_node.c \
ph_util_mutex_struct.c \
ph_util_x_stdlib.c \

SRCS_IN_DIR  = $(addprefix $(SRCDIR)/, $(SRCS_LIST))
INCDIR		= include/
INCLUDE		= -I$(INCDIR)
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR	= .
endif
# OBJS		= $(SRCS:%.c=%.o)
OBJECTS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS_IN_DIR:%.c=%.o)))
DEPENDS		= $(OBJECTS:.o=.d)
# B_SRCS	:= 
# ifeq "$(strip $(SRCDIR))" ""
#   SRCDIR  = .
# endif
# B_OBJS		= $(B_SRCS:%.c=%.o)
# B_OBJECTS   = $(addprefix $(OBJDIR)/, $(B_OBJS))
# ifdef WITH_BONUS
# 	OBJS += $(B_OBJECTS)
# endif
# LIBFT		= $(LIBDIR)libft.a
# LIBDIR		= libft/
#=============================
#rule
#=============================
# $(NAME): $(OBJECTS) $(LIBFT)
$(NAME): $(OBJECTS) 
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)

	@echo $(SKYBLUE) "make .o" $(RESET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
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

sani_add: CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
sani_add: re

sani_thread: CFLAGS +=  -g  -fsanitize=thread 
sani_thread: re

sani-helgrind:  CFLAGS +=  -g  valgrind --tool=helgrind
sani_thread: re

#=============================
#make&test
#=============================
run: 
#	make re
	make sani_thread
	bash test.sh

test: 
	make re
	bash test.sh

test1:
	make sani_thread
	bash test.sh

test2: 
	make sani_add
	bash test.sh

1: 
	make sani_thread
	./philo 4 310 200 100
2:
#	make re
	make sani_thread
	./philo 5 800 200 200 7
3:
	make sani_thread
	./philo 5 800 200 200 
4:
	make sani_thread
	./philo 4 410 200 200
5:
#	make re	
	make sani_thread
#	./philo 200 2000 1000 1000  >out 
	./philo 200 2000 1000 1000

51:
	make sani_add
	./philo 200 2000 1000 1000

52:
	make re	
	./philo 200 2000 1000 1000

6:
	make sani_thread
	./philo 5 510 200 100

62:
	make re
	./philo 5 510 200 100

7:
	make sani_thread
#	make sani_add
#	make re
	./philo 5 1410 200 500



error:
	make sani_thread
	./philo 5 800 200 200 >> err1

.PHONY: all clean fclean re bonus sani run sani2

#=============================
#color
#=============================
RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"