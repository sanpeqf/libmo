# SPDX-License-Identifier: GPL-2.0-or-later
flags := -g -Wall -Werror -I src/ -D_GNU_SOURCE -DLIBMO_DEBUG
head := src/libmo.h src/bitmap.c src/pjwhash.c
head += examples/helper.c
obj := src/libmo.o
demo := examples/simple

extra := $(patsubst ./%,%, $(shell find -name "*.po"))
extra := $(addsuffix .mo,$(basename $(extra)))

ifeq ("$(origin V)", "command line")
BUILD_VERBOSE = $V
else
BUILD_VERBOSE =
endif

ifeq ($(BUILD_VERBOSE),1)
Q =
else
MAKEFLAGS += -s
Q = @
endif

all: $(demo) $(extra) FORCE

%.o:%.c $(head)
	$Q echo -e "\t\e[32mCC\e[0m\t" $@
	$Q gcc -o $@ -c $< $(flags)

%.mo:%.po
	$Q echo -e "\t\e[32mMSGFMT\e[0m\t" $@
	$Q msgfmt -o $@ $<

$(demo): $(obj) $(addsuffix .c,$(demo))
	$Q echo -e "\t\e[34mMKELF\e[0m\t" $@
	$Q gcc -o $@ $@.c $(obj) $(flags)

clean:
	$Q rm -f $(obj) $(extra) $(demo)

FORCE:
.PHONY: FORCE
