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
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_integral< U >::value
            && std::is_unsigned< T >::value
            && std::is_unsigned< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( ( std::numeric_limits< T >::max )() < ( std::numeric_limits< U >::max )() && v > ( std::numeric_limits< T >::max )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_integral< U >::value
            && std::is_signed< T >::value
            && std::is_signed< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( ( std::numeric_limits< T >::max )() < ( std::numeric_limits< U >::max )() && v > ( std::numeric_limits< T >::max )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( ( std::numeric_limits< T >::min )() > ( std::numeric_limits< U >::min )() && v < ( std::numeric_limits< T >::min )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_integral< U >::value
            && std::is_signed< T >::value
            && std::is_unsigned< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( static_cast< typename std::make_unsigned< T >::type >( ( std::numeric_limits< T >::max )() ) < ( std::numeric_limits< U >::max )() && v > static_cast< typename std::make_unsigned< T >::type >( ( std::numeric_limits< T >::max )() ) )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_integral< U >::value
            && std::is_unsigned< T >::value
            && std::is_signed< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( v < 0 )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( ( std::numeric_limits< T >::max )() < static_cast< typename std::make_unsigned< U >::type >( ( std::numeric_limits< U >::max )() ) && static_cast< typename std::make_unsigned< U >::type >( v ) > ( std::numeric_limits< T >::max )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_unsigned< T >::value
            && std::is_floating_point< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( v < 0 )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( v > ( std::numeric_limits< T >::max )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_integral< T >::value
            && std::is_signed< T >::value
            && std::is_floating_point< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        if( v > ( std::numeric_limits< T >::max )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        if( v < ( std::numeric_limits< T >::min )() )
        {
            throw std::runtime_error( "Bad numeric cast" );
        }
        
        return static_cast< T >( v );
    }
    
    template
    <
        typename T,
        typename U,
        typename std::enable_if
        <
               std::is_floating_point< T >::value
            && std::is_integral< U >::value
        >
        ::type * = nullptr
    >
    T numeric_cast( U v )
    {
        return static_cast< T >( v );
    }
}

#endif /* ISOBMFF_CASTS_HPP */
