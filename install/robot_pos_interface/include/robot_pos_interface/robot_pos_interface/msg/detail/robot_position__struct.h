// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_pos_interface:msg/RobotPosition.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_H_
#define ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/RobotPosition in the package robot_pos_interface.
typedef struct robot_pos_interface__msg__RobotPosition
{
  int64_t frame;
  int64_t robot_id;
  int64_t x;
  int64_t y;
  int64_t angle;
} robot_pos_interface__msg__RobotPosition;

// Struct for a sequence of robot_pos_interface__msg__RobotPosition.
typedef struct robot_pos_interface__msg__RobotPosition__Sequence
{
  robot_pos_interface__msg__RobotPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_pos_interface__msg__RobotPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_H_
