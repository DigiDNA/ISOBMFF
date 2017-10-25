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
 * @file        Utils.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/Utils.hpp>
#include <sstream>
#include <iomanip>

namespace ISOBMFF
{
    namespace Utils
    {
        std::string Pad( const std::string & s, size_t length )
        {
            if( length <= s.size() )
            {
                return s;
            }
            
            return s + std::string( length - s.size(), ' ' );
        }
        
        std::string ToString( const std::vector< std::string > & v )
        {
            std::string s;
            
            for( const auto & i: v )
            {
                s += i + ", ";
            }
            
            if( s.length() )
            {
                s = s.substr( 0, s.length() - 2 );
            }
            
            return s;
        }
        
        std::string ToHexString( uint8_t u )
        {
            std::stringstream ss;
            
            ss << "0x"
               << std::hex
               << std::uppercase
               << std::setfill( '0' )
               << std::setw( 2 )
               << static_cast< uint32_t >( u );
            
            return ss.str();
        }
        
        std::string ToHexString( uint16_t u )
        {
            std::stringstream ss;
            
            ss << "0x"
               << std::hex
               << std::uppercase
               << std::setfill( '0' )
               << std::setw( 4 )
               << static_cast< uint32_t >( u );
            
            return ss.str();
        }
        
        std::string ToHexString( uint32_t u )
        {
            std::stringstream ss;
            
            ss << "0x"
               << std::hex
               << std::uppercase
               << std::setfill( '0' )
               << std::setw( 8 )
               << static_cast< uint32_t >( u );
            
            return ss.str();
        }
        
        std::string ToHexString( uint64_t u )
        {
            std::stringstream ss;
            
            ss << "0x"
               << std::hex
               << std::uppercase
               << std::setfill( '0' )
               << std::setw( 16 )
               << static_cast< uint32_t >( u );
            
            return ss.str();
        }
    }
}
