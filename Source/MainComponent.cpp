/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 150);

    addAndMakeVisible (fileButton = new TextButton ("new button"));
    fileButton->setButtonText (TRANS("file"));
    fileButton->addListener (this);
    fileButton->setColour (TextButton::buttonColourId, Colour (0xfffdfdfd));
    
    addAndMakeVisible (azimuthSlider = new Slider ("new slider"));
    azimuthSlider->setRange (-180.0, 180.0, 5);
    azimuthSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    azimuthSlider->addListener (this);
    
    addAndMakeVisible (elevationSlider = new Slider ("new slider"));
    elevationSlider->setRange (-40.0, 90.0, 10);
    elevationSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    elevationSlider->addListener (this);
    
    fileButton->setBounds (10, 20, 56, 24);
    azimuthSlider->setBounds (10,50 ,getWidth() - 70, 20);
    elevationSlider->setBounds (10, 80, getWidth() - 70, 20);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

}

void MainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == fileButton)
    {
        //[UserButtonCode_fileButton] -- add your button handler code here..
        File audioFile;
        FileChooser chooser ("Choose file to open",File::nonexistent,"*",true);
        chooser.browseForFileToOpen();
        audioFile = chooser.getResult();
        
        // only start playing if audio file exists, otherwise it will crash
        if (audioFile.exists()) {
            audioPlayer.setFile(audioFile);
            audioPlayer.play();
        }
        
    }
    
}

void MainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == azimuthSlider)
        audioPlayer.setAzimuth(azimuthSlider->getValue());
    else if (sliderThatWasMoved == elevationSlider)
        audioPlayer.setElevation(elevationSlider->getValue());
    
    audioPlayer.updateHRIR();

    
}
