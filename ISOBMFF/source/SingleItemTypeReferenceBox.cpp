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
 * @file        SingleItemTypeReferenceBox.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/SingleItemTypeReferenceBox.hpp>
#include <ISOBMFF/IREF.hpp>
#include <ISOBMFF/Parser.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::SingleItemTypeReferenceBox >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint32_t                _fromItemID;
        std::vector< uint32_t > _toItemIDs;
};

#define XS_PIMPL_CLASS ISOBMFF::SingleItemTypeReferenceBox
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    void SingleItemTypeReferenceBox::ReadData( Parser & parser, BinaryStream & stream )
    {
        const IREF * iref;
        uint16_t     count;
        uint16_t     i;
        
        iref = static_cast< const IREF * >( parser.GetInfo( "iref" ) );
        
        if( iref == nullptr )
        {
            Box::ReadData( parser, stream );
            
            return;
        }
        
        if( iref->GetVersion() == 0 )
        {
            this->SetFromItemID( stream.ReadBigEndianUInt16() );
            
            count = stream.ReadBigEndianUInt16();
            
            for( i = 0; i < count; i++ )
            {
                this->AddToItemID( stream.ReadBigEndianUInt16() );
            }
        }
        else if( iref->GetVersion() == 1 )
        {
            this->SetFromItemID( stream.ReadBigEndianUInt32() );
            
            count = stream.ReadBigEndianUInt16();
            
            for( i = 0; i < count; i++ )
            {
                this->AddToItemID( stream.ReadBigEndianUInt32() );
            }
        }
    }
    
    void SingleItemTypeReferenceBox::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string             i( ( indentLevel + 1 ) * 4, ' ' );
        std::vector< uint32_t > to;
        
        Box::WriteDescription( os, indentLevel );
        
        to = this->GetToItemIDs();
        
        os << std::endl
           << i << "- From item ID: " << this->GetFromItemID() << std::endl
           << i << "- To item IDs:  {";
       
       if( to.size() > 0 )
       {
           os << " ";
           
           for( auto u: to )
           {
               os << u << " ";
           }
       }
       
       os << "}";
    }
    
    uint32_t SingleItemTypeReferenceBox::GetFromItemID( void ) const
    {
        return this->impl->_fromItemID;
    }
    
    std::vector< uint32_t > SingleItemTypeReferenceBox::GetToItemIDs( void ) const
    {
        return this->impl->_toItemIDs;
    }
    
    void SingleItemTypeReferenceBox::SetFromItemID( uint32_t value )
    {
        this->impl->_fromItemID = value;
    }
    
    void SingleItemTypeReferenceBox::AddToItemID( uint32_t value )
    {
        this->impl->_toItemIDs.push_back( value );
    }
}

XS::PIMPL::Object< ISOBMFF::SingleItemTypeReferenceBox >::IMPL::IMPL( void ):
    _fromItemID( 0 )
{}

XS::PIMPL::Object< ISOBMFF::SingleItemTypeReferenceBox >::IMPL::IMPL( const IMPL & o ):
    _fromItemID( o._fromItemID ),
    _toItemIDs( o._toItemIDs )
{}

XS::PIMPL::Object< ISOBMFF::SingleItemTypeReferenceBox >::IMPL::~IMPL( void )
{}

