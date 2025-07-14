/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFURLTest : public ::testing::Test {
public:
  ISOBMFFURLTest() {}
  ~ISOBMFFURLTest() override {}
};

TEST_F(ISOBMFFURLTest, TestURLParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // url  size: 12 bytes
      // 0x00, 0x00, 0x00, 0x0c,
      // url
      // 0x75, 0x72, 0x6c, 0x20,
      // url  content:
      0x00, 0x00, 0x00, 0x01,
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("url ");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate URL box
  auto url = std::dynamic_pointer_cast<ISOBMFF::URL>(box);
  ASSERT_NE(url, nullptr) << "Failed to cast to URL";

  // Validate version and flags
  EXPECT_EQ(url->GetVersion(), 0);
  EXPECT_EQ(url->GetFlags(), 0x00000001);
}
} // namespace ISOBMFF
