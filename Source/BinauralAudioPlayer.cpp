//
//  BinauralAudioPlayer.cpp
//  Binaural
//
//  Created by Alex on 19/7/16.
//
//

#include "BinauralAudioPlayer.h"

BinauralAudioPlayer::BinauralAudioPlayer()
{
    int numOutputChannels = 2, numInputChannels = 0;
    azimuth=0;
    elevation=0;
    
    
    
    
    //initialize to default audio device
    audioDeviceManager.initialise (numInputChannels, /* number of input channels */
                                   numOutputChannels, /* number of output channels */
                                   0, /* no XML settings.. */
                                   true  /* select default device on failure */);
    currentAudioFileSource = NULL;
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    audioDeviceManager.addAudioCallback (this);
    
    

    

}

BinauralAudioPlayer::~BinauralAudioPlayer()
{
    audioDeviceManager.removeAudioCallback (this);
    
    if (transportSource.isPlaying())
        transportSource.stop();
    transportSource.setSource (NULL);
    
    if (currentAudioFileSource)
        deleteAndZero (currentAudioFileSource);
    
    audioSourcePlayer.setSource (NULL);
}

void BinauralAudioPlayer::audioDeviceIOCallback(const float** inputChannelData,
                                                int totalNumInputChannels,
                                                float** outputChannelData,
                                                int totalNumOutputChannels,
                                                int numSamples)
{
    // Create a buffer that points to outputChannelData
    AudioSampleBuffer outputBuffer (outputChannelData, totalNumOutputChannels, numSamples);
    
    AudioSourceChannelInfo info;
    info.buffer = &outputBuffer;
    info.startSample = 0;
    info.numSamples = numSamples;
    
    
    
    
    
    // Gets the audio buffer from AudioSource and stores it to outputBuffer
    // So, outputChannelData now stores the audio from the file transport stream
    transportSource.getNextAudioBlock (info);
    
    // do audio processing here, for example gain is applied to audio samples
    
    if (transportSource.isPlaying())
    {
        hrir.update(azimuth, elevation);
        convolverLeft.setIR(hrir.leftEar.getWritePointer(0));
        convolverRight.setIR(hrir.rightEar.getWritePointer(0));
        
        convolverLeft.process(outputChannelData[0], convolutionResult, numSamples);
        
        for (int i = 0; i < numSamples; i++)
            outputChannelData[0][i] = convolutionResult[i];
        
        convolverRight.process(outputChannelData[1], convolutionResult, numSamples);
        
        for (int i = 0; i < numSamples; i++) {
            outputChannelData[1][i] = convolutionResult[i];
            
            
        }
        

    }
}


void BinauralAudioPlayer::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
    int bufferSize=device->getCurrentBufferSizeSamples();
    
    hrir.update(azimuth, elevation);
    
    convolverLeft.init(bufferSize,hrir.leftEar.getWritePointer(0), 128);
    convolverRight.init(bufferSize,hrir.rightEar.getWritePointer(0), 128);
    convolutionResult= new float[bufferSize];
}

void BinauralAudioPlayer::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}


void BinauralAudioPlayer::setFile(File audioFile)
{
    if (transportSource.isPlaying()) {
        transportSource.stop();
        transportSource.setSource (NULL);
    }
    
    if (currentAudioFileSource)
        deleteAndZero (currentAudioFileSource);
    
    // get a format manager and set it up with the basic types (wav and aiff).
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
    
    if (reader != NULL) {
        currentFile = audioFile;
        
        currentAudioFileSource = new AudioFormatReaderSource (reader, true);
        
        // ..and plug it into our transport source
        transportSource.setSource(currentAudioFileSource);
        
        
    }
}

void BinauralAudioPlayer::play()
{
    transportSource.setPosition (0.0);
    transportSource.start();
    
    // check if audio file is set, or else it will crash
    if (currentAudioFileSource)
        currentAudioFileSource->setLooping(true);
}

void BinauralAudioPlayer::setAzimuth(int azimuth)
{
    this->azimuth=azimuth;
}

void BinauralAudioPlayer::setElevation(int elevation)
{
    this->elevation=elevation;
}

void BinauralAudioPlayer::updateHRIR()
{
    
}



