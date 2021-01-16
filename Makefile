CC = clang


TARGET_EXEC ?= main.out

BUILD_DIR ?= ./build
OUTPUT_DIR ?= ./output
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?=  $(INC_FLAGS)  -MMD -MP  -g -Wall 
CFLAGS := -lGL -lstdc++ -lglfw -lGLEW  -lc -lrt -lm -ldl

$(OUTPUT_DIR)/$(TARGET_EXEC): $(OBJS)
	rm -rf output
	mkdir output
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS)  -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC)  $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) 
	$(RM) -r $(OUTPUT_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p