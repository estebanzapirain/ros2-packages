// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice

#ifndef MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_H_
#define MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Block in the package map_interface.
typedef struct map_interface__msg__Block
{
  int64_t frame;
  int64_t sig;
  int64_t x;
  int64_t y;
  int64_t width;
  int64_t height;
} map_interface__msg__Block;

// Struct for a sequence of map_interface__msg__Block.
typedef struct map_interface__msg__Block__Sequence
{
  map_interface__msg__Block * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} map_interface__msg__Block__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_H_
