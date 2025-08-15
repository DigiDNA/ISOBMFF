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
 * @file        IINF.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <IINF.hpp>
#include <ContainerBox.hpp>

namespace ISOBMFF
{
    class IINF::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< std::shared_ptr< INFE > > _entries;
    };

    IINF::IINF():
        FullBox( "iinf" ),
        impl( std::make_unique< IMPL >() )
    {}

    IINF::IINF( const IINF & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    IINF::IINF( IINF && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    IINF::~IINF()
    {}

    IINF & IINF::operator =( IINF o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( IINF & o1, IINF & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void IINF::ReadData( Parser & parser, BinaryStream & stream )
    {
        ContainerBox container( "????" );

        FullBox::ReadData( parser, stream );

        if( this->GetVersion() == 0 )
        {
            stream.ReadBigEndianUInt16();
        }
        else
        {
            stream.ReadBigEndianUInt32();
        }

        container.ReadData( parser, stream );

        this->impl->_entries.clear();

        for( const auto & box: container.GetBoxes() )
        {
            if( dynamic_cast< INFE * >( box.get() ) != nullptr )
            {
                this->AddEntry( std::dynamic_pointer_cast< INFE >( box ) );
            }
        }
    }

    void IINF::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }

    void IINF::AddEntry( std::shared_ptr< INFE > entry )
    {
        if( entry != nullptr )
        {
            this->impl->_entries.push_back( entry );
        }
    }

    std::vector< std::shared_ptr< INFE > > IINF::GetEntries() const
    {
        return this->impl->_entries;
    }

    std::shared_ptr< INFE > IINF::GetItemInfo( uint32_t itemID ) const
    {
        for( const auto & infe: this->GetEntries() )
        {
            if( infe->GetItemID() == itemID )
            {
                return infe;
            }
        }

        return nullptr;
    }

    void IINF::AddBox( std::shared_ptr< Box > box )
    {
        this->AddEntry( std::dynamic_pointer_cast< INFE >( box ) );
    }

    std::vector< std::shared_ptr< Box > > IINF::GetBoxes() const
    {
        auto v( this->GetEntries() );

        return std::vector< std::shared_ptr< Box > >( v.begin(), v.end() );
    }

    IINF::IMPL::IMPL()
    {}

    IINF::IMPL::IMPL( const IMPL & o ):
        _entries( o._entries )
    {}

    IINF::IMPL::~IMPL()
    {}
}
