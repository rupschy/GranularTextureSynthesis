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
    auto backgroundImage = ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize);
    
    if (! backgroundImage.isNull()){
        backgroundImageComponent.setImage(backgroundImage,RectanglePlacement::centred);
    }
    else {
        jassert (!backgroundImage.isNull());
    }
    addAndMakeVisible(backgroundImageComponent);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 350);

    
    
    
    
    grainSizeSlider.addListener(this);
    grainSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainSizeSlider.setBounds(100,125,125,125);
    grainSizeSlider.setRange(128.f,1024.f,0.1f);
    grainSizeSlider.setValue(audioProcessor.grainSize);
    grainSizeSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 75,25);
    addAndMakeVisible(grainSizeSlider);
    
    algSelector.addListener(this);
    algSelector.addItem("Asynchronous",1);
    algSelector.addItem("Synchronous",2);
    algSelector.addItem("sMaRt",3);
    algSelector.setSelectedId(1);
    algSelector.setBounds(460,200,120,40);
    addAndMakeVisible(algSelector);
    
    meter1.setBounds(325,150,10,100);
    meter1.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meter1);
    
    meter2.setBounds(375,150,10,100);
    meter2.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meter2);
    
    startTimerHz(30);
    
    mutateButton.addListener(this);
    mutateButton.setBounds(460,125,100,40);
    mutateButton.setButtonText("Mutate");
    mutateButton.setToggleState(audioProcessor.mutateState, dontSendNotification);
    mutateButton.setRadioGroupId(1);
    addAndMakeVisible(mutateButton);
    
    notMutateButton.addListener(this);
    notMutateButton.setBounds(460,125,100,40);
    notMutateButton.setButtonText("Mutate off");
    notMutateButton.setToggleState(audioProcessor.mutateState, dontSendNotification);
    notMutateButton.setRadioGroupId(1);
    addAndMakeVisible(notMutateButton);
    
    mutateButton.setEnabled(audioProcessor.mutateState);
    notMutateButton.setEnabled(!audioProcessor.mutateState);
}

GranularTextureSynthesisAudioProcessorEditor::~GranularTextureSynthesisAudioProcessorEditor()
{
}

//==============================================================================
void GranularTextureSynthesisAudioProcessorEditor::paint (juce::Graphics& g)
{

    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll (juce::Colours::black);
    //addAndMakeVisible(mImageComponent);
//    g.setColour(juce::Colours::royalblue);
//    juce::Rectangle<int> areaHeader(1,1,700,75);
//    g.fillRect(areaHeader);
//
//    juce::Rectangle<int> areaRight(350,75,350,275);
//    g.setColour(juce::Colours::darkblue);
//    g.fillRect(areaRight);
//
//    juce::Rectangle<int> areaLeft(1,75,350,275);
//    g.setColour(juce::Colours::darkorchid);
//    g.fillRect(areaLeft);

    g.setColour(juce::Colours::cornflowerblue);
    g.setFont (18.0f);
    //g.drawFittedText ("| Granular |", getLocalBounds(), juce::Justification::centredLeft, 1);
    g.drawText("| Granular |", 100, 75, 125, 25,Justification::centred, 1);
    
    g.setColour(juce::Colours::darkorchid);
    //g.drawFittedText ("| Texturize |", getLocalBounds(), juce::Justification::centredRight, 1);
    g.drawText("| Texturize |", 460, 75, 125, 25,Justification::centred, 1);
    
    g.setColour(juce::Colours::cornflowerblue);
    g.setFont(64.f);
    g.drawFittedText("Texture Synthesizer", getLocalBounds(), juce::Justification::centredTop, 1);
//    const juce::Rectangle<float> area (5.f,80.f,90.f,20.f);
    
    // 3 Using Point and Path classes
//    juce::Path path;
//    path.startNewSubPath(juce::Point<float> (10,10));
//    path.lineTo(juce::Point<float> (50,10));
//    path.lineTo(juce::Point<float> (50,50));
//    path.lineTo(juce::Point<float> (10,50));
//    g.fillPath(path);
}

void GranularTextureSynthesisAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //mBgImage.setBounds(1, 1, 700, 350);
    //const juce::Rectangle<float> area (5.f,80.f,90.f,20.f);
    
    
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

void GranularTextureSynthesisAudioProcessorEditor::timerCallback(){
    meter1.update(audioProcessor.meterValue);
    meter2.update(audioProcessor.meterValue);
    
}


void GranularTextureSynthesisAudioProcessorEditor::buttonClicked(Button * button){
    // if clicked, do something
    if (button == &mutateButton){
        audioProcessor.mutateState = false;
    }
    if (button == &notMutateButton){
        audioProcessor.mutateState = true;
    }
}
