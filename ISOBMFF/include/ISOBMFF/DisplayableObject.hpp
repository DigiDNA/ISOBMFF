/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      DisplayableObject.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_DISPLAYABLE_OBJECT_HPP
#define ISOBMFF_DISPLAYABLE_OBJECT_HPP

#include <ostream>
#include <sstream>

namespace ISOBMFF
{
    template< class _T_ >
    class DisplayableObject
    {
        public:
            
            virtual ~DisplayableObject( void ) = default;
            
            virtual void WriteDescription( std::ostream & os, std::size_t indentLevel ) const = 0;
            
            std::string ToString( void ) const
            {
                std::stringstream ss;
                
                this->WriteDescription( ss, 0 );
                
                return ss.str();
            }
            
            friend std::ostream & operator << ( std::ostream & os, const _T_ & o )
            {
                o.WriteDescription( os, 0 );
                
                return os;
            }
    };
}

#endif /* ISOBMFF_DISPLAYABLE_OBJECT_HPP */


