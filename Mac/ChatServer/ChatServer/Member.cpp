
#include "Member.hpp"


Member::Member() :
is_active(false)
{
  memset(&buf, 0, sizeof(buf));
  len = sizeof(addr);
}