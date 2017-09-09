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
 * @file        IPMA.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/IPMA.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::IPMA >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< ISOBMFF::IPMA::Entry > _entries;
};

#define XS_PIMPL_CLASS ISOBMFF::IPMA
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    IPMA::IPMA( void ): FullBox( "ipma" )
    {}
    
    void IPMA::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint32_t count;
        uint32_t i;
        
        FullBox::ReadData( parser, stream );
        
        count = stream.ReadBigEndianUInt32();
        
        for( i = 0; i < count; i++ )
        {
            this->AddEntry( Entry( stream, *( this ) ) );
        }
    }
    
    void IPMA::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string          i( ( indentLevel + 1 ) * 4, ' ' );
        std::vector< Entry > entries;
        
        FullBox::WriteDescription( os, indentLevel );
        
        entries = this->GetEntries();
        
        os << std::endl
           << i << "- Entries: " << entries.size();
           
        if( entries.size() > 0 )
        {
            os << std::endl
               << i
               << "{"
               << std::endl;
            
            for( const auto & entry: entries )
            {
                entry.WriteDescription( os, indentLevel + 2 );
                
                os << std::endl;
            }
            
            os << i
               << "}";
        }
    }
    
    std::vector< IPMA::Entry > IPMA::GetEntries( void ) const
    {
        return this->impl->_entries;
    }
    
    void IPMA::AddEntry( const Entry & entry )
    {
        this->impl->_entries.push_back( entry );
    }
}

XS::PIMPL::Object< ISOBMFF::IPMA >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::IPMA >::IMPL::IMPL( const IMPL & o ):
    _entries( o._entries )
{}

XS::PIMPL::Object< ISOBMFF::IPMA >::IMPL::~IMPL( void )
{}

