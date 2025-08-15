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
 * @file        IROT.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <IROT.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class IROT::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint8_t _angle;
    };

    IROT::IROT():
        Box( "irot" ),
        impl( std::make_unique< IMPL >() )
    {}

    IROT::IROT( const IROT & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    IROT::IROT( IROT && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    IROT::~IROT()
    {}

    IROT & IROT::operator =( IROT o )
    {
        Box::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( IROT & o1, IROT & o2 )
    {
        using std::swap;

        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void IROT::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint8_t u8;

        ( void )parser;

        u8 = stream.ReadUInt8();

        this->SetAngle( u8 & 0x3 );
    }

    std::vector< std::pair< std::string, std::string > > IROT::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );

        props.push_back( { "Angle", std::to_string( this->GetAngle() ) } );

        return props;
    }

    uint8_t IROT::GetAngle() const
    {
        return this->impl->_angle;
    }

    void IROT::SetAngle( uint8_t value )
    {
        this->impl->_angle = value;
    }

    IROT::IMPL::IMPL():
        _angle( 0 )
    {}

    IROT::IMPL::IMPL( const IMPL & o ):
        _angle( o._angle )
    {}

    IROT::IMPL::~IMPL()
    {}
}
