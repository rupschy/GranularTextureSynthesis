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
    
    
    
}

GranularTextureSynthesisAudioProcessorEditor::~GranularTextureSynthesisAudioProcessorEditor()
{
}

//==============================================================================
void GranularTextureSynthesisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colours::transparentBlack);
//    g.drawImageWithin(const juce::Image("test_bg.jpg"), 0, 0, 700, 350, 0);
    g.setColour (juce::Colours::cornflowerblue);
    g.setFont (30.0f);
//    g.setFont(const Font) LEARN HOW TO SET FONT
    g.drawFittedText ("Sound Texture Synthesizer", getLocalBounds(), juce::Justification::centredTop , 3);
    
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
