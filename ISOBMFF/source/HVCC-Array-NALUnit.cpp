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
 * @file        HVCC-Array-NALUnit.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/HVCC.hpp>
#include <sstream>
#include <iomanip>

template<>
class XS::PIMPL::Object< ISOBMFF::HVCC::Array::NALUnit >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< uint8_t > _data;
};

#define XS_PIMPL_CLASS ISOBMFF::HVCC::Array::NALUnit
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    HVCC::Array::NALUnit::NALUnit( void )
    {}
    
    HVCC::Array::NALUnit::NALUnit( BinaryStream & stream )
    {
        std::vector< uint8_t > data;
        uint16_t               size;
        
        size = stream.ReadBigEndianUInt16();
        
        if( size > 0 )
        {
            data = std::vector< uint8_t >( size );
            
            stream.Read( &( data[ 0 ] ), size );
        }
        
        this->SetData( data );
    }
    
    std::string HVCC::Array::NALUnit::GetName( void ) const
    {
        return "NALUnit";
    }
    
    std::vector< uint8_t > HVCC::Array::NALUnit::GetData( void ) const
    {
        return this->impl->_data;
    }
    
    void HVCC::Array::NALUnit::SetData( const std::vector< uint8_t > & value )
    {
        this->impl->_data = value;
    }
    
    std::vector< std::pair< std::string, std::string > > HVCC::Array::NALUnit::GetDisplayableProperties( void ) const
    {
        std::vector< uint8_t > data;
        std::stringstream      ss;
        std::string            s;
        
        data = this->GetData();
        
        if( data.size() > 0 )
        {
            for( auto byte: data )
            {
                ss << std::hex
                   << std::uppercase
                   << std::setfill( '0' )
                   << std::setw( 2 )
                   << static_cast< uint32_t >( byte )
                   << " ";
            }
            
            s = ss.str();
            s = s.substr( 0, s.length() - 1 );
        }
        
        return
        {
            { "Data", s },
            { "Size", std::to_string( data.size() ) }
        };
    }
}

XS::PIMPL::Object< ISOBMFF::HVCC::Array::NALUnit >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::HVCC::Array::NALUnit >::IMPL::IMPL( const IMPL & o ):
    _data( o._data )
{}

XS::PIMPL::Object< ISOBMFF::HVCC::Array::NALUnit >::IMPL::~IMPL( void )
{}

