template<typename T>
class UniquePtr {
private:
    T *pointer;

public:
    UniquePtr(T *pointer);
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other);
    UniquePtr& operator=(UniquePtr&& other);

    ~UniquePtr();

    T operator*();
    T* operator->();
    bool operator!();
    operator bool();
    T* get();
    void reset();
    T* release();
};

#include "unique-inl.h"