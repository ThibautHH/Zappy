##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Global Makefile
##

.SECONDEXPANSION:
NAME		:=	zappy
CMPS		:=	server ai gui
CMPS_DIRS	:=	Server Client Graphical

_pos		=	$(if $(findstring $1,$2),$(call _pos,$1,$	\
					$(wordlist 2,$(words $2),$2),x $3),$3)
pos			=	$(words $(call _pos,$1,$2))
compdir		=	$(word $(call pos,$(1:$(NAME)_%=%),$(CMPS)),$(CMPS_DIRS))
CS_IMG		:=	ghcr.io/epitech/coding-style-checker:latest
DOCKER		:=	[ -r /var/run/docker.sock ] && [ -w /var/run/docker.sock ]
DOCKER		:=	$(shell cmd="$$(which docker)" &&				\
				if ! ($(DOCKER)); then cmd="sudo $${cmd}"; fi;	\
				echo "$${cmd}")

_default:				all

$(CMPS:%=$(NAME)_%):	$$@[all]

%:
	@$(foreach c,$(CMPS:%=$(NAME)_%),$(MAKE) -C $(call compdir,$c) $@;)

$(CMPS:%=$(NAME)_%[%]):
	@$(MAKE) -C $(call compdir,$(@:%[$*]=%)) $(subst ;, ,$*)

coding-style:			fclean
	@-echo 'Checking coding style...'
	@$(DOCKER) run --rm -v .:/mnt $(CS_IMG) /mnt /mnt

.PHONY:					_default coding-style $(CMPS:%=$(NAME)_%)
