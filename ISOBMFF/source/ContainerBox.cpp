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

#include <ISOBMFF/ContainerBox.hpp>
#include <ISOBMFF/Parser.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::ContainerBox >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< std::shared_ptr< ISOBMFF::Box > > _boxes;
};

#define XS_PIMPL_CLASS ISOBMFF::ContainerBox
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
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
            
            length   = stream.ReadBigEndianUInt32();
            name     = stream.ReadFourCC();
            
            if( length == 1 )
            {
                length  = stream.ReadBigEndianUInt64();
                
                if( name == "mdat" && parser.HasOption( ISOBMFF::Parser::Options::SkipMDAT ) )
                {
                    stream.DeleteBytes( length - 16 );
                }
                else
                {
                    content = BinaryStream( stream, length - 16 );
                }
            }
            else
            {
                if( name == "mdat" && parser.HasOption( ISOBMFF::Parser::Options::SkipMDAT ) )
                {
                    stream.DeleteBytes( length - 8 );
                }
                else
                {
                    content = BinaryStream( stream, length - 8 );
                }
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
    
    void ContainerBox::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        Box::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }
}

XS::PIMPL::Object< ISOBMFF::ContainerBox >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::ContainerBox >::IMPL::IMPL( const IMPL & o ):
    _boxes( o._boxes )
{}

XS::PIMPL::Object< ISOBMFF::ContainerBox >::IMPL::~IMPL( void )
{}

