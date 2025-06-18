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
 * @file        FullBox.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <FullBox.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class FullBox::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint8_t  _version;
            uint32_t _flags;
    };

    FullBox::FullBox( const std::string & name ):
        Box( name ),
        impl( std::make_unique< IMPL >() )
    {}

    FullBox::FullBox( const FullBox & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FullBox::FullBox( FullBox && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    FullBox::~FullBox()
    {}

    FullBox & FullBox::operator =( FullBox o )
    {
        Box::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( FullBox & o1, FullBox & o2 )
    {
        using std::swap;

        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void FullBox::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint32_t vf;

        ( void )parser;

        vf = stream.ReadBigEndianUInt32();

        this->SetVersion( static_cast< uint8_t >( vf >> 24 ) );
        this->SetFlags( vf & 0x00FFFFFF );
    }

    std::vector< std::pair< std::string, std::string > > FullBox::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );

        props.push_back( { "Version", std::to_string( this->GetVersion() ) } );
        props.push_back( { "Flags",   Utils::ToHexString( this->GetFlags() ) } );

        return props;
    }

    uint8_t FullBox::GetVersion() const
    {
        return this->impl->_version;
    }

    uint32_t FullBox::GetFlags() const
    {
        return this->impl->_flags;
    }

    void FullBox::SetVersion( uint8_t value )
    {
        this->impl->_version = value;
    }

    void FullBox::SetFlags( uint32_t value )
    {
        this->impl->_flags = value;
    }

    FullBox::IMPL::IMPL():
        _version( 0 ),
        _flags( 0 )
    {}

    FullBox::IMPL::IMPL( const IMPL & o ):
        _version( o._version ),
        _flags( o._flags )
    {}

    FullBox::IMPL::~IMPL()
    {}
}
