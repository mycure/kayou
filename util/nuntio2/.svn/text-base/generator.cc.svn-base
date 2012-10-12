#include <stdlib.h>
#include <assert.h>

#include "c-generator.hh"

Generator::Generator()
  : Visitor(),
    package()
{
}

Generator::~Generator()
{
}

Generator * createGenerator()
{
  const std::string target = getenv("TARGET");

  assert(!target.empty());
  if (target == "C")
    return new CGenerator;
  assert(false);
  return 0;
}
