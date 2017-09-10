/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
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
 * @file        FTYP.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/FTYP.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::FTYP >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string                _majorBrand;
        uint32_t                   _minorVersion;
        std::vector< std::string > _compatibleBrands;
};

#define XS_PIMPL_CLASS ISOBMFF::FTYP
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    FTYP::FTYP( void ): Box( "ftyp" )
    {}
    
    void FTYP::ReadData( Parser & parser, BinaryStream & stream )
    {
        this->SetMajorBrand( stream.ReadFourCC() );
        this->SetMinorVersion( stream.ReadBigEndianUInt32() );
        
        while( stream.HasBytesAvailable() )
        {
            this->AddCompatibleBrand( stream.ReadFourCC() );
        }
        
        if( this->GetMajorBrand() == "qt  " )
        {
            parser.SetPreferredStringType( Parser::StringType::Pascal );
        }
        else
        {
            parser.SetPreferredStringType( Parser::StringType::NULLTerminated );
        }
    }
    
    std::vector< std::pair< std::string, std::string > > FTYP::GetDisplayableProperties( void ) const
    {
        auto props( Box::GetDisplayableProperties() );
        
        props.push_back( { "Major brand",       this->GetMajorBrand() } );
        props.push_back( { "Minor version",     std::to_string( this->GetMinorVersion() ) } );
        props.push_back( { "Compatible brands", Utils::ToString( this->GetCompatibleBrands() ) } );
        
        return props;
    }
    
    std::string FTYP::GetMajorBrand( void ) const
    {
        return this->impl->_majorBrand;
    }
    
    uint32_t FTYP::GetMinorVersion( void ) const
    {
        return this->impl->_minorVersion;
    }
    
    std::vector< std::string > FTYP::GetCompatibleBrands( void ) const
    {
        return this->impl->_compatibleBrands;
    }
    
    void FTYP::SetMajorBrand( const std::string & value )
    {
        this->impl->_majorBrand = value;
    }
    
    void FTYP::SetMinorVersion( uint32_t value )
    {
        this->impl->_minorVersion = value;
    }
    
    void FTYP::SetCompatibleBrands( const std::vector< std::string > & value )
    {
        this->impl->_compatibleBrands = value;
    }
    
    void FTYP::AddCompatibleBrand( const std::string & value )
    {
        this->impl->_compatibleBrands.push_back( value );
    }
}

XS::PIMPL::Object< ISOBMFF::FTYP >::IMPL::IMPL( void ):
    _minorVersion( 0 )
{}

XS::PIMPL::Object< ISOBMFF::FTYP >::IMPL::IMPL( const IMPL & o ):
    _majorBrand( o._majorBrand ),
    _minorVersion( o._minorVersion ),
    _compatibleBrands( o._compatibleBrands )
{}

XS::PIMPL::Object< ISOBMFF::FTYP >::IMPL::~IMPL( void )
{}

