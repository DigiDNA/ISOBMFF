/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

// This file was auto-generated using fuzz/converter.py from
// Parser_unittest.cpp.
// Do not edit directly.

#include <ISOBMFF.hpp>        // for various
#include <ISOBMFF/Parser.hpp> // for Parser

// libfuzzer infra to test the fuzz target
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const std::vector<uint8_t> buffer_vector = {data, data + size};
  {
    ISOBMFF::Parser parser;
    parser.Parse(buffer_vector);
  }
  return 0;
}
