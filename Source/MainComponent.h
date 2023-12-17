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
                       // public Slider::Listener,
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
    //void sliderValueChanged(Slider* slider) override;
    int currentOutputIndex;
    int nextOutputIndex;
    int globalGrainSize;
    int globalFlux;
    int globalCurrentGrainCounter;
    int globalOutputChannel;
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
