/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularTextureSynthesisAudioProcessorEditor::GranularTextureSynthesisAudioProcessorEditor (GranularTextureSynthesisAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 350);

    auto bgImage = ImageCache::getFromMemory(BinaryData::bg_jpg, BinaryData::bg_jpgSize);
    
    if (! bgImage.isNull())
        mImageComponent.setImage(bgImage,RectanglePlacement::stretchToFit);
    else
        jassert (! bgImage.isNull());
    
    addAndMakeVisible(mImageComponent);
    
    
    
    grainSizeSlider.addListener(this);
    grainSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainSizeSlider.setBounds(350,125,100,100);
    grainSizeSlider.setRange(128.f,1024.f,0.1f);
    grainSizeSlider.setValue(audioProcessor.grainSize);
    grainSizeSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 75,25);
    addAndMakeVisible(grainSizeSlider);
    
    algSelector.addListener(this);
    algSelector.addItem("Asynchronous",1);
    algSelector.addItem("Synchronous",2);
    algSelector.addItem("sMaRt",3);
    algSelector.setSelectedId(1);
    algSelector.setBounds(75,125,120,40);
    addAndMakeVisible(algSelector);
    
    meter.setBounds(625,250,100,10);
    meter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(meter);
    
    startTimerHz(30);
    
//    continuousButton.addListener(this);
//    continuousButton.setBounds(25,25,100,40);
//    continuousButton.setButtonText("Continuous Variation");
//    continuousButton.setToggleState(audioProcessor.continuousProc, dontSendNotification);
//    continuousButton.setRadioGroupId(1); // links with notContinuous
//    addAndMakeVisible(continuousButton);
}

GranularTextureSynthesisAudioProcessorEditor::~GranularTextureSynthesisAudioProcessorEditor()
{
}

//==============================================================================
void GranularTextureSynthesisAudioProcessorEditor::paint (juce::Graphics& g)
{

    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//    g.fillAll (juce::Colours::transparentBlack);
//    g.drawImageWithin(const juce::Image("test_bg.jpg"), 0, 0, 700, 350, 0);
//    g.setColour (juce::Colours::cornflowerblue);
//    g.setFont (30.0f);
//    g.setFont(const Font) LEARN HOW TO SET FONT
//    g.drawFittedText ("Sound Texture Synthesizer", getLocalBounds(), juce::Justification::centredTop , 3);
    
    // g.drawFittedText
}

void GranularTextureSynthesisAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    mImageComponent.setBounds(1, 1, 700, 350);
}

void GranularTextureSynthesisAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if (slider == &grainSizeSlider){
        audioProcessor.grainSize = grainSizeSlider.getValue();
    }
}

void GranularTextureSynthesisAudioProcessorEditor::comboBoxChanged(ComboBox * comboBox){
    if(comboBox == &algSelector){
        if(algSelector.getSelectedId() == 1){
            // Asynchronous
            audioProcessor.algorithm = 1.f;
        }
        if(algSelector.getSelectedId() == 2){
            // Asynchronous
            audioProcessor.algorithm = 2.f;
        }
        if(algSelector.getSelectedId() == 3){
            // Asynchronous
            audioProcessor.algorithm =3.f;
        }
    }
    
}

void GranularTextureSynthesisAudioProcessorEditor::timerCallBack(){
    meter.update(audioProcessor.meterValue);
}
