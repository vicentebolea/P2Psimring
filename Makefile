# AUTHOR: Vicente Adolfo Bolea Sanchez
# EMAIL: <vicente.bolea@gmail.com>

include Makefile.vars

# Create the objects in the bin directory
%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $(BINDIR)/$@ $(OPTIONS)

#Linking
all:

build: packet lru 
	@echo Packing objects	
	$(AR) $(ARFLAGS) $(BINDIR)/$(OBJECTS) -o $(BINDIR)/objects.a
	@echo Done packing objects	

src:
	$(MAKE) -C $(SRCDIR)

depend:
	if	[ ! -f /usr/lib/libtynixml.* ]; do       \
		$(MAKE) -C ./lib                           \
	fi
	if	[ ! -f /usr/lib/libminIni.* ]; do        \
		$(MAKE) -C ./lib                           \
	fi

clean:
	-rm $(BINDIR)/*.o

dist:
	tar -cvzf unip2p_`date +"%d-%m-%y"`.tar.gz ./*
