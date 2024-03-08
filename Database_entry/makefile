include ../common.mk
include ../components.mk



#--------------------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------------------

# Собрать результирующий файл (статическую библиотеку) данного компонента
build_component: ./$(COMPONENT_KEY_WORD).$(SLIB_EXT)

build_main: build_component
	g++ -g -Wall -Wextra -pedantic -std=c++20 -I $(PASSMAN_DIR_PATH) ./$(COMPONENT_KEY_WORD).$(SLIB_EXT) ./main.cpp

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
