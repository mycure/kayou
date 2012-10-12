#
# ---------- packages ---------------------------------------------------------
#

import os

import lexer
import message

#
# ---------- keywords ---------------------------------------------------------
#

KeywordMessage = "message"
KeywordSection = "section"

KeywordBoolean = "boolean"
KeywordCharacter = "character"
KeywordInteger = "integer"
KeywordNatural = "natural"
KeywordString = "string"
KeywordReal = "real"
KeywordRaw = "raw"

KeywordAlias = "alias"

#
# ---------- classes ----------------------------------------------------------
#

class Parser:
  def __init__(self, file):
    self.file = file
    self.stream = None
    self.lexer = None

    self.messages = []

  def Parse(self):
    stream = None
    message = None

    self.stream = Load(self.file)

    if not self.stream:
      print "[error] unable to parse the file '" + self.file + "'"
      return None

    self.lexer = lexer.Lexer(self.stream)

    while True:
      message = self.Message()

      if not message:
        break

      this.messages += [ message ]

#
# ---------- functions --------------------------------------------------------
#

def Identifier(parser, token):
  line = None

  line = Parser.lexer.stream.count("\n",
                                   0,
                                   self.lexer.offset - len(token.value))

    return self.file + ":" + str(line)

def Load(file):
  handle = None
  line = None

  if not os.path.exists(file):
    return None

  try:
    handle = open(file, "r")
  except IOError:
    return None

  content = ""
  for line in handle.readlines():
    content += line

  handle.close()

  return content

# XXX
p = Parser("../tests/message.msg")
p.Parse()
