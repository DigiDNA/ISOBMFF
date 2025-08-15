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
 * @file        ILOC-Item-Extent.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ILOC.hpp>

namespace ISOBMFF
{
    class ILOC::Item::Extent::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint64_t _index;
            uint64_t _offset;
            uint64_t _length;
    };

    ILOC::Item::Extent::Extent():
        impl( std::make_unique< IMPL >() )
    {}

    ILOC::Item::Extent::Extent( BinaryStream & stream, const ILOC & iloc ):
        impl( std::make_unique< IMPL >() )
    {
        if( ( iloc.GetVersion() == 1 || iloc.GetVersion() == 2 ) && iloc.GetIndexSize() > 0 )
        {
            if( iloc.GetIndexSize() == 2 )
            {
                this->SetIndex( stream.ReadBigEndianUInt16() );
            }
            else if( iloc.GetIndexSize() == 4 )
            {
                this->SetIndex( stream.ReadBigEndianUInt32() );
            }
            else if( iloc.GetIndexSize() == 8 )
            {
                this->SetIndex( stream.ReadBigEndianUInt64() );
            }
        }

        if( iloc.GetOffsetSize() == 2 )
        {
            this->SetOffset( stream.ReadBigEndianUInt16() );
        }
        else if( iloc.GetOffsetSize() == 4 )
        {
            this->SetOffset( stream.ReadBigEndianUInt32() );
        }
        else if( iloc.GetOffsetSize() == 8 )
        {
            this->SetOffset( stream.ReadBigEndianUInt64() );
        }

        if( iloc.GetLengthSize() == 2 )
        {
            this->SetLength( stream.ReadBigEndianUInt16() );
        }
        else if( iloc.GetLengthSize() == 4 )
        {
            this->SetLength( stream.ReadBigEndianUInt32() );
        }
        else if( iloc.GetLengthSize() == 8 )
        {
            this->SetLength( stream.ReadBigEndianUInt64() );
        }
    }

    ILOC::Item::Extent::Extent( const ILOC::Item::Extent & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    ILOC::Item::Extent::Extent( ILOC::Item::Extent && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    ILOC::Item::Extent::~Extent()
    {}

    ILOC::Item::Extent & ILOC::Item::Extent::operator =( ILOC::Item::Extent o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( ILOC::Item::Extent & o1, ILOC::Item::Extent & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string ILOC::Item::Extent::GetName() const
    {
        return "Extent";
    }

    uint64_t ILOC::Item::Extent::GetIndex() const
    {
        return this->impl->_index;
    }

    uint64_t ILOC::Item::Extent::GetOffset() const
    {
        return this->impl->_offset;
    }

    uint64_t ILOC::Item::Extent::GetLength() const
    {
        return this->impl->_length;
    }

    void ILOC::Item::Extent::SetIndex( uint64_t value )
    {
        this->impl->_index = value;
    }

    void ILOC::Item::Extent::SetOffset( uint64_t value )
    {
        this->impl->_offset = value;
    }

    void ILOC::Item::Extent::SetLength( uint64_t value )
    {
        this->impl->_length = value;
    }

    std::vector< std::pair< std::string, std::string > > ILOC::Item::Extent::GetDisplayableProperties() const
    {
        return
        {
            { "Index",  std::to_string( this->GetIndex() ) },
            { "Offset", std::to_string( this->GetOffset() ) },
            { "Length", std::to_string( this->GetLength() ) }
        };
    }

    ILOC::Item::Extent::IMPL::IMPL():
        _index( 0 ),
        _offset( 0 ),
        _length( 0 )
    {}

    ILOC::Item::Extent::IMPL::IMPL( const IMPL & o ):
        _index( o._index ),
        _offset( o._offset ),
        _length( o._length )
    {}

    ILOC::Item::Extent::IMPL::~IMPL()
    {}
}
