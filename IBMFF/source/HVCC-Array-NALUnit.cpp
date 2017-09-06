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
 * @file        HVCC-Array-NALUnit.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/HVCC.hpp>
#include <sstream>
#include <iomanip>

template<>
class XS::PIMPL::Object< IBMFF::HVCC::Array::NALUnit >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< uint8_t > _data;
};

#define XS_PIMPL_CLASS IBMFF::HVCC::Array::NALUnit
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    HVCC::HVCC::Array::NALUnit::NALUnit( void )
    {}
    
    HVCC::HVCC::Array::NALUnit::NALUnit( BinaryStream & stream )
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
    
    std::vector< uint8_t > HVCC::HVCC::Array::NALUnit::GetData( void ) const
    {
        return this->impl->_data;
    }
    
    void HVCC::HVCC::Array::NALUnit::SetData( const std::vector< uint8_t > & value )
    {
        this->impl->_data = value;
    }
    
    std::ostream & operator << ( std::ostream & os, const HVCC::HVCC::Array::NALUnit & unit )
    {
        std::vector< uint8_t > data;
        
        data = unit.GetData();
        
        os << "{";
        
        if( data.size() > 0 )
        {
            for( auto byte: data )
            {
                {
                    std::stringstream ss;
                    
                    ss << std::hex
                       << std::uppercase
                       << std::setfill( '0' )
                       << std::setw( 2 )
                       << static_cast< uint32_t >( byte );
                    os << " " << ss.str();
                }
            }
            
            os << " ";
        }
        
        os << "}";
        
        return os;
    }
}

XS::PIMPL::Object< IBMFF::HVCC::Array::NALUnit >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::HVCC::Array::NALUnit >::IMPL::IMPL( const IMPL & o ):
    _data( o._data )
{}

XS::PIMPL::Object< IBMFF::HVCC::Array::NALUnit >::IMPL::~IMPL( void )
{}

