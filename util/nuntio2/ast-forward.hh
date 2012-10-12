#ifndef AST_FORWARD_HH
# define AST_FORWARD_HH

# include <vector>

struct File;
struct Node;
struct Import;
struct Declaration;
struct Package;
struct Message;
struct Alias;
struct Field;
struct Type;
struct IntegerType;
struct Import;

typedef std::vector<Field *> Fields;
typedef std::vector<Import *> Imports;
typedef std::vector<Declaration *> Declarations;

#endif /* !AST_FORWARD_HH */
