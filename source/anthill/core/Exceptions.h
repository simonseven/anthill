#pragma once

#include "anthill/anthill.h"

#include <exception>
#include <string>
#include <sstream>

namespace anthill {

class ANTHILL_API ExceptionBase : public std::exception {

public:

    ExceptionBase();
    ExceptionBase(char const* what);

    virtual 
    ~ExceptionBase() throw();

    std::string const&
    message() const;

    virtual char const*
    what() const throw();

    virtual void
    write(std::ostream& sink) const;

protected:

    std::string m_what;

};

class ANTHILL_API InternalException : public ExceptionBase {

public:

    InternalException();

    InternalException(char const* fileName,
                      int lineNumber,
                      char const* message);

    InternalException(char const* message);
};


} // anthill



#define AX_ENFORCE(CONDITION) do { if (!(CONDITION)) { throw anthill::InternalException(__FILE__, __LINE__, #CONDITION); }} while (false)
#define AX_ENFORCE_MSG(CONDITION, MESSAGE) do { if (!(CONDITION)) { std::ostringstream ostr; ostr << (MESSAGE); throw anthill::InternalException(__FILE__, __LINE__, ostr.str().c_str()); }} while (false)
#define AX_ENFORCE_RANGE(VALUE, MINVALUE, MAXVALUE) do { auto x = (VALUE); if ((x < (MINVALUE)) || (x > (MAXVALUE))) { throw anthill::InternalException("Out of range"); }} while(false)
#define AX_ENFORCE_NOT_NULL(PTR) do { if (!(PTR)) { throw anthill::InternalException(__FILE__, __LINE__, "Pointer or shared_ptr is NULL"); }} while (false)
#define AX_FAIL_MSG(MESSAGE) do { std::ostringstream ostr; ostr << (MESSAGE); throw anthill::InternalException(__FILE__, __LINE__, ostr.str().c_str()); } while (false)
#define AX_FAIL() do { throw anthill::InternalException(__FILE__, __LINE__, "AX_FAIL"); } while(false)
#define AX_NOTIMPL(F) do { std::ostringstream ostr; ostr << (F) << " not implemented"; throw anthill::InternalException(__FILE__, __LINE__, ostr.str().c_str()); } while (false)

#if AX_COMPILER_VISUAL_STUDIO
    #pragma warning(disable:4127)
#endif

