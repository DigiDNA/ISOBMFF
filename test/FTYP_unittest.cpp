/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFFTYPTest : public ::testing::Test {
public:
  ISOBMFFFTYPTest() {}
  ~ISOBMFFFTYPTest() override {}
};

TEST_F(ISOBMFFFTYPTest, TestFTYPParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // ftyp size: 24 bytes
      // 0x00, 0x00, 0x00, 0x18,
      // // ftyp
      // 0x66, 0x74, 0x79, 0x70,
      // ftyp content
      0x6d, 0x70, 0x34, 0x32,
      0x00, 0x00, 0x00, 0x00,
      0x69, 0x73, 0x6f, 0x6d,
      0x6d, 0x70, 0x34, 0x32
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("ftyp");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate FTYP box
  auto ftyp = std::dynamic_pointer_cast<ISOBMFF::FTYP>(box);
  EXPECT_TRUE(ftyp != nullptr);

  // Validate major brand
  EXPECT_EQ(ftyp->GetMajorBrand(), "mp42");

  // Validate minor version
  EXPECT_EQ(ftyp->GetMinorVersion(), 0);

  // Validate compatible brands
  std::vector<std::string> compatibleBrands = ftyp->GetCompatibleBrands();
  ASSERT_EQ(compatibleBrands.size(), 2);
  EXPECT_EQ(compatibleBrands[0], "isom");
  EXPECT_EQ(compatibleBrands[1], "mp42");

  // Validate displayable properties
  auto displayableProperties = ftyp->GetDisplayableProperties();
  ASSERT_EQ(displayableProperties.size(), 3);
  EXPECT_EQ(displayableProperties[0].first, "Major brand");
  EXPECT_EQ(displayableProperties[0].second, "mp42");
  EXPECT_EQ(displayableProperties[1].first, "Minor version");
  EXPECT_EQ(displayableProperties[1].second, "0");
  EXPECT_EQ(displayableProperties[2].first, "Compatible brands");
  EXPECT_EQ(displayableProperties[2].second, Utils::ToString(compatibleBrands));
}
} // namespace ISOBMFF
