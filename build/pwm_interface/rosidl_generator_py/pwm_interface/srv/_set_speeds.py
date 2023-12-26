# generated from rosidl_generator_py/resource/_idl.py.em
# with input from pwm_interface:srv/SetSpeeds.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetSpeeds_Request(type):
    """Metaclass of message 'SetSpeeds_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('pwm_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'pwm_interface.srv.SetSpeeds_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_speeds__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_speeds__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_speeds__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_speeds__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_speeds__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetSpeeds_Request(metaclass=Metaclass_SetSpeeds_Request):
    """Message class 'SetSpeeds_Request'."""

    __slots__ = [
        '_id',
        '_left',
        '_right',
    ]

    _fields_and_field_types = {
        'id': 'uint8',
        'left': 'uint8',
        'right': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.id = kwargs.get('id', int())
        self.left = kwargs.get('left', int())
        self.right = kwargs.get('right', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.id != other.id:
            return False
        if self.left != other.left:
            return False
        if self.right != other.right:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'id' field must be an unsigned integer in [0, 255]"
        self._id = value

    @builtins.property
    def left(self):
        """Message field 'left'."""
        return self._left

    @left.setter
    def left(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'left' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'left' field must be an unsigned integer in [0, 255]"
        self._left = value

    @builtins.property
    def right(self):
        """Message field 'right'."""
        return self._right

    @right.setter
    def right(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'right' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'right' field must be an unsigned integer in [0, 255]"
        self._right = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetSpeeds_Response(type):
    """Metaclass of message 'SetSpeeds_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('pwm_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'pwm_interface.srv.SetSpeeds_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_speeds__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_speeds__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_speeds__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_speeds__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_speeds__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetSpeeds_Response(metaclass=Metaclass_SetSpeeds_Response):
    """Message class 'SetSpeeds_Response'."""

    __slots__ = [
        '_ok',
    ]

    _fields_and_field_types = {
        'ok': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.ok = kwargs.get('ok', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.ok != other.ok:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def ok(self):
        """Message field 'ok'."""
        return self._ok

    @ok.setter
    def ok(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ok' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'ok' field must be an integer in [-128, 127]"
        self._ok = value


class Metaclass_SetSpeeds(type):
    """Metaclass of service 'SetSpeeds'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('pwm_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'pwm_interface.srv.SetSpeeds')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_speeds

            from pwm_interface.srv import _set_speeds
            if _set_speeds.Metaclass_SetSpeeds_Request._TYPE_SUPPORT is None:
                _set_speeds.Metaclass_SetSpeeds_Request.__import_type_support__()
            if _set_speeds.Metaclass_SetSpeeds_Response._TYPE_SUPPORT is None:
                _set_speeds.Metaclass_SetSpeeds_Response.__import_type_support__()


class SetSpeeds(metaclass=Metaclass_SetSpeeds):
    from pwm_interface.srv._set_speeds import SetSpeeds_Request as Request
    from pwm_interface.srv._set_speeds import SetSpeeds_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
