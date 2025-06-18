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
 * @file        STSD.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <STSD.hpp>
#include <ContainerBox.hpp>

namespace ISOBMFF
{
    class STSD::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::vector< std::shared_ptr< Box > > _boxes;
    };

    STSD::STSD():
        FullBox( "stsd" ),
        impl( std::make_unique< IMPL >() )
    {}

    STSD::STSD( const STSD & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    STSD::STSD( STSD && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    STSD::~STSD()
    {}

    STSD & STSD::operator =( STSD o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( STSD & o1, STSD & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void STSD::ReadData( Parser & parser, BinaryStream & stream )
    {
        ContainerBox container( "????" );

        FullBox::ReadData( parser, stream );
        stream.ReadBigEndianUInt32();
        container.ReadData( parser, stream );

        this->impl->_boxes = container.GetBoxes();
    }

    void STSD::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }

    void STSD::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }

    std::vector< std::shared_ptr< Box > > STSD::GetBoxes() const
    {
        return this->impl->_boxes;
    }

    STSD::IMPL::IMPL()
    {}

    STSD::IMPL::IMPL( const IMPL & o ):
        _boxes( o._boxes )
    {}

    STSD::IMPL::~IMPL()
    {}
}
