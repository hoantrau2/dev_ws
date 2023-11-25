// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tutorial_interfaces:msg/Float64.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__STRUCT_H_
#define TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Float64 in the package tutorial_interfaces.
typedef struct tutorial_interfaces__msg__Float64
{
  rosidl_runtime_c__double__Sequence data;
  int32_t size;
} tutorial_interfaces__msg__Float64;

// Struct for a sequence of tutorial_interfaces__msg__Float64.
typedef struct tutorial_interfaces__msg__Float64__Sequence
{
  tutorial_interfaces__msg__Float64 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tutorial_interfaces__msg__Float64__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__STRUCT_H_
