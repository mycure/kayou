#ifndef C_STRUCT_GENERATOR_HH
# define C_STRUCT_GENERATOR_HH

# include <sstream>

# include "visitor.hh"

class CStructGenerator : public Visitor
{
public:
  void generate(const Message & node);

  virtual void visit(const IntegerType & node);

  std::stringstream out;
};

#endif /* !C_STRUCT_GENERATOR_HH */
