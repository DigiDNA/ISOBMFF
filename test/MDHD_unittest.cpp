/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <MDHD.hpp>             // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFMDHDTest : public ::testing::Test {
public:
  ISOBMFFMDHDTest() {}
  ~ISOBMFFMDHDTest() override {}
};

TEST_F(ISOBMFFMDHDTest, TestMDHDParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // mdhd size: 32 bytes
      0x00, 0x00, 0x00, 0x20,
      // mdhd
      0x6d, 0x64, 0x68, 0x64,
      // mdhd content:
      0x00, 0x00, 0x00, 0x00, 0xe4, 0x00, 0xb3, 0x34,
      0xe4, 0x00, 0xb3, 0x34, 0x00, 0x01, 0x5f, 0x90,
      0x00, 0x01, 0xef, 0x13, 0x00, 0x00, 0x00, 0x00,
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("mdhd");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate MDHD box
  auto mdhd = std::dynamic_pointer_cast<ISOBMFF::MDHD>(box);
  EXPECT_TRUE(mdhd != nullptr);
  // Validate creation time
  EXPECT_EQ(mdhd->GetCreationTime(), 1835296868);
  // Validate modification time
  EXPECT_EQ(mdhd->GetModificationTime(), 0);

  // Validate pad
  EXPECT_EQ(mdhd->GetPad(), 0);

  // Validate language
  EXPECT_EQ(mdhd->GetLanguage0(), 0);
  EXPECT_EQ(mdhd->GetLanguage1(), 0);
  EXPECT_EQ(mdhd->GetLanguage2(), 1);

  // Validate predefined
  EXPECT_EQ(mdhd->GetPredefined(), 24464);

  // Validate displayable properties
  auto props = mdhd->GetDisplayableProperties();
  EXPECT_EQ(props.size(), 11); // 2 from FullBox + 9 from MDHD

  // Validate FullBox properties
  EXPECT_EQ(props[0].first, "Version");
  EXPECT_EQ(props[0].second, "0");
  EXPECT_EQ(props[1].first, "Flags");
  EXPECT_EQ(props[1].second, "0x00000020");

  // Validate MDHD properties
  EXPECT_EQ(props[2].first, "Creation time");
  EXPECT_EQ(props[2].second, std::to_string(mdhd->GetCreationTime()));
  EXPECT_EQ(props[3].first, "Modification time");
  EXPECT_EQ(props[3].second, std::to_string(mdhd->GetModificationTime()));
  EXPECT_EQ(props[4].first, "Timescale");
  EXPECT_EQ(props[4].second, std::to_string(mdhd->GetTimescale()));
  EXPECT_EQ(props[5].first, "Duration");
  EXPECT_EQ(props[5].second, std::to_string(mdhd->GetDuration()));
  EXPECT_EQ(props[6].first, "Pad");
  EXPECT_EQ(props[6].second, std::to_string(mdhd->GetPad()));
  EXPECT_EQ(props[7].first, "Language0");
  EXPECT_EQ(props[7].second, std::to_string(mdhd->GetLanguage0()));
  EXPECT_EQ(props[8].first, "Language1");
  EXPECT_EQ(props[8].second, std::to_string(mdhd->GetLanguage1()));
  EXPECT_EQ(props[9].first, "Language2");
  EXPECT_EQ(props[9].second, std::to_string(mdhd->GetLanguage2()));
  EXPECT_EQ(props[10].first, "Predefined");
  EXPECT_EQ(props[10].second, std::to_string(mdhd->GetPredefined()));
}
} // namespace ISOBMFF
