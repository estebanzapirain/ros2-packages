// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pwm_interface:srv/SetSpeeds.idl
// generated code does not contain a copyright notice

#ifndef PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_H_
#define PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetSpeeds in the package pwm_interface.
typedef struct pwm_interface__srv__SetSpeeds_Request
{
  uint8_t id;
  uint8_t left;
  uint8_t right;
} pwm_interface__srv__SetSpeeds_Request;

// Struct for a sequence of pwm_interface__srv__SetSpeeds_Request.
typedef struct pwm_interface__srv__SetSpeeds_Request__Sequence
{
  pwm_interface__srv__SetSpeeds_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pwm_interface__srv__SetSpeeds_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SetSpeeds in the package pwm_interface.
typedef struct pwm_interface__srv__SetSpeeds_Response
{
  int8_t ok;
} pwm_interface__srv__SetSpeeds_Response;

// Struct for a sequence of pwm_interface__srv__SetSpeeds_Response.
typedef struct pwm_interface__srv__SetSpeeds_Response__Sequence
{
  pwm_interface__srv__SetSpeeds_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pwm_interface__srv__SetSpeeds_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_H_
