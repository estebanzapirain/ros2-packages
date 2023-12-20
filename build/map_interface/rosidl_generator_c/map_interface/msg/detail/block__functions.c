// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice
#include "map_interface/msg/detail/block__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
map_interface__msg__Block__init(map_interface__msg__Block * msg)
{
  if (!msg) {
    return false;
  }
  // frame
  // sig
  // x
  // y
  // width
  // height
  return true;
}

void
map_interface__msg__Block__fini(map_interface__msg__Block * msg)
{
  if (!msg) {
    return;
  }
  // frame
  // sig
  // x
  // y
  // width
  // height
}

bool
map_interface__msg__Block__are_equal(const map_interface__msg__Block * lhs, const map_interface__msg__Block * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // frame
  if (lhs->frame != rhs->frame) {
    return false;
  }
  // sig
  if (lhs->sig != rhs->sig) {
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
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  return true;
}

bool
map_interface__msg__Block__copy(
  const map_interface__msg__Block * input,
  map_interface__msg__Block * output)
{
  if (!input || !output) {
    return false;
  }
  // frame
  output->frame = input->frame;
  // sig
  output->sig = input->sig;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  return true;
}

map_interface__msg__Block *
map_interface__msg__Block__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  map_interface__msg__Block * msg = (map_interface__msg__Block *)allocator.allocate(sizeof(map_interface__msg__Block), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(map_interface__msg__Block));
  bool success = map_interface__msg__Block__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
map_interface__msg__Block__destroy(map_interface__msg__Block * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    map_interface__msg__Block__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
map_interface__msg__Block__Sequence__init(map_interface__msg__Block__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  map_interface__msg__Block * data = NULL;

  if (size) {
    data = (map_interface__msg__Block *)allocator.zero_allocate(size, sizeof(map_interface__msg__Block), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = map_interface__msg__Block__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        map_interface__msg__Block__fini(&data[i - 1]);
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
map_interface__msg__Block__Sequence__fini(map_interface__msg__Block__Sequence * array)
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
      map_interface__msg__Block__fini(&array->data[i]);
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

map_interface__msg__Block__Sequence *
map_interface__msg__Block__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  map_interface__msg__Block__Sequence * array = (map_interface__msg__Block__Sequence *)allocator.allocate(sizeof(map_interface__msg__Block__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = map_interface__msg__Block__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
map_interface__msg__Block__Sequence__destroy(map_interface__msg__Block__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    map_interface__msg__Block__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
map_interface__msg__Block__Sequence__are_equal(const map_interface__msg__Block__Sequence * lhs, const map_interface__msg__Block__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!map_interface__msg__Block__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
map_interface__msg__Block__Sequence__copy(
  const map_interface__msg__Block__Sequence * input,
  map_interface__msg__Block__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(map_interface__msg__Block);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    map_interface__msg__Block * data =
      (map_interface__msg__Block *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!map_interface__msg__Block__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          map_interface__msg__Block__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!map_interface__msg__Block__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
