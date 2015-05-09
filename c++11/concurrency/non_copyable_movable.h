#ifndef NON_COPYABLE_MOVABLE_H_INCLUDED
#define NON_COPYABLE_MOVABLE_H_INCLUDED

class non_copyable_movable
{
protected:
  non_copyable_movable()
  {}

private:
  non_copyable_movable(const non_copyable_movable&) = delete;
  non_copyable_movable(non_copyable_movable&&) = delete;
  non_copyable_movable &operator=(const non_copyable_movable&) = delete;
};

#endif
