#include "MainComponent.h"
MainComponent::MainComponent() : juce::AudioAppComponent(otherDeviceManager), state(Stopped), openB("Open"), playB("Play"), stopB("Stop"), pauseB("Pause")/*, grainSizeSlider("Grain Size"), fluxSlider("Flux")*/
{
    //Sliders & their labels prep
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mGrainSizeSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mFluxSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSpreadSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
    mGrainSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
    mFluxSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
    mSpreadSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
    shouldPaint = false;
    mAttackSlider.setRange (0.01,10);
    mGrainSizeSlider.setRange (1,1000);
    mFluxSlider.setRange (0,1000);
    mSpreadSlider.setRange (0,100);
    mAttackSlider.setValue(.1);
    mGrainSizeSlider.setValue(5);
    mFluxSlider.setValue(0);
    mSpreadSlider.setValue (50);
    mAttackSlider.setNumDecimalPlacesToDisplay(2);
    mGrainSizeSlider.setNumDecimalPlacesToDisplay(0);
    mFluxSlider.setNumDecimalPlacesToDisplay(0);
    mSpreadSlider.setNumDecimalPlacesToDisplay(0);
    mAttackSlider.setColour(Slider::ColourIds::thumbColourId,Colours::red);
    mGrainSizeSlider.setColour(Slider::ColourIds::thumbColourId,Colours::red);
    mFluxSlider.setColour(Slider::ColourIds::thumbColourId,Colours::red);
    mSpreadSlider.setColour(Slider::ColourIds::thumbColourId,Colours::red);
    mAttackLabel.setText ("Attack (ms)",NotificationType::dontSendNotification);
    mGrainSizeLabel.setText ("Grain size",NotificationType::dontSendNotification);
    mFluxLabel.setText ("Flux",NotificationType::dontSendNotification);
    mSpreadLabel.setText ("Spread (%)",NotificationType::dontSendNotification);
    mAttackLabel.setFont(10.0f);
    mAttackLabel.setJustificationType(Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    mGrainSizeLabel.setFont(10.0f);
    mGrainSizeLabel.setJustificationType(Justification::centredTop);
    mGrainSizeLabel.attachToComponent(&mGrainSizeSlider, false);
    mFluxLabel.setFont(10.0f);
    mFluxLabel.setJustificationType(Justification::centredTop);
    mFluxLabel.attachToComponent(&mFluxSlider, false);
    mSpreadLabel.setFont(10.0f);
    mSpreadLabel.setJustificationType(Justification::centredTop);
    mSpreadLabel.attachToComponent(&mSpreadSlider, false);
    noticeAboutOutputs.setFont(10.0f);
    noticeAboutOutputs.setText ("NOTE: Always route outputs starting from 1+2 sequentially upwards. If you must use a non-standard subset of output channels #s, do this by rewiring in an external controller such as Focusrite Control.",NotificationType::dontSendNotification);
    
    mAttackSlider.addListener(this);
    mGrainSizeSlider.addListener(this);
    mFluxSlider.addListener(this);
    mSpreadSlider.addListener(this);
    addAndMakeVisible(mAttackSlider);
    addAndMakeVisible(mGrainSizeSlider);
    addAndMakeVisible(mFluxSlider);
    addAndMakeVisible(mSpreadSlider);
    addAndMakeVisible(mAttackLabel);
    addAndMakeVisible(mGrainSizeLabel);
    addAndMakeVisible(mFluxLabel);
    addAndMakeVisible(mSpreadLabel);
    addAndMakeVisible(noticeAboutOutputs);
    
    attackBlocks = 0;
    otherDeviceManager.initialise(8, 8, nullptr, true);
        audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 0, 8, 0, 8, true, true, true, true));
        addAndMakeVisible(audioSettings.get());
    attack = 0.1;
    grainSize = 5;
    flux = 0;
    spread = 50;
    currentGrainCounter = grainSize;
    outputChannel = 0;
    //I'm so serious I tried EVERYTHING and this was the only way
    backgroundGifFrames[182];
    backgroundGifFrames[0] = juce::ImageFileFormat::loadFrom(BinaryData::frame_000_delay0_08s_gif, BinaryData::frame_000_delay0_08s_gifSize);
    backgroundGifFrames[1] = juce::ImageFileFormat::loadFrom(BinaryData::frame_001_delay0_08s_gif, BinaryData::frame_001_delay0_08s_gifSize);
    backgroundGifFrames[2] = juce::ImageFileFormat::loadFrom(BinaryData::frame_002_delay0_08s_gif, BinaryData::frame_002_delay0_08s_gifSize);
    backgroundGifFrames[3] = juce::ImageFileFormat::loadFrom(BinaryData::frame_003_delay0_08s_gif, BinaryData::frame_003_delay0_08s_gifSize);
    backgroundGifFrames[4] = juce::ImageFileFormat::loadFrom(BinaryData::frame_004_delay0_08s_gif, BinaryData::frame_004_delay0_08s_gifSize);
    backgroundGifFrames[5] = juce::ImageFileFormat::loadFrom(BinaryData::frame_005_delay0_08s_gif, BinaryData::frame_005_delay0_08s_gifSize);
    backgroundGifFrames[6] = juce::ImageFileFormat::loadFrom(BinaryData::frame_006_delay0_08s_gif, BinaryData::frame_006_delay0_08s_gifSize);
    backgroundGifFrames[7] = juce::ImageFileFormat::loadFrom(BinaryData::frame_007_delay0_08s_gif, BinaryData::frame_007_delay0_08s_gifSize);
    backgroundGifFrames[8] = juce::ImageFileFormat::loadFrom(BinaryData::frame_008_delay0_08s_gif, BinaryData::frame_008_delay0_08s_gifSize);
    backgroundGifFrames[9] = juce::ImageFileFormat::loadFrom(BinaryData::frame_009_delay0_08s_gif, BinaryData::frame_009_delay0_08s_gifSize);
    backgroundGifFrames[10] = juce::ImageFileFormat::loadFrom(BinaryData::frame_000_delay0_08s_gif, BinaryData::frame_000_delay0_08s_gifSize);
    backgroundGifFrames[11] = juce::ImageFileFormat::loadFrom(BinaryData::frame_011_delay0_08s_gif, BinaryData::frame_011_delay0_08s_gifSize);
    backgroundGifFrames[12] = juce::ImageFileFormat::loadFrom(BinaryData::frame_012_delay0_08s_gif, BinaryData::frame_012_delay0_08s_gifSize);
    backgroundGifFrames[13] = juce::ImageFileFormat::loadFrom(BinaryData::frame_013_delay0_08s_gif, BinaryData::frame_013_delay0_08s_gifSize);
    backgroundGifFrames[14] = juce::ImageFileFormat::loadFrom(BinaryData::frame_014_delay0_08s_gif, BinaryData::frame_014_delay0_08s_gifSize);
    backgroundGifFrames[15] = juce::ImageFileFormat::loadFrom(BinaryData::frame_015_delay0_08s_gif, BinaryData::frame_015_delay0_08s_gifSize);
    backgroundGifFrames[16] = juce::ImageFileFormat::loadFrom(BinaryData::frame_016_delay0_08s_gif, BinaryData::frame_016_delay0_08s_gifSize);
    backgroundGifFrames[17] = juce::ImageFileFormat::loadFrom(BinaryData::frame_017_delay0_08s_gif, BinaryData::frame_017_delay0_08s_gifSize);
    backgroundGifFrames[18] = juce::ImageFileFormat::loadFrom(BinaryData::frame_018_delay0_08s_gif, BinaryData::frame_018_delay0_08s_gifSize);
    backgroundGifFrames[19] = juce::ImageFileFormat::loadFrom(BinaryData::frame_019_delay0_08s_gif, BinaryData::frame_019_delay0_08s_gifSize);
    backgroundGifFrames[20] = juce::ImageFileFormat::loadFrom(BinaryData::frame_020_delay0_08s_gif, BinaryData::frame_020_delay0_08s_gifSize);
    backgroundGifFrames[21] = juce::ImageFileFormat::loadFrom(BinaryData::frame_021_delay0_08s_gif, BinaryData::frame_021_delay0_08s_gifSize);
    backgroundGifFrames[22] = juce::ImageFileFormat::loadFrom(BinaryData::frame_022_delay0_08s_gif, BinaryData::frame_022_delay0_08s_gifSize);
    backgroundGifFrames[23] = juce::ImageFileFormat::loadFrom(BinaryData::frame_023_delay0_08s_gif, BinaryData::frame_023_delay0_08s_gifSize);
    backgroundGifFrames[24] = juce::ImageFileFormat::loadFrom(BinaryData::frame_024_delay0_08s_gif, BinaryData::frame_024_delay0_08s_gifSize);
    backgroundGifFrames[25] = juce::ImageFileFormat::loadFrom(BinaryData::frame_025_delay0_08s_gif, BinaryData::frame_025_delay0_08s_gifSize);
    backgroundGifFrames[26] = juce::ImageFileFormat::loadFrom(BinaryData::frame_026_delay0_08s_gif, BinaryData::frame_026_delay0_08s_gifSize);
    backgroundGifFrames[27] = juce::ImageFileFormat::loadFrom(BinaryData::frame_027_delay0_08s_gif, BinaryData::frame_027_delay0_08s_gifSize);
    backgroundGifFrames[28] = juce::ImageFileFormat::loadFrom(BinaryData::frame_028_delay0_08s_gif, BinaryData::frame_028_delay0_08s_gifSize);
    backgroundGifFrames[29] = juce::ImageFileFormat::loadFrom(BinaryData::frame_029_delay0_08s_gif, BinaryData::frame_029_delay0_08s_gifSize);
    backgroundGifFrames[30] = juce::ImageFileFormat::loadFrom(BinaryData::frame_030_delay0_08s_gif, BinaryData::frame_030_delay0_08s_gifSize);
    backgroundGifFrames[31] = juce::ImageFileFormat::loadFrom(BinaryData::frame_031_delay0_08s_gif, BinaryData::frame_031_delay0_08s_gifSize);
    backgroundGifFrames[32] = juce::ImageFileFormat::loadFrom(BinaryData::frame_032_delay0_08s_gif, BinaryData::frame_032_delay0_08s_gifSize);
    backgroundGifFrames[33] = juce::ImageFileFormat::loadFrom(BinaryData::frame_033_delay0_08s_gif, BinaryData::frame_033_delay0_08s_gifSize);
    backgroundGifFrames[34] = juce::ImageFileFormat::loadFrom(BinaryData::frame_034_delay0_08s_gif, BinaryData::frame_034_delay0_08s_gifSize);
    backgroundGifFrames[35] = juce::ImageFileFormat::loadFrom(BinaryData::frame_035_delay0_08s_gif, BinaryData::frame_035_delay0_08s_gifSize);
    backgroundGifFrames[36] = juce::ImageFileFormat::loadFrom(BinaryData::frame_036_delay0_08s_gif, BinaryData::frame_036_delay0_08s_gifSize);
    backgroundGifFrames[37] = juce::ImageFileFormat::loadFrom(BinaryData::frame_037_delay0_08s_gif, BinaryData::frame_037_delay0_08s_gifSize);
    backgroundGifFrames[38] = juce::ImageFileFormat::loadFrom(BinaryData::frame_038_delay0_08s_gif, BinaryData::frame_038_delay0_08s_gifSize);
    backgroundGifFrames[39] = juce::ImageFileFormat::loadFrom(BinaryData::frame_039_delay0_08s_gif, BinaryData::frame_039_delay0_08s_gifSize);
    backgroundGifFrames[40] = juce::ImageFileFormat::loadFrom(BinaryData::frame_040_delay0_08s_gif, BinaryData::frame_040_delay0_08s_gifSize);
    backgroundGifFrames[41] = juce::ImageFileFormat::loadFrom(BinaryData::frame_041_delay0_08s_gif, BinaryData::frame_041_delay0_08s_gifSize);
    backgroundGifFrames[42] = juce::ImageFileFormat::loadFrom(BinaryData::frame_042_delay0_08s_gif, BinaryData::frame_042_delay0_08s_gifSize);
    backgroundGifFrames[43] = juce::ImageFileFormat::loadFrom(BinaryData::frame_043_delay0_08s_gif, BinaryData::frame_043_delay0_08s_gifSize);
    backgroundGifFrames[44] = juce::ImageFileFormat::loadFrom(BinaryData::frame_044_delay0_08s_gif, BinaryData::frame_044_delay0_08s_gifSize);
    backgroundGifFrames[45] = juce::ImageFileFormat::loadFrom(BinaryData::frame_045_delay0_08s_gif, BinaryData::frame_045_delay0_08s_gifSize);
    backgroundGifFrames[46] = juce::ImageFileFormat::loadFrom(BinaryData::frame_046_delay0_08s_gif, BinaryData::frame_046_delay0_08s_gifSize);
    backgroundGifFrames[47] = juce::ImageFileFormat::loadFrom(BinaryData::frame_047_delay0_08s_gif, BinaryData::frame_047_delay0_08s_gifSize);
    backgroundGifFrames[48] = juce::ImageFileFormat::loadFrom(BinaryData::frame_048_delay0_08s_gif, BinaryData::frame_048_delay0_08s_gifSize);
    backgroundGifFrames[49] = juce::ImageFileFormat::loadFrom(BinaryData::frame_049_delay0_08s_gif, BinaryData::frame_049_delay0_08s_gifSize);
    backgroundGifFrames[50] = juce::ImageFileFormat::loadFrom(BinaryData::frame_050_delay0_08s_gif, BinaryData::frame_050_delay0_08s_gifSize);
    backgroundGifFrames[51] = juce::ImageFileFormat::loadFrom(BinaryData::frame_051_delay0_08s_gif, BinaryData::frame_051_delay0_08s_gifSize);
    backgroundGifFrames[52] = juce::ImageFileFormat::loadFrom(BinaryData::frame_052_delay0_08s_gif, BinaryData::frame_052_delay0_08s_gifSize);
    backgroundGifFrames[53] = juce::ImageFileFormat::loadFrom(BinaryData::frame_053_delay0_08s_gif, BinaryData::frame_053_delay0_08s_gifSize);
    backgroundGifFrames[54] = juce::ImageFileFormat::loadFrom(BinaryData::frame_054_delay0_08s_gif, BinaryData::frame_054_delay0_08s_gifSize);
    backgroundGifFrames[55] = juce::ImageFileFormat::loadFrom(BinaryData::frame_055_delay0_08s_gif, BinaryData::frame_055_delay0_08s_gifSize);
    backgroundGifFrames[56] = juce::ImageFileFormat::loadFrom(BinaryData::frame_056_delay0_08s_gif, BinaryData::frame_056_delay0_08s_gifSize);
    backgroundGifFrames[57] = juce::ImageFileFormat::loadFrom(BinaryData::frame_057_delay0_08s_gif, BinaryData::frame_057_delay0_08s_gifSize);
    backgroundGifFrames[58] = juce::ImageFileFormat::loadFrom(BinaryData::frame_058_delay0_08s_gif, BinaryData::frame_058_delay0_08s_gifSize);
    backgroundGifFrames[59] = juce::ImageFileFormat::loadFrom(BinaryData::frame_059_delay0_08s_gif, BinaryData::frame_059_delay0_08s_gifSize);
    backgroundGifFrames[60] = juce::ImageFileFormat::loadFrom(BinaryData::frame_060_delay0_08s_gif, BinaryData::frame_060_delay0_08s_gifSize);
    backgroundGifFrames[61] = juce::ImageFileFormat::loadFrom(BinaryData::frame_061_delay0_08s_gif, BinaryData::frame_061_delay0_08s_gifSize);
    backgroundGifFrames[62] = juce::ImageFileFormat::loadFrom(BinaryData::frame_062_delay0_08s_gif, BinaryData::frame_062_delay0_08s_gifSize);
    backgroundGifFrames[63] = juce::ImageFileFormat::loadFrom(BinaryData::frame_063_delay0_08s_gif, BinaryData::frame_063_delay0_08s_gifSize);
    backgroundGifFrames[64] = juce::ImageFileFormat::loadFrom(BinaryData::frame_064_delay0_08s_gif, BinaryData::frame_064_delay0_08s_gifSize);
    backgroundGifFrames[65] = juce::ImageFileFormat::loadFrom(BinaryData::frame_065_delay0_08s_gif, BinaryData::frame_065_delay0_08s_gifSize);
    backgroundGifFrames[66] = juce::ImageFileFormat::loadFrom(BinaryData::frame_066_delay0_08s_gif, BinaryData::frame_066_delay0_08s_gifSize);
    backgroundGifFrames[67] = juce::ImageFileFormat::loadFrom(BinaryData::frame_067_delay0_08s_gif, BinaryData::frame_067_delay0_08s_gifSize);
    backgroundGifFrames[68] = juce::ImageFileFormat::loadFrom(BinaryData::frame_068_delay0_08s_gif, BinaryData::frame_068_delay0_08s_gifSize);
    backgroundGifFrames[69] = juce::ImageFileFormat::loadFrom(BinaryData::frame_069_delay0_08s_gif, BinaryData::frame_069_delay0_08s_gifSize);
    backgroundGifFrames[70] = juce::ImageFileFormat::loadFrom(BinaryData::frame_070_delay0_08s_gif, BinaryData::frame_070_delay0_08s_gifSize);
    backgroundGifFrames[71] = juce::ImageFileFormat::loadFrom(BinaryData::frame_071_delay0_08s_gif, BinaryData::frame_071_delay0_08s_gifSize);
    backgroundGifFrames[72] = juce::ImageFileFormat::loadFrom(BinaryData::frame_072_delay0_08s_gif, BinaryData::frame_072_delay0_08s_gifSize);
    backgroundGifFrames[73] = juce::ImageFileFormat::loadFrom(BinaryData::frame_073_delay0_08s_gif, BinaryData::frame_073_delay0_08s_gifSize);
    backgroundGifFrames[74] = juce::ImageFileFormat::loadFrom(BinaryData::frame_074_delay0_08s_gif, BinaryData::frame_074_delay0_08s_gifSize);
    backgroundGifFrames[75] = juce::ImageFileFormat::loadFrom(BinaryData::frame_075_delay0_08s_gif, BinaryData::frame_075_delay0_08s_gifSize);
    backgroundGifFrames[76] = juce::ImageFileFormat::loadFrom(BinaryData::frame_076_delay0_08s_gif, BinaryData::frame_076_delay0_08s_gifSize);
    backgroundGifFrames[77] = juce::ImageFileFormat::loadFrom(BinaryData::frame_077_delay0_08s_gif, BinaryData::frame_077_delay0_08s_gifSize);
    backgroundGifFrames[78] = juce::ImageFileFormat::loadFrom(BinaryData::frame_078_delay0_08s_gif, BinaryData::frame_078_delay0_08s_gifSize);
    backgroundGifFrames[79] = juce::ImageFileFormat::loadFrom(BinaryData::frame_079_delay0_08s_gif, BinaryData::frame_079_delay0_08s_gifSize);
    backgroundGifFrames[80] = juce::ImageFileFormat::loadFrom(BinaryData::frame_080_delay0_08s_gif, BinaryData::frame_080_delay0_08s_gifSize);
    backgroundGifFrames[81] = juce::ImageFileFormat::loadFrom(BinaryData::frame_081_delay0_08s_gif, BinaryData::frame_081_delay0_08s_gifSize);
    backgroundGifFrames[82] = juce::ImageFileFormat::loadFrom(BinaryData::frame_082_delay0_08s_gif, BinaryData::frame_082_delay0_08s_gifSize);
    backgroundGifFrames[83] = juce::ImageFileFormat::loadFrom(BinaryData::frame_083_delay0_08s_gif, BinaryData::frame_083_delay0_08s_gifSize);
    backgroundGifFrames[84] = juce::ImageFileFormat::loadFrom(BinaryData::frame_084_delay0_08s_gif, BinaryData::frame_084_delay0_08s_gifSize);
    backgroundGifFrames[85] = juce::ImageFileFormat::loadFrom(BinaryData::frame_085_delay0_08s_gif, BinaryData::frame_085_delay0_08s_gifSize);
    backgroundGifFrames[86] = juce::ImageFileFormat::loadFrom(BinaryData::frame_086_delay0_08s_gif, BinaryData::frame_086_delay0_08s_gifSize);
    backgroundGifFrames[87] = juce::ImageFileFormat::loadFrom(BinaryData::frame_087_delay0_08s_gif, BinaryData::frame_087_delay0_08s_gifSize);
    backgroundGifFrames[88] = juce::ImageFileFormat::loadFrom(BinaryData::frame_088_delay0_08s_gif, BinaryData::frame_088_delay0_08s_gifSize);
    backgroundGifFrames[89] = juce::ImageFileFormat::loadFrom(BinaryData::frame_089_delay0_08s_gif, BinaryData::frame_089_delay0_08s_gifSize);
    backgroundGifFrames[90] = juce::ImageFileFormat::loadFrom(BinaryData::frame_090_delay0_08s_gif, BinaryData::frame_090_delay0_08s_gifSize);
    backgroundGifFrames[91] = juce::ImageFileFormat::loadFrom(BinaryData::frame_091_delay0_08s_gif, BinaryData::frame_091_delay0_08s_gifSize);
    backgroundGifFrames[92] = juce::ImageFileFormat::loadFrom(BinaryData::frame_092_delay0_08s_gif, BinaryData::frame_092_delay0_08s_gifSize);
    backgroundGifFrames[93] = juce::ImageFileFormat::loadFrom(BinaryData::frame_093_delay0_08s_gif, BinaryData::frame_093_delay0_08s_gifSize);
    backgroundGifFrames[94] = juce::ImageFileFormat::loadFrom(BinaryData::frame_094_delay0_08s_gif, BinaryData::frame_094_delay0_08s_gifSize);
    backgroundGifFrames[95] = juce::ImageFileFormat::loadFrom(BinaryData::frame_095_delay0_08s_gif, BinaryData::frame_095_delay0_08s_gifSize);
    backgroundGifFrames[96] = juce::ImageFileFormat::loadFrom(BinaryData::frame_096_delay0_08s_gif, BinaryData::frame_096_delay0_08s_gifSize);
    backgroundGifFrames[97] = juce::ImageFileFormat::loadFrom(BinaryData::frame_097_delay0_08s_gif, BinaryData::frame_097_delay0_08s_gifSize);
    backgroundGifFrames[98] = juce::ImageFileFormat::loadFrom(BinaryData::frame_098_delay0_08s_gif, BinaryData::frame_098_delay0_08s_gifSize);
    backgroundGifFrames[99] = juce::ImageFileFormat::loadFrom(BinaryData::frame_099_delay0_08s_gif, BinaryData::frame_099_delay0_08s_gifSize);
    backgroundGifFrames[100] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0100_delay0_08s_gif, BinaryData::frame_0100_delay0_08s_gifSize);
    backgroundGifFrames[101] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0101_delay0_08s_gif, BinaryData::frame_0101_delay0_08s_gifSize);
    backgroundGifFrames[102] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0102_delay0_08s_gif, BinaryData::frame_0102_delay0_08s_gifSize);
    backgroundGifFrames[103] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0103_delay0_08s_gif, BinaryData::frame_0103_delay0_08s_gifSize);
    backgroundGifFrames[104] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0104_delay0_08s_gif, BinaryData::frame_0104_delay0_08s_gifSize);
    backgroundGifFrames[105] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0105_delay0_08s_gif, BinaryData::frame_0105_delay0_08s_gifSize);
    backgroundGifFrames[106] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0106_delay0_08s_gif, BinaryData::frame_0106_delay0_08s_gifSize);
    backgroundGifFrames[107] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0107_delay0_08s_gif, BinaryData::frame_0107_delay0_08s_gifSize);
    backgroundGifFrames[108] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0108_delay0_08s_gif, BinaryData::frame_0108_delay0_08s_gifSize);
    backgroundGifFrames[109] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0109_delay0_08s_gif, BinaryData::frame_0109_delay0_08s_gifSize);
    backgroundGifFrames[110] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0110_delay0_08s_gif, BinaryData::frame_0110_delay0_08s_gifSize);
    backgroundGifFrames[111] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0111_delay0_08s_gif, BinaryData::frame_0111_delay0_08s_gifSize);
    backgroundGifFrames[112] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0112_delay0_08s_gif, BinaryData::frame_0112_delay0_08s_gifSize);
    backgroundGifFrames[113] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0113_delay0_08s_gif, BinaryData::frame_0113_delay0_08s_gifSize);
    backgroundGifFrames[114] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0114_delay0_08s_gif, BinaryData::frame_0114_delay0_08s_gifSize);
    backgroundGifFrames[115] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0115_delay0_08s_gif, BinaryData::frame_0115_delay0_08s_gifSize);
    backgroundGifFrames[116] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0116_delay0_08s_gif, BinaryData::frame_0116_delay0_08s_gifSize);
    backgroundGifFrames[117] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0117_delay0_08s_gif, BinaryData::frame_0117_delay0_08s_gifSize);
    backgroundGifFrames[118] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0118_delay0_08s_gif, BinaryData::frame_0118_delay0_08s_gifSize);
    backgroundGifFrames[119] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0119_delay0_08s_gif, BinaryData::frame_0119_delay0_08s_gifSize);
    backgroundGifFrames[120] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0120_delay0_08s_gif, BinaryData::frame_0120_delay0_08s_gifSize);
    backgroundGifFrames[121] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0121_delay0_08s_gif, BinaryData::frame_0121_delay0_08s_gifSize);
    backgroundGifFrames[122] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0122_delay0_08s_gif, BinaryData::frame_0122_delay0_08s_gifSize);
    backgroundGifFrames[123] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0123_delay0_08s_gif, BinaryData::frame_0123_delay0_08s_gifSize);
    backgroundGifFrames[124] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0124_delay0_08s_gif, BinaryData::frame_0124_delay0_08s_gifSize);
    backgroundGifFrames[125] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0125_delay0_08s_gif, BinaryData::frame_0125_delay0_08s_gifSize);
    backgroundGifFrames[126] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0126_delay0_08s_gif, BinaryData::frame_0126_delay0_08s_gifSize);
    backgroundGifFrames[127] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0127_delay0_08s_gif, BinaryData::frame_0127_delay0_08s_gifSize);
    backgroundGifFrames[128] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0128_delay0_08s_gif, BinaryData::frame_0128_delay0_08s_gifSize);
    backgroundGifFrames[129] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0129_delay0_08s_gif, BinaryData::frame_0129_delay0_08s_gifSize);
    backgroundGifFrames[130] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0130_delay0_08s_gif, BinaryData::frame_0130_delay0_08s_gifSize);
    backgroundGifFrames[131] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0131_delay0_08s_gif, BinaryData::frame_0131_delay0_08s_gifSize);
    backgroundGifFrames[132] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0132_delay0_08s_gif, BinaryData::frame_0132_delay0_08s_gifSize);
    backgroundGifFrames[133] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0133_delay0_08s_gif, BinaryData::frame_0133_delay0_08s_gifSize);
    backgroundGifFrames[134] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0134_delay0_08s_gif, BinaryData::frame_0134_delay0_08s_gifSize);
    backgroundGifFrames[135] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0135_delay0_08s_gif, BinaryData::frame_0135_delay0_08s_gifSize);
    backgroundGifFrames[136] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0136_delay0_08s_gif, BinaryData::frame_0136_delay0_08s_gifSize);
    backgroundGifFrames[137] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0137_delay0_08s_gif, BinaryData::frame_0137_delay0_08s_gifSize);
    backgroundGifFrames[138] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0138_delay0_08s_gif, BinaryData::frame_0138_delay0_08s_gifSize);
    backgroundGifFrames[139] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0139_delay0_08s_gif, BinaryData::frame_0139_delay0_08s_gifSize);
    backgroundGifFrames[140] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0140_delay0_08s_gif, BinaryData::frame_0140_delay0_08s_gifSize);
    backgroundGifFrames[141] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0141_delay0_08s_gif, BinaryData::frame_0141_delay0_08s_gifSize);
    backgroundGifFrames[142] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0142_delay0_08s_gif, BinaryData::frame_0142_delay0_08s_gifSize);
    backgroundGifFrames[143] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0143_delay0_08s_gif, BinaryData::frame_0143_delay0_08s_gifSize);
    backgroundGifFrames[144] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0144_delay0_08s_gif, BinaryData::frame_0144_delay0_08s_gifSize);
    backgroundGifFrames[145] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0145_delay0_08s_gif, BinaryData::frame_0145_delay0_08s_gifSize);
    backgroundGifFrames[146] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0146_delay0_08s_gif, BinaryData::frame_0146_delay0_08s_gifSize);
    backgroundGifFrames[147] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0147_delay0_08s_gif, BinaryData::frame_0147_delay0_08s_gifSize);
    backgroundGifFrames[148] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0148_delay0_08s_gif, BinaryData::frame_0148_delay0_08s_gifSize);
    backgroundGifFrames[149] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0149_delay0_08s_gif, BinaryData::frame_0149_delay0_08s_gifSize);
    backgroundGifFrames[150] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0150_delay0_08s_gif, BinaryData::frame_0150_delay0_08s_gifSize);
    backgroundGifFrames[151] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0151_delay0_08s_gif, BinaryData::frame_0151_delay0_08s_gifSize);
    backgroundGifFrames[152] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0152_delay0_08s_gif, BinaryData::frame_0152_delay0_08s_gifSize);
    backgroundGifFrames[153] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0153_delay0_08s_gif, BinaryData::frame_0153_delay0_08s_gifSize);
    backgroundGifFrames[154] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0154_delay0_08s_gif, BinaryData::frame_0154_delay0_08s_gifSize);
    backgroundGifFrames[155] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0155_delay0_08s_gif, BinaryData::frame_0155_delay0_08s_gifSize);
    backgroundGifFrames[156] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0156_delay0_08s_gif, BinaryData::frame_0156_delay0_08s_gifSize);
    backgroundGifFrames[157] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0157_delay0_08s_gif, BinaryData::frame_0157_delay0_08s_gifSize);
    backgroundGifFrames[158] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0158_delay0_08s_gif, BinaryData::frame_0158_delay0_08s_gifSize);
    backgroundGifFrames[159] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0159_delay0_08s_gif, BinaryData::frame_0159_delay0_08s_gifSize);
    backgroundGifFrames[160] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0160_delay0_08s_gif, BinaryData::frame_0160_delay0_08s_gifSize);
    backgroundGifFrames[161] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0161_delay0_08s_gif, BinaryData::frame_0161_delay0_08s_gifSize);
    backgroundGifFrames[162] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0162_delay0_08s_gif, BinaryData::frame_0162_delay0_08s_gifSize);
    backgroundGifFrames[163] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0163_delay0_08s_gif, BinaryData::frame_0163_delay0_08s_gifSize);
    backgroundGifFrames[164] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0164_delay0_08s_gif, BinaryData::frame_0164_delay0_08s_gifSize);
    backgroundGifFrames[165] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0165_delay0_08s_gif, BinaryData::frame_0165_delay0_08s_gifSize);
    backgroundGifFrames[166] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0166_delay0_08s_gif, BinaryData::frame_0166_delay0_08s_gifSize);
    backgroundGifFrames[167] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0167_delay0_08s_gif, BinaryData::frame_0167_delay0_08s_gifSize);
    backgroundGifFrames[168] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0168_delay0_08s_gif, BinaryData::frame_0168_delay0_08s_gifSize);
    backgroundGifFrames[169] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0169_delay0_08s_gif, BinaryData::frame_0169_delay0_08s_gifSize);
    backgroundGifFrames[170] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0170_delay0_08s_gif, BinaryData::frame_0170_delay0_08s_gifSize);
    backgroundGifFrames[171] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0171_delay0_08s_gif, BinaryData::frame_0171_delay0_08s_gifSize);
    backgroundGifFrames[172] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0172_delay0_08s_gif, BinaryData::frame_0172_delay0_08s_gifSize);
    backgroundGifFrames[173] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0173_delay0_08s_gif, BinaryData::frame_0173_delay0_08s_gifSize);
    backgroundGifFrames[174] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0174_delay0_08s_gif, BinaryData::frame_0174_delay0_08s_gifSize);
    backgroundGifFrames[175] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0175_delay0_08s_gif, BinaryData::frame_0175_delay0_08s_gifSize);
    backgroundGifFrames[176] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0176_delay0_08s_gif, BinaryData::frame_0176_delay0_08s_gifSize);
    backgroundGifFrames[177] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0177_delay0_08s_gif, BinaryData::frame_0177_delay0_08s_gifSize);
    backgroundGifFrames[178] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0178_delay0_08s_gif, BinaryData::frame_0178_delay0_08s_gifSize);
    backgroundGifFrames[179] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0179_delay0_08s_gif, BinaryData::frame_0179_delay0_08s_gifSize);
    backgroundGifFrames[180] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0180_delay0_08s_gif, BinaryData::frame_0180_delay0_08s_gifSize);
    backgroundGifFrames[181] = juce::ImageFileFormat::loadFrom(BinaryData::frame_0181_delay0_08s_gif, BinaryData::frame_0181_delay0_08s_gifSize);
    
    startTimerHz(30);
    
    setAudioChannels (2, 2);
    
    openB.onClick = [this] {  openButtonClicked(); };
    addAndMakeVisible(&openB);
    
    playB.onClick = [this] { playButtonClicked(); };
    playB.setColour(TextButton::buttonColourId, Colours::red);
    playB.setEnabled(true);
    addAndMakeVisible(&playB);
    
    stopB.onClick = [this] { stopButtonClicked(); };
    stopB.setColour(TextButton::buttonColourId, Colours::red);
    stopB.setEnabled(false);
    addAndMakeVisible(&stopB);
    
    pauseB.onClick = [this] { pauseButtonClicked(); };
    pauseB.setColour(TextButton::buttonColourId, Colours::red);
    pauseB.setEnabled(false);
    addAndMakeVisible(&pauseB);

    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    transportStateChanged(Stopped);
    setSize(1500, 640);
}


MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    DBG("Samples Per Block Expected: " << samplesPerBlockExpected);
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    globalSampleRate = static_cast<int>(sampleRate);
    DBG("globalSampleRate set to: " << globalSampleRate);
    globalNumSamples = samplesPerBlockExpected;
    DBG("globalNumSamples set to: " << globalNumSamples);
}

void MainComponent::openButtonClicked()
{
    //Prompt user for audio file - default desktop directory
    FileChooser file ("Choose audio - wav or mp3 accepted", File::getSpecialLocation(File::userDesktopDirectory), "*.wav; *.mp3");
    
    //Load in selected audio file
    if (file.browseForFileToOpen())
    {
        File sourceAudio;
        sourceAudio = file.getResult();
        AudioFormatReader* formatReader = formatManager.createReaderFor(sourceAudio);
        if (formatReader != nullptr)
        {
            transportStateChanged(Stopped);
            //prep
            std::unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource (formatReader, true));
            transportSource.setSource(tempSource.get());
            transportStateChanged(Stopped);
            
            readerSource.reset(tempSource.release());
            auto sampleLength = static_cast<int>(formatReader->lengthInSamples);
            mWaveForm.setSize(1,sampleLength);
            shouldPaint = true;
            formatReader->read (&mWaveForm, 0, sampleLength ,0,true, false);
        }
    }
}

void MainComponent::playButtonClicked()
{
    if (state == Paused)
    {
        lastPlayPosition = transportSource.getCurrentPosition();
        transportSource.start();
    }
    if (state == Stopped){
        lastPlayPosition = 0.0;
        transportSource.start();
    }
    transportStateChanged(Playing);
}
void MainComponent::pauseButtonClicked()
{
    if (state == Playing)
    {
        transportStateChanged(Paused);
    }
}
void MainComponent::stopButtonClicked()
{
    if (state == Playing || state == Paused)
    {
        transportStateChanged(Stopped);
    }
}
void MainComponent::transportStateChanged(TransportState newState)
{
    if (newState != state)
    {
        state = newState;
        
        switch (state) {
            case Playing:
                playB.setEnabled(false);
                pauseB.setEnabled(true);
                stopB.setEnabled(true);
                break;
            case Paused:
                lastPlayPosition = transportSource.getCurrentPosition();
                transportSource.stop();
                playB.setEnabled(true);
                pauseB.setEnabled(false);
                stopB.setEnabled(true);
                break;
            case Stopped:
                lastPlayPosition = 0.0;
                transportSource.setPosition(lastPlayPosition);
                transportSource.stop();
                playB.setEnabled(true);
                pauseB.setEnabled(false);
                stopB.setEnabled(false);
                break;
        }
    }
}
void MainComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    
}
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    // Get the number of output channels
    int numChannels = bufferToFill.buffer->getNumChannels();
    //if -> grain finished - time to set a new grain
    bool isLastAudioBlockInGrain = (currentGrainCounter == 1);
    bool isFirstAudioBlockInGrain = false;
    if (currentGrainCounter == 0){
        int fluxVal;
        if (flux > 0){
            fluxVal = randomGenerator.nextInt(flux);
        }
        else{
            fluxVal = 0;
        }
        int newIndividualGrainSize = grainSize + fluxVal;
        currentGrainCounter = newIndividualGrainSize;
        //Weighted distribution (based on spread) outputChannel selection algorithm;
        // spread = 0: always chooses current channel
        // ||
        // spread dictates probability spread from current output channel;
        // the closer a channel is to the current channel, the more likely it will be selected
        //
        // ||
        // spread = 100: even distribution of probabilities for all channels
        
        // Create a vector to store the channel indices
            std::vector<int> usedChannels;
        // Iterate through the channels and check if they are used
        for (int channel = 0; channel < numChannels; ++channel)
        {
            if (bufferToFill.buffer->getWritePointer(channel) != nullptr)
            {
                // This channel is used, add its index to the vector
                usedChannels.push_back(channel);
            }
        }
        // Now, 'usedChannels' contains the indices of the channels that are used in the buffer
        /*for (int channelIndex : usedChannels)
        {
            DBG("Channel " << channelIndex + 1 << " is used.");
        }*/
        int currentChannel = outputChannel;
        // Calculate the probability distribution
        std::vector<float> probabilities;
        float spreadFactor = static_cast<float>(100 - spread) / usedChannels.size();

        for (int i = 0; i < usedChannels.size(); ++i)
        {
            float distance = std::abs(usedChannels[i] - currentChannel);
            float probability = 1.0f / (1.0f + spreadFactor * distance);
            probabilities.push_back(probability);
        }

        // Normalize probabilities to ensure they sum up to 1
        float sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0f);
        for (float& probability : probabilities)
        {
            probability /= sum;
        }

        // Select the next channel based on the probability distribution
        float randomValue = randomGenerator.nextFloat();
        float cumulativeProbability = 0.0f;
        int nextChannel = -1;

        for (int i = 0; i < probabilities.size(); ++i)
        {
            cumulativeProbability += probabilities[i];
            if (randomValue <= cumulativeProbability)
            {
                nextChannel = usedChannels[i];
                break;
            }
        }
        outputChannel = nextChannel;
        isFirstAudioBlockInGrain = true;
    }
    else{
        currentGrainCounter--;
    }
    // Initialize a buffer to hold the downmixed audio
    AudioSampleBuffer outputBuffer(bufferToFill.buffer->getArrayOfWritePointers() + outputChannel, 1, globalNumSamples);
    float* downmixChannel = outputBuffer.getWritePointer(0);

    // Sum the audio data from all channels into the downmix buffer
    for (int channel = 0; channel < numChannels; ++channel)
    {
        const float* sourceChannel = bufferToFill.buffer->getReadPointer(channel);

        for (int sample = 0; sample < globalNumSamples; ++sample)
        {
            downmixChannel[sample] += sourceChannel[sample];
        }
    }

    // Find the maximum absolute value in the downmix buffer
    float maxAbsValue = 0.0f;
    for (int sample = 0; sample < globalNumSamples; ++sample)
    {
        maxAbsValue = jmax(maxAbsValue, std::abs(downmixChannel[sample]));
    }
    // Scale the downmix buffer to prevent clipping
    if (maxAbsValue > 1.0f)
    {
        float scale = 1.0f / maxAbsValue;
        for (int sample = 0; sample < globalNumSamples; ++sample)
        {
            downmixChannel[sample] *= scale;
        }
    }
    // Fill the selected output channel with audio data
    transportSource.getNextAudioBlock(AudioSourceChannelInfo(outputBuffer));
    //built in release over 1 audio block to prevent clipping
    if (isLastAudioBlockInGrain){
        outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 1, 0);
    }
    //attack envelope based on conversion of input attack in seconds into blocks
    else if (isFirstAudioBlockInGrain){
        attackBlockCounter = 0;
        //outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 0, 1);
        int attackSamples = static_cast<int>(attack * globalSampleRate);

        // Calculate the number of blocks needed, rounding down
        attackBlocks = std::floor(static_cast<double>(attackSamples) / globalNumSamples);

        envelopeIncrement = (1/attackBlocks);
        outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 0, envelopeIncrement);
        attackRampGateOn = true;
    }
    else if (attackRampGateOn){
        if (attackBlockCounter < attackBlocks){
            outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), (double)((double)attackBlockCounter /(double)attackBlocks), (double)((double)attackBlockCounter+1.0) / (double)attackBlocks);
            attackBlockCounter ++;
        }
        else{
            attackRampGateOn = false;
        }
    }
    
     //mute the other output channels
     for (int i = 0; i < numChannels; ++i)
     {
         if (i != outputChannel)
             bufferToFill.buffer->clear(i, bufferToFill.startSample, bufferToFill.numSamples);
     }
}
void MainComponent::releaseResources()
{
}
//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.drawImage (backgroundGifFrames[currentAnimationFrame], getLocalBounds().toFloat());
    
    //handle draw waveform and playbackLine
    if (shouldPaint){
        //waveform
        g.setColour(Colours::white);
        Path p;
        mAudioPoints.clear();
        auto ratio = mWaveForm.getNumSamples() / (getWidth()/2.25);
        auto buffer = mWaveForm.getReadPointer(0);
        // x axis scaling
        for (int sample = 0 ; sample < mWaveForm.getNumSamples(); sample+= ratio){
            mAudioPoints.push_back (buffer[sample]);
        }
        p.startNewSubPath(getWidth()/2,getHeight()/4);
        //y axis scaling
        for (int sample = 0; sample < mAudioPoints.size(); ++sample){
            
            auto point = jmap <float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight()/5,0);
            p.lineTo(sample + getWidth()/2, (point+getHeight()/4) - getHeight()/10);
        }
        g.strokePath(p, PathStrokeType(2));
        //playback line
        g.setColour(Colours::red);
        Path playbackLine;
        double currentPosition = transportSource.getCurrentPosition();
        double lengthInSeconds = transportSource.getLengthInSeconds();
        // Calculate the playback percentage
        double playbackPercentage = (currentPosition / lengthInSeconds);
        double playbackLineX = getWidth()/2 + (playbackPercentage * getWidth()/2.25);
        playbackLine.startNewSubPath(playbackLineX,getHeight()/4+getHeight()/5);
        playbackLine.lineTo(playbackLineX,getHeight()/4-getHeight()/5);
        g.strokePath(playbackLine, PathStrokeType(2));
    }
    
}
void MainComponent::sliderValueChanged(Slider* slider){
    if (slider == &mAttackSlider){
        attack = (double) mAttackSlider.getValue();
    }
    else if (slider == &mGrainSizeSlider){
        grainSize = mGrainSizeSlider.getValue();
    }
    else if (slider == &mFluxSlider){
        flux = mFluxSlider.getValue();
    }
    else if (slider == &mSpreadSlider){
        spread = mSpreadSlider.getValue();
    }
    else{
        DBG("Invalid slider");
    }
}

void MainComponent::timerCallback()
{
    // Update the frame index for the next paint
    if (currentAnimationFrame == 181){
        currentAnimationFrame = 0;
    }
    else{
        currentAnimationFrame = (currentAnimationFrame + 1);
    }
    repaint();
}

void MainComponent::resized()
{
    openB.setBounds(20, 20, getWidth()/3, 40);
    playB.setBounds(20, 70, getWidth()/3, 40);
    stopB.setBounds(20, 120, getWidth()/3, 40);
    pauseB.setBounds(20, 170, getWidth()/3, 40);
    audioSettings->setBounds(20, 220, getWidth()/3, 200);
    mAttackSlider.setBounds(getWidth()/2, getHeight()/2 + getHeight()/10 + 10, getWidth()/10, getWidth()/10);
    mGrainSizeSlider.setBounds(getWidth()/2 + getWidth()/10 + 20, getHeight()/2 + getHeight()/10 + 10, getWidth()/10, getWidth()/10);
    mFluxSlider.setBounds(getWidth()/2 + (getWidth()/10+20) * 2, getHeight()/2 + getHeight()/10 + 10, getWidth()/10, getWidth()/10);
    mSpreadSlider.setBounds(getWidth()/2  + (getWidth()/10+20) * 3 , getHeight()/2 + getHeight()/10 + 10, getWidth()/10, getWidth()/10);
    noticeAboutOutputs.setBounds(20, getHeight()-120, getWidth()/3, 100);
}
