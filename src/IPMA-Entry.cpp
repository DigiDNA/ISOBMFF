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
 * @file        IPMA-Entry.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <IPMA.hpp>

namespace ISOBMFF
{
    class IPMA::Entry::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t                                      _itemID;
            std::vector< std::shared_ptr< Association > > _associations;
    };

    IPMA::Entry::Entry():
        impl( std::make_unique< IMPL >() )
    {}

    IPMA::Entry::Entry( BinaryStream & stream, const IPMA & ipma ):
        impl( std::make_unique< IMPL >() )
    {
        uint8_t count;
        uint8_t i;

        if( ipma.GetVersion() < 1 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
        }
        else
        {
            this->SetItemID( stream.ReadBigEndianUInt32() );
        }

        count = stream.ReadUInt8();

        for( i = 0; i < count; i++ )
        {
            this->AddAssociation( std::make_shared< Association >( stream, ipma ) );
        }
    }

    IPMA::Entry::Entry( const IPMA::Entry & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    IPMA::Entry::Entry( IPMA::Entry && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    IPMA::Entry::~Entry()
    {}

    IPMA::Entry & IPMA::Entry::operator =( IPMA::Entry o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( IPMA::Entry & o1, IPMA::Entry & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string IPMA::Entry::GetName() const
    {
        return "Entry";
    }

    void IPMA::Entry::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        DisplayableObject::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::pair< std::string, std::string > > IPMA::Entry::GetDisplayableProperties() const
    {
        return
        {
            { "Item ID",      std::to_string( this->GetItemID() ) },
            { "Associations", std::to_string( this->GetAssociations().size() ) }
        };
    }

    std::vector< std::shared_ptr< DisplayableObject > > IPMA::Entry::GetDisplayableObjects() const
    {
        auto v( this->GetAssociations() );

        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }

    uint32_t IPMA::Entry::GetItemID() const
    {
        return this->impl->_itemID;
    }

    void IPMA::Entry::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }

    std::vector< std::shared_ptr< IPMA::Entry::Association > > IPMA::Entry::GetAssociations() const
    {
        return this->impl->_associations;
    }

    void IPMA::Entry::AddAssociation( std::shared_ptr< Association > association )
    {
        this->impl->_associations.push_back( association );
    }

    IPMA::Entry::IMPL::IMPL():
        _itemID( 0 )
    {}

    IPMA::Entry::IMPL::IMPL( const IMPL & o ):
        _itemID( o._itemID ),
        _associations( o._associations )
    {}

    IPMA::Entry::IMPL::~IMPL()
    {}
}
