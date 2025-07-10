# C-

**C-** is a lightweight object-oriented layer for the C programming language, written entirely in C.  
It adds just enough abstraction to make C feel a little more modern — but not enough to be accused of using C++.

Think of it as:  
>  *"C, but with classes and safety. Kind of."*

---

##  Features

- **Class-like macros** (`class(...)`, `method`, `defmethod`)
- **Instance methods** with `this->` pointer syntax
- **Basic memory-safe wrappers** (`safe_malloc`, `safe_realloc`)
- **Simple string utilities** (e.g., `indexOfChar`, `substr`)
- **`new(Class, var)` and `bind(...)` to simulate objects**
- No compiler magic — just clever macros and raw C

---

##  Example

```c
#include "cclass.h"

#define self_type Person
class(Person) {
    char* name;
    int age;
    method(void, greet);
};
#undef self_type

defmethod(Person, void, greet) {
    printf("Hi, I'm %s and I'm %d years old.\n", this->name, this->age);
}

void Person_init(Person* this, const char* name, int age) {
    this->name = strdup(name);
    this->age = age;
    bind(Person, this, greet);
}

int main() {
    new(Person, p);
    Person_init(&p, "Alice", 30);
    p.greet(&p);
}
