# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:36:23 by ple-stra          #+#    #+#              #
#    Updated: 2024/03/18 03:26:26 by ple-stra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= RPN

SRCS_DIR	:= srcs
SRCS		:= main.cpp RPN.cpp
BUILD_DIR	:= build
OBJS_DIR	:= $(BUILD_DIR)/objs
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INC			:= -I./includes

CC			:= c++
CFLAGS		:= -std=c++98 -Wall -Wextra
ifneq (nWerror, $(filter nWerror,$(MAKECMDGOALS)))
	CFLAGS	+= -Werror
endif
ifeq (sanitize, $(filter sanitize,$(MAKECMDGOALS)))
	CFLAGS 	+= -fsanitize=address
endif
ifeq (g3, $(filter g3,$(MAKECMDGOALS)))
	CFLAGS 	+= -g3
endif
ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+= -D KDEBUG=1
endif
LFLAGS		:=
DEPDIR		:= $(BUILD_DIR)/deps
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
DEPFILES 	:= $(SRCS:%.cpp=$(DEPDIR)/%.d)

RM			:= rm -rf

all			: $(NAME)

$(DEPFILES)	:
include $(wildcard $(DEPFILES))

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(DEPDIR)/%.d
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@


$(NAME)		: $(OBJS)
			$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS) $(LFLAGS)

clean		:
			$(RM) $(OBJS_DIR)
			$(RM) $(DEPDIR)

fclean		:
			$(RM) $(BUILD_DIR)
			$(RM) $(NAME)

re			: fclean all

nWerror		:
			@echo "WARN: Compiling without Werror flag!"
sanitize	:
			@echo "WARN: Compiling with fsanitize flag!"
g3			:
			@echo "WARN: Compiling with g3 flag!"
debug		:
			@echo "WARN: debug is enabled"

.PHONY: \
 all clean fclean re\
 nWerror sanitize g3 debug
