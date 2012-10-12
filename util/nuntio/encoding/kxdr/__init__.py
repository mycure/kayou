

import encoding
from .. import std

class		c_kxdr(std.c_std):
  def		__init__(self):
    self.name = "kxdr"

  def		encode_int32(self, id):
    encoding.g_output.write("kxdr_int32(kxdr, " + id + "\n") 
