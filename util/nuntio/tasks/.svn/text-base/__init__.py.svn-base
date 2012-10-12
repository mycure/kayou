#
# ---------- header -----------------------------------------------------------
#
# project       nuntio
#
# license       kaneton license
#
# file          /home/arkho/kaneton/tool/nuntio/tasks/__init__.py
#
# created          [sun jul 29 11:38:51 2007]
# updated          [sun jul 29 11:39:46 2007]
#

#
# ---------- information ------------------------------------------------------
#
# This file is the manager of all the process which are applied to the
# file in entry
#

#
# ---------- imports ----------------------------------------------------------
#
# Common imports
import sys
import re

# Nuntio imports
import parser
import exception
import encoding


#
# ---------- functions --------------------------------------------------------
#

# process
#
# file: file to process
#
# Apply many tasks to the file
def		process(nuntio, file):
  f = None
  content = ""
  n = 0

# 1) Get the contain of the file
  try:
    f = open(file, 'r')
    for line in f:
      content += line
    f.close()

# 2) Initialize the encoding stuff
    encoding.init(nuntio)

# 3) Parse the file
    parser.parse(content)

# 4) Catch some errors
  except IOError, e:
    sys.stderr.write(nuntio.program + ": No such file or directory: " +
		     file + "\n")

  except exception.NuntioError, inst:
    sys.stderr.write(nuntio.program + ": " + file + ": " +  str(inst) + "\n")

