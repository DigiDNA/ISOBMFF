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
 * @header      Casts.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_CASTS_HPP
#define ISOBMFF_CASTS_HPP

#include <type_traits>
#include <limits>
#include <stdexcept>

namespace ISOBMFF
{
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_integral< _U_ >::value
            && std::is_unsigned< _T_ >::value
            && std::is_unsigned< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( std::numeric_limits< _T_ >::max() < std::numeric_limits< _U_ >::max() && v > std::numeric_limits< _T_ >::max() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_integral< _U_ >::value
            && std::is_signed< _T_ >::value
            && std::is_signed< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( std::numeric_limits< _T_ >::max() < std::numeric_limits< _U_ >::max() && v > std::numeric_limits< _T_ >::max() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( std::numeric_limits< _T_ >::min() > std::numeric_limits< _U_ >::min() && v < std::numeric_limits< _T_ >::min() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_integral< _U_ >::value
            && std::is_signed< _T_ >::value
            && std::is_unsigned< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( static_cast< std::make_unsigned< _T_ >::type >( std::numeric_limits< _T_ >::max() ) < std::numeric_limits< _U_ >::max() && v > static_cast< std::make_unsigned< _T_ >::type >( std::numeric_limits< _T_ >::max() ) )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_integral< _U_ >::value
            && std::is_unsigned< _T_ >::value
            && std::is_signed< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( v < 0 )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( std::numeric_limits< _T_ >::max() < static_cast< std::make_unsigned< _U_ >::type >( std::numeric_limits< _U_ >::max() ) && static_cast< std::make_unsigned< _U_ >::type >( v ) > std::numeric_limits< _T_ >::max() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_unsigned< _T_ >::value
            && std::is_floating_point< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( v < 0 )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( v > std::numeric_limits< _T_ >::max() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_integral< _T_ >::value
            && std::is_signed< _T_ >::value
            && std::is_floating_point< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        if( v > std::numeric_limits< _T_ >::max() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( v < std::numeric_limits< _T_ >::min() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< _T_ >( v );
    }
    
    template
    <
        typename _T_,
        typename _U_,
        typename std::enable_if
        <
               std::is_floating_point< _T_ >::value
            && std::is_integral< _U_ >::value
        >
        ::type * = nullptr
    >
    _T_ numeric_cast( _U_ v )
    {
        return static_cast< _T_ >( v );
    }
}

#endif /* ISOBMFF_CASTS_HPP */
