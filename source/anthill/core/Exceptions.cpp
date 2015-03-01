#include "Exceptions.h"

namespace anthill {

ExceptionBase::ExceptionBase() : m_what("Protoculture Exception")
{
}

ExceptionBase::ExceptionBase(char const* what) : m_what(what)
{
}

ExceptionBase::~ExceptionBase() throw()
{
}

std::string const&
ExceptionBase::message() const
{
    return m_what;
}

char const*
ExceptionBase::what() const throw()
{
    return m_what.c_str();
}

void
ExceptionBase::write(std::ostream& sink) const
{
    sink <<  m_what;
}

////////

InternalException::InternalException() : ExceptionBase("Internal exception")
{
}

InternalException::InternalException(char const* message) : ExceptionBase("Internal exception")
{
    m_what = std::string(message);
}

InternalException::InternalException(char const* fileName,
                                     int lineNumber,
                                     char const* message) : ExceptionBase("Internal exception")
{
    m_what += "(In ";
    m_what += fileName;
    m_what += " at ";
    m_what += lineNumber;
    m_what += " \"";
    m_what += message;
    m_what += "\")";
}


} // anthill