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
 * @file        STSS.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <STSS.hpp>
#include <Parser.hpp>
#include <cstdint>
#include <cstring>

namespace ISOBMFF
{
    class STSS::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< uint32_t > _sample_number;
    };

    STSS::STSS():
        FullBox( "stss" ),
        impl( std::make_unique< IMPL >() )
    {}

    STSS::STSS( const STSS & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    STSS::STSS( STSS && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    STSS::~STSS()
    {}

    STSS & STSS::operator =( STSS o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( STSS & o1, STSS & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void STSS::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        uint32_t entry_count = stream.ReadBigEndianUInt32();

        for( uint32_t i = 0; i < entry_count; i++ )
        {
            this->impl->_sample_number.push_back(  stream.ReadBigEndianUInt32() );
        }
    }

    std::vector< std::pair< std::string, std::string > > STSS::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        for( unsigned int index = 0; index < this->GetEntryCount(); index++ )
        {
            props.push_back( { "Sample Number",  std::to_string( this->GetSampleNumber(  index) ) } );
        }

        return props;
    }

    size_t STSS::GetEntryCount() const
    {
        return this->impl->_sample_number.size();
    }

    uint32_t STSS::GetSampleNumber( size_t index ) const
    {
        return this->impl->_sample_number[ index ];
    }

    STSS::IMPL::IMPL()
    {}

    STSS::IMPL::IMPL( const IMPL & o )
    {
        this->_sample_number  = o._sample_number;
    }

    STSS::IMPL::~IMPL()
    {}
}
