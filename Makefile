NAME = jojishiEngine
CFLAGS = -std=c++11
# CFLAGS += -Wall -Werror -Wextra  

# Debug
ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 -fno-inline
endif

# Profile
ifeq ($(PROF),yes)
	CFLAGS += -pg
endif

# Opti
ifeq ($(PROD),yes)
	CFLAGS += -O2
endif

# Sanitize
ifeq ($(SAN),yes)
	LDFLAGS += -fsanitize=address
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# Input
#SRC_SUBDIR += input
#SOURCES += readline.c

# main
SOURCES += main.cpp

# memory allocator
SRC_SUBDIR += memory_allocator
CFLAGS += -I memory_allocator/
SOURCES += stackAllocator.class.cpp

# asset_db_system
SRC_SUBDIR += asset_database_system
CFLAGS += -I asset_database_system
SOURCES += assetSystem.class.cpp
SOURCES += assetSystemWorker.class.cpp

# file loader
SRC_SUBDIR += file_loader
CFLAGS += -I file_loader
SOURCES += fileLoader.class.cpp

#	renderer
SRC_SUBDIR += renderer
CFLAGS += -I renderer
SOURCES += renderDataSys.class.cpp

# Generation
INC_PATH = inc
INC_PATH += assimp/include
SRC_PATH = src
CFLAGS += $(addprefix -I,$(INC_PATH))
vpath %.cpp $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Lib tierces
#LIB42_PATH = lib42
#LIB42 = $(LIB42_PATH)/lib42.a
#CFLAGS += -I $(LIB42_PATH)/inc
#LDFLAGS += -L $(LIB42_PATH) -l42

# Lib tierces
LIB_ASSIMP_PATH = assimp
CFLAGS += -I $(LIB_ASSIMP_PATH)/include
LDFLAGS += -L $(LIB_ASSIMP_PATH)/lib/ -lassimp

# Object files
OBJ_PATH = .obj
OBJECTS = $(SOURCES:%.cpp=$(OBJ_PATH)/%.o)

BUILD_DIR = $(OBJ_PATH) $(DEP_PATH)

# Rules
.PHONY: all

.SECONDARY: $(OBJECTS)

all: $(LIB42) $(DEPS) $(NAME)

$(NAME): $(OBJECTS) | $(LIB42)
	g++ -o $@ $^ $(LDFLAGS)
	@sleep 0.2
	aplay makefile_asset/oe.wav&

$(LIB42):
	$(MAKE) -C $(LIB42_PATH) all

$(OBJECTS): $(OBJ_PATH)/%.o: %.cpp | $(OBJ_PATH)
	g++ $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@-mkdir -p $@

.PHONY: clean fclean re sanitize unsanitize

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) -rf $(DEP_PATH)

sound: 
	aplay makefile_asset/roll.wav&

re: sound fclean all

sanitize:
	$(MAKE) -C ./ re SAN=yes DEBUG=yes

unsanitize:
	$(MAKE) -C ./ re DEBUG=yes

# Submodule
.PHONY: sub-update sub-init

sub-init:
	git submodule update --init --recursive

sub-update:
	git submodule update --remote --recursive

# Tests
.PHONY: check test-cleanup

check: all
	@$(MAKE) -C $(TEST_PATH) re
	@./$(TEST_EXEC)

# Tools
.PHONY: norme valgrind ctags clean-tools

norme:
	@ ! norminette -R CheckTopCommentHeader $(SRC_PATH) | grep -v -B 1 "^Norme"
	@ ! norminette -R CheckTopCommentHeader $(INC_PATH) | grep -v -B 1 "^Norme"

valgrind:
	valgrind --leak-check=full ./$(NAME)

callgrind:
	valgrind --tool=callgrind --callgrind-out-file=$(CG_OUTPUT_FILE) ./$(NAME)
	callgrind_annotate --auto=yes $(CG_OUTPUT_FILE)

ctags:
	ctags -R --tag-relative=yes --exclude='.git*' --exclude='test' --exclude='*.o' --exclude='*dSYM' --exclude='doc' --exclude='exercices'

clean-tools:
	$(RM) -r *.dSYM/
