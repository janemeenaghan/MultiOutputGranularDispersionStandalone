/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent() : juce::AudioAppComponent(otherDeviceManager), state(Stopped), openButton("Open"), playButton("Play"), stopButton("Stop"), pauseButton("Pause"), audioBlockLengthSlider("Audio Block Length")
{
    otherDeviceManager.initialise(2, 2, nullptr, true);
    audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 0, 2, 0, 2, true, true, true, true));
    addAndMakeVisible(audioSettings.get());
    
    setAudioChannels (2, 2);
    
    openButton.onClick = [this] {  openButtonClicked(); };
    addAndMakeVisible(&openButton);
    
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour(TextButton::buttonColourId, Colours::green);
    playButton.setEnabled(true);
    addAndMakeVisible(&playButton);
    
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    stopButton.setEnabled(false);
    addAndMakeVisible(&stopButton);
    
    pauseButton.onClick = [this] { pauseButtonClicked(); };
    pauseButton.setColour(TextButton::buttonColourId, Colours::yellow);
    pauseButton.setEnabled(false); // Initially disabled
    addAndMakeVisible(&pauseButton);
    
    formatManager.registerBasicFormats();
    transport.addChangeListener(this);
    
    
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
    transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::openButtonClicked()
{
    //choose a file
    FileChooser chooser ("Choose a Wav or AIFF File", File::getSpecialLocation(File::userDesktopDirectory), "*.wav; *.mp3");
    
    //if the user chooses a file
    if (chooser.browseForFileToOpen())
    {
        File myFile;
        
        //what did the user choose?
        myFile = chooser.getResult();
        
        //read the file
        AudioFormatReader* reader = formatManager.createReaderFor(myFile);
        
        if (reader != nullptr)
        {
            //get the file ready to play
            std::unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource (reader, true));
        
            transport.setSource(tempSource.get());
            transportStateChanged(Stopped);
        
            playSource.reset(tempSource.release());
        }
    }
}

void MainComponent::playButtonClicked()
{
    if (state == Paused)
       {
           // Set the position to resume playback from the same location
           transport.setPosition(lastPlayPosition);
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
            lastPlayPosition = transport.getCurrentPosition();
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
                playButton.setEnabled(true);
                pauseButton.setEnabled(false);
                transport.setPosition(0.0);
                break;
                
            case Playing:
                playButton.setEnabled(true);
                pauseButton.setEnabled(true);
                stopButton.setEnabled(true);
                break;
                
            case Starting:
                stopButton.setEnabled(true);
                pauseButton.setEnabled(true);
                playButton.setEnabled(false);
                transport.start();
                break;
                
            case Stopping:
                playButton.setEnabled(true);
                pauseButton.setEnabled(false);
                stopButton.setEnabled(false);
                transport.stop();
                break;
            case Paused:
                playButton.setEnabled(true);
                pauseButton.setEnabled(false);
                stopButton.setEnabled(true);
                transport.stop();
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
    if (source == &transport)
    {
        if (transport.isPlaying())
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
    transport.getNextAudioBlock(AudioSourceChannelInfo(outputBuffer));

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
    openButton.setBounds(10, 10, getWidth() - 20, 30);
    playButton.setBounds(10, 50, getWidth() - 20, 30);
    stopButton.setBounds(10, 90, getWidth() - 20, 30);
    pauseButton.setBounds(10, 130, getWidth() - 20, 30);
    audioSettings->setBounds(10, 400, getWidth() - 20, 100);
    audioBlockLengthSlider.setBounds(10, 280, getWidth() - 20, 30);
}
