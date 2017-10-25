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
 * @file        IPCO.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/IPCO.hpp>

namespace ISOBMFF
{
    IPCO::IPCO( void ): ContainerBox( "ipco" )
    {}
    
    std::shared_ptr< Box > IPCO::GetPropertyAtIndex( size_t index ) const
    {
        auto boxes( this->GetBoxes() );
        
        if( index >= boxes.size() )
        {
            return nullptr;
        }
        
        return boxes[ index ];
    }
    
    std::shared_ptr< Box > IPCO::GetProperty( const IPMA::Entry::Association & association ) const
    {
        auto     boxes( this->GetBoxes() );
        uint16_t index;
        
        index = association.GetPropertyIndex();
        
        if( index == 0 )
        {
            return nullptr;
        }
        
        if( boxes.size() < index )
        {
            return nullptr;
        }
        
        return boxes[ index - 1 ];
    }
    
    std::vector< std::shared_ptr< Box > > IPCO::GetProperties( const IPMA::Entry & entry ) const
    {
        std::vector< std::shared_ptr< Box > > boxes;
        std::shared_ptr< Box >                box;
        
        for( const auto & b: entry.GetAssociations() )
        {
            box = this->GetProperty( *( b ) );
            
            if( box != nullptr )
            {
                boxes.push_back( box );
            }
        }
        
        return boxes;
    }
}
