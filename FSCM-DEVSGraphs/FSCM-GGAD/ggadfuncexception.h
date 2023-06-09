
#ifndef __GGADFUNCEXCEPTION_H__
#define __GGADFUNCEXCEPTION_H__

#include <string>

class GgadFuncException {
    std::string message_;
    int formalParams_;
    int actualParams_;
public:
    GgadFuncException( const char *message, int formalParams = 0, int actualParams = 0 )
    : message_(message), formalParams_(formalParams), actualParams_(actualParams)
    {
    }

    const std::string asString() {
        return message_ /* + ". Expected: " + formalParams_ + ", found: " + actualParams_ */;
    }
};

#endif // __GGADFUNCEXCEPTION_H__
