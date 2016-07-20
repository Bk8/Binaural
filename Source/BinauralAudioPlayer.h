//
//  BinauralAudioPlayer.hpp
//  Binaural
//
//  Created by Alex on 19/7/16.
//
//

#ifndef BinauralAudioPlayer_h
#define BinauralAudioPlayer_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFTConvolver/FFTConvolver.h"
#include "HRIR.h"
#include <atomic>

class BinauralAudioPlayer  : public AudioIODeviceCallback
{
public:
    BinauralAudioPlayer();
    ~BinauralAudioPlayer();
    
    void audioDeviceIOCallback(const float** inputChannelData,
                               int totalNumInputChannels,
                               float** outputChannelData,
                               int totalNumOutputChannels,
                               int numSamples);
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    
    void setFile(File audioFile);
    void play();
    void setAzimuth(int azimuth);
    void setElevation(int elevation);
    void updateHRIR();

private:
    
    AudioDeviceManager audioDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    AudioTransportSource transportSource;
    
    AudioFormatReaderSource* currentAudioFileSource;
    File currentFile;
    
    int azimuth;
    int elevation;
    
    //------------KlangFalter------------
    fftconvolver::FFTConvolver convolverLeft;
    fftconvolver::FFTConvolver convolverRight;
    //-----------------------------------
    HRIR hrir;
    float *convolutionResult;

    
};

#endif /* BinauralAudioPlayer_hpp */
