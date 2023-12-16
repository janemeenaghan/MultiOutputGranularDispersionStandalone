/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Slider::Listener,
                        public ChangeListener,
                        public juce::Timer

{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    void timerCallback() override;
private:
    AudioDeviceManager otherDeviceManager;
    std::unique_ptr <AudioDeviceSelectorComponent> audioSettings;
    int64 lastPlayPosition = 0;
    juce::Image gifImage;
    int grainSize,flux;
    
    //I'm so serious I tried EVERYTHING and this was the only way
    juce::Image backgroundGifFrames[181];
    juce::Image backgroundGifFrame0;
    juce::Image backgroundGifFrame1;
    juce::Image backgroundGifFrame2;
    juce::Image backgroundGifFrame3;
    juce::Image backgroundGifFrame4;
    juce::Image backgroundGifFrame5;
    juce::Image backgroundGifFrame6;
    juce::Image backgroundGifFrame7;
    juce::Image backgroundGifFrame8;
    juce::Image backgroundGifFrame9;
    juce::Image backgroundGifFrame10;
    juce::Image backgroundGifFrame11;
    juce::Image backgroundGifFrame12;
    juce::Image backgroundGifFrame13;
    juce::Image backgroundGifFrame14;
    juce::Image backgroundGifFrame15;
    juce::Image backgroundGifFrame16;
    juce::Image backgroundGifFrame17;
    juce::Image backgroundGifFrame18;
    juce::Image backgroundGifFrame19;
    juce::Image backgroundGifFrame20;
    juce::Image backgroundGifFrame21;
    juce::Image backgroundGifFrame22;
    juce::Image backgroundGifFrame23;
    juce::Image backgroundGifFrame24;
    juce::Image backgroundGifFrame25;
    juce::Image backgroundGifFrame26;
    juce::Image backgroundGifFrame27;
    juce::Image backgroundGifFrame28;
    juce::Image backgroundGifFrame29;
    juce::Image backgroundGifFrame30;
    juce::Image backgroundGifFrame31;
    juce::Image backgroundGifFrame32;
    juce::Image backgroundGifFrame33;
    juce::Image backgroundGifFrame34;
    juce::Image backgroundGifFrame35;
    juce::Image backgroundGifFrame36;
    juce::Image backgroundGifFrame37;
    juce::Image backgroundGifFrame38;
    juce::Image backgroundGifFrame39;
    juce::Image backgroundGifFrame40;
    juce::Image backgroundGifFrame41;
    juce::Image backgroundGifFrame42;
    juce::Image backgroundGifFrame43;
    juce::Image backgroundGifFrame44;
    juce::Image backgroundGifFrame45;
    juce::Image backgroundGifFrame46;
    juce::Image backgroundGifFrame47;
    juce::Image backgroundGifFrame48;
    juce::Image backgroundGifFrame49;
    juce::Image backgroundGifFrame50;
    juce::Image backgroundGifFrame51;
    juce::Image backgroundGifFrame52;
    juce::Image backgroundGifFrame53;
    juce::Image backgroundGifFrame54;
    juce::Image backgroundGifFrame55;
    juce::Image backgroundGifFrame56;
    juce::Image backgroundGifFrame57;
    juce::Image backgroundGifFrame58;
    juce::Image backgroundGifFrame59;
    juce::Image backgroundGifFrame60;
    juce::Image backgroundGifFrame61;
    juce::Image backgroundGifFrame62;
    juce::Image backgroundGifFrame63;
    juce::Image backgroundGifFrame64;
    juce::Image backgroundGifFrame65;
    juce::Image backgroundGifFrame66;
    juce::Image backgroundGifFrame67;
    juce::Image backgroundGifFrame68;
    juce::Image backgroundGifFrame69;
    juce::Image backgroundGifFrame70;
    juce::Image backgroundGifFrame71;
    juce::Image backgroundGifFrame72;
    juce::Image backgroundGifFrame73;
    juce::Image backgroundGifFrame74;
    juce::Image backgroundGifFrame75;
    juce::Image backgroundGifFrame76;
    juce::Image backgroundGifFrame77;
    juce::Image backgroundGifFrame78;
    juce::Image backgroundGifFrame79;
    juce::Image backgroundGifFrame80;
    juce::Image backgroundGifFrame81;
    juce::Image backgroundGifFrame82;
    juce::Image backgroundGifFrame83;
    juce::Image backgroundGifFrame84;
    juce::Image backgroundGifFrame85;
    juce::Image backgroundGifFrame86;
    juce::Image backgroundGifFrame87;
    juce::Image backgroundGifFrame88;
    juce::Image backgroundGifFrame89;
    juce::Image backgroundGifFrame90;
    juce::Image backgroundGifFrame91;
    juce::Image backgroundGifFrame92;
    juce::Image backgroundGifFrame93;
    juce::Image backgroundGifFrame94;
    juce::Image backgroundGifFrame95;
    juce::Image backgroundGifFrame96;
    juce::Image backgroundGifFrame97;
    juce::Image backgroundGifFrame98;
    juce::Image backgroundGifFrame99;
    juce::Image backgroundGifFrame100;
    juce::Image backgroundGifFrame101;
    juce::Image backgroundGifFrame102;
    juce::Image backgroundGifFrame103;
    juce::Image backgroundGifFrame104;
    juce::Image backgroundGifFrame105;
    juce::Image backgroundGifFrame106;
    juce::Image backgroundGifFrame107;
    juce::Image backgroundGifFrame108;
    juce::Image backgroundGifFrame109;
    juce::Image backgroundGifFrame110;
    juce::Image backgroundGifFrame111;
    juce::Image backgroundGifFrame112;
    juce::Image backgroundGifFrame113;
    juce::Image backgroundGifFrame114;
    juce::Image backgroundGifFrame115;
    juce::Image backgroundGifFrame116;
    juce::Image backgroundGifFrame117;
    juce::Image backgroundGifFrame118;
    juce::Image backgroundGifFrame119;
    juce::Image backgroundGifFrame120;
    juce::Image backgroundGifFrame121;
    juce::Image backgroundGifFrame122;
    juce::Image backgroundGifFrame123;
    juce::Image backgroundGifFrame124;
    juce::Image backgroundGifFrame125;
    juce::Image backgroundGifFrame126;
    juce::Image backgroundGifFrame127;
    juce::Image backgroundGifFrame128;
    juce::Image backgroundGifFrame129;
    juce::Image backgroundGifFrame130;
    juce::Image backgroundGifFrame131;
    juce::Image backgroundGifFrame132;
    juce::Image backgroundGifFrame133;
    juce::Image backgroundGifFrame134;
    juce::Image backgroundGifFrame135;
    juce::Image backgroundGifFrame136;
    juce::Image backgroundGifFrame137;
    juce::Image backgroundGifFrame138;
    juce::Image backgroundGifFrame139;
    juce::Image backgroundGifFrame140;
    juce::Image backgroundGifFrame141;
    juce::Image backgroundGifFrame142;
    juce::Image backgroundGifFrame143;
    juce::Image backgroundGifFrame144;
    juce::Image backgroundGifFrame145;
    juce::Image backgroundGifFrame146;
    juce::Image backgroundGifFrame147;
    juce::Image backgroundGifFrame148;
    juce::Image backgroundGifFrame149;
    juce::Image backgroundGifFrame150;
    juce::Image backgroundGifFrame151;
    juce::Image backgroundGifFrame152;
    juce::Image backgroundGifFrame153;
    juce::Image backgroundGifFrame154;
    juce::Image backgroundGifFrame155;
    juce::Image backgroundGifFrame156;
    juce::Image backgroundGifFrame157;
    juce::Image backgroundGifFrame158;
    juce::Image backgroundGifFrame159;
    juce::Image backgroundGifFrame160;
    juce::Image backgroundGifFrame161;
    juce::Image backgroundGifFrame162;
    juce::Image backgroundGifFrame163;
    juce::Image backgroundGifFrame164;
    juce::Image backgroundGifFrame165;
    juce::Image backgroundGifFrame166;
    juce::Image backgroundGifFrame167;
    juce::Image backgroundGifFrame168;
    juce::Image backgroundGifFrame169;
    juce::Image backgroundGifFrame170;
    juce::Image backgroundGifFrame171;
    juce::Image backgroundGifFrame172;
    juce::Image backgroundGifFrame173;
    juce::Image backgroundGifFrame174;
    juce::Image backgroundGifFrame175;
    juce::Image backgroundGifFrame176;
    juce::Image backgroundGifFrame177;
    juce::Image backgroundGifFrame178;
    juce::Image backgroundGifFrame179;
    juce::Image backgroundGifFrame180;
    juce::Image backgroundGifFrame181;
    
    int currentAnimationFrame = 0;
    enum TransportState
    {
        Stopped,
        Starting,
        Stopping,
        Playing,
        Paused
    };
    
    TransportState state;
    Slider grainSizeSlider;
    Slider fluxSlider;
    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void pauseButtonClicked();
    void grainSizeSliderValueChanged(Slider* slider) override;
    void fluxSliderValueChanged(Slider* slider) override;
    void transportStateChanged(TransportState newState);
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    int currentOutputIndex;
    int nextOutputIndex;
    float envelope;
    // Function to update envelope during transitions
    void updateEnvelope(int numSamples);
    
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    TextButton openB;
    TextButton playB;
    TextButton stopB;
    TextButton pauseB;
    //==============================================================================
    // Your private member variables go here...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
