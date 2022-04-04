#ifndef DS_CPP_LIST_ERROR_H
#define DS_CPP_LIST_ERROR_H

namespace ds_cpp {

struct list_error {
  static constexpr const char *kInvalidRange
      = "[ds_cpp:list]: `low` must <= `high`";
  static constexpr const char *kVisitIndexError
      = "[ds_cpp:list]: `visit index` must < `size`";
  static constexpr const char *kVisitPositionError
      = "[ds_cpp:list]: LNP must be valid";
  static constexpr const char *kNullptrError
      = "[ds_cpp:list]: LNP must not be nullptr";
};

}  // namespace ds_cpp

#endif
