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
 * @header      Parser.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_PARSER_HPP
#define ISOBMFF_PARSER_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <string>
#include <functional>
#include <memory>
#include <cstdint>
#include <ISOBMFF/Box.hpp>
#include <ISOBMFF/File.hpp>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT Parser: public XS::PIMPL::Object< Parser >
    {
        public:
            
            using XS::PIMPL::Object< Parser >::impl;
            
            enum class StringType: int
            {
                NULLTerminated,
                Pascal
            };
            
            enum class Options: uint64_t
            {
                SkipMDATData = 1 << 0
            };
            
            Parser( void );
            Parser( const std::string & path );
            
            void RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >( void ) > & createBox );
            void RegisterContainerBox( const std::string & type );
            
            std::shared_ptr< Box > CreateBox( const std::string & type ) const;
            
            void Parse( const std::string & path ) ISOBMFF_NOEXCEPT( false );
            
            std::shared_ptr< File > GetFile( void ) const;
            
            StringType GetPreferredStringType( void ) const;
            void       SetPreferredStringType( StringType value );
            
            uint64_t GetOptions( void ) const;
            void     SetOptions( uint64_t value );
            void     AddOption( Options option );
            void     RemoveOption( Options option );
            bool     HasOption( Options option );
            
            const void * GetInfo( const std::string & key );
            void         SetInfo( const std::string & key, void * value );
    };
}

#endif /* ISOBMFF_PARSER_HPP */
