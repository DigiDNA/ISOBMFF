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
 * @file        META.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/META.hpp>
#include <IBMFF/ContainerBox.hpp>

template<>
class XS::PIMPL::Object< IBMFF::META >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        bool                                         _isFullBox;
        std::vector< std::shared_ptr< IBMFF::Box > > _boxes;
};

#define XS_PIMPL_CLASS IBMFF::META
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    META::META( void ): IBMFF::FullBox( "meta" )
    {}
    
    void META::ReadData( Parser & parser, BinaryStream & stream )
    {
        char         n[ 4 ];
        ContainerBox container( "????" );
        
        stream.Get( reinterpret_cast< uint8_t * >( n ), 4, 4 );
        
        this->impl->_isFullBox = strncmp( n, "hdlr", 4 ) != 0;
        
        if( this->impl->_isFullBox )
        {
            FullBox::ReadData( parser, stream );
        }
        
        container.ReadData( parser, stream );
        
        this->impl->_boxes = container.GetBoxes();
    }
    
    void META::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string                           i( indentLevel * 4, ' ' );
        std::vector< std::shared_ptr< Box > > boxes;
        
        if( this->impl->_isFullBox )
        {
            FullBox::WriteDescription( os, indentLevel );
        }
        else
        {
            Box::WriteDescription( os, indentLevel );
        }
        
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
    
    void META::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }
    
    std::vector< std::shared_ptr< Box > > META::GetBoxes( void ) const
    {
        return this->impl->_boxes;
    }
}

XS::PIMPL::Object< IBMFF::META >::IMPL::IMPL( void ):
    _isFullBox( true )
{}

XS::PIMPL::Object< IBMFF::META >::IMPL::IMPL( const IMPL & o ):
    _isFullBox( o._isFullBox ),
    _boxes( o._boxes )
{}

XS::PIMPL::Object< IBMFF::META >::IMPL::~IMPL( void )
{}

