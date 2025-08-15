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
 * @header      Container.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_CONTAINER_HPP
#define ISOBMFF_CONTAINER_HPP

#include <Macros.hpp>
#include <Box.hpp>
#include <vector>
#include <memory>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT Container
    {
        public:

            static void WriteBoxes( const std::vector< std::shared_ptr< Box > > & boxes, std::ostream & os, std::size_t indentLevel );

            virtual ~Container();

            virtual void                                  AddBox( std::shared_ptr< Box > box ) = 0;
            virtual std::vector< std::shared_ptr< Box > > GetBoxes()                     const = 0;

            void WriteBoxes( std::ostream & os, std::size_t indentLevel ) const;

            std::vector< std::shared_ptr< Box > > GetBoxes( const std::string & name ) const;
            std::shared_ptr< Box >                GetBox( const std::string & name )   const;

            template< class _T_ >
            std::shared_ptr< _T_ > GetTypedBox( const std::string & name ) const
            {
                return std::dynamic_pointer_cast< _T_ >( this->GetBox( name ) );
            }
    };
}

#endif /* ISOBMFF_CONTAINER_HPP */
