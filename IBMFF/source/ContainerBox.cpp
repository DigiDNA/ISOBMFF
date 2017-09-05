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
 * @file        ContainerBox.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/ContainerBox.hpp>
#include <IBMFF/Parser.hpp>

template<>
class XS::PIMPL::Object< IBMFF::ContainerBox >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< std::shared_ptr< IBMFF::Box > > _boxes;
};

#define XS_PIMPL_CLASS IBMFF::ContainerBox
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    void ContainerBox::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint64_t               length;
        std::string            name;
        std::shared_ptr< Box > box;
        BinaryStream           content;
        
        this->impl->_boxes.clear();
        
        while( stream.HasBytesAvailable() )
        {
            ( void )parser;
            
            length   = stream.ReadBigEndianUnsignedInteger();
            name     = stream.ReadFourCC();
            
            if( length == 1 )
            {
                length  = stream.ReadBigEndianUnsignedLong();
                content = BinaryStream( stream, length - 16 );
            }
            else
            {
                content = BinaryStream( stream, length - 8 );
            }
            
            box = parser.CreateBox( name );
            
            if( box != nullptr )
            {
                box->ReadData( parser, content );
                this->AddBox( box );
            }
        }
    }
    
    void ContainerBox::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }
    
    std::vector< std::shared_ptr< Box > > ContainerBox::GetBoxes( void ) const
    {
        return this->impl->_boxes;
    }
    
    std::vector< std::shared_ptr< Box > > ContainerBox::GetBoxes( const std::string & name ) const
    {
        std::vector< std::shared_ptr< Box > > boxes;
        
        for( const auto & box: this->GetBoxes() )
        {
            if( box->GetName() == name )
            {
                boxes.push_back( box );
            }
        }
        
        return boxes;
    }
    
    std::shared_ptr< Box > ContainerBox::GetBox( const std::string & name ) const
    {
        for( const auto & box: this->GetBoxes() )
        {
            if( box->GetName() == name )
            {
                return box;
            }
        }
        
        return nullptr;
    }
    
    void ContainerBox::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string                           i( indentLevel * 4, ' ' );
        std::vector< std::shared_ptr< Box > > boxes;
        
        Box::WriteDescription( os, indentLevel );
        
        boxes = this->GetBoxes();
        
        if( boxes.size() > 0 )
        {
            os << std::endl
               << i
               << "{"
               << std::endl;
            
            for( const auto & box: boxes )
            {
                box->WriteDescription( os, indentLevel + 1 );
                
                os << std::endl;
            }
            
            os << i
               << "}";
        }
    }
}

XS::PIMPL::Object< IBMFF::ContainerBox >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< IBMFF::ContainerBox >::IMPL::IMPL( const IMPL & o ):
    _boxes( o._boxes )
{}

XS::PIMPL::Object< IBMFF::ContainerBox >::IMPL::~IMPL( void )
{}

