
#include "string.h"


namespace System
{
    class Object
    {
    private:
         Object()
         {

         }
    public:
        ~Object()
        {

        }

        virtual String ToString()
        {
            CString s = "Object";
            CString a = s + "asd";
            return s;
        }
    };    
}