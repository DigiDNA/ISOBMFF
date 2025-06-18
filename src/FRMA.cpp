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
 * @file        FRMA.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <FRMA.hpp>
#include <Parser.hpp>
#include <Utils.hpp>

namespace ISOBMFF
{
    class FRMA::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            std::string _dataFormat;
    };

    FRMA::FRMA():
        Box( "frma" ),
        impl( std::make_unique< IMPL >() )
    {}

    FRMA::FRMA( const FRMA & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FRMA::FRMA( FRMA && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    FRMA::~FRMA()
    {}

    FRMA & FRMA::operator =( FRMA o )
    {
        Box::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( FRMA & o1, FRMA & o2 )
    {
        using std::swap;

        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void FRMA::ReadData( Parser & parser, BinaryStream & stream )
    {
        ( void )parser;

        this->SetDataFormat( stream.ReadFourCC() );
    }

    std::vector< std::pair< std::string, std::string > > FRMA::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );

        props.push_back( { "Data format", this->GetDataFormat() } );

        return props;
    }

    std::string FRMA::GetDataFormat() const
    {
        return this->impl->_dataFormat;
    }

    void FRMA::SetDataFormat( const std::string & value )
    {
        this->impl->_dataFormat = value;
    }

    FRMA::IMPL::IMPL()
    {}

    FRMA::IMPL::IMPL( const IMPL & o ):
        _dataFormat( o._dataFormat )
    {}

    FRMA::IMPL::~IMPL()
    {}
}
