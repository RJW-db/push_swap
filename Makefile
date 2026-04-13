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
LIBFTX_PATH		:=	$(EXT_LIB)/$(LIB_A)

SRC				:=	ps_nodes.c					ps_commands.c					ps_to_b.c	\
					ps_to_b_2.c					ps_to_a.c						ps_utils.c	\
					ps_utils_2.c				ps_utils_3.c

MANDATORY		:=	main.c
BNS				:=	main_bonus.c				checker.c

# Generate source file names
SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC))
MSRC			:=	$(addprefix $(SRC_DIR)/, $(MANDATORY))
BSRC			:=	$(addprefix $(SRC_DIR)/, $(BNS))

# Generate object file names
OBJ				:=	$(SRC:%.c=$(BUILD_DIR)/%.o)
MOBJ			:=	$(MSRC:%.c=$(BUILD_DIR)/%.o)
BOBJ			:=	$(BSRC:%.c=$(BUILD_DIR)/%.o)

# Generate Dependency files
DEPS			:=	$(OBJ:.o=.d) $(MOBJ:.o=.d) $(BOBJ:.o=.d)

DELETE			:=	*.out			**/*.out			.DS_Store	\
					**/.DS_Store	.dSYM/				**/.dSYM/

INCLUDES		:=	-I $(INC_DIR) -I $(EXT_INC)
BUILD			:=	$(COMPILER) $(INCLUDES) $(CFLAGS)

all: libftx_submodules $(NAME)

$(OBJ) $(MOBJ) $(BOBJ): | $(LIBFTX_PATH)

$(NAME): $(OBJ) $(MOBJ)
	@$(BUILD) $(OBJ) $(MOBJ) $(EXT_LIB)/libftx.a -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BNS_NAME): $(BOBJ) | $(NAME)
	@$(BUILD) $(OBJ) $(BOBJ) $(EXT_LIB)/libftx.a -o $(BNS_NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -I $(EXT_INC) -c $< -o $@

# $(EXT_LIB)/$(SRC_DIR)/get_next_line/.git:
# 	git submodule update --init extern_libary/libftx
# 	git -C $(EXT_LIB) checkout main
# 	cd $(EXT_LIB) && git submodule update --init src/get_next_line
# 	cd $(EXT_LIB)/src/get_next_line && \
# 		git checkout $$(git config -f $(abspath $(EXT_LIB))/.gitmodules submodule.src/get_next_line.branch || echo main)

# $(LIBFTX_PATH): | $(EXT_LIB)/$(SRC_DIR)/get_next_line/.git
# 	@$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) SUBMODULES_CMD= gnl $(LIB_A) $(filter debug valgrind,$(MAKECMDGOALS))

$(EXT_LIB)/$(SRC_DIR)/get_next_line/.git:
	git submodule update --init extern_libary/libftx
	git -C $(EXT_LIB) checkout main
	cd $(EXT_LIB) && git submodule update --init src/get_next_line
	cd $(EXT_LIB)/src/get_next_line && \
		git checkout $$(git config -f $(abspath $(EXT_LIB))/.gitmodules submodule.src/get_next_line.branch || echo main)

$(LIBFTX_PATH): | $(EXT_LIB)/$(SRC_DIR)/get_next_line/.git
	@$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) SUBMODULES_CMD= gnl $(LIB_A) $(filter debug valgrind,$(MAKECMDGOALS))

# Optionally, keep this for broader submodule updates if you want:
libftx_submodules:
	@if [ -d "$(EXT_LIB)/.git" ]; then \
		cd $(EXT_LIB) && git submodule update --init; \
		cd $(EXT_LIB) && git submodule update --remote --merge; \
	fi

bonus: $(BNS_NAME)

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME) $(BNS_NAME)
	@$(MAKE) $(PRINT_NO_DIR) -C $(EXT_LIB) fclean;
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) all

bre:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) bonus

debug: all

print-%:
	$(info $($*))

-include $(DEPS)

.PHONY:	all bonus libftx submodule_build submodule clean fclean re bre debug print-%

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
