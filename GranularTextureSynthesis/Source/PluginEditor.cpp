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
    auto backgroundImage = ImageCache::getFromMemory(BinaryData::bg_1_png, BinaryData::bg_1_pngSize);
    
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
    
    // Label classes
    grainSizeLabel.setText("Grain Size", dontSendNotification);
    grainSizeLabel.attachToComponent(&grainSizeSlider,false);
    grainSizeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(grainSizeLabel);
    
//    smoothingFilterLabel.setText("Smoothing Filter?", dontSendNotification);
//    smoothingFilterLabel.attachToComponent(&algSelector,false);
//    smoothingFilterLabel.setJustificationType(Justification::centred);
//    addAndMakeVisible(smoothingFilterLabel);

    gainSliderLabel.setText("Make-up", dontSendNotification);
    gainSliderLabel.attachToComponent(&gainSlider,false);
    gainSliderLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(gainSliderLabel);

    
    algorithmSelectorLabel.setText("Select Algorithm", dontSendNotification);
    algorithmSelectorLabel.attachToComponent(&algSelector,false);
    algorithmSelectorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(algorithmSelectorLabel);
    
    //inputMeterLabel.setFont(6.f);
    inputMeterLabel.setText("In", dontSendNotification);
    inputMeterLabel.attachToComponent(&inputMeter,false);
    inputMeterLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(inputMeterLabel);
    
    //outputMeterLabel.setFont(6.f);
    outputMeterLabel.setText("Out", dontSendNotification);
    outputMeterLabel.attachToComponent(&outputMeter,false);
    outputMeterLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(outputMeterLabel);
    
    smoothingFilterLabel.setText("Smoothing filter envelope?",dontSendNotification);
    smoothingFilterLabel.setBounds(520,35,150,25);
    addAndMakeVisible(smoothingFilterLabel);
    
    varianceSliderLabel.setText("Variance", dontSendNotification);
    varianceSliderLabel.attachToComponent(&varianceSlider,false);
    varianceSliderLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(varianceSliderLabel);
    
    
    grainSizeSlider.addListener(this);
    grainSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainSizeSlider.setBounds(80,175,100,100);
//    juce::Range<double> grainRange(800,48000,800);
    grainSizeSlider.setRange(1024, 49152, 1024);
    //grainSizeSlider.setMinAndMaxValues(0,1);
//    grainSizeSlider.setMinValue(0);
//    grainSizeSlider.setMaxValue(1);
    //grainSizeSlider.setRange(128.f,1024.f,0.1f);
    grainSizeSlider.setValue(audioProcessor.grainSize);
    grainSizeSlider.setNumDecimalPlacesToDisplay(0);
    grainSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 75,25);
    addAndMakeVisible(grainSizeSlider);
    
    gainSlider.addListener(this);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setValue(audioProcessor.gain);
    gainSlider.setRange(0.01f, 1.5f, 0.01f);
    gainSlider.setBounds(625,185,50,150);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 45,45);
    addAndMakeVisible(gainSlider);
    
    algSelector.addListener(this);
    algSelector.addItem("Asynchronous",1);
    algSelector.addItem("Synchronous",2);
    algSelector.addItem("sMaRt",3);
    algSelector.setSelectedId(1);
    algSelector.setBounds(340,60,120,40);
    addAndMakeVisible(algSelector);
    
    inputMeter.setBounds(545,185,10,100);
    inputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(inputMeter);
    
    outputMeter.setBounds(590,185,10,100);
    outputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(outputMeter);
    
    smoothButton.addListener(this);
    smoothButton.setBounds(565,75,50,50);
    smoothButton.setButtonText("Yes");
    smoothButton.setToggleState(audioProcessor.smoothState, dontSendNotification);
    smoothButton.setRadioGroupId(1);
    //smoothButton.setEnabled(audioProcessor.smoothState);
    addAndMakeVisible(smoothButton);
    
    
    notSmoothButton.addListener(this);
    notSmoothButton.setBounds(625,75,50,50);
    notSmoothButton.setButtonText("No");
    notSmoothButton.setToggleState(shouldBeOn, dontSendNotification);
    // notSmoothButton.setState(juce::Button::buttonOver);
    notSmoothButton.setToggleState(audioProcessor.notSmoothState, dontSendNotification);
    notSmoothButton.setRadioGroupId(1);
    //notSmoothButton.setEnabled(!audioProcessor.smoothState);
    addAndMakeVisible(notSmoothButton);
    

    startTimerHz(30);
    
    
    
//    mutateButton.addListener(this);
//    mutateButton.setBounds(460,125,100,40);
//    mutateButton.setButtonText("Mutate");
//    mutateButton.setToggleState(audioProcessor.mutateState, dontSendNotification);
//    mutateButton.setRadioGroupId(1);
//    addAndMakeVisible(mutateButton);
    
//    notMutateButton.addListener(this);
//    notMutateButton.setBounds(460,125,100,40);
//    notMutateButton.setButtonText("Mutate off");
//    notMutateButton.setToggleState(audioProcessor.mutateState, dontSendNotification);
//    notMutateButton.setRadioGroupId(1);
//    addAndMakeVisible(notMutateButton);
    
//    mutateButton.setEnabled(audioProcessor.mutateState);
//    notMutateButton.setEnabled(!audioProcessor.mutateState);
    
    varianceSlider.addListener(this);
    varianceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    varianceSlider.setBounds(180,175,100,100);
    varianceSlider.setRange(0, 100, 1);
    varianceSlider.setValue(audioProcessor.grainSize);
    varianceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 75,25);
    addAndMakeVisible(varianceSlider);
    

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
    
    
//    juce::Rectangle<int> areaRight(350,75,350,275);
//    g.setColour(juce::Colours::darkblue);
//    g.fillRect(areaRight);
//
//    juce::Rectangle<int> areaLeft(1,75,350,275);
//    g.setColour(juce::Colours::darkorchid);
//    g.fillRect(areaLeft);

//    g.setColour(juce::Colours::cornflowerblue);
//    g.setFont (18.0f);
    //g.drawFittedText ("| Granular |", getLocalBounds(), juce::Justification::centredLeft, 1);
//    g.drawText("| Granular |", 100, 75, 125, 25,Justification::centred, 1);
    
//    g.setColour(juce::Colours::darkorchid);
    //g.drawFittedText ("| Texturize |", getLocalBounds(), juce::Justification::centredRight, 1);
//    g.drawText("| Texturize |", 460, 75, 125, 25,Justification::centred, 1);
    
//    g.setColour(juce::Colours::cornflowerblue);
//    g.setFont(64.f);
//    g.drawFittedText("Texture Synthesizer", getLocalBounds(), juce::Justification::centredTop, 1);
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
    
    backgroundImageComponent.setBounds(1, 1, 700, 350);
    
        //juce::Rectangle<int> areaHeader(1,1,700,75);
    //const juce::Rectangle<float> area (5.f,80.f,90.f,20.f);
    
    
}

void GranularTextureSynthesisAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if (slider == &grainSizeSlider){
        audioProcessor.grainSize = grainSizeSlider.getValue();
    }
    if (slider == &gainSlider){
        audioProcessor.gain = gainSlider.getValue();
    }
    if (slider == &varianceSlider){
        audioProcessor.variance = varianceSlider.getValue();
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
    inputMeter.update(audioProcessor.meterValueInput);
    outputMeter.update(audioProcessor.meterValueInput);
    
}


void GranularTextureSynthesisAudioProcessorEditor::buttonClicked(Button * button){
    // if clicked, do something
    if (button == &mutateButton){
        audioProcessor.mutateState = false;
    }
    if (button == &notMutateButton){
        audioProcessor.mutateState = true;
    }
    if (button == &smoothButton){
        audioProcessor.smoothState = true;
        //smoothButton.setEnabled(true);
        //notSmoothButton.setEnabled(false);
    }
    if (button == &notSmoothButton){
        audioProcessor.smoothState = false;
        //smoothButton.setEnabled(false);
        //notSmoothButton.setEnabled(true);
    }
}
