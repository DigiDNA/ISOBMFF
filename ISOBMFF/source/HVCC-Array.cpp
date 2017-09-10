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
 * @file        HVCC-Array.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/HVCC.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::HVCC::Array >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        bool                                                            _arrayCompleteness;
        uint8_t                                                         _nalUnitType;
        std::vector< std::shared_ptr< ISOBMFF::HVCC::Array::NALUnit > > _nalUnits;
};

#define XS_PIMPL_CLASS ISOBMFF::HVCC::Array
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    HVCC::HVCC::Array::Array( void )
    {}
    
    HVCC::HVCC::Array::Array( BinaryStream & stream )
    {
        uint8_t  u8;
        uint16_t count;
        uint16_t i;
        
        u8 = stream.ReadUInt8();
        
        this->SetArrayCompleteness( ( u8 & 0x80 ) != 0 );
        this->SetNALUnitType( u8 & 0x3F );
        
        count = stream.ReadBigEndianUInt16();
        
        for( i = 0; i < count; i++ )
        {
            this->AddNALUnit( std::make_shared< NALUnit >( stream ) );
        }
    }
    
    bool HVCC::HVCC::Array::GetArrayCompleteness( void ) const
    {
        return this->impl->_arrayCompleteness;
    }
    
    uint8_t HVCC::HVCC::Array::GetNALUnitType( void ) const
    {
        return this->impl->_nalUnitType;
    }
    
    void HVCC::HVCC::Array::SetArrayCompleteness( bool value )
    {
        this->impl->_arrayCompleteness = value;
    }
    
    void HVCC::HVCC::Array::SetNALUnitType( uint8_t value )
    {
        this->impl->_nalUnitType = value;
    }
    
    std::vector< std::shared_ptr< HVCC::HVCC::Array::NALUnit > > HVCC::HVCC::Array::GetNALUnits( void ) const
    {
        return this->impl->_nalUnits;
    }
    
    void HVCC::HVCC::Array::AddNALUnit( std::shared_ptr< NALUnit > unit )
    {
        this->impl->_nalUnits.push_back( unit );
    }
    
    void HVCC::HVCC::Array::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( ( indentLevel ) * 4, ' ' );
        auto        units( this->GetNALUnits() );
        
        os << i << "{" << std::endl
           << i << "    Array completeness: " << ( ( this->GetArrayCompleteness() ) ? "yes" : "no" ) << std::endl
           << i << "    NAL unit type:      " << static_cast< uint32_t >( this->GetNALUnitType() ) << std::endl
           << i << "    NAL units:          " << units.size();
        
        if( units.size() > 0 )
        {
            os << std::endl
               << i
               << "    {"
               << std::endl;
            
            for( const auto & unit: units )
            {
                os << i << "        " << *( unit ) << std::endl;
            }
            
            os << i
               << "    }";
        }
        
        os << std::endl << i << "}";
    }
    
    std::ostream & operator << ( std::ostream & os, const HVCC::HVCC::Array & array )
    {
        array.WriteDescription( os, 0 );
        
        return os;
    }
}

XS::PIMPL::Object< ISOBMFF::HVCC::Array >::IMPL::IMPL( void ):
    _arrayCompleteness( false ),
    _nalUnitType( 0 )
{}

XS::PIMPL::Object< ISOBMFF::HVCC::Array >::IMPL::IMPL( const IMPL & o ):
    _arrayCompleteness( o._arrayCompleteness ),
    _nalUnitType( o._nalUnitType ),
    _nalUnits( o._nalUnits )
{}

XS::PIMPL::Object< ISOBMFF::HVCC::Array >::IMPL::~IMPL( void )
{}

