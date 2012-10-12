#ifndef GENERATOR_HH
# define GENERATOR_HH

# include <ostream>
# include <string>

# include "ast-forward.hh"
# include "visitor.hh"

class Generator : public Visitor
{
public:
  Generator();
  virtual ~Generator();

  virtual void generate(const File * file) = 0;
  void enterPackage(const std::string & name);
  void leavePackage();

  virtual void visit(const Node & node) {}
  virtual void visit(const Package & node) {}
  virtual void visit(const Message & node) {}
  virtual void visit(const Alias & node) {}
  virtual void visit(const IntegerType & node) {}

protected:
  std::vector<std::string> package;
};

Generator * createGenerator();

#endif /* !GENERATOR_HH */
