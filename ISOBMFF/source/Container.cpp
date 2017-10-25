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
 * @file        Container.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/Container.hpp>

namespace ISOBMFF
{
    Container::~Container( void )
    {}
    
    void Container::WriteBoxes( const std::vector< std::shared_ptr< Box > > & boxes, std::ostream & os, std::size_t indentLevel )
    {
        std::string i( indentLevel * 4, ' ' );
        
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
    
    void Container::WriteBoxes( std::ostream & os, std::size_t indentLevel ) const
    {
        Container::WriteBoxes( this->GetBoxes(), os, indentLevel );
    }
    
    std::vector< std::shared_ptr< Box > > Container::GetBoxes( const std::string & name ) const
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
    
    std::shared_ptr< Box > Container::GetBox( const std::string & name ) const
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
}

