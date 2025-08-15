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
 * @file        AVCC-NALUnit.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <AVCC.hpp>
#include <sstream>
#include <iomanip>

namespace ISOBMFF
{
    class AVCC::NALUnit::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< uint8_t > _data;
    };

    AVCC::NALUnit::NALUnit():
        impl( std::make_unique< IMPL >() )
    {}

    AVCC::NALUnit::NALUnit( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        std::vector< uint8_t > data;
        uint16_t               nal_unit_length;

        nal_unit_length = stream.ReadBigEndianUInt16();

        if( nal_unit_length > 0 )
        {
            data = std::vector< uint8_t >( nal_unit_length );

            stream.Read( &( data[ 0 ] ), nal_unit_length );
        }

        this->SetData( data );
    }

    AVCC::NALUnit::NALUnit( const AVCC::NALUnit & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    AVCC::NALUnit::NALUnit( AVCC::NALUnit && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    AVCC::NALUnit::~NALUnit()
    {}

    AVCC::NALUnit & AVCC::NALUnit::operator =( AVCC::NALUnit o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( AVCC::NALUnit & o1, AVCC::NALUnit & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string AVCC::NALUnit::GetName() const
    {
        return "NALUnit";
    }

    std::vector< uint8_t > AVCC::NALUnit::GetData() const
    {
        return this->impl->_data;
    }

    void AVCC::NALUnit::SetData( const std::vector< uint8_t > & value )
    {
        this->impl->_data = value;
    }

    std::vector< std::pair< std::string, std::string > > AVCC::NALUnit::GetDisplayableProperties() const
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
            { "Length", std::to_string( data.size() ) },
            { "Data", s }
        };
    }

    AVCC::NALUnit::IMPL::IMPL()
    {}

    AVCC::NALUnit::IMPL::IMPL( const IMPL & o ):
        _data( o._data )
    {}

    AVCC::NALUnit::IMPL::~IMPL()
    {}
}
