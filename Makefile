BUILD_PATH = build
DEBUG_PATH = $(BUILD_PATH)/debug
RELEASE_PATH = $(BUILD_PATH)/release



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
CVERSION = c++23

OUT_NAME = lib$(LIB_NAME).a

OUT_LIB = $(OUT_PATH)/$(OUT_NAME)

TEST_PATH = test
TEST_FILE = $(TEST_PATH)/main.cpp


INCLUDE_PATH = ./include



SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

FULL_OBJECTS = $(addprefix $(OUT_PATH)/, $(notdir $(OBJECTS)))



# runc: $(OUT_LIB)
# 	@ echo Running...
# 	@ $(OUT_LIB)


# run:
# 	@ echo Running;
# 	@ $(OUT_LIB)


# links object files into a executable
.PHONY:
$(OUT_LIB) build: $(OBJECTS)
	@ echo Linking objects: $(FULL_OBJECTS)
	@ ar rcs $(OUT_LIB) $(FULL_OBJECTS)
	@ echo Library created at $(OUT_LIB)




# compiles source files into objects
$(OBJECTS): %.o: %.cpp
	@ echo Compiling $<
	@ g++ -c $< -o $(addprefix $(OUT_PATH)/, $(notdir $@)) $(OPTIMIZATION) -I $(INCLUDE_PATH) --std=$(CVERSION)



# cleans up build folder
.PHONY:
clean:
	@ rm -r $(DEBUG_PATH)/*
	@ rm -r $(RELEASE_PATH)/*