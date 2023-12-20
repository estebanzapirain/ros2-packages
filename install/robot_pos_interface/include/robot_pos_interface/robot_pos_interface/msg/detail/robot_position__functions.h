// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robot_pos_interface:msg/RobotPosition.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__FUNCTIONS_H_
#define ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robot_pos_interface/msg/rosidl_generator_c__visibility_control.h"

#include "robot_pos_interface/msg/detail/robot_position__struct.h"

/// Initialize msg/RobotPosition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_pos_interface__msg__RobotPosition
 * )) before or use
 * robot_pos_interface__msg__RobotPosition__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__init(robot_pos_interface__msg__RobotPosition * msg);

/// Finalize msg/RobotPosition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
void
robot_pos_interface__msg__RobotPosition__fini(robot_pos_interface__msg__RobotPosition * msg);

/// Create msg/RobotPosition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_pos_interface__msg__RobotPosition__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
robot_pos_interface__msg__RobotPosition *
robot_pos_interface__msg__RobotPosition__create();

/// Destroy msg/RobotPosition message.
/**
 * It calls
 * robot_pos_interface__msg__RobotPosition__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
void
robot_pos_interface__msg__RobotPosition__destroy(robot_pos_interface__msg__RobotPosition * msg);

/// Check for msg/RobotPosition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__are_equal(const robot_pos_interface__msg__RobotPosition * lhs, const robot_pos_interface__msg__RobotPosition * rhs);

/// Copy a msg/RobotPosition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__copy(
  const robot_pos_interface__msg__RobotPosition * input,
  robot_pos_interface__msg__RobotPosition * output);

/// Initialize array of msg/RobotPosition messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_pos_interface__msg__RobotPosition__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__Sequence__init(robot_pos_interface__msg__RobotPosition__Sequence * array, size_t size);

/// Finalize array of msg/RobotPosition messages.
/**
 * It calls
 * robot_pos_interface__msg__RobotPosition__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
void
robot_pos_interface__msg__RobotPosition__Sequence__fini(robot_pos_interface__msg__RobotPosition__Sequence * array);

/// Create array of msg/RobotPosition messages.
/**
 * It allocates the memory for the array and calls
 * robot_pos_interface__msg__RobotPosition__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
robot_pos_interface__msg__RobotPosition__Sequence *
robot_pos_interface__msg__RobotPosition__Sequence__create(size_t size);

/// Destroy array of msg/RobotPosition messages.
/**
 * It calls
 * robot_pos_interface__msg__RobotPosition__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
void
robot_pos_interface__msg__RobotPosition__Sequence__destroy(robot_pos_interface__msg__RobotPosition__Sequence * array);

/// Check for msg/RobotPosition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__Sequence__are_equal(const robot_pos_interface__msg__RobotPosition__Sequence * lhs, const robot_pos_interface__msg__RobotPosition__Sequence * rhs);

/// Copy an array of msg/RobotPosition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_pos_interface
bool
robot_pos_interface__msg__RobotPosition__Sequence__copy(
  const robot_pos_interface__msg__RobotPosition__Sequence * input,
  robot_pos_interface__msg__RobotPosition__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__FUNCTIONS_H_
