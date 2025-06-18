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
 * @file        META.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <META.hpp>
#include <ContainerBox.hpp>
#include <cstring>

namespace ISOBMFF
{
    class META::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            bool                                  _isFullBox;
            std::vector< std::shared_ptr< Box > > _boxes;
    };

    META::META():
        FullBox( "meta" ),
        impl( std::make_unique< IMPL >() )
    {}

    META::META( const META & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    META::META( META && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    META::~META()
    {}

    META & META::operator =( META o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( META & o1, META & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void META::ReadData( Parser & parser, BinaryStream & stream )
    {
        char         n[ 4 ];
        ContainerBox container( "????" );

        stream.Get( reinterpret_cast< uint8_t * >( n ), 4, 4 );

        this->impl->_isFullBox = strncmp( n, "hdlr", 4 ) != 0;

        if( this->impl->_isFullBox )
        {
            FullBox::ReadData( parser, stream );
        }

        container.ReadData( parser, stream );

        this->impl->_boxes = container.GetBoxes();
    }

    void META::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        if( this->impl->_isFullBox )
        {
            FullBox::WriteDescription( os, indentLevel );
        }
        else
        {
            Box::WriteDescription( os, indentLevel );
        }

        Container::WriteBoxes( os, indentLevel );
    }

    void META::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }

    std::vector< std::shared_ptr< Box > > META::GetBoxes() const
    {
        return this->impl->_boxes;
    }

    META::IMPL::IMPL():
        _isFullBox( true )
    {}

    META::IMPL::IMPL( const IMPL & o ):
        _isFullBox( o._isFullBox ),
        _boxes( o._boxes )
    {}

    META::IMPL::~IMPL()
    {}
}
