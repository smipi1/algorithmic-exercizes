# Prints something in color
define printInColor
	echo -n "\033[$(1)m$(2)\033[0m\n"
endef

# Colorized output
RED=31
YELLOW=33
STEP_INFO_COLOR=$(RED)

# Tools to change case
toUppercase=$(shell echo "$1" | tr a-z A-Z)
toLowercase=$(shell echo "$1" | tr A-Z a-z)

# Prints the step information if called
define stepinfo
	@echo
	@$(call printInColor,$(STEP_INFO_COLOR),Making $@)
endef

define createBuildLogDir
	if ! test -d "$(BUILD_LOG_DIR)"; then \
		$(call printInColor,$(YELLOW),Creating $(BUILD_LOG_DIR)); \
		mkdir -p $(BUILD_LOG_DIR); \
	fi
endef

ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

vpath %.done $(BUILD_DIR)

define done
	@$(call printInColor,$(STEP_INFO_COLOR),Done $@)
	@touch $(BUILD_DIR)/$@
endef

# A literal space.
space :=
space +=

# Joins elements of the list in arg 2 with the given separator.
#   1. Element separator.
#   2. The list.
join-with = $(subst $(space),$1,$(strip $2))

.PHONY : print-%
print-%:
	@echo "$*=$($*)"
