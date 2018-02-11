
# A C++ Factory

This is a C++ factory.  It requires manual registration of subclasses, but it's a simple thing to 
call `registerType<>()` to add a new class.  The key can be an `int` or `string` (or probably any
other type of variable you require).


## Example 1:

```
#include "Factory.h"

class SampleFactory : public Factory<sample_parent_class, std::string> {
public:
  SampleFactory() {
    registerType<smple_child_class>("child1");
  };
};

SampleFactory sample_factory;

auto sample_thing = sample_factory.create("child1");
```



## Example 2:

```
#include "Factory.h"

class ObjectTypeFactory : public Factory<object_type_generic, int, Object *> {
   public:
      ObjectTypeFactory() {
         registerType<object_type_weapon>(OBJECT_WEAPON);
      };
};

ObjectTypeFactory object_type_factory;

auto object = object_type_factory.create(type_id, this);
```

