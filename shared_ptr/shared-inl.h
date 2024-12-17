template <typename T>
SharedPtr<T>::SharedPtr()
{
    this->pointer = nullptr;
    count = new int(0);
}

template <typename T>
SharedPtr<T>::SharedPtr(T* pointer)
{
    this->pointer = pointer;
    count = new int(1);
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr& other)
{
    pointer = other.pointer;
    count = other.count;
    (*count)++;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& other)
{
    pointer = other.pointer;
    count = other.count;
    (*count)++;
    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other)
{
    pointer = other.pointer;
    other.pointer = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other)
{
    if (this == &other)
        return *this;

    delete pointer;

    pointer = other.pointer;
    other.pointer = nullptr;

    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if ((*count) == 1)
        delete pointer;
}

template <typename T>
T SharedPtr<T>::operator*()
{
    return *pointer;
}

template <typename T>
T* SharedPtr<T>::operator->()
{
    return pointer;
}

template <typename T>
bool SharedPtr<T>::operator!()
{
    return pointer == nullptr;
}

template <typename T>
SharedPtr<T>::operator bool()
{
    return pointer != nullptr;
}

template <typename T>
T* SharedPtr<T>::get()
{
    return pointer;
}

template <typename T>
void SharedPtr<T>::reset()
{
    if ((*count) == 0)
        delete pointer;
    pointer = nullptr;
}

template <typename T>
T* SharedPtr<T>::release()
{
    T* temp = pointer;
    pointer = nullptr;
    return temp;
}

template <typename T>
int SharedPtr<T>::use_count()
{
    return *count;
}
