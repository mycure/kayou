#ifndef COMPILER_HH
# define COMPILER_HH

# include <string>
# include <map>

# include "singleton.hh"
# include "ast.hh"

class Compiler : public Singleton<Compiler>
{
public:
  void generate(const std::string & path);
  void generate(const File * file);
  File * parseFile(const std::string & path);
  void importDependencies(const File * file);

  Compiler();

protected:
  /// key: package name
  typedef std::map<std::string, Declarations *> declarations_t;
  /// key: file name
  typedef std::map<std::string, File *> files_t;

  declarations_t declarations;
  files_t        files;
};

#endif /* !COMPILER_HH */
