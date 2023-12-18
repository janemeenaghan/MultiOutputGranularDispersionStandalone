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
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void paint (Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (Slider* slider) override;
    
private:
    enum TransportState
    {
        Stopped,
        Playing,
        Paused
    };
    AudioDeviceManager otherDeviceManager;
    std::unique_ptr <AudioDeviceSelectorComponent> audioSettings;
    AudioFormatManager formatManager;
    AudioTransportSource transportSource;
    TransportState state;
    AudioBuffer <float> mWaveForm;
    std::vector<float> mAudioPoints;
    int64 lastPlayPosition = 0;
    juce::Image gifImage;
    juce::Image backgroundGifFrames[182];
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    int currentOutputIndex, nextOutputIndex, grainSize, flux, spread, currentGrainCounter, outputChannel, globalSampleRate, globalNumSamples, globalReleaseTime,attackBlocks,attackBlockCounter;
    int currentAnimationFrame = 0;
    float envelope,envelopeVal,envelopeIncrement;
    bool attackRampGateOn, shouldPaint;
    double attack;
    Random randomGenerator;
    TextButton openB,playB,stopB,pauseB;
    Slider mAttackSlider, mGrainSizeSlider, mFluxSlider, mSpreadSlider;
    Label mAttackLabel, mGrainSizeLabel, mFluxLabel, mSpreadLabel, noticeAboutOutputs;

    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void pauseButtonClicked();
    void transportStateChanged(TransportState newState);
    void changeListenerCallback (ChangeBroadcaster *source) override;
    void updateEnvelope();
    int convertSecondsToBlocks();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
