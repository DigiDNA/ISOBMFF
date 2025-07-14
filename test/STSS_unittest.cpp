/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFSTSSTest : public ::testing::Test {
public:
  ISOBMFFSTSSTest() {}
  ~ISOBMFFSTSSTest() override {}
};

TEST_F(ISOBMFFSTSSTest, TestSTSSParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // stss size: 24 bytes
      // 0x00, 0x00, 0x00, 0x18,
      // stss
      // 0x73, 0x74, 0x73, 0x73,
      // stss content:
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1f
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("stss");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate STSS box
  auto stss = std::dynamic_pointer_cast<ISOBMFF::STSS>(box);
  ASSERT_NE(stss, nullptr) << "Failed to cast to STSS";

  // Validate entry count
  EXPECT_EQ(stss->GetEntryCount(), 2);
  // Validate sample numbers
  EXPECT_EQ(stss->GetSampleNumber(0), 1);
  EXPECT_EQ(stss->GetSampleNumber(1), 31);
}
} // namespace ISOBMFF
