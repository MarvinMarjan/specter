BUILD_PATH = build
DEBUG_PATH = $(BUILD_PATH)/debug
RELEASE_PATH = $(BUILD_PATH)/release

LIB_PATH = lib

# define RELEASE to build with release configuration, debug will be used otherwise
ifdef RELEASE
	OPTIMIZATION = -O3
	OUT_PATH = $(RELEASE_PATH)
	LIB_NAME = specter
else
	OPTIMIZATION = -Og
	OUT_PATH = $(DEBUG_PATH)
	LIB_NAME = specter_d
endif

CC = g++
CPP_VERSION = --std=c++20

OUT_NAME = lib$(LIB_NAME).a
OUT_LIB_PATH = $(LIB_PATH)/$(OUT_NAME)

TEST_PATH = test
TEST_FILE = $(TEST_PATH)/main.cpp
TEST_APP_NAME = test
TEST_APP_PATH = $(TEST_PATH)/$(TEST_APP_NAME)
TEST_LIBS = -lspecter_d -ltinfo

INCLUDE_PATH = ./include

CPP_COMPILE_FLAGS = -I$(INCLUDE_PATH) $(OPTIMIZATION) $(CPP_VERSION)

SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

FULL_OBJECTS = $(addprefix $(OUT_PATH)/, $(notdir $(OBJECTS)))



.PHONY:
testc: $(TEST_APP_PATH)
	@ echo Running test...
	@ echo
	@ $(TEST_APP_PATH)


.PHONY:
run:
	@ echo Running test...
	@ echo
	@ $(TEST_APP_PATH)


$(TEST_APP_PATH): $(TEST_FILE) $(OUT_LIB_PATH)
	@ echo Compiling test with library $(LIB_NAME)
	@ $(CC) $< -o $(TEST_APP_PATH)


# links object files into a executable
.PHONY:
$(OUT_LIB_PATH) build: $(OBJECTS)
	@ echo Linking objects: $(FULL_OBJECTS)
	@ ar rcs $(OUT_LIB_PATH) $(FULL_OBJECTS)
	@ echo Library created at $(OUT_LIB_PATH)


# compiles source files into objects
$(OBJECTS): %.o: %.cpp
	@ echo Compiling $<
	@ $(CC) -c $< -o $(addprefix $(OUT_PATH)/, $(notdir $@)) $(CPP_COMPILE_FLAGS)


# cleans up build folder
.PHONY:
clean:
	@ rm -r $(DEBUG_PATH)/*
	@ rm -r $(RELEASE_PATH)/*