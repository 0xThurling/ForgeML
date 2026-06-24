#pragma once

#include <sstream>
#include <stdexcept>

namespace forgeml {
class MlError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

[[noreturn]] inline void assertion_failed(
        const char* expr,
        const char* file,
        int line,
        const char* msg 
        ) 
{
  std::ostringstream oss;
    oss << "Assertion failed: (" << expr << ")";
    if (msg && *msg) {
        oss << " - " << msg;
    }
    oss << " [" << file << ":" << line << "]";
  throw MlError(oss.str());
}
} // namespace forgeml

#define ML_ASSERT(cond, msg) \
    do {\
        if (!(cond)) { \
            ::forgeml::assertion_failed(#cond, __FILE__, __LINE__, (msg)); \
        } \
    } while (false)
