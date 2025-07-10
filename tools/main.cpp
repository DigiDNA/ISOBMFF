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
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include <getopt.h>


/* option values */
typedef struct arg_options
{
    int debug;
    bool analyze_flag;
    std::vector<char *> infiles;
} arg_options;


/* default option values */
arg_options DEFAULT_OPTIONS{
    .debug = 0,
    .analyze_flag = true,
    .infiles = std::vector<char *>(),
};

void usage(char *name) {
    fprintf(stderr, "usage: %s [options]\n", name);
    fprintf(stderr, "where options are:\n");
    fprintf(stderr, "\t-d:\t\tIncrease debug verbosity [%i]\n",
            DEFAULT_OPTIONS.debug);
    fprintf(stderr, "\t-q:\t\tZero debug verbosity\n");
    fprintf(stderr, "\t--analyze-flag:\tSet analyze flag%s\n",
            DEFAULT_OPTIONS.analyze_flag ? " [default]" : "");
    fprintf(stderr, "\t--no-analyze-flag:\tReset analyze flag%s\n",
            DEFAULT_OPTIONS.analyze_flag ? "" : " [default]");
    fprintf(stderr, "\tinfile [infile]+:\t\tSelect infiles\n");
    fprintf(stderr, "\t-h:\t\tHelp\n");
    exit(-1);
}


// long options with no equivalent short option
enum {
    QUIET_OPTION = CHAR_MAX + 1,
    ANALYZE_FLAG_OPTION,
    NO_ANALYZE_FLAG_OPTION,
    HELP_OPTION,
};

arg_options *parse_args(int argc, char *const *argv) {
    int c;
    static arg_options options;

    // set default option values
    options = DEFAULT_OPTIONS;

    // getopt_long stores the option index here
    int optindex = 0;

  // long options
    static struct option longopts[] =
    {
        // matching options to short options
        {"debug", no_argument, nullptr, 'd'},
        {"integer", required_argument, nullptr, 'I'},
        // options without a short option
        {"quiet", no_argument, nullptr, QUIET_OPTION},
        {"analyze-flag", no_argument, nullptr, ANALYZE_FLAG_OPTION},
        {"no-analyze-flag", no_argument, nullptr, NO_ANALYZE_FLAG_OPTION},
        {"help", no_argument, nullptr, HELP_OPTION},
        {nullptr, 0, nullptr, 0}
    };

  // parse arguments
    while (true)
    {
        c = getopt_long(argc, argv, "dh", longopts, &optindex);
        if (c == -1)
        {
            break;
        }
        switch (c)
        {
            case 0:
                // long options that define flags
                // if this option set a flag, do nothing else now
                if (longopts[optindex].flag != nullptr)
                {
                    break;
                }
                printf("option %s", longopts[optindex].name);
                if (optarg)
                {
                    printf(" with arg %s", optarg);
                }
                break;

            case 'd':
                options.debug += 1;
                break;

            case QUIET_OPTION:
                options.debug = 0;
                break;

            case ANALYZE_FLAG_OPTION:
                options.analyze_flag = true;
                break;

            case NO_ANALYZE_FLAG_OPTION:
                options.analyze_flag = false;
                break;

            case HELP_OPTION:
              case 'h':
                usage(argv[0]);

            default:
                printf("Unsupported option: %c\n", c);
                usage(argv[0]);
        }
    }

    // remaining arguments are infiles
    for ( int i = optind; i < argc; ++i )
    {
        options.infiles.push_back(argv[i]);
    }

    return &options;
}



int main( int argc, char *const * argv )
{
    arg_options *options;

    // parse args
    options = parse_args(argc, argv);
    if (options == nullptr)
    {
      usage(argv[0]);
      exit(-1);
    }
    if ( options->debug > 0 )
    {
        printf("options->debug = %i\n", options->debug);
        printf("options->analyze_flag = %i\n", options->analyze_flag);
        for (const auto & infile : options->infiles)
        {
            printf("options->infile = %s\n", infile);
        }
    }

    // parse the input files
    ISOBMFF::Parser parser;
    std::string     path;
    std::ifstream   stream;
    
    if( options->infiles.size() == 0 )
    {
        std::cerr << "No input file provided" << std::endl;

        #if defined( _WIN32 ) && defined( _DEBUG )
        getchar();
        #endif
        
        return EXIT_FAILURE;
    }
    
    for (const auto & infile : options->infiles)
    {
        path = infile;
        stream = std::ifstream( infile );
        stream = std::ifstream( infile );
        
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
        
        if ( options->analyze_flag )
        {
            std::cout << *( parser.GetFile() ) << std::endl << std::endl;
        }
    }

    #if defined( _WIN32 ) && defined( _DEBUG )
    getchar();
    #endif
    
    return EXIT_SUCCESS;
}
