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
 * @file        SCHM.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <SCHM.hpp>
#include <Parser.hpp>
#include <cstdint>

namespace ISOBMFF
{
    class SCHM::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::string _schemeType;
            uint32_t    _schemeVersion;
            std::string _schemeURI;
    };

    SCHM::SCHM():
        FullBox( "schm" ),
        impl( std::make_unique< IMPL >() )
    {}

    SCHM::SCHM( const SCHM & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    SCHM::SCHM( SCHM && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    SCHM::~SCHM()
    {}

    SCHM & SCHM::operator =( SCHM o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( SCHM & o1, SCHM & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void SCHM::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        this->SetSchemeType( stream.ReadFourCC() );
        this->SetSchemeVersion( stream.ReadBigEndianUInt32() );

        if( this->GetFlags() & 0x000001 )
        {
            if( parser.GetPreferredStringType() == Parser::StringType::Pascal )
            {
                this->SetSchemeURI( stream.ReadPascalString() );
            }
            else
            {
                this->SetSchemeURI( stream.ReadNULLTerminatedString() );
            }
        }
    }

    std::vector< std::pair< std::string, std::string > > SCHM::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Scheme type",    this->GetSchemeType() } );
        props.push_back( { "Scheme version", std::to_string( this->GetSchemeVersion() ) } );
        props.push_back( { "Scheme URI",     this->GetSchemeURI() } );

        return props;
    }

    std::string SCHM::GetSchemeType() const
    {
        return this->impl->_schemeType;
    }

    uint32_t SCHM::GetSchemeVersion() const
    {
        return this->impl->_schemeVersion;
    }

    std::string SCHM::GetSchemeURI() const
    {
        return this->impl->_schemeURI;
    }

    void SCHM::SetSchemeType( const std::string & value )
    {
        this->impl->_schemeType = value;
    }

    void SCHM::SetSchemeVersion( uint32_t value )
    {
        this->impl->_schemeVersion = value;
    }

    void SCHM::SetSchemeURI( const std::string & value )
    {
        this->impl->_schemeURI = value;
    }

    SCHM::IMPL::IMPL():
        _schemeVersion( 0 )
    {}

    SCHM::IMPL::IMPL( const IMPL & o ):
        _schemeType( o._schemeType ),
        _schemeVersion( o._schemeVersion ),
        _schemeURI( o._schemeURI )
    {}

    SCHM::IMPL::~IMPL()
    {}
}
