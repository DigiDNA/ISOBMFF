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
 * @file        PITM.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <PITM.hpp>

namespace ISOBMFF
{
    class PITM::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t _itemID;
    };

    PITM::PITM():
        FullBox( "pitm" ),
        impl( std::make_unique< IMPL >() )
    {}

    PITM::PITM( const PITM & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    PITM::PITM( PITM && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    PITM::~PITM()
    {}

    PITM & PITM::operator =( PITM o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( PITM & o1, PITM & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void PITM::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        if( this->GetVersion() == 0 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
        }
        else
        {
            this->SetItemID( stream.ReadBigEndianUInt32() );
        }
    }

    std::vector< std::pair< std::string, std::string > > PITM::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Item ID", std::to_string( this->GetItemID() ) } );

        return props;
    }

    uint32_t PITM::GetItemID() const
    {
        return this->impl->_itemID;
    }

    void PITM::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }

    PITM::IMPL::IMPL():
        _itemID( 0 )
    {}

    PITM::IMPL::IMPL( const IMPL & o ):
        _itemID( o._itemID )
    {}

    PITM::IMPL::~IMPL()
    {}
}
