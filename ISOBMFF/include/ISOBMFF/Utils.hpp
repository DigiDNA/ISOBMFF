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
 * @header      Utils.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_UTILS_HPP
#define ISOBMFF_UTILS_HPP

#include <ISOBMFF/Macros.hpp>
#include <vector>
#include <string>
#include <cstdint>

namespace ISOBMFF
{
    namespace Utils
    {
        ISOBMFF_EXPORT std::string Pad( const std::string & s, size_t length );
        ISOBMFF_EXPORT std::string ToString( const std::vector< std::string > & v );
        ISOBMFF_EXPORT std::string ToHexString( uint8_t u );
        ISOBMFF_EXPORT std::string ToHexString( uint16_t u );
        ISOBMFF_EXPORT std::string ToHexString( uint32_t u );
        ISOBMFF_EXPORT std::string ToHexString( uint64_t u );
        
        template< typename _T_ >
        std::string ToString( const std::vector< _T_ > & v )
        {
            std::vector< std::string > s;
            
            for( const auto & i: v )
            {
                s.push_back( std::to_string( i ) );
            }
            
            return ToString( s );
        }
    }
}

#endif /* ISOBMFF_UTILS_HPP */
