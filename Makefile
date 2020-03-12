NAME = asm

FLAGS = -g -Wall -Wextra -Werror
FILES = srcs/main.c \
	srcs/check_fextension.c \
	srcs/read_file.c \
	srcs/ft_vrealloc.c \
	srcs/frontend_analysis.c  \
	srcs/ft_assembler.c  \
	srcs/line_parser.c  \
	srcs/ft_cmd_parser.c  \
	srcs/op.c  \
	srcs/code_parser.c  \
	srcs/syntax_analys.c  \
	srcs/semantic_analys.c  \
	srcs/ft_backend_analysis.c  \
	srcs/champ_exe_code.c  \
	srcs/ft_get_tcode.c  \
	srcs/gen_code_tools.c  \
	srcs/gen_ind_args.c  \
	srcs/gen_sdir_args.c  \
	srcs/gen_ldir_args.c  \
	srcs/gen_args_bytecode.c  \
	srcs/ft_pc_counter.c  \
	srcs/code_gen_utils.c  \
	srcs/ft_labels_checker.c  \
	srcs/syntax_analysis_utils.c  \
	srcs/args_checker_utils.c  \
	srcs/syntax_utils.c  \
	srcs/label_tokenizer_utils.c  \
	srcs/syntax_checker_utils.c \
	srcs/ft_cmd_parser_manager.c  \
	srcs/ft_get_name.c  \
	srcs/ft_get_comment.c  \

OBJ = $(FILES:.c=.o)

LIBFT = ./libft/libft.a

INCLUDES = includes/

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ) $(HEADER_FILES)
	gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ) : %.o : %.c
	gcc $(FLAGS)  $< -o $@ -c -I $(INCLUDES) -I $(INCLUDES)

$(LIBFT) :
	make -C ./libft/

clean :
	@rm -rf $(OBJ)
	@make clean -C ./libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./libft

re : fclean all

.PHONY : clean fclean re $(LIBFT)
