include ../common.mk

#--------------------------------------------------------------------------------------------------
# Directories and their structure
#--------------------------------------------------------------------------------------------------

GOOGLE_TEST_INCLUDE_PATH := /usr/local/include
COMPONENT_NAMES ?= $(subst Unit_tests,,$(subst /,,$(subst ../,,$(sort $(dir $(wildcard ../*/))))))



#--------------------------------------------------------------------------------------------------
# File names
#--------------------------------------------------------------------------------------------------

UT_MAIN_TEST_FILE := UT_TestMain

GOOGLE_TEST_STATIC_LIB_PATH := /lib/x86_64-linux-gnu/libgtest.a

COMPONENTS := $(addprefix ../,$(addsuffix /component.$(SLIB_EXT),$(COMPONENT_NAMES)))

UT_CPP_FILES := $(wildcard ./*/$(CPP_DIR)/*.cpp)
UT_OBJ_FILES := $(subst $(CPP_DIR),$(OBJ_DIR),$(subst .cpp,.o,$(UT_CPP_FILES)))
UT_D_FILES := $(UT_MAIN_TEST_FILE).d $(subst $(CPP_DIR),$(D_DIR),$(subst .cpp,.d,$(UT_CPP_FILES)))



#--------------------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------------------

# Сборка всех тестов.
build: ./$(UT_MAIN_TEST_FILE).$(EXE_EXT)

# Запуск всех тестов.
TEST_CASES_FILTER ?= *
run_tests:
	./$(UT_MAIN_TEST_FILE).$(EXE_EXT) --gtest_filter=$(TEST_CASES_FILTER)

# Создание единого для всех тестов исполняемого файла.
./$(UT_MAIN_TEST_FILE).$(EXE_EXT): $(COMPONENTS) $(UT_OBJ_FILES) $(UT_MAIN_TEST_FILE).cpp
	$(COMPILER) $(COMPILER_FLAGS) -L $(GOOGLE_TEST_INCLUDE_PATH) -l gtest -l pthread $(UT_OBJ_FILES) $(COMPONENTS) $(GOOGLE_TEST_STATIC_LIB_PATH) $(UT_MAIN_TEST_FILE).cpp



# Компиляция компонентов.
define component_goal_template =
../$(1)/component.$$(SLIB_EXT):
	@echo "Component $$@"
	$$(MAKE) -C ../$(1) build_component
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call component_goal_template,$(component))))

# Создание и обновление объектных файлов.
define obj_file_goal_template =
./$(1)/$$(OBJ_DIR)/%.o: ./$(1)/$$(D_DIR)/%.d | ./$(1)/$$(OBJ_DIR)
	$$(COMPILER) $$(COMPILER_FLAGS) -I $(GOOGLE_TEST_INCLUDE_PATH) ./$(1)/$$(CPP_DIR)/$$*.cpp
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call obj_file_goal_template,$(component))))

# Создание и обновление файлов зависимостей.
define d_file_goal_template =
./$(1)/$$(D_DIR)/%.d: | ./$(1)/$$(D_DIR)
	$$(COMPILER) -MM -MT './$(1)/$$(OBJ_DIR)/$$*.o ./$$@' -o $$@ ./$(1)/$$(CPP_DIR)/$$*.cpp \
	-I $$(PASSMAN_DIR_PATH)
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call d_file_goal_template,$(component))))

# Создание директорий для объектных файлов.
define obj_dir_goal_template =
./$(1)/$$(OBJ_DIR):
	mkdir -p $$@
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call obj_dir_goal_template,$(component))))

# Создание директорий для файлов зависимостей.
define d_dir_goal_template =
./$(1)/$$(D_DIR):
	mkdir -p $$@
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call d_dir_goal_template,$(component))))



#--------------------------------------------------------------------------------------------------
# CLEAN
#--------------------------------------------------------------------------------------------------

# Шаблон для генерации правил "clean" и "clean_all" для запуска в директории каждого компонента.
define clean_component_goal_template =
$(1)_component_$(2):
	$(MAKE) -C ../$(2) $(1)
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call clean_component_goal_template,clean,$(component))))
$(foreach component,$(COMPONENT_NAMES),$(eval $(call clean_component_goal_template,clean_all,$(component))))
CLEAN_COMPONENT_GOALS := $(addprefix clean_component_, $(COMPONENT_NAMES))
CLEAN_ALL_COMPONENT_GOALS := $(addprefix clean_all_component_, $(COMPONENT_NAMES))

# Шаблон для генерации правил "clean" и "clean_all" для запуска в директории каждого компонента тестов.
define clean_test_component_goal_template =
clean_test_component_$(1):
	rm -r -f ./$(1)/$(OBJ_DIR)
	rm -r -f ./$(1)/$(D_DIR)
endef
$(foreach component,$(COMPONENT_NAMES),$(eval $(call clean_test_component_goal_template,$(component))))
CLEAN_TEST_COMPONENT_GOALS := $(addprefix clean_test_component_, $(COMPONENT_NAMES))

clean_tests: $(CLEAN_TEST_COMPONENT_GOALS)

clean: $(CLEAN_COMPONENT_GOALS) clean_test

clean_all: $(CLEAN_ALL_COMPONENT_GOALS) clean_tests
	rm -f ./$(UT_MAIN_TEST_FILE).$(EXE_EXT)



#--------------------------------------------------------------------------------------------------
# INCLUDE FILES WITH DEPENDENCIES
#--------------------------------------------------------------------------------------------------

ifeq (,$(findstring help,$(MAKECMDGOALS)))
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
# Подключаем файлы зависимостей ('.d') соответствующих '.cpp' файлам.
$(UT_D_FILES):
include $(wildcard $(UT_D_FILES))
endif
endif
