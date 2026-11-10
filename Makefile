VERSION := 5.4

PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/share/man

CC ?= cc

PKG_CONFIG ?= pkg-config

BLD_DIR ?= build
SRC_DIR ?= src
SCR_DIR ?= scripts
MAN_DIR ?= man

DMENU_DEPS := $(addprefix $(BLD_DIR)/,dmenu.o drw.o util.o)
STEST_DEPS := $(BLD_DIR)/stest.o
PC_DEPS    := xinerama fontconfig x11 xft freetype2

		 CFLAGS ?= -Werror -Os
override CFLAGS += -std=c99 -Wpedantic -Wall

LDFLAGS  ?=
CPPFLAGS := $(shell $(PKG_CONFIG) --cflags $(PC_DEPS))    \
			-DXINERAMA -D_DEFAULT_SOURCE -D_BSD_SOURCE    \
			-D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L \
			-DVERSION=\"$(VERSION)\"
LDLIBS   := $(shell $(PKG_CONFIG) --libs $(PC_DEPS))

TMPCFG  := $(SRC_DIR)/config.h
CONFIG  := $(shell test -f config.h              \
				&& echo config.h                 \
			  	|| echo $(SRC_DIR)/config.def.h)
SCRIPTS := $(patsubst $(SCR_DIR)/%,%,$(wildcard $(SCR_DIR)/*))

$(BLD_DIR):
	mkdir $@

$(TMPCFG): $(CONFIG)
	@if [ "$<" = config.h ]; then \
		echo '#include "../$<"' > $@; \
	else \
		cp -f $< $@; \
	fi

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(DMENU_DEPS): $(TMPCFG)

$(BLD_DIR)/dmenu: $(DMENU_DEPS)
	$(CC) -o $@ $(DMENU_DEPS) $(LDFLAGS) $(LDLIBS)

$(BLD_DIR)/stest: $(STEST_DEPS)
	$(CC) -o $@ $(STEST_DEPS) $(LDFLAGS)

all: dmenu stest

dmenu: $(BLD_DIR)/dmenu

stest: $(BLD_DIR)/stest

get-applied:
	@git log --oneline base-$(VERSION)..HEAD \
		| grep '^\([[:digit:]]\|[[:alpha:]]\)\+ applied patch:' \
		| sed 's/applied patch//'

get-added:
	@git log --oneline base-$(VERSION)..HEAD \
		| grep '^\([[:digit:]]\|[[:alpha:]]\)\+ added patch:' \
		| sed 's/added patch//'

get-config:
	@git log --oneline base-$(VERSION)..HEAD \
		| grep '^\([[:digit:]]\|[[:alpha:]]\)\+ config:' \
		| sed 's/config//'

clean-bld:
	rm -rf $(BLD_DIR)

clean-src:
	rm -f $(TMPCFG) $(SRC_DIR)/*.orig $(SRC_DIR)/*.rej

clean: clean-bld clean-src

install-bins: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(BLD_DIR)/dmenu $(BLD_DIR)/stest $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu
	chmod 755 $(DESTDIR)$(PREFIX)/bin/stest

install-scripts:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	@for script in $(SCRIPTS); do 											  \
		printf "installing script: %s\n" $$script; 							  \
		cp -f $(SCR_DIR)/$$script $(DESTDIR)$(PREFIX)/bin/$$script || exit 1; \
		chmod 755 $(DESTDIR)$(PREFIX)/bin/$$script || exit 1;  			      \
	done

install-mans:
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < $(MAN_DIR)/dmenu.1 \
		> $(DESTDIR)$(MANPREFIX)/man1/dmenu.1
	sed "s/VERSION/$(VERSION)/g" < $(MAN_DIR)/stest.1 \
		> $(DESTDIR)$(MANPREFIX)/man1/stest.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/dmenu.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/stest.1

install: install-bins install-scripts install-mans

uninstall-bins:
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu
	rm -f $(DESTDIR)$(PREFIX)/bin/stest

uninstall-scripts:
	rm -f $(addprefix $(DESTDIR)$(PREFIX)/bin/,$(SCRIPTS))

uninstall-mans:
	rm -f $(DESTDIR)$(MANPREFIX)/man1/dmenu.1
	rm -f $(DESTDIR)$(MANPREFIX)/man1/stest.1

uninstall: uninstall-bins uninstall-scripts uninstall-mans

.DEFAULT_GOAL := all
.PHONY: all dmenu stest 										\
	get-config get-added get-applied 							\
	clean-bld clean-src clean 									\
	install-bins install-scripts install-mans install  			\
	uninstall-bins uninstall-scripts uninstall-mans uninstall
