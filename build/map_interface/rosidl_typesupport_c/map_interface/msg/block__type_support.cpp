// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "map_interface/msg/detail/block__struct.h"
#include "map_interface/msg/detail/block__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace map_interface
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _Block_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Block_type_support_ids_t;

static const _Block_type_support_ids_t _Block_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Block_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Block_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Block_type_support_symbol_names_t _Block_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, map_interface, msg, Block)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, map_interface, msg, Block)),
  }
};

typedef struct _Block_type_support_data_t
{
  void * data[2];
} _Block_type_support_data_t;

static _Block_type_support_data_t _Block_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Block_message_typesupport_map = {
  2,
  "map_interface",
  &_Block_message_typesupport_ids.typesupport_identifier[0],
  &_Block_message_typesupport_symbol_names.symbol_name[0],
  &_Block_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Block_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Block_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace map_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, map_interface, msg, Block)() {
  return &::map_interface::msg::rosidl_typesupport_c::Block_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
