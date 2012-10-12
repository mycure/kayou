#ifndef C_EXTRACT_GENERATOR_HH
# define C_EXTRACT_GENERATOR_HH

# include <sstream>

# include "visitor.hh"

class CExtractGenerator : public Visitor
{
public:
  void generate(const Message & node);
  void generate();

  virtual void visit(const IntegerType & node);

  std::stringstream out;
};

#endif /* !C_EXTRACT_GENERATOR_HH */
