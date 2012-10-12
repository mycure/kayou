#ifndef C_SIZE_GENERATOR_HH
# define C_SIZE_GENERATOR_HH

# include <sstream>

# include "visitor.hh"

class CSizeGenerator : public Visitor
{
public:
  void generate(const Message & node);
  void generate();

  virtual void visit(const IntegerType & node);

  std::stringstream out;
  const Field * currentField;
};

#endif /* !C_SIZE_GENERATOR_HH */
