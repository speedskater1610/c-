#ifndef CMINUS_H
#define CMINUS_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// so that there is a boolean type
typedef unsigned char bool
#define true 1
#define false 0


// String type
typedef char* String

//for index comparison
#define npos -1


/// @brief a substring functions that works on strings that returns the position between 2 indexs on a string
/// @param str      the string being substring-ed
/// @param index1   the first index of the substring
/// @param index2   the second index of the substring
void substr (String str, size_t index1, size_t index2) {

    // error handling so that ranges should work
    if (index1 >= index2) {
        //xor swap wiothout a temp varible
        //this just switches the 2 varibles
        index1 ^= index2;
        index2 ^= index1;
        index1 ^= index2;
    }
    // if the ranges are larger than the str
    if (index2 > strlen(str)) {
        index2 = strlen(str);
    }
    if (index1 > strlen(str)) {
        index1 = strlen(str);
    }
    // if they are the samje or the diffrence between them is 0 (they both where larger than the strlen)
    if (index1 == index2 || index1 - index2 == 0) {
        return;
    }

    for (size_t i = index1; i < index2; i++) {
        putchar(str[i]);
    }
    putchar('\n');
}


/// @brief returns the index of a specific character ina string
/// @param str the string that that the char gets looked for in 
/// @param index the char you are looking for
/// @return npos or -1 if not found and the index where it is found if it is found
int indexOfChar(const String str, char ch) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) return (int)i;
    }
    return npos;
}
/// @brief returns the index of a specific string 
/// @param str the main string that the other string is being loooked for in
/// @param index the string that is being looked for in the str varible
/// @return npos or -1 if not found or the index of the first letter
int indexOfStr (String str, String index) {
    char* pos = strstr(str, substr);
    if (pos != NULL) {
        return (int)(pos - str); // pointer arithmetic to get index
    }
    return npos;
}



//CLASSES
// to make a class (the same as "typedef struct")
#define class(name) \
    typedef struct name name; \
    struct name



// define a method as a function pointer in struct
#define method(ret_type, name) \
    ret_type (*name)(struct this_type* this)



// 0 init an object
#define new(Type, varname) \
    Type varname; memset(&varname, 0, sizeof(Type))



// make a method implementation with 'this' as parameter (so things can be done with this->)
#define defmethod(classname, rettype, methodname) \
    rettype classname##_##methodname(classname* this)



// bind a method pointer for a pointer variable with classname (just connecting the method to the class)
#define bind(classname, obj, methodname) \
    (obj)->methodname = classname##_##methodname

#endif



//MEMORY SAFETY IN C
#ifndef MEMSAFE_H
#define MEMSAFE_H


// mollloc safely
#define safe_malloc(size) \
    checked_malloc((size), __FILE__, __LINE__)

// safely calloc
#define safe_calloc(count, size) \
    checked_calloc((count), (size), __FILE__, __LINE__)

//safely re allocate
#define safe_realloc(ptr, size) \
    checked_realloc((ptr), (size), __FILE__, __LINE__)

// for checking and mollocing
static inline void* checked_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "[%s:%d] malloc(%zu) failed\n", file, line, size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// for checking and safely callocing
static inline void* checked_calloc(size_t count, size_t size, const char* file, int line) {
    void* ptr = calloc(count, size);
    if (!ptr) {
        fprintf(stderr, "[%s:%d] calloc(%zu, %zu) failed\n", file, line, count, size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// for checking and safely re alllocating
static inline void* checked_realloc(void* ptr, size_t size, const char* file, int line) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "[%s:%d] realloc failed\n", file, line);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

#endif // CMINUS_H
