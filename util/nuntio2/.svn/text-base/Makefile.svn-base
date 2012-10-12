all:

-include config.mk

BIN = nuntio
HDR = ast.hh compiler.hh generator.hh c-generator.hh lexer.hh \
      parser.hh visitor.hh c-struct-generator.hh c-serialize-generator.hh \
      c-size-generator.hh c-extract-generator.hh
SRC = parser.cc lexer.cc main.cc compiler.cc generator.cc c-generator.cc \
      c-struct-generator.cc c-serialize-generator.cc c-size-generator.cc \
      c-extract-generator.cc
OBJ = $(SRC:.cc=.o)

all: $(BIN)

$(BIN): deps.mk $(OBJ)
	$(CXX) $(OBJ) -o $@ -lm -lgc

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.hh %.cc: %.y
	bison --locations -t -v -rall -d -o $*.cc $*.y

%.hh %.cc: %.l
	flex --bison-locations --bison-bridge --never-interactive --header-file=$*.hh -o $*.cc $*.l

clean:
	rm -f {parser,lexer}.[hc][hc] parser *.o parser.output y.tab.h

distclean: clean
	rm -f $(BIN)

deps.mk: $(HDR) $(SRC)
	$(CXX) $(CXXFLAGS) -MM $(SRC) >$@

parser.o lexer.o: parser.hh parser.cc lexer.hh lexer.cc

-include deps.mk
