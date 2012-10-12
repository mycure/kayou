#ifndef VISITOR_HH
# define VISITOR_HH

# include "ast-forward.hh"

class Visitor
{
public:
  virtual ~Visitor() {}

  virtual void visit(const Node & node) {}
  virtual void visit(const Package & node) {}
  virtual void visit(const Message & node) {}
  virtual void visit(const Alias & node) {}
  virtual void visit(const IntegerType & node) {}
};

#endif /* !VISITOR_HH */
