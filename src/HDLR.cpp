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
 * @file        HDLR.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <HDLR.hpp>
#include <Parser.hpp>
#include <cstdint>
#include <cstring>

namespace ISOBMFF
{
    class HDLR::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint32_t    _predefined;
            std::string _handlerType;
            uint32_t    _reserved[ 3 ];
            std::string _handlerName;
    };

    HDLR::HDLR():
        FullBox( "hdlr" ),
        impl( std::make_unique< IMPL >() )
    {}

    HDLR::HDLR( const HDLR & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    HDLR::HDLR( HDLR && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    HDLR::~HDLR()
    {}

    HDLR & HDLR::operator =( HDLR o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( HDLR & o1, HDLR & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void HDLR::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        this->impl->_predefined = stream.ReadBigEndianUInt32();

        this->SetHandlerType( stream.ReadFourCC() );

        this->impl->_reserved[ 0 ] = stream.ReadBigEndianUInt32();
        this->impl->_reserved[ 1 ] = stream.ReadBigEndianUInt32();
        this->impl->_reserved[ 2 ] = stream.ReadBigEndianUInt32();

        if( stream.HasBytesAvailable() )
        {
            if
            (
                   parser.GetPreferredStringType() == Parser::StringType::Pascal
                || this->impl->_predefined         == 1835560050 /* mhlr */
                || this->impl->_reserved[ 0 ]      == 1634758764 /* appl */
            )
            {
                this->SetHandlerName( stream.ReadPascalString() );
            }
            else
            {
                this->SetHandlerName( stream.ReadNULLTerminatedString() );
            }
        }
        else
        {
            this->SetHandlerName( "" );
        }
    }

    std::vector< std::pair< std::string, std::string > > HDLR::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Handler type", this->GetHandlerType() } );
        props.push_back( { "Handler name", this->GetHandlerName() } );

        return props;
    }

    std::string HDLR::GetHandlerType() const
    {
        return this->impl->_handlerType;
    }

    std::string HDLR::GetHandlerName() const
    {
        return this->impl->_handlerName;
    }

    void HDLR::SetHandlerType( const std::string & value )
    {
        this->impl->_handlerType = value;
    }

    void HDLR::SetHandlerName( const std::string & value )
    {
        this->impl->_handlerName = value;
    }

    HDLR::IMPL::IMPL():
        _predefined( 0 )
    {
        memset( this->_reserved, 0, sizeof( this->_reserved ) );
    }

    HDLR::IMPL::IMPL( const IMPL & o ):
        _predefined( o._predefined ),
        _handlerType( o._handlerType ),
        _handlerName( o._handlerName )
    {
        memcpy( this->_reserved, o._reserved, sizeof( this->_reserved ) );
    }

    HDLR::IMPL::~IMPL()
    {}
}
