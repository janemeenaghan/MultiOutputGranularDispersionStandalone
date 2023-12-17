#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


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
    void sliderValueChanged (Slider* slider) override;
    
private:
    AudioDeviceManager otherDeviceManager;
    std::unique_ptr <AudioDeviceSelectorComponent> audioSettings;
    int64 lastPlayPosition = 0;
    juce::Image gifImage;
    int grainSize,flux,spread;
    double attack;
    
    //I'm so serious I tried EVERYTHING and this was the only way
    juce::Image backgroundGifFrames[16];
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
    
    Slider mAttackSlider, mGrainSizeSlider, mFluxSlider, mSpreadSlider;
    Label mAttackLabel, mGrainSizeLabel, mFluxLabel, mSpreadLabel;
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
   // Slider grainSizeSlider;
   // Slider fluxSlider;
    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void pauseButtonClicked();
    void transportStateChanged(TransportState newState);
    void changeListenerCallback (ChangeBroadcaster *source) override;
    // Function to update envelope during transitions
    void updateEnvelope();
    int currentOutputIndex, nextOutputIndex, globalGrainSize, globalFlux, globalCurrentGrainCounter, globalOutputChannel, globalSampleRate, globalNumSamples, globalReleaseTime;
    float envelope;
    Random randomGenerator;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TextButton openB,playB,stopB,pauseB;
    //==============================================================================
    // Your private member variables go here...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
