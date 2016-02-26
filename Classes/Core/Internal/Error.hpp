//
//  Error.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/19/16.
//
//

#ifndef Error_hpp
#define Error_hpp

struct Error : std::exception
{
    char text[1000];
    
    Error(char const* fmt, ...) __attribute__((format(printf,2,3))) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(text, sizeof text, fmt, ap);
        va_end(ap);
    }
    
    char const* what() const throw() { return text; }
};

#endif /* Error_hpp */
