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
 * @file        IINF.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/IINF.hpp>
#include <ISOBMFF/ContainerBox.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::IINF >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< std::shared_ptr< ISOBMFF::INFE > > _entries;
};

#define XS_PIMPL_CLASS ISOBMFF::IINF
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    IINF::IINF( void ): FullBox( "iinf" )
    {}
    
    void IINF::ReadData( Parser & parser, BinaryStream & stream )
    {
        ContainerBox container( "????" );
        
        FullBox::ReadData( parser, stream );
        
        if( this->GetVersion() == 0 )
        {
            stream.ReadBigEndianUInt16();
        }
        else
        {
            stream.ReadBigEndianUInt32();
        }
        
        container.ReadData( parser, stream );
        
        this->impl->_entries.clear();
        
        for( const auto & box: container.GetBoxes() )
        {
            if( dynamic_cast< INFE * >( box.get() ) != nullptr )
            {
                this->AddEntry( std::dynamic_pointer_cast< INFE >( box ) );
            }
        }
    }
    
    void IINF::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        auto v( this->GetEntries() );
        
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( std::vector< std::shared_ptr< Box > >( v.begin(), v.end() ), os, indentLevel + 1 );
    }
    
    void IINF::AddEntry( std::shared_ptr< INFE > entry )
    {
        if( entry != nullptr )
        {
            this->impl->_entries.push_back( entry );
        }
    }
    
    std::vector< std::shared_ptr< INFE > > IINF::GetEntries( void ) const
    {
        return this->impl->_entries;
    }
}

XS::PIMPL::Object< ISOBMFF::IINF >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::IINF >::IMPL::IMPL( const IMPL & o ):
    _entries( o._entries )
{}

XS::PIMPL::Object< ISOBMFF::IINF >::IMPL::~IMPL( void )
{}

