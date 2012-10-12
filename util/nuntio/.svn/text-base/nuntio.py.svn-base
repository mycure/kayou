#! /usr/bin/python

#
# ---------- header -----------------------------------------------------------
#
# project       nuntio
#
# license       kaneton license
#
# file          /home/mycure/Z/nuntio/nuntio.py
#
# created          [sun jul 29 09:42:00 2007]
# updated       julien quintard   [sat aug 16 17:17:28 2008]
#

#
# ---------- information ------------------------------------------------------
#
# XXXX
#

#
# ---------- imports ----------------------------------------------------------
#
import sys
from optparse import OptionParser

import tasks
import exception

#
# ---------- classes ----------------------------------------------------------
#

class	c_nuntio:
  def	__init__():
    self.program = None
    self.arguments = None
    self.options = None
    self.files = None
    self.std = None
#    self.raw = None
#    self.config = None



#
# ---------- globals ----------------------------------------------------------
#

g_nuntio = None


#
# ---------- functions --------------------------------------------------------
#

def		nuntio():
  global	g_nuntio

  g_nuntio = c_nuntio

  g_nuntio.program = sys.argv[0]
  g_nuntio.arguments = sys.argv[1:]

  options()

  process()

# Verbose


def		options():
  global g_nuntio

  usage = "usage: %prog [options] file1 [file2 | ... ]"
  optparser = OptionParser(usage=usage)
  optparser.add_option("-a", "--arch", action="store", dest="arch", 
  			help="Architecture of the host")
  optparser.add_option("-s", "--std", action="store", dest="std", default="kxdr",
			help="Standard to use. kxdr is the default.")
  optparser.add_option("-o", "--output", action="store", dest="output",
  			help="Write output to OUTPUT.")

  (g_nuntio.options,  g_nuntio.files) = optparser.parse_args()

def		process():
  file = None

  for file in g_nuntio.files:
    tasks.process(g_nuntio, file)



#
# ---------- entry point ------------------------------------------------------
#
if __name__ == '__main__':
  nuntio()
