NAME            = gnl.a
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
SRC_DIR         = src
BUILD_DIR       = build
LIBFT_DIR       = ./libft
LIBFT_A         = $(LIBFT_DIR)/libft.a

SRCS            = get_next_line.c get_next_line_utils.c
SRC_PATHS       = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS            = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

GREEN           = \033[0;32m
RESET           = \033[0m

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "$(GREEN)Compilation de libft...$(RESET)"
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Création de la librairie $(NAME)...$(RESET)"
	ar rcs $(NAME) $(OBJS)

clean:
	@echo "$(GREEN)Nettoyage des .o...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(GREEN)Nettoyage complet...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

