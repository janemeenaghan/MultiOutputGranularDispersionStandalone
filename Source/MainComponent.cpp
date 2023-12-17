#include "MainComponent.h"
MainComponent::MainComponent() : juce::AudioAppComponent(otherDeviceManager), state(Stopped), openB("Open"), playB("Play"), stopB("Stop"), pauseB("Pause")/*, grainSizeSlider("Grain Size"), fluxSlider("Flux")*/
{
    
    otherDeviceManager.initialise(2, 2, nullptr, true);
        audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 0, 2, 0, 2, true, true, true, true));
        addAndMakeVisible(audioSettings.get());
     globalGrainSize = 2;
     globalFlux = 100;
     globalCurrentGrainCounter = 30;
     globalOutputChannel = 0;
    //I'm so serious I tried EVERYTHING and this was the only way
    backgroundGifFrames[16];
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
    
    //juce::MemoryInputStream gifStream(BinaryData::backgroundGif_gif, BinaryData::backgroundGif_gifSize, false);
    //gifImage = juce::ImageFileFormat::loadFrom(gifStream);
    // Start the timer to update the animation
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
    pauseB.setEnabled(false); // Initially disabled
    addAndMakeVisible(&pauseB);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    
    // Initialize the grain size slider
 /*   grainSizeSlider.setSliderStyle(Slider::LinearHorizontal);
    grainSizeSlider.setRange(1, 500, 1);  // Adjust the range as needed
    grainSizeSlider.setValue(256);  // Set an initial value
    grainSizeSlider.addListener(this);
    addAndMakeVisible(&grainSizeSlider);
    */
    
    // Initialize the flux slider
  /*  fluxSlider.setSliderStyle(Slider::LinearHorizontal);
    fluxSlider.setRange(1, 500, 1);  // Adjust the range as needed
    fluxSlider.setValue(0);  // Set an initial value
    fluxSlider.addListener(this);
    addAndMakeVisible(&fluxSlider);
    
    flux = 500;
    grainSize = 500;*/


    setSize(1200, 512);
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
            //prep
            std::unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource (formatReader, true));
            transportSource.setSource(tempSource.get());
            transportStateChanged(Stopped);
        
            readerSource.reset(tempSource.release());
        }
    }
}

void MainComponent::playButtonClicked()
{
    if (state == Paused)
       {
           // Set the position to resume playback from the same location
           transportSource.setPosition(lastPlayPosition);
       }
    transportStateChanged(Starting);
}

void MainComponent::stopButtonClicked()
{
    transportStateChanged(Stopping);
}

void MainComponent::pauseButtonClicked()
{
    if (state == Playing)
        {
            //lastPlayPosition = playSource->getNextReadPosition();
            lastPlayPosition = transportSource.getCurrentPosition();
            transportStateChanged(Paused);
        }
}

void MainComponent::transportStateChanged(TransportState newState)
{
    if (newState != state)
    {
        state = newState;
        
        switch (state) {
            case Stopped:
                playB.setEnabled(true);
                pauseB.setEnabled(false);
                transportSource.setPosition(0.0);
                break;
                
            case Playing:
                playB.setEnabled(true);
                pauseB.setEnabled(true);
                stopB.setEnabled(true);
                break;
                
            case Starting:
                stopB.setEnabled(true);
                pauseB.setEnabled(true);
                playB.setEnabled(false);
                transportSource.start();
                break;
                
            case Stopping:
                playB.setEnabled(true);
                pauseB.setEnabled(false);
                stopB.setEnabled(false);
                transportSource.stop();
                break;
            case Paused:
                playB.setEnabled(true);
                pauseB.setEnabled(false);
                stopB.setEnabled(true);
                transportSource.stop();
                break;
        }
    }
}/*
void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &grainSizeSlider)
    {
        grainSize = static_cast<int>(grainSizeSlider.getValue());
    }
    if (slider == &fluxSlider)
    {
        flux = Random().nextInt(static_cast<int>(fluxSlider.getValue()));
    }
}*/

void MainComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            transportStateChanged(Playing);
        }
        else
        {
            transportStateChanged(Stopped);
        }
    }
}
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    ;
    //what about cases where you have >2 outs but they're all above output 1 & 2 and you want to skip those?
    bufferToFill.clearActiveBufferRegion();
    // Get the number of output channels
    int numChannels = bufferToFill.buffer->getNumChannels();
    // Choose a random output channel index
    //randomOutputIndex = 1;
    
    //if -> grain finished - time to set a new grain
    
    bool lastAudioBlockInGrain = (globalCurrentGrainCounter == 1);
    bool firstAudioBlockInGrain = false;
    if (globalCurrentGrainCounter == 0){
        int fluxVal;
        if (globalFlux > 0){
            fluxVal = randomGenerator.nextInt(globalFlux);
        }
        else{
            fluxVal = 0;
        }
        int newIndividualGrainSize = globalGrainSize + fluxVal;
        globalCurrentGrainCounter = newIndividualGrainSize;
        globalOutputChannel = randomGenerator.nextInt(numChannels);
        //apply envelope to new grain
        firstAudioBlockInGrain = true;
        //updateEnvelope();
    }
    else{
        globalCurrentGrainCounter--;
    }
    
    DBG("bufferToFill.numSamples: " << bufferToFill.numSamples);
    DBG("vs globalNumSamples: " << globalNumSamples);
    
    
    AudioSampleBuffer outputBuffer(bufferToFill.buffer->getArrayOfWritePointers() + globalOutputChannel, 1, globalNumSamples);
    // Fill the selected output channel with audio data
    transportSource.getNextAudioBlock(AudioSourceChannelInfo(outputBuffer));
    
    //apply release envelope if end
    
    //built in attack and release over 1 audio block to prevent clipping
    if (lastAudioBlockInGrain){
        outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 1, 0);
    }
    if (firstAudioBlockInGrain){
        outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 0, 1);
    }
    
     //mute the other output channels
     for (int i = 0; i < numChannels; ++i)
     {
         if (i != globalOutputChannel)
             bufferToFill.buffer->clear(i, bufferToFill.startSample, bufferToFill.numSamples);
     }
}/*
void MainComponent::applyAttackEnvelope()
{
    float attackTime = 0.1f;  // Adjust this as needed
    int attackSamples = static_cast<int>(attackTime * globalSampleRate);
    DBG("attackSamples set to: " << attackSamples);
    
}
    
    
}
void MainComponent::updateEnvelope()
{
    // Simple linear envelope
    float attackTime = 0.1f;  // Adjust this as needed
    float releaseTime = 0.1f; // Adjust this as needed
    int attackSamples = static_cast<int>(attackTime * globalSampleRate);
    int releaseSamples = static_cast<int>(releaseTime * globalSampleRate);
    DBG("attackSamples set to: " << attackSamples);
    DBG("releaseSamples set to: " << releaseSamples);
    for (int i = 0; i < globalNumSamples; ++i)
    {
        if (i < attackSamples)
        {
            envelope = static_cast<float>(i) / static_cast<float>(attackSamples);
        }
        else if (i >= globalNumSamples - releaseSamples)
        {
            envelope = static_cast<float>(globalNumSamples - i) / static_cast<float>(releaseSamples);
        }
        else
        {
            envelope = 1.0f;
        }
    }
}*/

void MainComponent::releaseResources()
{
}
//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll (Colours::black);
   // Image background = ImageCache::getFromMemory (BinaryData::backgroundGif_gif, BinaryData::backgroundGif_gifSize);
        g.drawImage (backgroundGifFrames[currentAnimationFrame], getLocalBounds().toFloat());
   // g.drawImage(gifImage, getLocalBounds().toFloat(), currentAnimationFrame * gifImage.getWidth(), 0, gifImage.getWidth(), gifImage.getHeight());


}
void MainComponent::timerCallback()
{
    // Update the frame index for the next paint
    if (currentAnimationFrame == 15){
        currentAnimationFrame = 0;
    }
    else{
        currentAnimationFrame = (currentAnimationFrame + 1);
    }
    repaint();
}

void MainComponent::resized()
{
    openB.setBounds(20, 20, getWidth()/4, 40);
    playB.setBounds(20, 70, getWidth()/4, 40);
    stopB.setBounds(20, 120, getWidth()/4, 40);
    pauseB.setBounds(20, 170, getWidth()/4, 40);
    audioSettings->setBounds(20, 220, getWidth()/4, 200);
  //  grainSizeSlider.setBounds(20, 280, getWidth() - 80, 60);
   // fluxSlider.setBounds(40+(getWidth() - 80), 280, getWidth() - 80, 60);
}
