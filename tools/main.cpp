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
 * @file        main.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF.hpp>
#include <iostream>
#include <fstream>
#include <cstring>

int main( int argc, const char * argv[] )
{
    ISOBMFF::Parser parser;
    std::string     path;
    int             i;
    std::ifstream   stream;
    
    if( argc < 2 )
    {
        std::cerr << "No input file provided" << std::endl;

        #if defined( _WIN32 ) && defined( _DEBUG )
        getchar();
        #endif
        
        return EXIT_FAILURE;
    }
    
    for( i = 1; i < argc; i++ )
    {
        path   = argv[ i ];
        stream = std::ifstream( path );
        
        if( path.length() == 0 || stream.good() == false )
        {
            std::cerr << "Input file does not exist: '" << path << "'" << std::endl;

            #if defined( _WIN32 ) && defined( _DEBUG )
            getchar();
            #endif
            
            return EXIT_FAILURE;
        }
        
        stream.close();
        
        try
        {
            parser.AddOption( ISOBMFF::Parser::Options::SkipMDATData );
            parser.Parse( path );
        }
        catch( const std::runtime_error & e )
        {
            std::cerr << e.what() << std::endl;

            #if defined( _WIN32 ) && defined( _DEBUG )
            getchar();
            #endif
            
            return EXIT_FAILURE;
        }
        
        std::cout << *( parser.GetFile() ) << std::endl << std::endl;
    }

    #if defined( _WIN32 ) && defined( _DEBUG )
    getchar();
    #endif
    
    return EXIT_SUCCESS;
}
