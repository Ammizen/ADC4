#include <stdexcept>

#ifdef _WIN32
class NotImplementedException : public std::exception
{
public:
    virtual char const* what() const { return "Function not yet implemented."; }
};

class FileNotFoundException : public std::exception
{
public:
    virtual char const* what() const { return "Specified file does not exist."; }
};
#endif