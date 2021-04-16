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
    
    setSize (700, 350);
    
    // Label classes
    gainSliderLabel.setText("Make-up", dontSendNotification);
    gainSliderLabel.attachToComponent(&gainSlider,false);
    gainSliderLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(gainSliderLabel);
    
    algorithmSelectorLabel.setText("Select Algorithm", dontSendNotification);
    algorithmSelectorLabel.attachToComponent(&algSelector,false);
    algorithmSelectorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(algorithmSelectorLabel);
    
    
    grainSizeSelectorLabel.setText("Select Grain Size", dontSendNotification);
    grainSizeSelectorLabel.attachToComponent(&grainSizeSelector,false);
    grainSizeSelectorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(grainSizeSelectorLabel);
    
    inputMeterLabel.setText("In", dontSendNotification);
    inputMeterLabel.attachToComponent(&inputMeter,false);
    inputMeterLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(inputMeterLabel);
    
    outputMeterLabel.setText("Out", dontSendNotification);
    outputMeterLabel.attachToComponent(&outputMeter,false);
    outputMeterLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(outputMeterLabel);
    
    smoothingFilterLabel.setText("Smoothing filter envelope?",dontSendNotification);
    smoothingFilterLabel.setBounds(520,35,150,25);
    addAndMakeVisible(smoothingFilterLabel);
    
    varianceSliderLabel.setText("Variation Seed", dontSendNotification);
    varianceSliderLabel.attachToComponent(&varianceSlider,false);
    varianceSliderLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(varianceSliderLabel);
    
    overlapSelectorLabel.setText("Select Overlap Percent", dontSendNotification);
    overlapSelectorLabel.attachToComponent(&overlapSelector, false);
    overlapSelectorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(overlapSelectorLabel);
    
    wetDrySliderLabel.setText("Dry/Wet", dontSendNotification);
    wetDrySliderLabel.attachToComponent(&wetDrySlider, false);
    wetDrySliderLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(wetDrySliderLabel);
    

    //ComboBoxes
    algSelector.addItem("Asynchronous",1);
    algSelector.addItem("Synchronous",2);
    algSelector.addItem("sMaRt",3);
    algSelector.setBounds(350,60,120,40);
    addAndMakeVisible(algSelector);
    comboBoxAttachments.emplace_back(new AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state, "algSelectionValue", algSelector));
    
    grainSizeSelector.addItem("64",1);
    grainSizeSelector.addItem("128",2);
    grainSizeSelector.addItem("256",3);
    grainSizeSelector.addItem("512",4);
    grainSizeSelector.addItem("1024",5);
    grainSizeSelector.addItem("2048",6);
    grainSizeSelector.addItem("4096",7);
    grainSizeSelector.addItem("8192",8);
    grainSizeSelector.setBounds(350,160,120,40);
    addAndMakeVisible(grainSizeSelector);
    comboBoxAttachments.emplace_back(new AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state,"grainSizeSelectionValue", grainSizeSelector));
    
    overlapSelector.addItem("0%", 1);
    overlapSelector.addItem("25%",2);
    overlapSelector.addItem("50%",3);
    overlapSelector.addItem("75%",4);
    overlapSelector.setBounds(350,260,120,40);
    addAndMakeVisible(overlapSelector);
    comboBoxAttachments.emplace_back(new AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state, "overlapSelectionValue", overlapSelector));
    
    
    //Meters
    inputMeter.setBounds(545,185,10,100);
    inputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(inputMeter);
    
    outputMeter.setBounds(590,185,10,100);
    outputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(outputMeter);
    
    
    //Buttons
    smoothButton.setBounds(540,75,50,50);
    smoothButton.setButtonText("Yes");
    smoothButton.setToggleState(audioProcessor.smoothState, dontSendNotification);
    smoothButton.setRadioGroupId(1);
    addAndMakeVisible(smoothButton);
    buttonAttachments.emplace_back(new AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.state, "smoothState", smoothButton));
    
    notSmoothButton.setBounds(620,75,50,50);
    notSmoothButton.setButtonText("No");
    notSmoothButton.setToggleState(audioProcessor.notSmoothState, dontSendNotification);
    notSmoothButton.setRadioGroupId(1);
    addAndMakeVisible(notSmoothButton);
    buttonAttachments.emplace_back(new AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.state, "notSmoothState", notSmoothButton));
    

    // Sliders
    varianceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    varianceSlider.setBounds(195,180,100,100);
    varianceSlider.setRange(1, 8, 4);
    varianceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 75,25);
    addAndMakeVisible(varianceSlider);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "varianceValue", varianceSlider));
    
    wetDrySlider.setRange(0, 1, 0.01);
    wetDrySlider.setBounds(65,180,100,100);
    wetDrySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetDrySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(wetDrySlider);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"wetDryValue",wetDrySlider));
    
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(0.01f, 1.5f, 0.01f);
    gainSlider.setBounds(615,185,50,135);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 45,45);
    addAndMakeVisible(gainSlider);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "makeupGainValue", gainSlider));
    
    //Timer
    startTimerHz(30);
    

    
    //Font code from Erin!
//    void RandomPannerAudioProcessorEditor::setFontParameters(Font* font) {
//        font->setTypefaceName("Avenir Next");
//        font->setTypefaceStyle("Demi Bold");
//        font->setHeight(20);
//    }
    
//    setFontParameters(&font);
    
//    saturationLabel.setFont(font);
}

GranularTextureSynthesisAudioProcessorEditor::~GranularTextureSynthesisAudioProcessorEditor()
{
}

//==============================================================================
void GranularTextureSynthesisAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void GranularTextureSynthesisAudioProcessorEditor::resized()
{
    backgroundImageComponent.setBounds(1, 1, 700, 350);
}

void GranularTextureSynthesisAudioProcessorEditor::sliderValueChanged(Slider * slider){
}

void GranularTextureSynthesisAudioProcessorEditor::comboBoxChanged(ComboBox * comboBox){
    if(comboBox == &algSelector){
        if(algSelector.getSelectedId() == 1){
            // Asynchronous
            audioProcessor.algorithm = 1;
        }
        if(algSelector.getSelectedId() == 2){
            // Asynchronous
            audioProcessor.algorithm = 2;
        }
        if(algSelector.getSelectedId() == 3){
            // Asynchronous
            audioProcessor.algorithm =3;
        }
    if(comboBox == &grainSizeSelector)
        if(grainSizeSelector.getSelectedId() == 1){
            //64
            audioProcessor.grainSize = 64;
        }
        if(grainSizeSelector.getSelectedId() == 2){
            //128
            audioProcessor.grainSize = 128;
        }
        if(grainSizeSelector.getSelectedId() == 3){
            //256
            audioProcessor.grainSize = 256;
        }
        if(grainSizeSelector.getSelectedId() == 4){
            //512
            audioProcessor.grainSize = 512;
        }
        if(grainSizeSelector.getSelectedId() == 5){
            //1024
            audioProcessor.grainSize = 1024;
        }
        if(grainSizeSelector.getSelectedId() == 6){
            //2048
            audioProcessor.grainSize = 2048;
        }
        if(grainSizeSelector.getSelectedId() == 7){
            //4096
            audioProcessor.grainSize = 4096;
        }
        if(grainSizeSelector.getSelectedId() == 8){
            //8192
            audioProcessor.grainSize = 8192;
        }
    }
    if(comboBox == &overlapSelector){
        if(grainSizeSelector.getSelectedId() == 1){
            // no overlap at all
            audioProcessor.overlapPercent = 0.f;
        }
        if(grainSizeSelector.getSelectedId() == 2){
            //25% overlap
            audioProcessor.overlapPercent = 0.25f;
        }
        if(grainSizeSelector.getSelectedId() == 3){
            //50% overlap (default)
            audioProcessor.overlapPercent = 0.50f;
        }
        if(grainSizeSelector.getSelectedId() == 4){
            //75% overlap
            audioProcessor.overlapPercent = 0.75f;
        }
    }
}

void GranularTextureSynthesisAudioProcessorEditor::timerCallback(){
    inputMeter.update(audioProcessor.meterValueInput);
    outputMeter.update(audioProcessor.meterValueOutput);
}


void GranularTextureSynthesisAudioProcessorEditor::buttonClicked(Button * button){
    // if clicked, do something
    if (button == &smoothButton){
        audioProcessor.smoothState = true;
    }
    if (button == &notSmoothButton){
        audioProcessor.smoothState = false;
    }
}
