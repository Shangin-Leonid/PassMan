include ../../../common.mk
include ../../../components.mk



#--------------------------------------------------------------------------------------------------
# NAMES, FILES, DIRS
#--------------------------------------------------------------------------------------------------

MAIN := UT_TU_FileDataGeneratorMain
FILE_DATA_GENERATOR := UT_TU_FileDataGenerator

DATA_GENERATOR_DIR := ../Data_generator
DATA_GENERATOR_OBJ := $(OBJ_DIR)/UT_TU_DataGenerator.o

DATABASE_ENTRY_PATH := ../../../Database_entry


#--------------------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------------------

.PHONY: build run

build: ./$(MAIN).$(EXE_EXT)

RUN_PARAMS ?=
run:
	./$(MAIN).$(EXE_EXT) $(RUN_PARAMS)

./$(MAIN).$(EXE_EXT): build_DatabaseEntry_component build_DataGenerator ./$(OBJ_DIR)/$(FILE_DATA_GENERATOR).o ./$(OBJ_DIR)/$(MAIN).o
	$(COMPILER) $(COMPILER_FLAGS) ./$(OBJ_DIR)/$(MAIN).o ./$(OBJ_DIR)/$(FILE_DATA_GENERATOR).o $(DATA_GENERATOR_DIR)/$(DATA_GENERATOR_OBJ) $(DATABASE_ENTRY_PATH)/component.a

build_DataGenerator:
	$(MAKE) -C $(DATA_GENERATOR_DIR) $(DATA_GENERATOR_OBJ)

build_DatabaseEntry_component:
	$(MAKE) -C $(DATABASE_ENTRY_PATH) build_component



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
