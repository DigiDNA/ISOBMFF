/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFHDLRTest : public ::testing::Test {
public:
  ISOBMFFHDLRTest() {}
  ~ISOBMFFHDLRTest() override {}
};

TEST_F(ISOBMFFHDLRTest, TestHDLRParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // hdlr size: 33 bytes
      // 0x00, 0x00, 0x00, 0x21,
      // // hdlr
      // 0x68, 0x64, 0x6c, 0x72,
      // hdlr content
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x6d, 0x64, 0x74, 0x61,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("hdlr");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate HDLR box
  auto hdlr = std::dynamic_pointer_cast<ISOBMFF::HDLR>(box);
  EXPECT_TRUE(hdlr != nullptr);

  // Validate handler type
  EXPECT_EQ(hdlr->GetHandlerType(), "mdta");
  // Validate handler name
  EXPECT_EQ(hdlr->GetHandlerName(), "");
  // Validate displayable properties
  auto displayableProperties = hdlr->GetDisplayableProperties();
  ASSERT_EQ(displayableProperties.size(), 4); // Adjust based on actual properties
  EXPECT_EQ(displayableProperties[0].first, "Version");
  EXPECT_EQ(displayableProperties[1].first, "Flags");
  EXPECT_EQ(displayableProperties[2].first, "Handler type");
  EXPECT_EQ(displayableProperties[2].second, "mdta");
  EXPECT_EQ(displayableProperties[3].first, "Handler name");
  EXPECT_EQ(displayableProperties[3].second, "");
}
} // namespace ISOBMFF
