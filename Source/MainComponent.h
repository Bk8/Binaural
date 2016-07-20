/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BinauralAudioPlayer.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public ButtonListener,
                               public SliderListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;


private:
    ScopedPointer<TextButton> fileButton;
    ScopedPointer<Label> chooseLabel;
    ScopedPointer<Slider> azimuthSlider;
    ScopedPointer<Slider> elevationSlider;
    
    
    BinauralAudioPlayer audioPlayer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
