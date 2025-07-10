#include "cclass.h"



// ===== CLASSES DEF =====
#define self_type Person
class(Person) {
    char* name;
    int age;
    method(void, greet);
};
#undef self_type

defmethod(Person, void, greet) {
    printf("Hello, my name is %s and I am %d years old.\n", this->name, this->age);
}

void Person_init(Person* this, const char* name, int age) {
    this->name = strdup(name);
    this->age = age;
    bind(Person, this, greet);  // <-- pass class name, pointer, method
}

void Person_destroy(Person* this) {
    free(this->name);
}

int main() {
    // ===== MEMORY SAFE STRING ALLOCATION =====
    string greeting = safe_malloc(100);
    strcpy(greeting, "Hi! Welcome to the custom C class example.");
    
    printf("Original Greeting: %s\n", greeting);

    // ===== STRING FUNCTIONS =====
    printf("Substring (5 to 15): ");
    substr(greeting, 5, 15);

    printf("Index of character 'W': %d\n", indexOfChar(greeting, 'W'));
    printf("Index of string \"Welcome\": %d\n", indexOfStr(greeting, "Welcome"));

    // ===== CLASS & METHODS =====
    new(Person, p);
    Person_init(&p, "Alice", 30);
    p.greet(&p);
    Person_destroy(&p);

    // ===== SAFE REALLOC EXAMPLE =====
    greeting = safe_realloc(greeting, 200);
    strcat(greeting, " Have a nice day!");
    printf("Updated Greeting: %s\n", greeting);

    // Cleanup
    free(greeting);
    return 0;
}


