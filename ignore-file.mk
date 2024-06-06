##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Ignore file Makefile
##

IGNORE_FILE				:=	.gitignore
IGNORED_FILES			:=
ifndef $(NAME)_LINK
IGNORED_FILES			+=  $($(NAME)_MAIN_SRC)
endif
IGNORE_FILE_RULES		+=	.PHONY

IGNORED_OBJS			:=	$($(NAME)_MAIN_OBJ) $($(NAME)_OBJS)
IGNORED_PCHS			:=	$($(NAME)_OBJS:$(OBJ_EXT)=$(PCH_EXT))
IGNORED_DEPS			:=	$($(NAME)_MAIN_DEP) $($(NAME)_DEPS)
IGNORED_CHDS			:=	$($(NAME)_CHDS)
IGNORED_BINS			:=	$($(NAME)_TARGET)

define nl


endef
define $(IGNORE_FILE)_CONTENT
##
## EPITECH PROJECT, $(shell date +%Y)
## $($(NAME)_DISPLAY)
## File description:
## $(IGNORE_FILE)
##

# Ignore object files
$(IGNORED_OBJS:=$(nl))
# Ignore precomiled headers
$(IGNORED_PCHS:=$(nl))
# Ignore dependency files
$(IGNORED_DEPS:=$(nl))$(IGNORED_CHDS:=$(nl))
# Ignore binary files
a.out
$(IGNORED_BINS:=$(nl))
# Ignore logs and reports
*.gcda
*.gcno
vgcore.*

# Ignore temporary files
*tmp*
*~
\#*#
.#*

# Miscellanous
$(IGNORED_FILES:%=%$(nl))
endef

$(IGNORE_FILE):
ifeq ($(wildcard $(IGNORE_FILE)),)
	@-echo 'Generating $@ file...'
else
	@-echo 'Updating $@ file...'
endif
	@echo -ne "$(subst $(nl),\n,$($@_CONTENT))" > $@
	@sed -i -E 's/^ //g' $@
