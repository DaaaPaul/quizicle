# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  quizicle_config = debug
endif

PROJECTS := quizicle

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

quizicle:
ifneq (,$(quizicle_config))
	@echo "==== Building quizicle ($(quizicle_config)) ===="
	@${MAKE} --no-print-directory -C . -f quizicle.make config=$(quizicle_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f quizicle.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   quizicle"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"