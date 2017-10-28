/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
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
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
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
        /*!
         * @function    Pad
         * @abstact     Pads a string with spaces to a specific length.
         * @param       s       The string to pad.
         * @param       length  The desired length of the returned string.
         * @result      The padded string.
         * @discussion  If the input string is longer than the `length`
         *              argument, the input string will be return untouched.
         */
        ISOBMFF_EXPORT std::string Pad( const std::string & s, size_t length );
        
        /*!
         * @function    ToString
         * @abstract    Returns a string representation of a string vector.
         * @param       v   The string vector.
         * @result      A string representing all values of the input string vector.
         * @discussion  Individual values will be separated by a comma and a
         *              space.
         */
        ISOBMFF_EXPORT std::string ToString( const std::vector< std::string > & v );
        
        /*!
         * @function    ToHexString
         * @abstract    Returns an hexadecimal string representation of an 8-bits unsigned integer value.
         * @param       u   The 8-bits unsigned integer value.
         * @result      The hexacdecimal string representation of the value.
         * @discussion  Result string will be prefixed by `0x`, and padded
         *              with zeros if necessary.
         */
        ISOBMFF_EXPORT std::string ToHexString( uint8_t u );
        
        /*!
         * @function    ToHexString
         * @abstract    Returns an hexadecimal string representation of a 16-bits unsigned integer value.
         * @param       u   The 16-bits unsigned integer value.
         * @result      The hexacdecimal string representation of the value.
         * @discussion  Result string will be prefixed by `0x`, and padded
         *              with zeros if necessary.
         */
        ISOBMFF_EXPORT std::string ToHexString( uint16_t u );
        
        /*!
         * @function    ToHexString
         * @abstract    Returns an hexadecimal string representation of a 32-bits unsigned integer value.
         * @param       u   The 32-bits unsigned integer value.
         * @result      The hexacdecimal string representation of the value.
         * @discussion  Result string will be prefixed by `0x`, and padded
         *              with zeros if necessary.
         */
        ISOBMFF_EXPORT std::string ToHexString( uint32_t u );
        
        /*!
         * @function    ToHexString
         * @abstract    Returns an hexadecimal string representation of a 64-bits unsigned integer value.
         * @param       u   The 64-bits unsigned integer value.
         * @result      The hexacdecimal string representation of the value.
         * @discussion  Result string will be prefixed by `0x`, and padded
         *              with zeros if necessary.
         */
        ISOBMFF_EXPORT std::string ToHexString( uint64_t u );
        
        /*!
         * @function        ToString
         * @abstract        Returns a string representation of a vector of values.
         * @templatefield   _T_ The type of value contained in the input vector.
         * @param           v   The input vector.
         * @result          A string representing all values of the input string vector.
         * @discussion      Individual values will be separated by a comma and a
         *                  space.
         *                  This method will call `std::to_string` on each value
         *                  from the input vector.
         */
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
