
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
ph_begin_init_mutex.c \
ph_error_get_num.c \
ph_error_check.c \
ph_malloc.c \
ph_run_1_parallel.c \
ph_run_2_rutine_philo.c \
ph_run_3_rutine_monitor.c \
ph_run_4_eating.c \
ph_run_5_judge.c \
ph_run_6_put.c \
ph_run_7_util.c \
ph_finish.c \
ph_finish_free.c \
ph_util_libft.c \
ph_util_atoi.c \
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
#=============================
#make&test
#=============================
run: 
#	make re
	make sani_thread
	bash test.sh

run2: 
	make re
#	make sani_thread
	./philo 5 800 200 200
#	./philo 5 800 200 200 7 | grep died >out 

run3: 
	make re
#	./philo 5 800 200 200 | grep eating >out 
	./philo 5 800 200 200 
#	./philo 4 410 200 200
# ./philo 200 2000 1000 1000
run4: 
	make sani_add
#	make sani_thread
	./philo 4 310 200 100
#	./philo 5 800 200 200 
run5: 
	make re
	./philo 4 410 200 200
	./philo 5 800 200 200 7

1: 
	make sani_thread
	./philo 4 310 200 100
2:
	make sani_thread
	./philo 5 800 200 200 7
3:
	make sani_thread
	./philo 5 800 200 200 
4:
	make sani_thread
	./philo 4 410 200 200
5:
	make sani_add
	./philo 200 2000 1000 1000

error:
	make sani_thread
	./philo 5 800 200 200 >> err

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