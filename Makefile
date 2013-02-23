# AUTHOR: Vicente Adolfo Bolea Sanchez
# EMAIL: <vicente.bolea@gmail.com>

include Makefile.vars

# Create the objects in the bin directory
%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $(BINDIR)/$@ $(OPTIONS)

#Linking
all: 
	$(MAKE) -C $(LIBDIR)
	$(MAKE) -C $(SRCDIR)

#build: packet lru 
	#@echo Packing objects	
	#$(AR) $(ARFLAGS) $(BINDIR)/$(OBJECTS) -o $(BINDIR)/objects.a
	#@echo Done packing objects	

src:
	$(MAKE) -C $(SRCDIR)

clean:
	$(MAKE) -C $(SRCDIR) clean
	$(MAKE) -C $(LIBDIR) clean

dist:
	tar -cvzf unip2p_`date +"%d-%m-%y"`.tar.gz ./*
