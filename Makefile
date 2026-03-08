NAME			:=	push_swap
BNS_NAME		:=	checker

MAKEFLAGS		+=	-j
COMPILER		:=	cc
CFLAGS			:=	-Wall -Wextra -Werror							\
					-Wpedantic -Wundef -Wstrict-prototypes			\
					-Wshadow -Wconversion -Wsign-conversion			\
					-Wformat=2 -Wuninitialized -Wunreachable-code	\
					-MMD -MP

OPTIMIZATION	:=	-O2
SECURITY		:=	-D_FORTIFY_SOURCE=2 -fstack-protector-strong
DEBUG_FLAGS		:=	-g3 -fno-omit-frame-pointer
SANITIZERS		:=	-fsanitize=address,undefined,null,leak,integer-divide-by-zero,signed-integer-overflow,bounds,alignment
CFLAGS			+=	$(OPTIMIZATION) $(SECURITY)
ifneq ($(filter debug,$(MAKECMDGOALS)),)
	CFLAGS		+=	$(DEBUG_FLAGS) $(SANITIZERS)
endif

PRINT_NO_DIR	:=	--no-print-directory
RM				:=	rm -rf

SRC_DIR			:=	src
INC_DIR			:=	include
BUILD_DIR		:=	.build

# Extern Library
EXT_DIR			:=	extern_libary
EXT_LIB			:=	$(EXT_DIR)/libftx
EXT_INC			:=	$(EXT_LIB)/$(INC_DIR)
LIBFTX_OBJ_DIR	:=	$(BUILD_DIR)/libftx
LIB_A			:=	libftx.a

BNS				:=	main_bonus.c				checker.c

PUSH_SWAP		:=	main.c		ps_nodes.c					ps_commands.c					ps_to_b.c	\
					ps_to_b_2.c					ps_to_a.c						ps_utils.c	\
					ps_utils_2.c				ps_utils_3.c

# Generate source file names
SRC				:=	$(addprefix $(SRC_DIR)/, $(PUSH_SWAP))

# Generate object file names
OBJ				:=	$(SRC:%.c=$(BUILD_DIR)/%.o)

# Generate Dependency files
DEPS			:=	$(OBJ:.o=.d)


DELETE			:=	*.out			**/*.out			.DS_Store	\
					**/.DS_Store	.dSYM/				**/.dSYM/

all: $(NAME)

# $(NAME): libftx $(OBJ)
$(NAME): $(OBJ)
	@printf "$(CREATED)" $@ $(CUR_DIR)

# $(NAME): $(OBJ)
# 	@cc $(CFLAGS) $(OBJ) -o $(NAME)

# $(BNS_NAME): $(BOBJ)
# 	@cc $(CFLAGS) $(BOBJ) -o $(BNS_NAME)

# $(NAME): libftx $(OBJ)
# 	mkdir -p $(LIBFTX_OBJ_DIR)
# 	cd $(LIBFTX_OBJ_DIR) && ar x ../../$(EXT_LIB)/$(LIB_A)
# 	ar rcs $(NAME) $(OBJ) $(LIBFTX_OBJ_DIR)/*.o
# 	@printf "$(CREATED)" $@ $(CUR_DIR)

# $(BUILD_DIR)/%.o: %.c
$(BUILD_DIR)/%.o: %.c | libftx
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -I $(EXT_INC) -c $< -o $@

# $(CLONE_LIBFTX) is set to nothing when dbltoa is used as a submodule in libftx,
# preventing nested cloning of libftx inside dbltoa.
# libftx:
# 	$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) $(LIB_A) gnl $(filter debug,$(MAKECMDGOALS))

# $(EXT_LIB)/.git:
# 	git clone git@github.com:RJW-db/libftx.git $(EXT_LIB)

$(EXT_LIB)/$(SRC_DIR)/get_next_line/.git:
	git submodule update --init extern_libary/libftx
	cd $(EXT_LIB) && git submodule update --init src/get_next_line
	cd $(EXT_LIB)/src/get_next_line && \
		git checkout $$(git config -f $(abspath $(EXT_LIB))/.gitmodules submodule.src/get_next_line.branch || echo main)

libftx: | $(EXT_LIB)/$(SRC_DIR)/get_next_line/.git
	@$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) SUBMODULES_CMD= $(LIB_A) gnl $(filter debug,$(MAKECMDGOALS))

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) fclean;
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)


# clean:
# 	@$(RM) $(BUILD_DIR) $(DELETE)
# 	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

# fclean: clean
# 	@$(RM) $(NAME)
# # 	@rm -f $(INC_DIR)/libftx.h
# 	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re: fclean all

# Submodule: skip `all` to avoid parallel conflicts. Standalone: triggers `all`.
debug: $(if $(and $(CLONE_LIBFTX),$(filter debug,$(MAKECMDGOALS))),all)

print-%:
	$(info $($*))

-include $(DEPS)

.PHONY:	all libftx submodule_build submodule clean fclean re debug print-%

# Terminal markup
BOLD			:=	\033[1m
GREEN			:=	\033[32m
MAGENTA			:=	\033[35m
CYAN			:=	\033[36m
RESET			:=	\033[0m

R_MARK_UP		:=	$(MAGENTA)$(BOLD)
CA_MARK_UP		:=	$(GREEN)$(BOLD)

# Current directory and formatted status messages
CUR_DIR			:=	$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED			:=	$(R_MARK_UP)REMOVED $(CYAN)%s$(MAGENTA) (%s) $(RESET)\n
CREATED			:=	$(CA_MARK_UP)CREATED $(CYAN)%s$(GREEN) (%s) $(RESET)\n
