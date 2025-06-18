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
 * @file        HVCC-Array-NALUnit.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <HVCC.hpp>
#include <sstream>
#include <iomanip>

namespace ISOBMFF
{
    class HVCC::Array::NALUnit::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< uint8_t > _data;
    };

    HVCC::Array::NALUnit::NALUnit():
        impl( std::make_unique< IMPL >() )
    {}

    HVCC::Array::NALUnit::NALUnit( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        std::vector< uint8_t > data;
        uint16_t               size;

        size = stream.ReadBigEndianUInt16();

        if( size > 0 )
        {
            data = std::vector< uint8_t >( size );

            stream.Read( &( data[ 0 ] ), size );
        }

        this->SetData( data );
    }

    HVCC::Array::NALUnit::NALUnit( const HVCC::Array::NALUnit & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    HVCC::Array::NALUnit::NALUnit( HVCC::Array::NALUnit && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    HVCC::Array::NALUnit::~NALUnit()
    {}

    HVCC::Array::NALUnit & HVCC::Array::NALUnit::operator =( HVCC::Array::NALUnit o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( HVCC::Array::NALUnit & o1, HVCC::Array::NALUnit & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string HVCC::Array::NALUnit::GetName() const
    {
        return "NALUnit";
    }

    std::vector< uint8_t > HVCC::Array::NALUnit::GetData() const
    {
        return this->impl->_data;
    }

    void HVCC::Array::NALUnit::SetData( const std::vector< uint8_t > & value )
    {
        this->impl->_data = value;
    }

    std::vector< std::pair< std::string, std::string > > HVCC::Array::NALUnit::GetDisplayableProperties() const
    {
        std::vector< uint8_t > data;
        std::stringstream      ss;
        std::string            s;

        data = this->GetData();

        if( data.size() > 0 )
        {
            for( auto byte: data )
            {
                ss << std::hex
                   << std::uppercase
                   << std::setfill( '0' )
                   << std::setw( 2 )
                   << static_cast< uint32_t >( byte )
                   << " ";
            }

            s = ss.str();
            s = s.substr( 0, s.length() - 1 );
        }

        return
        {
            { "Data", s },
            { "Size", std::to_string( data.size() ) }
        };
    }

    HVCC::Array::NALUnit::IMPL::IMPL()
    {}

    HVCC::Array::NALUnit::IMPL::IMPL( const IMPL & o ):
        _data( o._data )
    {}

    HVCC::Array::NALUnit::IMPL::~IMPL()
    {}
}
