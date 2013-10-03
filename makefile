VPATH = src
objects = main.o data.o alphabet.o constant.o vertice.o processing.o word_table.o
objdir := objects
objs := $(addprefix $(objdir)/, $(objects))

neighborhood: $(objs)
	cc -o neighborhood $(objs)

$(objdir)/%.o : %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(objs): | $(objdir)

$(objdir):
	mkdir $(objdir)

clean:
	if [ -d "objects" ]; then rm -fr objects; fi
	if [ -x "neighborhood" ]; then rm neighborhood; fi
