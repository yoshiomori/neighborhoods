VPATH = src
objects = main.o safe.o
objdir := objects
objs := $(addprefix $(objdir)/, $(objects))

c_neig: CFLAGS = -Wall -pedantic -ansi -g
c_neig: $(objs)
	cc -o c_neig $(objs)

$(objdir)/%.o : %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(objs): | $(objdir)

$(objdir):
	mkdir $(objdir)

clean:
	if [ -d "objects" ]; then rm -fr objects; fi
	if [ -x "c_neig" ]; then rm c_neig; fi
	find ./ -name '*~' -exec rm {} \;
