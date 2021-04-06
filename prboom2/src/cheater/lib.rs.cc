#include "../m_cheat.hh"
#include "../m_argv.hh"
#include <cstdint>
#include <string>

extern "C" {
bool cxxbridge1$apply_cheats() noexcept;

::std::int32_t cxxbridge1$M_CheckParm(const ::std::string &parm) noexcept {
  ::std::int32_t (*M_CheckParm$)(const ::std::string &) = ::M_CheckParm;
  return M_CheckParm$(parm);
}

void cxxbridge1$cheat_god() noexcept {
  void (*cheat_god$)() = ::cheat_god;
  cheat_god$();
}
} // extern "C"

bool apply_cheats() noexcept {
  return cxxbridge1$apply_cheats();
}
