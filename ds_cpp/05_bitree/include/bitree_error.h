#ifndef DS_CPP_BITREE_ERROR_H
#define DS_CPP_BITREE_ERROR_H

namespace ds_cpp {

struct bitree_error {
  static constexpr const char *kConstructFromVectorError
      = "[ds_cpp:bitree]: not valid level-traverse sequence";
};

}  // namespace ds_cpp

#endif
