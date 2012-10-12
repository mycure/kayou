#
# ---------- header -----------------------------------------------------------
#
# project       nuntio
#
# license       kaneton license
#
# file          /home/arkho/kaneton/tool/nuntio/tasks/build/parser.py
#
# created          [sun jul 29 14:21:35 2007]
# updated          [sun jul 29 14:22:01 2007]
#

#
# ---------- information ------------------------------------------------------
#
# Parse the stream for the message language. Take a look at Readme
# for more information
#

#
# ---------- imports ----------------------------------------------------------
#
import tokenizer
import syntax
import exception
import encoding


#
# ---------- globals ----------------------------------------------------------
#
g_scanner = None


#
# ---------- functions --------------------------------------------------------
#

#
# parse()
#
# Parse the stream
#
def		parse(stream):
  global	g_scanner

  g_scanner = tokenizer.c_tokenizer(stream)

  return parse_blocks()


#
# okToken(tok)
#
# Check if tok is a valid object
#
def		okToken(tok):
  if tok is None:
    raise exception.NuntioUnexpectedEndOfFile(g_scanner.nline)
  return True


#
# parse_blocks()
#
# Branch to message, rawblock or option parsing function
#
def		parse_blocks():
  tok = g_scanner.getToken()

  while tok:
    # 1) message
    if syntax.s_message == tok.group():
      parse_message()

    # 2) rawblock
    elif syntax.s_lrawblock == tok.group():
      parse_rawblock()

    # 3) options
    # XXX todo options
    else:
      raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				       "Invalid token: " + tok.group())
    tok = g_scanner.getToken()


#
# parse_rawblock()
#
# Get a block of raw data and keep it to yank it in the result file
#
def		parse_rawblock():
  #
  # XXX TODO
  #
  while True:
    tok = g_scanner.getToken()
    if okToken(tok) and tok.re.pattern == syntax.s_rrawblock:
      break


#
# parse_message()
#
# Parse the contain of a message
#
def		parse_message():
  id = g_scanner.getToken()

  # 1) Check the validity of the message identifiant
  if okToken(id) and id.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, id.start(),
				     "Invalid message name: " + id.group())
  # 2) Paye ta brace
  lbrace = g_scanner.getToken()
  if okToken(lbrace) and lbrace.group() != syntax.s_lbrace:
    raise exception.NuntioParseError(g_scanner.nline, lbrace.start(),
				     "Invalid token: " + lbrace.group() \
				     + ". '{' expected")
  # 3) Begin the encoding of a new message
  encoding.new(id.group())

  # 4) Parse the contain of the message
  parse_declarations()

  # 5) Finalize the encoding of the message
  encoding.end(id.group())


#
# parse_declarations()
#
# Parse the types of the message language
#
def		parse_declarations():
  while True:
    dec = g_scanner.getToken()
    # 1) Integers
    if okToken(dec) and dec.group() == syntax.s_integer:
      parse_integer()
    # 2) Signed integers
    elif dec.group() == syntax.s_signed:
      parse_sinteger()
    # 3) Unsigned integers
    elif dec.group() == syntax.s_unsigned:
      parse_uinteger()
    # 4) Doubles
    elif dec.group() == syntax.s_double:
      parse_double()
    # 5) Strings
    elif dec.group() == syntax.s_string:
      parse_string()
    # 6) Structs
    elif dec.group() == syntax.s_struct:
      parse_struct()
    # 7) raw data
    elif dec.group() == syntax.s_raw:
      parse_raw()
    # 8) Right brace, end of the declarations
    elif dec.group() == syntax.s_rbrace:
      break
    else:
      raise exception.NuntioParseError(g_scanner.nline, dec.start(),
				       "Unexpected token: " + dec.group())

#
# parse_raw()
#
# Parse raw data
#
def		parse_raw():
  dim = None

  # 1) Get the size of the raw data
  tok = g_scanner.getToken()
  if okToken(tok) and tok.re.pattern == syntax.s_lchevron:
    tok, dim = parse_array()

  # 2) Get the id
  if okToken(tok) and tok.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				     "Invalid variable name: " + tok.group())
  encoding.process(encoding.raw, tok.group(), dim)


#
# Parse structures
#
def		parse_struct():
  dim = None

  tok = g_scanner.getToken()

  # 1) Check the size
  if okToken(tok) and tok.re.pattern == syntax.s_lchevron:
    tok, dim = parse_array()

  # 2) Check the validity of the variable name
  if okToken(tok) and tok.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				     "Invalid variable name: " + tok.group())

  # 3) Begin to encode the structure
  encoding.new(tok.group(), dim)
  lbrace = g_scanner.getToken()
  if okToken(lbrace) and lbrace.group() != syntax.s_lbrace:
    raise exception.NuntioParseError(g_scanner.nline, lbrace.start(),
				     "Unexpected token: " + lbrace.group() \
				     + ". '{' expected")

  # 4) Parse the contain
  parse_declarations()

  # 5) Work done
  encoding.end(tok.group())


#
# parse_uinteger()
#
# Parse an unsigned integer
#
def		parse_uinteger():
  dec = g_scanner.getToken()

  # 1) Check it is an integer declaration
  if okToken(dec) and dec.group() != syntax.s_integer:
    raise exception.NuntioParseError(g_scanner.nline, dec.start(),
				     "Unexpected token: " + dec.group()\
				     + ': "integer" expected')
  # 2) Parse integer
  parse_integer("unsigned")


#
# parse_sinteger()
#
# Parse a signed integer
#
def		parse_sinteger():
  dec = g_scanner.getToken()

  # 1) Check for an integer declaration
  if okToken(dec) and dec.group() != syntax.s_integer:
    raise exception.NuntioParseError(g_scanner.nline, dec.start(),
				     "Unexpected token: " + dec.group()\
				     + ': "integer" expected')
  # 2) Parse integer
  parse_integer("signed")


#
# parse_integer()
#
# Parse integer declaration
#
def		parse_integer(sign = None):
  size = None
  dim = None
  tok = g_scanner.getToken()

  # 1) Look if the size is explained
  if okToken(tok) and "\\" + tok.group() == syntax.s_lparen:
    size = g_scanner.getToken()
    if okToken(size) and size.re.pattern != syntax.s_digit:
      raise exception.NuntioParseError(g_scanner.nline, size.start(),
				       size.group() + ": Size integer expected")

    if size.group() != "32" and size.group() != "64" and size.group() != "128":
	raise exception.NuntioBadIntegerSize(g_scanner.nline, size.group())

    rparen = g_scanner.getToken()
    if okToken(rparen) and "\\" + rparen.group() != syntax.s_rparen:
	raise exception.NuntioParseError(g_scanner.nline, rparen.start(),
					 "Unexpected token: " + rparen.group()\
					 + ' ")" expected')
    tok = g_scanner.getToken()

  # 2) Look for an array of intger declaration
  if okToken(tok) and tok.re.pattern == syntax.s_lchevron:
    tok, dim = parse_array()

  # 3) Check that the variable name is correct
  if okToken(tok) and tok.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				     "Invalid variable name: " + tok.group())
  # 4) /* No comment */
  if sign is None:
    sign = "signed"

  if sign == 'signed':
    sign = "int"
  else:
    sign = "uint"

  # 5) If the size is not explain, 32 is taken
  if size is None:
    sz = "32"
  else:
    sz = size.group()

  # 6) Let's encode
  encoding.process(sign + sz, tok.group(), dim)


#
# parse_double()
#
# Parse a double
#
def		parse_double():
  dim = None

  # 1) Check for array decl
  tok = g_scanner.getToken()
  if okToken(tok) and tok.re.pattern == syntax.s_lchevron:
    tok, dim = parse_array()

  # 2) Check the variable name
  if okToken(tok) and tok.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				     "Invalid variable name: " + tok.group())

  # 3) Encode
  encoding.process(encoding.double, tok.group(), dim)


#
# parse_string()
#
# Parse a string
#
def		parse_string():
  dim = None

  # 1) Check for array decl
  tok = g_scanner.getToken()
  if okToken(tok) and tok.re.pattern != syntax.s_lchevron:
    raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				     "Unexpected token: " + tok.group()\
				     + ": '<' expected")
  # 2) Parse the array declaration
  id, dim = parse_array()

  # 3) Check the variable name
  if okToken(id) and id.re.pattern != syntax.s_word:
    raise exception.NuntioParseError(g_scanner.nline, id.start(),
				     "Invalid variable name: " + id.group())

  # 4) Encode
  encoding.process(encoding.string, id.group(), dim)


#
# parse_array()
#
# Parse an array declaration
#
def		parse_array():
  dim = []

  while True:
    var = None
    tok = g_scanner.getToken()

    # 1) Check if this array dim has a variable for the current size
    if okToken(tok) and tok.re.pattern == syntax.s_word:
      var = tok.group()
      # 2) Need a colon like delimiter
      colon = g_scanner.getToken()
      if okToken(colon) and colon.re.pattern != syntax.s_colon:
	raise exception.NuntioParseError(g_scanner.nline, colon.start(),
					 "Unexpected token: " + tok.group()\
					 + ': ":" expected')
      tok = g_scanner.getToken()

    # 3) Get the size of this array
    if okToken(tok) and tok.re.pattern != syntax.s_digit:
      raise exception.NuntioParseError(g_scanner.nline, tok.start(),
				       "Array size expected: " + tok.group())

    # 4) Add this new array and the variable name
    dim.append({'max' : tok.group(), 'id' : var})

    # 5) Array decl ends with a '>'
    rchevron = g_scanner.getToken()
    if okToken(rchevron) and rchevron.re.pattern != syntax.s_rchevron:
      raise exception.NuntioParseError(g_scanner.nline, rchevron.start(),
				       "Unexpected token: " + rchevron.group()\
				       + ": '>' expected")
    tok = g_scanner.getToken()

    # 6) If the token is a '<', continue with a new array
    if okToken(tok) and tok.re.pattern != syntax.s_lchevron:
      break

  return tok, dim
