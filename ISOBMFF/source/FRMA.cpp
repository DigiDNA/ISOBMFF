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

#include <ISOBMFF/FRMA.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::FRMA >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string _dataFormat;
};

#define XS_PIMPL_CLASS ISOBMFF::FRMA
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    FRMA::FRMA( void ): Box( "frma" )
    {}
    
    void FRMA::ReadData( Parser & parser, BinaryStream & stream )
    {
        ( void )parser;
        
        this->SetDataFormat( stream.ReadFourCC() );
    }
    
    std::vector< std::pair< std::string, std::string > > FRMA::GetDisplayableProperties( void ) const
    {
        auto props( Box::GetDisplayableProperties() );
        
        props.push_back( { "Data format", this->GetDataFormat() } );
        
        return props;
    }
    
    std::string FRMA::GetDataFormat( void ) const
    {
        return this->impl->_dataFormat;
    }
    
    void FRMA::SetDataFormat( const std::string & value )
    {
        this->impl->_dataFormat = value;
    }
}

XS::PIMPL::Object< ISOBMFF::FRMA >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::FRMA >::IMPL::IMPL( const IMPL & o ):
    _dataFormat( o._dataFormat )
{}

XS::PIMPL::Object< ISOBMFF::FRMA >::IMPL::~IMPL( void )
{}

