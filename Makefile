NAME		:= philo
CC			:= cc
# CC			:= clang
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O
DFLAGS		:= -MMD -MP
SRCS		:= 	ph_main.c \
				ph_begin.c \
				ph_begin_check.c \
				ph_begin_build.c \
				ph_list.c \
				ph_list_thread.c \
				ph_list_malloc.c \
				ph_thread.c \
				ph_start_routine.c \
				ph_put.c \
				ph_atoi.c \
				ph_libft.c \

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

run: 
	make
	./philo 10 2 3 4 50
	./philo 1 100000000 10 10 1
#	./philo 5 100000000 
#	./philo 7 a 10 10
#	./philo 123a 10 10 10 

.PHONY: all clean fclean re bonus sani

RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"