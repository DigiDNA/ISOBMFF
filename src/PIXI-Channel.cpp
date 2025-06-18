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
 * @file        PIXI-Channel.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <PIXI.hpp>

namespace ISOBMFF
{
    class PIXI::Channel::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint8_t _bitsPerChannel;
    };

    PIXI::Channel::Channel():
        impl( std::make_unique< IMPL >() )
    {}

    PIXI::Channel::Channel( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        this->SetBitsPerChannel( stream.ReadUInt8() );
    }

    PIXI::Channel::Channel( const Channel & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    PIXI::Channel::Channel( Channel && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    PIXI::Channel::~Channel()
    {}

    PIXI::Channel & PIXI::Channel::operator =( PIXI::Channel o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( PIXI::Channel & o1, PIXI::Channel & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string PIXI::Channel::GetName() const
    {
        return "Channel";
    }

    uint8_t PIXI::Channel::GetBitsPerChannel() const
    {
        return this->impl->_bitsPerChannel;
    }

    void PIXI::Channel::SetBitsPerChannel( uint8_t value )
    {
        this->impl->_bitsPerChannel = value;
    }

    std::vector< std::pair< std::string, std::string > > PIXI::Channel::GetDisplayableProperties() const
    {
        return
        {
            { "Bits per channel", std::to_string( this->GetBitsPerChannel() ) },
        };
    }

    PIXI::Channel::IMPL::IMPL():
        _bitsPerChannel( 0 )
    {}

    PIXI::Channel::IMPL::IMPL( const IMPL & o ):
        _bitsPerChannel( o._bitsPerChannel )
    {}

    PIXI::Channel::IMPL::~IMPL()
    {}
}
