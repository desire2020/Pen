#ifndef SUIMEM_HPP
#define SUIMEM_HPP
namespace sui
{
    template <class T>
    T* clone_ptr(const T* rhs)
    {
        if (rhs == NULL)
            return NULL;
        return new T(*rhs);
    }
    template <class T>
    T* move_ptr(T *& rhs)
    {
        if (rhs == NULL)
            return NULL;
        T* tmp = rhs;
        rhs = NULL;
        return tmp;
    }
}
#endif // SUIMEM_HPP
