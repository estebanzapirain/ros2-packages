// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from pwm_interface:srv/SetSpeeds.idl
// generated code does not contain a copyright notice

#ifndef PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_HPP_
#define PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__pwm_interface__srv__SetSpeeds_Request __attribute__((deprecated))
#else
# define DEPRECATED__pwm_interface__srv__SetSpeeds_Request __declspec(deprecated)
#endif

namespace pwm_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetSpeeds_Request_
{
  using Type = SetSpeeds_Request_<ContainerAllocator>;

  explicit SetSpeeds_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->left = 0;
      this->right = 0;
    }
  }

  explicit SetSpeeds_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->left = 0;
      this->right = 0;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _left_type =
    uint8_t;
  _left_type left;
  using _right_type =
    uint8_t;
  _right_type right;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__left(
    const uint8_t & _arg)
  {
    this->left = _arg;
    return *this;
  }
  Type & set__right(
    const uint8_t & _arg)
  {
    this->right = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pwm_interface__srv__SetSpeeds_Request
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pwm_interface__srv__SetSpeeds_Request
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetSpeeds_Request_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->left != other.left) {
      return false;
    }
    if (this->right != other.right) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetSpeeds_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetSpeeds_Request_

// alias to use template instance with default allocator
using SetSpeeds_Request =
  pwm_interface::srv::SetSpeeds_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pwm_interface


#ifndef _WIN32
# define DEPRECATED__pwm_interface__srv__SetSpeeds_Response __attribute__((deprecated))
#else
# define DEPRECATED__pwm_interface__srv__SetSpeeds_Response __declspec(deprecated)
#endif

namespace pwm_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetSpeeds_Response_
{
  using Type = SetSpeeds_Response_<ContainerAllocator>;

  explicit SetSpeeds_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ok = 0;
    }
  }

  explicit SetSpeeds_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ok = 0;
    }
  }

  // field types and members
  using _ok_type =
    int8_t;
  _ok_type ok;

  // setters for named parameter idiom
  Type & set__ok(
    const int8_t & _arg)
  {
    this->ok = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pwm_interface__srv__SetSpeeds_Response
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pwm_interface__srv__SetSpeeds_Response
    std::shared_ptr<pwm_interface::srv::SetSpeeds_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetSpeeds_Response_ & other) const
  {
    if (this->ok != other.ok) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetSpeeds_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetSpeeds_Response_

// alias to use template instance with default allocator
using SetSpeeds_Response =
  pwm_interface::srv::SetSpeeds_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pwm_interface

namespace pwm_interface
{

namespace srv
{

struct SetSpeeds
{
  using Request = pwm_interface::srv::SetSpeeds_Request;
  using Response = pwm_interface::srv::SetSpeeds_Response;
};

}  // namespace srv

}  // namespace pwm_interface

#endif  // PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__STRUCT_HPP_
