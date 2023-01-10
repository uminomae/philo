#=============================
#make&test
#=============================
run: 
# make re
	make sani_thread
	bash test.sh
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