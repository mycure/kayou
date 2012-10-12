#ifndef CORE_SINGLETON_HH
# define CORE_SINGLETON_HH

template <typename T>
class Singleton
{
public:
  static inline T& instance();
};

# include "singleton.hxx"

#endif /* !CORE_SINGLETON_HH */
