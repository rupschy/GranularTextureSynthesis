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
    
    
    
    
    auto bgImage = ImageCache::getFromMemory(BinaryData::test_bg_jpg, BinaryData::test_bg_jpgSize);
    
    if (! bgImage.isNull())
        mImageComponent.setImage(bgImage,RectanglePlacement::stretchToFit);
    else
        jassert (! bgImage.isNull());
    
    
    
    addAndMakeVisible(mImageComponent);
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
    
    mImageComponent.setBoundsRelative(0.f, 0.f, 0.25f, 0.25f);
}
