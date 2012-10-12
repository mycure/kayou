class Message:
  def __init__(self):
    self.name = None
    self.declaractions = None

  def Parse(self):
    token = None

    token = self.lexer.Token()

    if not token:
      return None

    if not ((token.type == lexer.TypeWord) and                          \
            (token.value == KeywordMessage)):
      print "[error][" + self.Identifier(token) + "] " +                \
            "expecting keyword(" + KeywordMessage + ") instead of " +   \
            token.String()

    token = self.lexer.Token()

    if not token:
      print "[error][" + self.Identifier(token) + "] " +                \
            "incomplete message definition"

    if not (token.type == lexer.TypeWord):
      print "[error][" + self.Identifier(token) + "] " +                \
            "expecting message name instead of " + token.String()

    self.name = token.value

    token = self.lexer.Token()

    if not token:
      print "[error][" + self.Identifier(token) + "] " +                \
            "incomplete message definition"

    if not (token.type == lexer.TypeLeftBrace):
      print "[error][" + self.Identifier(token) + "] " +                \
            "expecting character({) instead of " + token.String()

class Section:
  def __init__(self, name):
    self.name = name
    self.declarations = None

class Declarations:
  def __init__(self):
    self.declarations = []

  def Put(self, declaration):
    self.declarations += [ declaration ]

class Declaration:
  def __init__(self):
    self.type = None
    self.name = None

class Type:
  def __init__(self):
    pass
# XXX
