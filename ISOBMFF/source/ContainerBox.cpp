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
 * @file        ContainerBox.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/ContainerBox.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/BinaryDataStream.hpp>

namespace ISOBMFF
{
    class ContainerBox::IMPL
    {
        public:
            
            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();
            
            std::vector< std::shared_ptr< Box > > _boxes;
    };
    
    ContainerBox::ContainerBox( const std::string & name ):
        Box( name ),
        impl( std::make_unique< IMPL >() )
    {}
    
    ContainerBox::ContainerBox( const ContainerBox & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    ContainerBox::ContainerBox( ContainerBox && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    ContainerBox::~ContainerBox()
    {}
    
    ContainerBox & ContainerBox::operator =( ContainerBox o )
    {
        Box::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( ContainerBox & o1, ContainerBox & o2 )
    {
        using std::swap;
        
        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void ContainerBox::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint64_t               length;
        std::string            name;
        std::shared_ptr< Box > box;
        BinaryDataStream     * content;
        
        this->impl->_boxes.clear();
        
        while( stream.HasBytesAvailable() )
        {
            ( void )parser;
            
            length   = stream.ReadBigEndianUInt32();
            if( length == 0 && !stream.HasBytesAvailable() )
            {
                // some ISOBMFF multiplexers end a box list with a length=0
                // entry
                break;
            }
            name     = stream.ReadFourCC();
            content  = nullptr;
            
            if( length == 1 )
            {
                length = stream.ReadBigEndianUInt64();
                
                if
                (
                       length > ( std::numeric_limits< size_t >::max )()
                    || ( name == "mdat" && parser.HasOption( Parser::Options::SkipMDATData ) )
                )
                {
                    stream.Seek( length - 16, BinaryStream::SeekDirection::Current );
                }
                else
                {
                    content = new BinaryDataStream( stream.Read( static_cast< size_t >( length ) - 16 ) );
                }
            }
            else
            {
                if( name == "mdat" && parser.HasOption( Parser::Options::SkipMDATData ) )
                {
                    stream.Seek( length - 8, BinaryStream::SeekDirection::Current );
                }
                else
                {
                    content = new BinaryDataStream( stream.Read( static_cast< uint32_t >( length ) - 8 ) );
                }
            }
            
            box = parser.CreateBox( name );
            
            if( box != nullptr )
            {
                if( content )
                {
                    try{
                        box->ReadData( parser, *content );
                    }
                    catch( std::exception & e )
                    {
                        delete( content );
                        std::cerr << "Exception while reading box " << name << ": " << e.what() << std::endl;
                        throw;
                    }
                }
                
                this->AddBox( box );
            }
            if( content )
            {
                delete( content );
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
    
    std::vector< std::shared_ptr< Box > > ContainerBox::GetBoxes() const
    {
        return this->impl->_boxes;
    }
    
    void ContainerBox::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        Box::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }
    
    ContainerBox::IMPL::IMPL()
    {}

    ContainerBox::IMPL::IMPL( const IMPL & o ):
        _boxes( o._boxes )
    {}

    ContainerBox::IMPL::~IMPL()
    {}
}
