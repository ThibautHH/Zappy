##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Tests Makefile
##

$(NAME)_TESTS			:=	$(NAME)_tests

$($(NAME)_TESTS)_SRCS	:=	$(shell find $(TESTS_DIR) -type f				\
							-name '*$(SRC_EXT)' ! -name ".*" 2>/dev/null)

$($(NAME)_TESTS)_OBJS	:=													\
	$($($(NAME)_TESTS)_SRCS:%$(SRC_EXT)=$(OBJ_DIR)%$(OBJ_EXT))

$($(NAME)_TESTS)_DEPS	:=	$($($(NAME)_TESTS)_OBJS:$(OBJ_EXT)=$(DEP_EXT))

$($(NAME)_TESTS)_CHDS	:=													\
	$(wildcard $($($(NAME)_TESTS)_SRCS:$(SRC_EXT)=$(HDR_EXT)))
$($(NAME)_TESTS)_CHDS	:=													\
	$($($(NAME)_TESTS)_CHDS:$(SRC_DIR)%$(HDR_EXT)=$(OBJ_DIR)%$(CHD_EXT))

include	$($($(NAME)_TESTS)_DEPS) $($($(NAME)_TESTS)_CHDS)

IGNORED_OBJS			+=	$($($(NAME)_TESTS)_OBJS)
IGNORED_PCHS			+=	$($($(NAME)_TESTS)_OBJS:$(OBJ_EXT)=$(PCH_EXT))
IGNORED_DEPS			+=	$($($(NAME)_TESTS)_DEPS)
IGNORED_CHDS			+=	$($($(NAME)_TESTS)_CHDS)
IGNORED_BINS			+=	$($(NAME)_TESTS)

IGNORE_FILE_RULES		+=	tests tests-debug

$(NAME)_TEST_SCRIPT	:=	$(TESTS_DIR)test-arguments
ifdef $(NAME)_LINK
$($(NAME)_TESTS)_REQS	:=	$($(NAME)_OBJS)
else
$($(NAME)_TESTS)_REQS	:=	$($(NAME)_TARGET)
$($(NAME)_TESTS):		LIBS += $(NAME)
endif
$($(NAME)_TESTS):		LIBS += criterion
$($(NAME)_TESTS):		GCCFLAGS += --coverage
$($(NAME)_TESTS):		$($($(NAME)_TESTS)_REQS) $($($(NAME)_TESTS)_OBJS)
	@-echo 'Linking $@ binary...'
ifdef $(NAME)_LINK
	@$(LINKER) $(GCCFLAGS) -o $@ $^	$(LDLIBS) $(LDFLAGS)
else
	@$(LINKER) $(GCCFLAGS) -o $@ $(filter-out $<,$^) $(LDLIBS) $(LDFLAGS)
endif

$($($(NAME)_TESTS)_OBJS):	GCCFLAGS := $(filter-out --coverage,$(GCCFLAGS))

TESTFLAGS				+=	$(TEST_SUITES:%=--filter '%/*')

tests:					$($(NAME)_TESTS)
ifdef $(NAME)_TEST_SCRIPT
tests:					$(NAME)
	@-echo 'Running test script...'
	@$($(NAME)_TEST_SCRIPT)
endif
	@-echo 'Running tests...'
	@./$($(NAME)_TESTS) --verbose $(TESTFLAGS)

tests-debug:			GCCFLAGS += -g
tests-debug:			$($(NAME)_TESTS)
	@-echo 'Debugging tests...'
	@-valgrind --trace-children=yes	./$($(NAME)_TESTS) --verbose $(TESTFLAGS)

coverage:				tests
	@-echo 'Generating coverage report...'
	@gcovr --exclude $(TESTS_DIR) --txt-metric line
	@gcovr --exclude $(TESTS_DIR) --txt-metric decision

tests-fclean:			fclean
	@-echo 'Deleting $($(NAME)_TESTS)...'
	@$(RM) $($(NAME)_TESTS)

tests-re:				tests-fclean tests

tests_run:				TESTFLAGS += --always-succeed
tests_run:				$($(NAME)_TESTS)
	@./$($(NAME)_TESTS) --verbose $(TESTFLAGS)
	@-find -type f \( -name '*.gcno' -o -name '*.gcda' \) -exec mv -- {} .. \;

.PHONY:					tests tests-debug coverage tests-fclean tests-re	\
						tests_run
