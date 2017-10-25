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

#include <ISOBMFF/HDLR.hpp>
#include <ISOBMFF/Parser.hpp>
#include <cstdint>

template<>
class XS::PIMPL::Object< ISOBMFF::HDLR >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint32_t    _predefined;
        std::string _handlerType;
        uint32_t    _reserved[ 3 ];
        std::string _handlerName;
};

#define XS_PIMPL_CLASS ISOBMFF::HDLR
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    HDLR::HDLR( void ): FullBox( "hdlr" )
    {}
    
    void HDLR::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );
        
        this->impl->_predefined = stream.ReadBigEndianUInt32();
        
        this->SetHandlerType( stream.ReadFourCC() );
        
        this->impl->_reserved[ 0 ] = stream.ReadBigEndianUInt32();
        this->impl->_reserved[ 1 ] = stream.ReadBigEndianUInt32();
        this->impl->_reserved[ 2 ] = stream.ReadBigEndianUInt32();
        
        if( parser.GetPreferredStringType() == Parser::StringType::Pascal )
        {
            this->SetHandlerName( stream.ReadPascalString() );
        }
        else
        {
            this->SetHandlerName( stream.ReadNULLTerminatedString() );
        }
    }
    
    std::vector< std::pair< std::string, std::string > > HDLR::GetDisplayableProperties( void ) const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Handler type", this->GetHandlerType() } );
        props.push_back( { "Handler name", this->GetHandlerName() } );
        
        return props;
    }
    
    std::string HDLR::GetHandlerType( void ) const
    {
        return this->impl->_handlerType;
    }
    
    std::string HDLR::GetHandlerName( void ) const
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
}

XS::PIMPL::Object< ISOBMFF::HDLR >::IMPL::IMPL( void ):
    _predefined( 0 )
{
    memset( this->_reserved, 0, sizeof( this->_reserved ) );
}

XS::PIMPL::Object< ISOBMFF::HDLR >::IMPL::IMPL( const IMPL & o ):
    _predefined( o._predefined ),
    _handlerType( o._handlerType ),
    _handlerName( o._handlerName )
{
    memcpy( this->_reserved, o._reserved, sizeof( this->_reserved ) );
}

XS::PIMPL::Object< ISOBMFF::HDLR >::IMPL::~IMPL( void )
{}
