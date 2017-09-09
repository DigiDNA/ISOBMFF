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
 * @file        IPMA-Entry.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/IPMA.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::IPMA::Entry >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint32_t                                         _itemID;
        std::vector< ISOBMFF::IPMA::Entry::Association > _associations;
};

#define XS_PIMPL_CLASS ISOBMFF::IPMA::Entry
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    IPMA::Entry::Entry( void )
    {}
    
    IPMA::Entry::Entry( BinaryStream & stream, const IPMA & ipma )
    {
        uint8_t count;
        uint8_t i;
        
        if( ipma.GetVersion() < 1 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
        }
        else
        {
            this->SetItemID( stream.ReadBigEndianUInt32() );
        }
        
        count = stream.ReadUInt8();
        
        for( i = 0; i < count; i++ )
        {
            this->AddAssociation( Association( stream, ipma ) );
        }
    }
    
    void IPMA::Entry::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string                i( ( indentLevel ) * 4, ' ' );
        std::vector< Association > associations;
        
        associations = this->GetAssociations();
        
        os << i << "{" << std::endl
           << i << "    - Item ID:      " << this->GetItemID() << std::endl
           << i << "    - Associations: " << associations.size();
        
        if( associations.size() > 0 )
        {
            os << std::endl
               << i
               << "    {"
               << std::endl;
            
            for( const auto & association: associations )
            {
                association.WriteDescription( os, indentLevel + 2 );
                
                os << std::endl;
            }
            
            os << i
               << "    }";
        }
        
        os << std::endl << i << "}";
    }
    
    std::ostream & operator << ( std::ostream & os, const IPMA::Entry & entry )
    {
        entry.WriteDescription( os, 0 );
        
        return os;
    }
    
    uint32_t IPMA::Entry::GetItemID( void ) const
    {
        return this->impl->_itemID;
    }
    
    void IPMA::Entry::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }
    
    std::vector< IPMA::Entry::Association > IPMA::Entry::GetAssociations( void ) const
    {
        return this->impl->_associations;
    }
    
    void IPMA::Entry::AddAssociation( const Association & association )
    {
        this->impl->_associations.push_back( association );
    }
}

XS::PIMPL::Object< ISOBMFF::IPMA::Entry >::IMPL::IMPL( void ):
    _itemID( 0 )
{}

XS::PIMPL::Object< ISOBMFF::IPMA::Entry >::IMPL::IMPL( const IMPL & o ):
    _itemID( o._itemID ),
    _associations( o._associations )
{}

XS::PIMPL::Object< ISOBMFF::IPMA::Entry >::IMPL::~IMPL( void )
{}

