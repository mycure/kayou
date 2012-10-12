template <typename T>
inline T&
Singleton<T>::instance()
{
  static T * instance_ = new T;

  return *instance_;
}
