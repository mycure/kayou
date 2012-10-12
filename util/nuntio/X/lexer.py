#
# ---------- packages ---------------------------------------------------------
#

import re

#
# ---------- types ------------------------------------------------------------
#

TypeSpaces = 0

TypeLeftBrace = 1
TypeRightBrace = 2
TypeLeftBracket = 3
TypeRightBracket = 4
TypeLeftChevron = 5
TypeRightChevron = 6
TypeColon = 7
TypeNumber = 8
TypeWord = 9
TypeLeftComment = 10
TypeRightComment = 11
TypeSemicolon = 12

#
# ---------- tokens -----------------------------------------------------------
#

TokenSpaces = re.compile("[ \t\r\n]+")

TokenLeftBrace = re.compile("{")
TokenRightBrace = re.compile("}")
TokenLeftBracket = re.compile("\[")
TokenRightBracket = re.compile("\]")
TokenLeftChevron = re.compile("<")
TokenRightChevron = re.compile(">")
TokenColon = re.compile(":")
TokenNumber = re.compile("[0-9]+")
TokenWord = re.compile("[a-zA-Z_][a-zA-Z0-9_]*")
TokenLeftComment = re.compile("/\*")
TokenRightComment = re.compile("\*/")
TokenSemicolon = re.compile(";")

Tokens = { TypeSpaces: TokenSpaces,
           TypeLeftBrace: TokenLeftBrace,
           TypeRightBrace: TokenRightBrace,
           TypeLeftBracket: TokenLeftBracket,
           TypeRightBracket: TokenRightBracket,
           TypeLeftChevron: TokenLeftChevron,
           TypeRightChevron: TokenRightChevron,
           TypeColon: TokenColon,
           TypeNumber: TokenNumber,
           TypeWord: TokenWord,
           TypeLeftComment: TokenLeftComment,
           TypeRightComment: TokenRightComment,
           TypeSemicolon: TokenSemicolon }

#
# ---------- classes ----------------------------------------------------------
#

#
# this class represents a token with its type and value.
#
class Token:
  #
  # constructor
  #
  def __init__(self, type, value):
    self.type = type
    self.value = value

  #
  # this method returns a human-readable representation of the token.
  #
  def String(self):
    if self.type == TypeSpaces:
      return "spaces(" + self.value + ")"

    if (self.type == TypeLeftBrace) or (self.type == TypeRightBrace) or \
       (self.type == TypeLeftBracket) or (self.type == TypeRightBracket) or \
       (self.type == TypeLeftChevron) or (self.type == TypeRightChevron) or \
       (self.type == TypeColon) or (self.type == TypeSemicolon):
      return "character(" + self.value + ")"

    if self.type == TypeNumber:
      return "number(" + self.value + ")"

    if self.type == TypeWord:
      return "word(" + self.value + ")"

    return "unknown(token)"

#
# this class tokenises the stream.
#
class Lexer:
  #
  # constructor
  #
  def __init__(self, stream):
    self.stream = stream
    self.offset = 0

  #
  # this method returns the next token. however, note that spaces and comments
  # are ignored i.e not returned.
  #
  def Token(self):
    match = None
    type = None
    token = None

    while (not token) or (token.type == TypeSpaces):
      match = None

      for type in Tokens:
        match = Tokens[type].match(self.stream, self.offset)

        if match:
          token = Token(type, self.stream[match.start():match.end()])

          self.offset += match.end() - match.start()
 
          break

      if not match:
        return None

    return token

# XXX[handle comments!!!]
