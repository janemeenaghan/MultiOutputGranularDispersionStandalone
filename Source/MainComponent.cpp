/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent() : juce::AudioAppComponent(otherDeviceManager), state(Stopped), openB("Open"), playB("Play"), stopB("Stop"), pauseB("Pause"), audioBlockLengthSlider("Audio Block Length")
{
    otherDeviceManager.initialise(2, 2, nullptr, true);
    audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 0, 2, 0, 2, true, true, true, true));
    addAndMakeVisible(audioSettings.get());
    
    setAudioChannels (2, 2);
    
    openB.onClick = [this] {  openButtonClicked(); };
    addAndMakeVisible(&openB);
    
    playB.onClick = [this] { playButtonClicked(); };
    playB.setColour(TextButton::buttonColourId, Colours::green);
    playB.setEnabled(true);
    addAndMakeVisible(&playB);
    
    stopB.onClick = [this] { stopButtonClicked(); };
    stopB.setColour(TextButton::buttonColourId, Colours::red);
    stopB.setEnabled(false);
    addAndMakeVisible(&stopB);
    
    pauseB.onClick = [this] { pauseButtonClicked(); };
    pauseB.setColour(TextButton::buttonColourId, Colours::yellow);
    pauseB.setEnabled(false); // Initially disabled
    addAndMakeVisible(&pauseB);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    
    // Initialize the audio block length slider
    audioBlockLengthSlider.setSliderStyle(Slider::LinearHorizontal);
    audioBlockLengthSlider.setRange(32, 1024, 1);  // Adjust the range as needed
    audioBlockLengthSlider.setValue(256);  // Set an initial value
    audioBlockLengthSlider.addListener(this);
    addAndMakeVisible(&audioBlockLengthSlider);

    setSize (400, 700);
}


MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
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
        AudioFormatReader* reader = formatManager.createReaderFor(sourceAudio);
        
        if (reader != nullptr)
        {
            //prep
            std::unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource (reader, true));
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

void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &audioBlockLengthSlider)
    {
        // Handle slider value change
        int newAudioBlockLength = static_cast<int>(audioBlockLengthSlider.getValue());
        // You can use newAudioBlockLength as needed
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
    bufferToFill.clearActiveBufferRegion();
    
    // Get the number of output channels
    int numChannels = bufferToFill.buffer->getNumChannels();

    // Choose a random output channel index
    int randomOutputIndex = Random().nextInt(numChannels);

    // Get the audio block for the selected output channel
    int audioBlockLength = static_cast<int>(audioBlockLengthSlider.getValue());
    AudioSampleBuffer outputBuffer(bufferToFill.buffer->getArrayOfWritePointers() + randomOutputIndex, 1, audioBlockLength);

    // Fill the selected output channel with audio data
    transportSource.getNextAudioBlock(AudioSourceChannelInfo(outputBuffer));

     //mute the other output channels
     for (int i = 0; i < numChannels; ++i)
     {
         if (i != randomOutputIndex)
             bufferToFill.buffer->clear(i, bufferToFill.startSample, bufferToFill.numSamples);
     }
    
    //transport.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    openB.setBounds(10, 10, getWidth() - 20, 30);
    playB.setBounds(10, 50, getWidth() - 20, 30);
    stopB.setBounds(10, 90, getWidth() - 20, 30);
    pauseB.setBounds(10, 130, getWidth() - 20, 30);
    audioSettings->setBounds(10, 400, getWidth() - 20, 100);
    audioBlockLengthSlider.setBounds(10, 280, getWidth() - 20, 30);
}
