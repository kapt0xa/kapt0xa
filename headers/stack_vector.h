#pragma once

#include <stdexcept>

template <typename T, size_t N>
class StackVector {
    T array_[N];
    size_t size_;
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    explicit StackVector(size_t a_size = 0);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

#define _Namespace_Stack_Vector_by_kapt0xa__Use_Iterators_ true

#if _Namespace_Stack_Vector_by_kapt0xa__Use_Iterators_

#define _Namespace_Stack_Vector_by_kapt0xa__Siplify_Forward_Iterators_ true

    template<typename valT, bool Reverse>
    struct BasicIterator
    {
        friend class StackVector;
        
        valT* raw_ptr_;

        explicit BasicIterator(valT* raw_ptr);
    public:
        using iterator_caategory = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = valT*;
        using reference = valT&;
        static const bool is_reverse = Reverse;

        BasicIterator() = default;
        BasicIterator(const BasicIterator<T, Reverse>& other);
        BasicIterator& operator = (const BasicIterator & other) = default;

        BasicIterator(const BasicIterator<valT, !Reverse> & other);

        BasicIterator& operator ++();
        BasicIterator& operator --();
        BasicIterator operator ++(int);
        BasicIterator operator --(int);
        BasicIterator& operator +=(ptrdiff_t offset);
        BasicIterator& operator -=(ptrdiff_t offset);
        BasicIterator operator +(ptrdiff_t offset);
        BasicIterator operator -(ptrdiff_t offset);
        ptrdiff_t operator -(const BasicIterator& other);
        bool operator ==(const BasicIterator& other);
        bool operator !=(const BasicIterator& other);
        bool operator <=(const BasicIterator& other);
        bool operator >=(const BasicIterator& other);
        bool operator <(const BasicIterator& other);
        bool operator >(const BasicIterator& other);
        operator valT* ();
        reference operator *();
        pointer operator ->();
        valT*& raw_ptr();
    };
#if _Namespace_Stack_Vector_by_kapt0xa__Siplify_Forward_Iterators_
    using iterator = T*;
    using const_iterator = const T*;
#else
    using iterator = BasicIterator<T, false>;
    using const_iterator = BasicIterator<const T, false>;
#endif
    using reverse_iterator = BasicIterator<T, true>;
    using const_reverse_iterator = BasicIterator<const T, true>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
#else

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    const T* cbegin() const;
    const T* cend() const;

#endif

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(const T& value);
    T PopBack();
};


template<typename T, size_t N>
inline StackVector<T, N>::StackVector(size_t a_size)
    :size_(a_size) 
{ if(a_size > N) throw std::invalid_argument("size is more than constant capacity \"N\""); }

template<typename T, size_t N>
inline T& StackVector<T, N>::operator[](size_t index)
{
    return array_[index];
}

template<typename T, size_t N>
inline const T& StackVector<T, N>::operator[](size_t index) const
{
    return array_[index];
}

template<typename T, size_t N>
inline size_t StackVector<T, N>::Size() const
{
    return size_;
}

template<typename T, size_t N>
inline size_t StackVector<T, N>::Capacity() const
{
    return N;
}

template<typename T, size_t N>
inline void StackVector<T, N>::PushBack(const T& value)
{
    if (size_ == N) throw std::overflow_error("vector size reached capacity, cant push back more");
    array_[size_] = value;
    ++size_;
}

template<typename T, size_t N>
inline T StackVector<T, N>::PopBack()
{
    if (size_ == 0) throw std::underflow_error("cant pop elements in empty vector");
    --size_;
    return array_[size_];
}

#if _Namespace_Stack_Vector_by_kapt0xa__Use_Iterators_

template<typename T, size_t N>
template<typename valT, bool Reverse>
StackVector<T, N>::BasicIterator<valT, Reverse>::BasicIterator(valT* raw_ptr)
    :raw_ptr_(raw_ptr) {}

template<typename T, size_t N>
template<typename valT, bool Reverse>
StackVector<T, N>::BasicIterator<valT, Reverse>::BasicIterator(const BasicIterator<valT, !Reverse>& other)
    :raw_ptr_(other.raw_ptr_){}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse>& StackVector<T, N>::BasicIterator<valT, Reverse>::operator++()
{
    if constexpr (Reverse)
        --raw_ptr_;
    else
        ++raw_ptr_;
    return *this;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse>& StackVector<T, N>::BasicIterator<valT, Reverse>::operator--()
{
    if constexpr (Reverse)
        ++raw_ptr_;
    else
        --raw_ptr_;
    return *this;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse> StackVector<T, N>::BasicIterator<valT, Reverse>::operator++(int)
{
    if constexpr (Reverse)
        return BasicIterator(raw_ptr_--);
    else
        return BasicIterator(raw_ptr_++);
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse> StackVector<T, N>::BasicIterator<valT, Reverse>::operator--(int)
{
    if constexpr (Reverse)
        return BasicIterator(raw_ptr_++);
    else
        return BasicIterator(raw_ptr_--);
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse>& StackVector<T, N>::BasicIterator<valT, Reverse>::operator+=(ptrdiff_t offset)
{
    if constexpr (Reverse)
        raw_ptr_ -= offset;
    else
        raw_ptr_ += offset;
    return *this;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse>& StackVector<T, N>::BasicIterator<valT, Reverse>::operator-=(ptrdiff_t offset)
{
    if constexpr (Reverse)
        raw_ptr_ += offset;
    else
        raw_ptr_ -= offset;
    return *this;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse> StackVector<T, N>::BasicIterator<valT, Reverse>::operator+(ptrdiff_t offset)
{
    auto copy = *this;
    if constexpr (Reverse)
        return copy -= offset;
    else
        return copy += offset;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse> StackVector<T, N>::BasicIterator<valT, Reverse>::operator-(ptrdiff_t offset)
{
    auto copy = *this;
    if constexpr (Reverse)
        return copy += offset;
    else
        return copy -= offset;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline ptrdiff_t StackVector<T, N>::BasicIterator<valT, Reverse>::operator-(const BasicIterator& other)
{
    if constexpr (Reverse)
        return  other.raw_ptr_ - raw_ptr_;
    else
        return raw_ptr_ - other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator==(const BasicIterator& other)
{
    return raw_ptr_ == other.raw_ptr_;
}


template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator!=(const BasicIterator& other)
{
    return raw_ptr_ != other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator<=(const BasicIterator& other)
{
    if constexpr (Reverse)
        return raw_ptr_ >= other.raw_ptr_;
    else
        return raw_ptr_ <= other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator>=(const BasicIterator& other)
{
    if constexpr (Reverse)
        return raw_ptr_ <= other.raw_ptr_;
    else
        return raw_ptr_ >= other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator<(const BasicIterator& other)
{
    if constexpr (Reverse)
        return raw_ptr_ > other.raw_ptr_;
    else
        return raw_ptr_ < other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline bool StackVector<T, N>::BasicIterator<valT, Reverse>::operator>(const BasicIterator& other)
{
    if constexpr (Reverse)
        return raw_ptr_ < other.raw_ptr_;
    else
        return raw_ptr_ > other.raw_ptr_;
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline valT& StackVector<T, N>::BasicIterator<valT, Reverse>::operator*()
{ return *raw_ptr_; }

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline valT* StackVector<T, N>::BasicIterator<valT, Reverse>::operator->()
{ return raw_ptr_; }

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline valT*& StackVector<T, N>::BasicIterator<valT, Reverse>::raw_ptr()
{ return raw_ptr_; }

#if _Namespace_Stack_Vector_by_kapt0xa__Siplify_Forward_Iterators_

template<typename T, size_t N>
inline T* StackVector<T, N>::begin()
{
    return BasicIterator<T, false>(array_);
}

template<typename T, size_t N>
inline T* StackVector<T, N>::end()
{
    return BasicIterator<T, false>(array_ + size_);
}

template<typename T, size_t N>
inline const T* StackVector<T, N>::begin() const
{
    return BasicIterator<const T, false>(array_);
}

template<typename T, size_t N>
inline const T* StackVector<T, N>::end() const
{
    return BasicIterator<const T, false>(array_ + size_);
}

template<typename T, size_t N>
inline const T* StackVector<T, N>::cbegin() const
{
    return BasicIterator<const T, false>(array_);
}

template<typename T, size_t N>
inline const T* StackVector<T, N>::cend() const
{
    return BasicIterator<const T, false>(array_ + size_);
}

#else

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<T, false> StackVector<T, N>::begin()
{
    return BasicIterator<T, false>(array_);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<T, false> StackVector<T, N>::end()
{
    return BasicIterator<T, false>(array_ + size_);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, false> StackVector<T, N>::begin() const
{
    return BasicIterator<const T, false>(array_);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, false> StackVector<T, N>::end() const
{
    return BasicIterator<const T, false>(array_ + size_);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, false> StackVector<T, N>::cbegin() const
{
    return BasicIterator<const T, false>(array_);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, false> StackVector<T, N>::cend() const
{
    return BasicIterator<const T, false>(array_ + size_);
}

#endif

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<T, true> StackVector<T, N>::rbegin()
{
    return BasicIterator<T, true>(array_ + size_ - 1);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<T, true> StackVector<T, N>::rend()
{
    return BasicIterator<T, true>(array_ - 1);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, true> StackVector<T, N>::rbegin() const
{
    return BasicIterator<const T, true>(array_ + size_ - 1);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, true> StackVector<T, N>::rend() const
{
    return BasicIterator<const T, true>(array_ - 1);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, true> StackVector<T, N>::crbegin() const
{
    return BasicIterator<const T, true>(array_ + size_ - 1);
}

template<typename T, size_t N>
inline StackVector<T, N>::BasicIterator<const T, true> StackVector<T, N>::crend() const
{
    return BasicIterator<const T, true>(array_ - 1);
}

template<typename T, size_t N>
template<typename valT, bool Reverse>
inline StackVector<T, N>::BasicIterator<valT, Reverse>::operator valT* ()
{ return raw_ptr_; }

#else

template<typename T, size_t N>
inline T* StackVector<T, N>::begin()
{ return array_; }

template<typename T, size_t N>
inline T* StackVector<T, N>::end()
{ return array_ + size_; }

template<typename T, size_t N>
inline const T* StackVector<T, N>::begin() const
{ return array_; }

template<typename T, size_t N>
inline const T* StackVector<T, N>::end() const
{ return array_ + size_; }

template<typename T, size_t N>
inline const T* StackVector<T, N>::cbegin() const
{ return array_; }

template<typename T, size_t N>
inline const T* StackVector<T, N>::cend() const
{ return array_ + size_; }

#endif
