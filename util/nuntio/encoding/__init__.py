




import sys


import nuntio
from exception import NuntioError

g_nuntio = None
g_std = None
g_output = None


signed_int32 = "int32"
unsigned_int32 = "uint32"
signed_int64 = "int64"
unsigned_int64 = "uint64"
signed_int128 = "int128"
unsigned_int128 = "uint128"
double = "double"
raw = "raw"
string = "string"
struct = "struct"



def		init(nuntio):
  global	g_nuntio
  global	g_std
  global	g_output

  g_nuntio = nuntio

  try:
    exec "import " + g_nuntio.options.std
  except ImportError:
    raise NuntioError(g_nuntio.options.std + ": This standard does not exist")
 
  c = "" + g_nuntio.options.std

  if g_nuntio.options.arch:
    exec "import " + g_nuntio.options.std + "." + g_nuntio.options.arch
    c += "." + g_nuntio.options.arch + ".c_" + g_nuntio.options.arch
  else:
    c += ".c_" + g_nuntio.options.std
  
  g_std = eval( c + "()")
  
  g_output = sys.stdout

def		new(id, dim = None):
  g_output.write("struct\t\tmessage_" + id + "\n{\n")

def		process(type, id, dim = None):
  exec "g_std.encode_" + type + "(id)"

#  exec g_nuntio.std + ".encode_" + type + "(id)"
#  if dim == None:
#    print "Process: " + type + ": " + id
#  else:
#    sdim = ""
#    for n in dim:
#      sdim += "<"
#      if n['id'] is not None:
#	sdim += n['id'] + ":"
#      sdim += n['max'] + ">"
#    print "Process: " + type + ": " + id + ": " + sdim


def		end(id):
  print "};\n/* End: " + id + " */\n"

