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
 * @header      Matrix.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_MATRIX_HPP
#define ISOBMFF_MATRIX_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <cstdint>

namespace ISOBMFF
{
    class Matrix: public XS::PIMPL::Object< Matrix >, public DisplayableObject
    {
        public:
            
            using XS::PIMPL::Object< Matrix >::impl;
            
            Matrix( void );
            Matrix( uint32_t a, uint32_t b, uint32_t u, uint32_t c, uint32_t d, uint32_t v, uint32_t x, uint32_t y, uint32_t w );
            
            std::string GetName( void ) const override;
            
            uint32_t GetA( void ) const;
            uint32_t GetB( void ) const;
            uint32_t GetU( void ) const;
            uint32_t GetC( void ) const;
            uint32_t GetD( void ) const;
            uint32_t GetV( void ) const;
            uint32_t GetX( void ) const;
            uint32_t GetY( void ) const;
            uint32_t GetW( void ) const;
            
            void SetA( uint32_t value );
            void SetB( uint32_t value );
            void SetU( uint32_t value );
            void SetC( uint32_t value );
            void SetD( uint32_t value );
            void SetV( uint32_t value );
            void SetX( uint32_t value );
            void SetY( uint32_t value );
            void SetW( uint32_t value );
            
            void                                                         WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void )                               const override;
    };
}

#endif /* ISOBMFF_MATRIX_HPP */
