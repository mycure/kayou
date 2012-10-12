#
# ---------- header -----------------------------------------------------------
#
# project       nuntio
#
# license       kaneton license
#
# file          /home/mycure/kayou/util/nuntio/tasks/tokenizer.py
#
# created          [mon jul 30 10:06:43 2007]
# updated       julien quintard   [sun aug 24 23:36:37 2008]
#

#
# ---------- information ------------------------------------------------------
#
# Tokenizer provide a simple scanner for the message language.
#

#
# ---------- imports ----------------------------------------------------------
#

import re
import syntax

#
# ---------- globals ----------------------------------------------------------
#
# Compilation of the regular expressions provided by syntax.py
#
e_nextline = re.compile(syntax.s_nextline)
e_space = re.compile(syntax.s_space)
e_lbrace = re.compile(syntax.s_lbrace)
e_rbrace = re.compile(syntax.s_rbrace)
e_lbrack = re.compile(syntax.s_lbrack)
e_rbrack = re.compile(syntax.s_rbrack)
e_lchevron = re.compile(syntax.s_lchevron)
e_rchevron = re.compile(syntax.s_rchevron)
e_rparen = re.compile(syntax.s_rparen)
e_lparen = re.compile(syntax.s_lparen)
e_colon = re.compile(syntax.s_colon)
e_digit = re.compile(syntax.s_digit)
e_word = re.compile(syntax.s_word)
e_lrawblock = re.compile(syntax.s_lrawblock)
e_rrawblock = re.compile(syntax.s_rrawblock)
e_anything = re.compile(syntax.s_anything)

#
# List of all the regexp
#
g_regexps = [e_digit, e_lbrace, e_rbrace, e_lbrack, e_lparen,
	     e_rparen, e_rbrack, e_lchevron, e_rchevron,
	     e_colon, e_word, e_lrawblock, e_rrawblock,
	     e_anything
	    ]

#
# ---------- classes ----------------------------------------------------------
#

# c_tokenizer
#
# Tokenizer object which contains all the information
class		c_tokenizer:
  def		__init__(self, s):
    self.stream = s
    self.nstreampos = 0
    self.curline = None
    self.npos = 0
    self.nline = 0

#
# ---------- functions --------------------------------------------------------
#

#
# eatspace()
#
# space greedy function
#
  def		eatspace(self):
    m = e_space.match(self.curline, self.npos)
    if m:
      self.npos = m.end()

#
# getToken()
#
# Return the next token
#
  def		getToken(self):
    self.getLine()
    if None == self.curline:
      return None

    self.eatspace()

    return self.getmatch()

#
# getLine()
#
# Return the line for the next token
#
  def		getLine(self):
    next = False

    if self.curline == None or self.npos >= len(self.curline):
      next = True

    while next:
      self.getNextLine()
      self.npos = 0
      if self.curline == None:
	return None
      self.eatspace()
      if self.curline != None and self.npos < len(self.curline):
	next = False

#
# getNextLine()
#
# Get the next line in the stream
#
  def		getNextLine(self):
    self.nline += 1
    m = e_nextline.match(self.stream, self.nstreampos)
    if m and self.nstreampos < len(self.stream):
      self.nstreampos = m.end() + 1
      self.curline = m.group()
    else:
      self.curline = None

#
# getmatch()
#
# Return the first matching token in the curline
#
  def		getmatch(self):
    m = None

    for r in g_regexps:
      m = r.match(self.curline, self.npos)
      if m:
	break

    if m:
      self.npos = m.end()
      if self.npos >= len(self.curline):
	self.curline = None
    return m
