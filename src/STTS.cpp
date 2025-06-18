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
 * @file        STTS.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <STTS.hpp>
#include <Parser.hpp>
#include <cstdint>
#include <cstring>

namespace ISOBMFF
{
    class STTS::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< uint32_t > _sample_count;
            std::vector< uint32_t > _sample_offset;
    };

    STTS::STTS():
        FullBox( "stts" ),
        impl( std::make_unique< IMPL >() )
    {}

    STTS::STTS( const STTS & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    STTS::STTS( STTS && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    STTS::~STTS()
    {}

    STTS & STTS::operator =( STTS o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( STTS & o1, STTS & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void STTS::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        uint32_t entry_count = stream.ReadBigEndianUInt32();

        for( uint32_t i = 0; i < entry_count; i++ )
        {
            this->impl->_sample_count.push_back(  stream.ReadBigEndianUInt32() );
            this->impl->_sample_offset.push_back( stream.ReadBigEndianUInt32() );
        }
    }

    std::vector< std::pair< std::string, std::string > > STTS::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        for( unsigned int index = 0; index < this->GetEntryCount(); index++ )
        {
            props.push_back( { "Sample Count",  std::to_string( this->GetSampleCount(  index) ) } );
            props.push_back( { "Sample Offset", std::to_string( this->GetSampleOffset( index) ) } );
        }

        return props;
    }

    size_t STTS::GetEntryCount() const
    {
        return this->impl->_sample_count.size();
    }

    uint32_t STTS::GetSampleCount( size_t index ) const
    {
        return this->impl->_sample_count[ index ];
    }

    uint32_t STTS::GetSampleOffset( size_t index ) const
    {
        return this->impl->_sample_offset[ index ];
    }

    STTS::IMPL::IMPL()
    {}

    STTS::IMPL::IMPL( const IMPL & o )
    {
        this->_sample_count  = o._sample_count;
        this->_sample_offset = o._sample_offset;
    }

    STTS::IMPL::~IMPL()
    {}
}
