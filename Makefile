CC = clang
CC_FLAGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow

# final binary
BIN = cmain

# put all auto generated stuff to this build dir.
BUILD_DIR = ./build

# list of all .c source files.
CCS = main.c $(wildcard *.c)

# all .o files go to build dir.
OBJ = $(CCS:%.c=$(BUILD_DIR)/%.o)

# gcc/clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)

# default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

# actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $^ -o $@

# include all .d files
-include $(DEP)

# build target for every single object file.
# the potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm $(BUILD_DIR)/$(BIN) $(OBJ) $(DEP)
