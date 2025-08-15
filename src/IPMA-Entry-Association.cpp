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
 * @file        IPMA-Entry-Association.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <IPMA.hpp>

namespace ISOBMFF
{
    class IPMA::Entry::Association::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            bool     _essential;
            uint16_t _propertyIndex;
    };

    IPMA::Entry::Association::Association():
        impl( std::make_unique< IMPL >() )
    {}

    IPMA::Entry::Association::Association( BinaryStream & stream, const IPMA & ipma ):
        impl( std::make_unique< IMPL >() )
    {
        if( ipma.GetFlags() & 0x01 )
        {
            {
                uint16_t u16;

                u16 = stream.ReadBigEndianUInt16();

                this->SetEssential( ( u16 >> 15 ) == 1 );
                this->SetPropertyIndex( u16 & 0x7FFF );
            }
        }
        else
        {
            {
                uint8_t u8;

                u8 = stream.ReadUInt8();

                this->SetEssential( ( u8 >> 7 ) == 1 );
                this->SetPropertyIndex( u8 & 0x7F );
            }
        }
    }

    IPMA::Entry::Association::Association( const IPMA::Entry::Association & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    IPMA::Entry::Association::Association( IPMA::Entry::Association && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    IPMA::Entry::Association::~Association()
    {}

    IPMA::Entry::Association & IPMA::Entry::Association::operator =( IPMA::Entry::Association o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( IPMA::Entry::Association & o1, IPMA::Entry::Association & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string IPMA::Entry::Association::GetName() const
    {
        return "Association";
    }

    std::vector< std::pair< std::string, std::string > > IPMA::Entry::Association::GetDisplayableProperties() const
    {
        return
        {
            { "Essential",      ( this->GetEssential() ) ? "yes" : "no" },
            { "Property index", std::to_string( this->GetPropertyIndex() ) }
        };
    }

    bool IPMA::Entry::Association::GetEssential() const
    {
        return this->impl->_essential;
    }

    uint16_t IPMA::Entry::Association::GetPropertyIndex() const
    {
        return this->impl->_propertyIndex;
    }

    void IPMA::Entry::Association::SetEssential( bool value )
    {
        this->impl->_essential = value;
    }

    void IPMA::Entry::Association::SetPropertyIndex( uint16_t value )
    {
        this->impl->_propertyIndex = value;
    }

    IPMA::Entry::Association::IMPL::IMPL():
        _essential( false ),
        _propertyIndex( 0 )
    {}

    IPMA::Entry::Association::IMPL::IMPL( const IMPL & o ):
        _essential( o._essential ),
        _propertyIndex( o._propertyIndex )
    {}

    IPMA::Entry::Association::IMPL::~IMPL()
    {}
}
