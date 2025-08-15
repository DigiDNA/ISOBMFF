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
 * @file        BinaryDataStream.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <string.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <BinaryDataStream.hpp>
#include <Casts.hpp>

namespace ISOBMFF
{
    class BinaryDataStream::IMPL
    {
        public:

            IMPL();
            IMPL( const std::vector< uint8_t > & data );
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< uint8_t > _data;
            size_t                 _pos;
    };

    BinaryDataStream::BinaryDataStream():
        impl( std::make_unique< IMPL >() )
    {}

    BinaryDataStream::BinaryDataStream( const std::vector< uint8_t > & data ):
        impl( std::make_unique< IMPL >( data ) )
    {}

    BinaryDataStream::BinaryDataStream( const BinaryDataStream & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    BinaryDataStream::BinaryDataStream( BinaryDataStream && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    BinaryDataStream::~BinaryDataStream()
    {}

    BinaryDataStream & BinaryDataStream::operator =( BinaryDataStream o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void BinaryDataStream::Read( uint8_t * buf, size_t size )
    {
        if( size > this->impl->_data.size() - this->impl->_pos )
        {
            throw std::runtime_error( "Invalid read - Not enough data available" );
        }

        memcpy( buf, &( this->impl->_data[ 0 ] ) + this->impl->_pos, size );

        this->impl->_pos += size;
    }

    void BinaryDataStream::Seek( std::streamoff offset, SeekDirection dir )
    {
        size_t pos;

        if( dir == SeekDirection::Begin )
        {
            if( offset < 0 )
            {
                throw std::runtime_error( "Invalid seek offset" );
            }

            pos = numeric_cast< size_t >( offset );
        }
        else if( dir == SeekDirection::End )
        {
            if( offset > 0 )
            {
                throw std::runtime_error( "Invalid seek offset" );
            }

            pos = this->impl->_data.size() - numeric_cast< size_t >( std::abs( offset ) );
        }
        else if( offset < 0 )
        {
            pos = this->impl->_pos - numeric_cast< size_t >( std::abs( offset ) );
        }
        else
        {
            pos = this->impl->_pos + numeric_cast< size_t >( offset );
        }

        if( pos > this->impl->_data.size() )
        {
            throw std::runtime_error( "Invalid seek offset" );
        }

        this->impl->_pos = pos;
    }

    size_t BinaryDataStream::Tell() const
    {
        return this->impl->_pos;
    }

    void swap( BinaryDataStream & o1, BinaryDataStream & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    BinaryDataStream::IMPL::IMPL():
        _pos( 0 )
    {}

    BinaryDataStream::IMPL::IMPL( const std::vector< uint8_t > & data ):
        _data( data ),
        _pos(  0 )
    {}

    BinaryDataStream::IMPL::IMPL( const IMPL & o ):
        _data( o._data ),
        _pos(  o._pos )
    {}

    BinaryDataStream::IMPL::~IMPL()
    {}
}
