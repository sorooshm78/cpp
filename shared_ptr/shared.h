template<typename T>
class SharedPtr {
private:
    T* pointer;
    int* count;

public:
    SharedPtr();
    SharedPtr(T *pointer);
    SharedPtr(SharedPtr& other);
    SharedPtr& operator=(SharedPtr& other);
    SharedPtr(SharedPtr&& other);
    SharedPtr& operator=(SharedPtr&& other);
    ~SharedPtr();

    T operator*();
    T* operator->();
    bool operator!();
    operator bool();
    int use_count();
    T* get();
    void reset();
    T* release();
};

#include "shared-inl.h"