
CC := clang++

SRCDIR := src/test
BUILDDIR := build
TARGETDIR := bin
TARGET := bin/test

# CPP files
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
# remove the src path and add the build path and the .o extension
OBJECTS := $(addprefix $(BUILDDIR)/,$(patsubst %.cpp,%.o,$(notdir $(SOURCES))))

CFLAGS := `llvm-config --cxxflags --ldflags --system-libs --libs core`

INC := 
# -I/usr/local/include -I $(SRCDIR)

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $^ $(CFLAGS) -o $(TARGET)"
	$(CC) $^ $(CFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
