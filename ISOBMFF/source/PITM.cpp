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
 * @file        PITM.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/PITM.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::PITM >::IMPL
{
    public:
        
        IMPL();
        IMPL( const IMPL & o );
        ~IMPL();
        
        uint32_t _itemID;
};

#define XS_PIMPL_CLASS ISOBMFF::PITM
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    PITM::PITM(): FullBox( "pitm" )
    {}
    
    void PITM::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );
        
        if( this->GetVersion() == 0 )
        {
            this->SetItemID( stream.ReadBigEndianUInt16() );
        }
        else
        {
            this->SetItemID( stream.ReadBigEndianUInt32() );
        }
    }
    
    std::vector< std::pair< std::string, std::string > > PITM::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Item ID", std::to_string( this->GetItemID() ) } );
        
        return props;
    }
    
    uint32_t PITM::GetItemID() const
    {
        return this->impl->_itemID;
    }
    
    void PITM::SetItemID( uint32_t value )
    {
        this->impl->_itemID = value;
    }
}

XS::PIMPL::Object< ISOBMFF::PITM >::IMPL::IMPL():
    _itemID( 0 )
{}

XS::PIMPL::Object< ISOBMFF::PITM >::IMPL::IMPL( const IMPL & o ):
    _itemID( o._itemID )
{}

XS::PIMPL::Object< ISOBMFF::PITM >::IMPL::~IMPL()
{}

