#ifndef AST_HH
# define AST_HH

# include <string>
# include <vector>
# include <gc/gc_cpp.h>

# include "ast-forward.hh"
# include "visitor.hh"

struct Node : public gc
{
  virtual ~Node() {}
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }
};

struct File : public Node
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  std::string    path;
  Declarations * declarations;
  Imports *      imports;
};

struct Import : public Node
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  std::string path;
};

struct Declaration : public Node
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }
};

struct Package : public Declaration
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  std::string    name;
  Declarations * declarations;
};

struct Message : public Declaration
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  Fields *    fields;
  std::string name;
};

struct Alias : public Declaration
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  Type * type;
  std::string name;
};

struct Field : public Node
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  Type * type;
  std::string name;
};

struct Type : public Node
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }
};

struct IntegerType : public Type
{
  virtual void accept(Visitor & visitor) { visitor.visit(*this); }

  bool     isSigned;
  unsigned size;
};

#endif /* !AST_HH */
