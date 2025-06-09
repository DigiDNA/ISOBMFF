/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <ISOBMFF/BinaryDataStream.hpp> // for BinaryDataStream
#include <ISOBMFF/Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFTKHDTest : public ::testing::Test {
public:
  ISOBMFFTKHDTest() {}
  ~ISOBMFFTKHDTest() override {}
};

TEST_F(ISOBMFFTKHDTest, TestTKHDParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // tkhd size: 92 bytes
      // 0x00, 0x00, 0x00, 0x5c,
      // // tkhd
      // 0x74, 0x6b, 0x68, 0x64,
      // tkhd content
      0x00, 0x00, 0x00, 0x07, 0xe4, 0x00, 0xb3, 0x34,
      0xe4, 0x00, 0xb3, 0x34, 0x00, 0x00, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x40, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00,
      0x09, 0x00, 0x00, 0x00
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("tkhd");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate TKHD box
  auto tkhd = std::dynamic_pointer_cast<ISOBMFF::TKHD>(box);
  EXPECT_TRUE(tkhd != nullptr);

  // Validate TKHD properties
  EXPECT_EQ(tkhd->GetCreationTime(), 3825251124);
  EXPECT_EQ(tkhd->GetModificationTime(), 3825251124);
  EXPECT_EQ(tkhd->GetTrackID(), 1);
  EXPECT_EQ(tkhd->GetDuration(), 0x00003702);
  EXPECT_EQ(tkhd->GetLayer(), 0);
  EXPECT_EQ(tkhd->GetAlternateGroup(), 0);
  EXPECT_EQ(tkhd->GetVolume(), 0);
  EXPECT_EQ(tkhd->GetWidth(), 1728);
  EXPECT_EQ(tkhd->GetHeight(), 2304);

  // Validate displayable properties
  auto displayableProperties = tkhd->GetDisplayableProperties();
  ASSERT_EQ(displayableProperties.size(), 12);
  EXPECT_EQ(displayableProperties[0].first, "Version");
  EXPECT_EQ(displayableProperties[1].first, "Flags");
  EXPECT_EQ(displayableProperties[2].first, "Creation time");
  EXPECT_EQ(displayableProperties[3].first, "Modification time");
  EXPECT_EQ(displayableProperties[4].first, "Track ID");
  EXPECT_EQ(displayableProperties[5].first, "Duration");
  EXPECT_EQ(displayableProperties[6].first, "Layer");
  EXPECT_EQ(displayableProperties[7].first, "Alternate group");
  EXPECT_EQ(displayableProperties[8].first, "Volume");
  EXPECT_EQ(displayableProperties[9].first, "Matrix");
  EXPECT_EQ(displayableProperties[10].first, "Width");
  EXPECT_EQ(displayableProperties[11].first, "Height");
}
} // namespace ISOBMFF
