#ifndef C_GENERATOR_HH
# define C_GENERATOR_HH

# include <fstream>

# include "generator.hh"

class CGenerator : public Generator
{
public:
  CGenerator();
  ~CGenerator();

  virtual void generate(const File * file);

  virtual void visit(const Node & node) {}
  virtual void visit(const Package & node) {}
  virtual void visit(const Message & node);
  virtual void visit(const Alias & node) {}

protected:
  void generateStruct(const Message & node);

  std::string headerPath;
  std::string sourcePath;

  std::ofstream header;
  std::ofstream source;
};

#endif /* !C_GENERATOR_HH */
