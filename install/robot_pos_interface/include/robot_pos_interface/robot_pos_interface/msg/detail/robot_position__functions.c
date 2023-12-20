// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_pos_interface:msg/RobotPosition.idl
// generated code does not contain a copyright notice
#include "robot_pos_interface/msg/detail/robot_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_pos_interface__msg__RobotPosition__init(robot_pos_interface__msg__RobotPosition * msg)
{
  if (!msg) {
    return false;
  }
  // frame
  // robot_id
  // x
  // y
  // angle
  return true;
}

void
robot_pos_interface__msg__RobotPosition__fini(robot_pos_interface__msg__RobotPosition * msg)
{
  if (!msg) {
    return;
  }
  // frame
  // robot_id
  // x
  // y
  // angle
}

bool
robot_pos_interface__msg__RobotPosition__are_equal(const robot_pos_interface__msg__RobotPosition * lhs, const robot_pos_interface__msg__RobotPosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // frame
  if (lhs->frame != rhs->frame) {
    return false;
  }
  // robot_id
  if (lhs->robot_id != rhs->robot_id) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // angle
  if (lhs->angle != rhs->angle) {
    return false;
  }
  return true;
}

bool
robot_pos_interface__msg__RobotPosition__copy(
  const robot_pos_interface__msg__RobotPosition * input,
  robot_pos_interface__msg__RobotPosition * output)
{
  if (!input || !output) {
    return false;
  }
  // frame
  output->frame = input->frame;
  // robot_id
  output->robot_id = input->robot_id;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // angle
  output->angle = input->angle;
  return true;
}

robot_pos_interface__msg__RobotPosition *
robot_pos_interface__msg__RobotPosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_pos_interface__msg__RobotPosition * msg = (robot_pos_interface__msg__RobotPosition *)allocator.allocate(sizeof(robot_pos_interface__msg__RobotPosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_pos_interface__msg__RobotPosition));
  bool success = robot_pos_interface__msg__RobotPosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_pos_interface__msg__RobotPosition__destroy(robot_pos_interface__msg__RobotPosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_pos_interface__msg__RobotPosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_pos_interface__msg__RobotPosition__Sequence__init(robot_pos_interface__msg__RobotPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_pos_interface__msg__RobotPosition * data = NULL;

  if (size) {
    data = (robot_pos_interface__msg__RobotPosition *)allocator.zero_allocate(size, sizeof(robot_pos_interface__msg__RobotPosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_pos_interface__msg__RobotPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_pos_interface__msg__RobotPosition__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_pos_interface__msg__RobotPosition__Sequence__fini(robot_pos_interface__msg__RobotPosition__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_pos_interface__msg__RobotPosition__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_pos_interface__msg__RobotPosition__Sequence *
robot_pos_interface__msg__RobotPosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_pos_interface__msg__RobotPosition__Sequence * array = (robot_pos_interface__msg__RobotPosition__Sequence *)allocator.allocate(sizeof(robot_pos_interface__msg__RobotPosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_pos_interface__msg__RobotPosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_pos_interface__msg__RobotPosition__Sequence__destroy(robot_pos_interface__msg__RobotPosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_pos_interface__msg__RobotPosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_pos_interface__msg__RobotPosition__Sequence__are_equal(const robot_pos_interface__msg__RobotPosition__Sequence * lhs, const robot_pos_interface__msg__RobotPosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_pos_interface__msg__RobotPosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_pos_interface__msg__RobotPosition__Sequence__copy(
  const robot_pos_interface__msg__RobotPosition__Sequence * input,
  robot_pos_interface__msg__RobotPosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_pos_interface__msg__RobotPosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_pos_interface__msg__RobotPosition * data =
      (robot_pos_interface__msg__RobotPosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_pos_interface__msg__RobotPosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_pos_interface__msg__RobotPosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_pos_interface__msg__RobotPosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
