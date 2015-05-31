/* Copyright (C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef INTRUSIVE_PTR_H_INCLUDED
#define INTRUSIVE_PTR_H_INCLUDED

namespace gl_wrapper
{
  namespace ref_count
  {
    template<class T>
    class intrusive_ptr
    {
    private:
      typedef intrusive_ptr this_type;

      /// Internal pointer to type
      T *_px;

    public:
      /// Type information
      typedef T element_type;

      /*! \brief default ctor initializes the internal pointer to 0
       */
      intrusive_ptr() :
        _px(0)
      {}

      /*! \brief ctor takes in a pointer to own note explicit is left off
       * so it is valid to cast this type to a pointer.
       */
      intrusive_ptr(T *p, const bool add_ref = true) :
        _px(p)
      {
        if (_px != 0 && add_ref) {
          intrusive_ptr_add_ref(_px);
        }
      }

      /*! dtor requires that when object is destroyed there be a
       * function within the scope of T or gl_wrapper::ref_count
       * which will destroy the pointer
       */
      ~intrusive_ptr()
      {
        if (_px != 0) {
          intrusive_ptr_release(_px);
        }
      }

      /*! \brief copy constructor of same type
       */
      intrusive_ptr(const intrusive_ptr &rhs) :
        _px(rhs._px)
      {
        if (_px != 0) {
          intrusive_ptr_add_ref(_px);
        }
      }

      /*! \brief copy constructor of different type
       */
      template<class Y>
      intrusive_ptr(const intrusive_ptr<Y> &rhs) :
        _px(rhs.get())
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();

        if (_px != 0) {
          intrusive_ptr_add_ref(_px);
        }
      }

      /*! \brief assignment operator of same type
       */
      intrusive_ptr &operator=(const intrusive_ptr &rhs)
      {
        this_type(rhs).swap(*this);
        return *this;
      }

      /*! \brief assignment operator of different type
       */
      template<class Y>
      intrusive_ptr &operator=(const intrusive_ptr<Y> &rhs)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();

        this_type(rhs).swap(*this);
        return *this;
      }

      /*! \brief assignment operator of same type pointer
       */
      intrusive_ptr &operator=(T *rhs)
      {
        this_type(rhs).swap(*this);
        return *this;
      }

      /*! \brief assignment operator of different type pointer
       */
      template <typename Y>
      intrusive_ptr &operator=(Y *rhs)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();

        this_type(rhs).swap(*this);
        return *this;
      }

      /*! \brief In essence resets this to 0
       */
      void reset()
      {
        this_type().swap(*this);
      }

      /*! \brief In essence resets this to new pointer deleting
       * the previous internal pointer. The value of this' internal pointer
       * is undefined since we are not working on a reference to the initial
       * pointer.
       */
      void reset(T *rhs)
      {
        this_type(rhs).swap(*this);
      }

      /*! \brief In essence resets this to new pointer deleting
       * the previous internal pointer. The value of this' internal pointer
       * is undefined since we are not working on a reference to the initial
       * pointer.
       */
      void reset(T *rhs, bool add_ref)
      {
        this_type(rhs, add_ref).swap(*this);
      }

      /*! \brief Get access to the underlying pointer.
       */
      T *get() const
      {
        return _px;
      }

      /*! \brief Release control of the pointer and return control back to
       * the calling code as a dumb pointer.
       */
      T *detach()
      {
        T *ret = _px;
        _px = 0;
        return ret;
      }

      /*! \brief Indirection operator so you can treat object as pointer
       */
      T &operator*() const
      {
        assert(_px != 0);
        return *_px;
      }

      /*! \brief Structure dereference operator so you can treat object as
       * pointer
       */
      T *operator->() const
      {
        assert(_px != 0);
        return _px;
      }

      /*! \brief Cast to boolean to check for NULL pointer or not
       */
      operator bool () const
      {
        return (_px != 0);
      }

      /*! \brief
       */
      bool operator!() const
      {
        return _px == 0;
      }

      /*! \brief swap the values of two intrusive pointer
       */
      void swap(intrusive_ptr &rhs)
      {
        T *tmp = _px;
        _px = rhs._px;
        rhs._px = tmp;
      }
    };

    template<class T, class Y>
    inline bool operator==(const intrusive_ptr<T> &a, const intrusive_ptr<Y> &b)
    {
      return a.get() == b.get();
    }

    template<class T, class Y>
    inline bool operator!=(const intrusive_ptr<T> &a, const intrusive_ptr<Y> &b)
    {
      return a.get() != b.get();
    }

    template<class T, class Y>
    inline bool operator==(const intrusive_ptr<T> &a, Y *b)
    {
      return a.get() == b;
    }

    template<class T, class Y>
    inline bool operator!=(const intrusive_ptr<T> &a, Y *b)
    {
      return a.get() != b;
    }

    template<class T, class Y>
    inline bool operator==(T *a, const intrusive_ptr<Y> &b)
    {
      return a == b.get();
    }

    template<class T, class Y>
    inline bool operator!=(T *a, const intrusive_ptr<Y> &b)
    {
      return a != b.get();
    }

    template<class T>
    inline bool operator!=(const intrusive_ptr<T> &a, const intrusive_ptr<T> &b)
    {
      return a.get() != b.get();
    }

    template<class T>
    inline bool operator<(const intrusive_ptr<T> &a, const intrusive_ptr<T> &b)
    {
      return std::less<T *>()(a.get(), b.get());
    }

    template<class T>
    void swap(intrusive_ptr<T> &lhs, intrusive_ptr<T> &rhs)
    {
      lhs.swap(rhs);
    }

    template<class T>
    T *get_pointer(const intrusive_ptr<T> &p)
    {
      return p.get();
    }

    /*! \brief allow for up-casting without rtti type checking.
     */
    template<class T, class Y>
    intrusive_ptr<T> static_intrusive_ptr_cast(const intrusive_ptr<Y> &p)
    {
      (void)static_cast<T*>(static_cast<Y*>(0));

      return static_cast<T *>(p.get());
    }

    /*! \brief add or remove const from pointers of polymorphic types
     */
    template<class T, class Y>
    intrusive_ptr<T> const_intrusive_ptr_cast(const intrusive_ptr<Y> &p)
    {
      (void)const_cast<T*>(static_cast<Y*>(0));

      return const_cast<T *>(p.get());
    }

    /*! \brief allow for the down-casting of intrusive_ptr
     */
    template<class T, class Y>
    intrusive_ptr<T> dynamic_intrusive_ptr_cast(const intrusive_ptr<Y> &p)
    {
      (void)dynamic_cast<T*>(static_cast<Y*>(0));

      return dynamic_cast<T *>(p.get());
    }
  }
}
#endif
