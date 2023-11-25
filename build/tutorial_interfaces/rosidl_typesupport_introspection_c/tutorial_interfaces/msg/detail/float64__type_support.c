// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from tutorial_interfaces:msg/Float64.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "tutorial_interfaces/msg/detail/float64__rosidl_typesupport_introspection_c.h"
#include "tutorial_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "tutorial_interfaces/msg/detail/float64__functions.h"
#include "tutorial_interfaces/msg/detail/float64__struct.h"


// Include directives for member types
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tutorial_interfaces__msg__Float64__init(message_memory);
}

void tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_fini_function(void * message_memory)
{
  tutorial_interfaces__msg__Float64__fini(message_memory);
}

size_t tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__size_function__Float64__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_const_function__Float64__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_function__Float64__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__fetch_function__Float64__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_const_function__Float64__data(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__assign_function__Float64__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_function__Float64__data(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__resize_function__Float64__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_member_array[2] = {
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tutorial_interfaces__msg__Float64, data),  // bytes offset in struct
    NULL,  // default value
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__size_function__Float64__data,  // size() function pointer
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_const_function__Float64__data,  // get_const(index) function pointer
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__get_function__Float64__data,  // get(index) function pointer
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__fetch_function__Float64__data,  // fetch(index, &value) function pointer
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__assign_function__Float64__data,  // assign(index, value) function pointer
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__resize_function__Float64__data  // resize(index) function pointer
  },
  {
    "size",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tutorial_interfaces__msg__Float64, size),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_members = {
  "tutorial_interfaces__msg",  // message namespace
  "Float64",  // message name
  2,  // number of fields
  sizeof(tutorial_interfaces__msg__Float64),
  tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_member_array,  // message members
  tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_init_function,  // function to initialize message memory (memory has to be allocated)
  tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_type_support_handle = {
  0,
  &tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tutorial_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tutorial_interfaces, msg, Float64)() {
  if (!tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_type_support_handle.typesupport_identifier) {
    tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &tutorial_interfaces__msg__Float64__rosidl_typesupport_introspection_c__Float64_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
