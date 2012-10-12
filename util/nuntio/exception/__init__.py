#
# ---------- header -----------------------------------------------------------
#
# project       nuntio
#
# license       kaneton license
#
# file          /home/arkho/kaneton/tool/nuntio/exception/__init__.py
#
# created          [sun jul 29 09:42:00 2007]
# updated          [sun jul 29 10:25:53 2007]
#

#
# ---------- information ------------------------------------------------------
#
# This file contains all the exceptions which are specific to nuntio
#

#
# ---------- classes ----------------------------------------------------------
#


#
# NuntioError
#
# Root class for all nuntio exceptions
#
class NuntioError(Exception):
  def __init__(self, message):
    self.msg = message
  def __str__(self):
    return str(self.msg)


#
# NuntioParseError
#
# Parser specific error
#
class NuntioParseError(NuntioError):
  def __init__(self, line, col, message):
    self.line = line
    self.col = col
    self.msg = message
  def __str__(self):
    return "Parse error:" + str(self.line) + ":" + str(self.col) \
	   + ": " + self.msg


#
# NuntioUnexpectedEndOfFile
#
# Raised exception when the parser does not except the end of file
#
class NuntioUnexpectedEndOfFile(NuntioError):
  def __init__(self, line):
    self.line = line
  def __str__(self):
    return "Parse error:" + str(self.line) + ": Unexpected end of file"


#
# NuntioBadIntegerSize
#
# The parser checks the validity of the integer size
#
class NuntioBadIntegerSize(NuntioError):
  def __init__(self, line, size):
    self.line = line
    self.size = size
  def __str__(self):
    return "Parse error:" + str(self.line) + ": Bad integer size: " \
	   + str(self.size)


#
# NuntioNotImplemented
#
# When a function is not implemented yet, Nuntio raises this exception
#
class NuntioNotImplemented(NuntioError):
  def __init__(self, std, func):
    self.func = func
    self.std = std
  def __str__(self):
    return "" + str(self.func) + " is not available with the " \
	   + str(self.std) + " standard"

