
#include <stdint.h>
#include <stddef.h>
#include <string.h>

namespace System
{
    class String
    {
    protected:
        String(const char *str, bool type) : is_constant(type)
        {
            ptr = (char *)str;
            strlen(str);
        }

    public:
        String()
        {
            is_constant = false;
        }

        String(const char *str)
        {
            is_constant = false;
        }
        virtual ~String()
        {
            if (!is_constant)
            {
                // free memory
            }
        }

        String &operator=(const char *str)
        {
        }

        String &operator=(const char &c)
        {
        }

        String &operator=(const String &rhs)
        {
        }

        String &operator=(const String &rhs)
        {
        }

        String &operator+=(const char *str)
        {
        }

        size_t Length() const
        {
            return len;
        }

        size_t Capacity() const
        {
            return cap;
        }

        void Resize(size_t n)
        {
        }

        void Resize(size_t n, char c)
        {
        }

        char &operator[](size_t pos)
        {
        }

        const char &operator[](size_t pos) const
        {
        }

        bool Empty() const
        {
            bool ret = len == 0 ? false : true;
            return ret;
        }

        void Clear()
        {
            memset(ptr, 0, len);
            len = 0;
        }

    private:
        

    protected:
        bool is_constant;
        char *ptr;
        size_t len;
        size_t cap;
    };

    class CString : public String
    {
    private:
       

    public:


        CString &operator=(const char *rhs) = delete;
        CString &operator=(const char &rhs) = delete;
        CString &operator+(const char *rhs) = delete;
        CString &operator+(const char &rhs) = delete;
        CString &operator+(const String &rhs) = delete;
        CString &operator+(const CString &rhs) = delete;
        size_t Capacity() const = delete;
        void Resize(size_t n, char c) = delete;
        void Clear() = delete;
        CString() = delete;
        

        CString(const char *str) : String(str)
        {
            is_constant = true;
            
        }

        CString(const CString & rhs)
        {
            this->len = rhs.len;
            this->is_constant = true;
            this->cap = 0;
            this->ptr = rhs.ptr;
        }

        CString(const CString && rhs)
        {
            this->len = rhs.len;
            this->is_constant = true;
            this->cap = 0;
            this->ptr = rhs.ptr;
        }


        virtual ~CString()
        {
            // do nothing
            len = 0;
            ptr = 0;
            cap = 0;
        }
    };

    String &operator+(const String &rhs)
    {
    }
    String &operator+(const CString &rhs)
    {
    }

    bool operator==(const String &lhs, const String &rhs)
    {
    }

    bool operator==(const CString &lhs, const CString &rhs)
    {
        if(lhs.)
    }

}