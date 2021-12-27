CPP = g++ 
FLAGS = -O5 -Wall -W
RM  = rm -f
EXEC = a.out
VPATH = classes

OBJDIR = ../build

CLASSES = \
	 main.o \
	 address.o \
	 Account.o \
	 kart.o \
	 order.o \
	 page.o \
	 pageCode.o \
	 Product.o \
	 review.o \
	 search.o \
	 tracklog.o \
	 tstamp.o \

FUNCTS = \
	 main.o \

OBJECTS = \
	 $(addprefix $(OBJDIR)/, $(FUNCTS)) \
	 $(addprefix $(OBJDIR)/, $(CLASSES)) \

all: $(OBJECTS) compile touch 

$(OBJDIR)/%.o: %.cpp | $(CRDIR)/$(OBJDIR)
					 $(CPP) $(FLAGS) $(INCLUDES) -c $< -o $@
$(CRDIR)/%:
					 mkdir -p $*
run: | all
					 ./$(EXEC)
clean:  
					 $(RM) $(OBJDIR) $(EXEC)
compile: 
					 $(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC) 
touch:
					 @echo " "
					 @echo "Compilation done successfully..................."
					 @echo " "
