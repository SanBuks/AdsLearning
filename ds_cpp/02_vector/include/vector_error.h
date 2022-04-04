#ifndef DS_CPP_VECTOR_ERROR_H
#define DS_CPP_VECTOR_ERROR_H

namespace ds_cpp {

struct vector_error {
  static constexpr const char *kInvalidRange
      = "[ds_cpp:vector]: `low` must <= `high`";
  static constexpr const char *kUpperBoundOverFlow
      = "[ds_cpp:vector]: `high` must <= `size`";
  static constexpr const char *kVisitIndexError
      = "[ds_cpp:vector]: `visit index` must < `size`";
  static constexpr const char *kVectorFull
      = "[ds_cpp:vector]: vector is full";
};

}  // namespace ds_cpp

#endif
