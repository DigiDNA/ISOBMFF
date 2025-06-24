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
 * @file        Matrix.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <Matrix.hpp>

namespace ISOBMFF
{
    class Matrix::IMPL
    {
        public:

            IMPL();
            IMPL( uint32_t a, uint32_t b, uint32_t u, uint32_t c, uint32_t d, uint32_t v, uint32_t x, uint32_t y, uint32_t w );
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t _a;
            uint32_t _b;
            uint32_t _u;
            uint32_t _c;
            uint32_t _d;
            uint32_t _v;
            uint32_t _x;
            uint32_t _y;
            uint32_t _w;
    };

    Matrix::Matrix():
        impl( std::make_unique< IMPL >() )
    {}

    Matrix::Matrix( uint32_t a, uint32_t b, uint32_t u, uint32_t c, uint32_t d, uint32_t v, uint32_t x, uint32_t y, uint32_t w ):
        impl( std::make_unique< IMPL >( a, b, u, c, d, v, x, y, w ) )
    {}

    Matrix::Matrix( const Matrix & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Matrix::Matrix( Matrix && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    Matrix::~Matrix()
    {}

    Matrix & Matrix::operator =( Matrix o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( Matrix & o1, Matrix & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string Matrix::GetName() const
    {
        return "Matrix";
    }

    uint32_t Matrix::GetA() const
    {
        return this->impl->_a;
    }

    uint32_t Matrix::GetB() const
    {
        return this->impl->_b;
    }

    uint32_t Matrix::GetU() const
    {
        return this->impl->_u;
    }

    uint32_t Matrix::GetC() const
    {
        return this->impl->_c;
    }

    uint32_t Matrix::GetD() const
    {
        return this->impl->_d;
    }

    uint32_t Matrix::GetV() const
    {
        return this->impl->_v;
    }

    uint32_t Matrix::GetX() const
    {
        return this->impl->_x;
    }

    uint32_t Matrix::GetY() const
    {
        return this->impl->_y;
    }

    uint32_t Matrix::GetW() const
    {
        return this->impl->_w;
    }

    void Matrix::SetA( uint32_t value )
    {
        this->impl->_a = value;
    }

    void Matrix::SetB( uint32_t value )
    {
        this->impl->_b = value;
    }

    void Matrix::SetU( uint32_t value )
    {
        this->impl->_u = value;
    }

    void Matrix::SetC( uint32_t value )
    {
        this->impl->_c = value;
    }

    void Matrix::SetD( uint32_t value )
    {
        this->impl->_d = value;
    }

    void Matrix::SetV( uint32_t value )
    {
        this->impl->_v = value;
    }

    void Matrix::SetX( uint32_t value )
    {
        this->impl->_x = value;
    }

    void Matrix::SetY( uint32_t value )
    {
        this->impl->_y = value;
    }

    void Matrix::SetW( uint32_t value )
    {
        this->impl->_w = value;
    }

    void Matrix::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( indentLevel * 4, ' ' );

        os << i
           << "{ a = " << this->GetA()
           << ", b = " << this->GetB()
           << ", u = " << this->GetU()
           << ", c = " << this->GetC()
           << ", d = " << this->GetD()
           << ", v = " << this->GetV()
           << ", x = " << this->GetX()
           << ", y = " << this->GetY()
           << ", w = " << this->GetW()
           << " }";
    }

    std::vector< std::pair< std::string, std::string > > Matrix::GetDisplayableProperties() const
    {
        return {
            { "a", std::to_string( this->GetA() ) },
            { "b", std::to_string( this->GetB() ) },
            { "u", std::to_string( this->GetU() ) },
            { "c", std::to_string( this->GetC() ) },
            { "d", std::to_string( this->GetD() ) },
            { "v", std::to_string( this->GetV() ) },
            { "x", std::to_string( this->GetX() ) },
            { "y", std::to_string( this->GetY() ) },
            { "w", std::to_string( this->GetW() ) },
        };
    }

    Matrix::IMPL::IMPL():
        IMPL( 0, 0, 0, 0, 0, 0, 0, 0, 0 )
    {}

    Matrix::IMPL::IMPL( uint32_t a, uint32_t b, uint32_t u, uint32_t c, uint32_t d, uint32_t v, uint32_t x, uint32_t y, uint32_t w ):
        _a( a ),
        _b( b ),
        _u( u ),
        _c( c ),
        _d( d ),
        _v( v ),
        _x( x ),
        _y( y ),
        _w( w )
    {}

    Matrix::IMPL::IMPL( const IMPL & o ):
        _a( o._a ),
        _b( o._b ),
        _u( o._u ),
        _c( o._c ),
        _d( o._d ),
        _v( o._v ),
        _x( o._x ),
        _y( o._y ),
        _w( o._w )
    {}

    Matrix::IMPL::~IMPL()
    {}
}
