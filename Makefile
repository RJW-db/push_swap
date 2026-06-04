NAME			:=	push_swap
BNS_NAME		:=	checker

MAKEFLAGS		+=	-j
COMPILER		:=	cc

BASE_FLAGS		:=	-std=c99 -Wall -Wextra -Werror

PEDANTIC		:=	-Wpedantic -pedantic-errors -Wundef -Wstrict-prototypes

WARNINGS		:=	-Wshadow -Wconversion -Wsign-conversion			\
					-Wformat=2 -Wuninitialized -Wunreachable-code

CAST_WARNINGS	:=	-Wbad-function-cast
ifeq ($(shell $(COMPILER) --version | grep -c "gcc"),1)
CAST_WARNINGS	+=	-Wcast-function-type
endif

DEPFLAGS		:=	-MMD -MP

OPTIMIZATION	:=	-O2
SECURITY		:=	-fstack-protector-strong
ifeq ($(shell uname -s),Linux)
SECURITY		+=	-D_FORTIFY_SOURCE=2
FSANITIZE		:=	leak
endif

SANITIZERS		:=	-fsanitize=$(FSANITIZE),address,undefined,null,integer-divide-by-zero,signed-integer-overflow,bounds,alignment
DEBUG_FLAGS		:=	-fno-omit-frame-pointer

CFLAGS			:=	$(BASE_FLAGS) $(PEDANTIC) $(WARNINGS) $(CAST_WARNINGS) \
					$(DEPFLAGS) $(OPTIMIZATION) $(SECURITY)

ifneq ($(filter valgrind,$(MAKECMDGOALS)),)
CFLAGS			+=	-g $(DEBUG_FLAGS)
else ifneq ($(filter debug,$(MAKECMDGOALS)),)
CFLAGS			+=	-g3 $(SANITIZERS) $(DEBUG_FLAGS) -fno-sanitize-recover=all
endif

PRINT_NO_DIR	:=	--no-print-directory
RM				:=	rm -rf

SRC_DIR			:=	src
INC_DIR			:=	include
BUILD_DIR		:=	.build

# Libftx
EXT_DIR			:=	extern_libary
LIBFTX_A		:=	libftx.a
LIBFTX_DIR		:=	$(EXT_DIR)/libftx
LIBFTX_INC		:=	$(LIBFTX_DIR)/$(INC_DIR)
LIBFTX			:=	$(LIBFTX_DIR)/$(LIBFTX_A)

SRC				:=	ps_nodes.c					ps_commands.c					ps_to_b.c	\
					ps_to_b_2.c					ps_to_a.c						ps_utils.c	\
					ps_utils_2.c				ps_utils_3.c

MANDATORY		:=	main.c
BNS				:=	main_bonus.c				checker.c

SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC))
MSRC			:=	$(addprefix $(SRC_DIR)/, $(MANDATORY))
BSRC			:=	$(addprefix $(SRC_DIR)/, $(BNS))

OBJ				:=	$(SRC:%.c=$(BUILD_DIR)/%.o)
MOBJ			:=	$(MSRC:%.c=$(BUILD_DIR)/%.o)
BOBJ			:=	$(BSRC:%.c=$(BUILD_DIR)/%.o)

DEPS			:=	$(OBJ:.o=.d) $(MOBJ:.o=.d) $(BOBJ:.o=.d)

DELETE			:=	*.out			**/*.out			.DS_Store	\
					**/.DS_Store	.dSYM/				**/.dSYM/

INCLUDES		:=	-I $(INC_DIR) -I $(LIBFTX_INC)
BUILD			:=	$(COMPILER) $(INCLUDES) $(CFLAGS)

all: $(NAME)

bonus: $(BNS_NAME)

$(NAME): $(OBJ) $(MOBJ)
	@$(BUILD) $(OBJ) $(MOBJ) $(LIBFTX) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BNS_NAME): $(BOBJ) | $(NAME)
	@$(BUILD) $(OBJ) $(BOBJ) $(LIBFTX) -o $(BNS_NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJ) $(MOBJ) $(BOBJ): | $(LIBFTX)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -I $(LIBFTX_INC) -c $< -o $@

submodules:
	@if [ ! -e "$(LIBFTX_DIR)/.git" ]; then																							\
		git submodule update --init $(LIBFTX_DIR); 																					\
		git -C $(LIBFTX_DIR) checkout $(shell git config -f .gitmodules submodule.$(LIBFTX_DIR).branch || echo main);				\
		git submodule update --remote --merge $(LIBFTX_DIR)																			\
		cd $(LIBFTX_DIR) && git submodule update --init $(SRC_DIR)/get_next_line;													\
		cd $(LIBFTX_DIR)/$(SRC_DIR)/get_next_line &&																				\
			git checkout $$(git config -f $(abspath $(LIBFTX_DIR))/.gitmodules submodule.src/get_next_line.branch || echo main);	\
	fi

$(LIBFTX): | submodules
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFTX_DIR) SUBMODULES_CMD= gnl $(filter debug valgrind,$(MAKECMDGOALS))

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME) $(BNS_NAME)
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFTX_DIR) fclean;
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) all

bre:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) bonus

debug: all

valgrind: all

print-%:
	$(info $($*))

-include $(DEPS)

.PHONY:	all bonus submodules	\
		clean fclean re bre		\
		debug valgrind print-%

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
