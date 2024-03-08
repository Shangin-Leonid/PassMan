include ../../../common.mk
include ../../../components.mk



#--------------------------------------------------------------------------------------------------
# NAMES, FILES, DIRS
#--------------------------------------------------------------------------------------------------

MAIN := UT_TU_DataGeneratorMain
DATA_GENERATOR := UT_TU_DataGenerator

COMPONENT_DIR := ../../../Database_entry
COMPONENT_SLIB := $(COMPONENT_DIR)/$(COMPONENT_KEY_WORD).$(SLIB_EXT)



#--------------------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------------------

.PHONY: build run

build: ./$(MAIN).$(EXE_EXT)

run:
	./$(MAIN).$(EXE_EXT)

# ./$(OBJ_DIR)/$(MAIN).o
./$(MAIN).$(EXE_EXT): build_Database_entry ./$(OBJ_DIR)/$(DATA_GENERATOR).o ./$(OBJ_DIR)/$(MAIN).o
	$(COMPILER) $(COMPILER_FLAGS) ./$(OBJ_DIR)/$(DATA_GENERATOR).o $(COMPONENT_SLIB) ./$(OBJ_DIR)/$(MAIN).o

build_Database_entry:
	$(MAKE) -C $(COMPONENT_DIR) build_component



#--------------------------------------------------------------------------------------------------
# INCLUDE FILES WITH DEPENDENCIES
#--------------------------------------------------------------------------------------------------

ifeq (,$(findstring help,$(MAKECMDGOALS)))
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
# Подключаем файлы зависимостей ('.d') соответствующих '.cpp' файлам.
$(D_FILES):
include $(wildcard $(D_FILES))
endif
endif
