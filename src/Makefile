
# vim: ft=make noexpandtab

OBJECTS := crupid.o parser.o bstrlib/bstrlib.o
OBJECTS_TESTS := $(OBJDIR_TESTS)/check.o $(OBJDIR_TESTS)/check_crupid.o

BINDIR_LINUX = ../bin/linux

OBJDIR_TESTS = ../obj/test_crupid

MD=mkdir -v -p

CFLAGS := -Wall -Werror
LDFLAGS += -lfcgi

crupid: OBJDIR := ../obj/linux

test_crupid: LDFLAGS += $(shell pkg-config --libs check)
test_crupid: CFLAGS += -DCHECK -g -Wall -Werror
test_crupid: OBJDIR := $(OBJDIR_TESTS)

all: crupid

crupid: $(addprefix ../obj/linux/,$(OBJECTS))
	$(CC) -o $@ $^ $(LDFLAGS)

../obj/linux/%.o: $(notdir %.c)
	$(MD) $(addprefix ../obj/linux/,$(shell dirname "$<"))
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR_TESTS)/%.o: ../tests/$(notdir %.c)
	$(MD) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf ../obj; \
	rm -f test_crupid; \
	rm -rf ../bin

