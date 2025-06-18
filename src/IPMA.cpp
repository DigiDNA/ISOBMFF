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
 * @file        IPMA.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <IPMA.hpp>

namespace ISOBMFF
{
    class IPMA::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< std::shared_ptr< Entry > > _entries;
    };

    IPMA::IPMA():
        FullBox( "ipma" ),
        impl( std::make_unique< IMPL >() )
    {}

    IPMA::IPMA( const IPMA & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    IPMA::IPMA( IPMA && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    IPMA::~IPMA()
    {}

    IPMA & IPMA::operator =( IPMA o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( IPMA & o1, IPMA & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void IPMA::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint32_t count;
        uint32_t i;

        FullBox::ReadData( parser, stream );

        count = stream.ReadBigEndianUInt32();

        for( i = 0; i < count; i++ )
        {
            this->AddEntry( std::make_shared< Entry >( stream, *( this ) ) );
        }
    }

    void IPMA::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::pair< std::string, std::string > > IPMA::GetDisplayableProperties() const
    {
        return
        {
            { "Entries", std::to_string( this->GetEntries().size() ) }
        };
    }

    std::vector< std::shared_ptr< DisplayableObject > > IPMA::GetDisplayableObjects() const
    {
        auto v( this->GetEntries() );

        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }

    std::vector< std::shared_ptr< IPMA::Entry > > IPMA::GetEntries() const
    {
        return this->impl->_entries;
    }

    std::shared_ptr< IPMA::Entry > IPMA::GetEntry( uint32_t itemID ) const
    {
        for( const auto & entry: this->GetEntries() )
        {
            if( entry->GetItemID() == itemID )
            {
                return entry;
            }
        }

        return nullptr;
    }

    void IPMA::AddEntry( std::shared_ptr< Entry > entry )
    {
        this->impl->_entries.push_back( entry );
    }

    IPMA::IMPL::IMPL()
    {}

    IPMA::IMPL::IMPL( const IMPL & o ):
        _entries( o._entries )
    {}

    IPMA::IMPL::~IMPL()
    {}
}
