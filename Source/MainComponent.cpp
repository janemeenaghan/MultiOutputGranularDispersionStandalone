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
}

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
   // DBG("attack: " << attack);
   // DBG("grainSize: " << grainSize);
   // DBG("flux: " << flux);
   // DBG("spread: " << spread);
   // DBG("currentGrainCounter: " << currentGrainCounter);
    //what about cases where you have >2 outs but they're all above output 1 & 2 and you want to skip those?
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
        for (int channelIndex : usedChannels)
        {
            DBG("Channel " << channelIndex + 1 << " is used.");
        }
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
        
        DBG("new outputChannel: " << outputChannel);
        //apply envelope to new grain
        isFirstAudioBlockInGrain = true;
        //updateEnvelope();
    }
    else{
        currentGrainCounter--;
    }
    
   // DBG("bufferToFill.numSamples: " << bufferToFill.numSamples);
   // DBG("vs globalNumSamples: " << globalNumSamples);
    
    
    AudioSampleBuffer outputBuffer(bufferToFill.buffer->getArrayOfWritePointers() + outputChannel, 1, globalNumSamples);
    // Fill the selected output channel with audio data
    transportSource.getNextAudioBlock(AudioSourceChannelInfo(outputBuffer));
    
    //apply release envelope if end
    
    //built in attack and release over 1 audio block to prevent clipping
    if (isLastAudioBlockInGrain){
        outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), 1, 0);
    }
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
            outputBuffer.applyGainRamp(0, outputBuffer.getNumSamples(), (double)(attackBlockCounter /attackBlocks), (double)(attackBlockCounter+1) / attackBlocks);
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
/*
  
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
    openB.setBounds(20, 20, getWidth()/3, 40);
    playB.setBounds(20, 70, getWidth()/3, 40);
    stopB.setBounds(20, 120, getWidth()/3, 40);
    pauseB.setBounds(20, 170, getWidth()/3, 40);
    audioSettings->setBounds(20, 220, getWidth()/3, 200);
    mAttackSlider.setBounds(getWidth()/2, 220, getWidth()/10, getWidth()/10);
    mGrainSizeSlider.setBounds(getWidth()/2 + getWidth()/10 + 20, 220, getWidth()/10, getWidth()/10);
    mFluxSlider.setBounds(getWidth()/2 + (getWidth()/10+20) * 2, 220, getWidth()/10, getWidth()/10);
    mSpreadSlider.setBounds(getWidth()/2  + (getWidth()/10+20) * 3 , 220, getWidth()/10, getWidth()/10);
    
    noticeAboutOutputs.setBounds(20, getHeight()-120, getWidth()/3, 100);
    /*
    mAttackLabel.setBounds(getWidth()/2 + getWidth()/20, 180, getWidth()/10, getWidth()/10);
    mGrainSizeLabel.setBounds(getWidth()/2 + getWidth()/10 + 20 + getWidth()/20, 180, getWidth()/10, getWidth()/10);
    mFluxLabel.setBounds(getWidth()/2 + (getWidth()/10+20) * 2 + getWidth()/20, 180, getWidth()/10, getWidth()/10);
    mSpreadLabel.setBounds(getWidth()/2  + (getWidth()/10+20) * 3 + getWidth()/20 , 180, getWidth()/10, getWidth()/10);*/
    
  //  grainSizeSlider.setBounds(20, 280, getWidth() - 80, 60);
   // fluxSlider.setBounds(40+(getWidth() - 80), 280, getWidth() - 80, 60);
}
