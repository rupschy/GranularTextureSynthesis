/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "SimpleMeter.h"

//==============================================================================
/**
*/
class GranularTextureSynthesisAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                      public juce::Slider::Listener,
                                                      public juce::ComboBox::Listener,
                                                      public juce::Button::Listener,
                                                      public Timer

//                                                      public juce::ToggleButton::Listener
{
public:
    GranularTextureSynthesisAudioProcessorEditor (GranularTextureSynthesisAudioProcessor&);
    ~GranularTextureSynthesisAudioProcessorEditor() override;

    //==============================================================================


    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Slider for grain size
    void sliderValueChanged(Slider * slider) override;
    
    // Drop-down for algorithm typing
    void comboBoxChanged(juce::ComboBox * comboBox) override;
    
    // Button for randomizing permutations
    void buttonClicked(Button * button) override;
    
    bool shouldBeOn = true;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularTextureSynthesisAudioProcessor& audioProcessor;
    
    ImageComponent backgroundImageComponent;

    Label grainSizeLabel;
    Label smoothingFilterLabel;
    Label inputMeterLabel;
    Label outputMeterLabel;
    Label algorithmSelectorLabel;
    Label gainSliderLabel;
    Label smoothFilterLabel;
    Label varianceSliderLabel;
    Label grainSizeSelectorLabel;
    
    // Visual meter
    SimpleMeter inputMeter;
    SimpleMeter outputMeter;
    
    
    void timerCallback() override;
    
    //Toggle Button for smoothing filtering
    ToggleButton smoothButton;
    ToggleButton notSmoothButton;
    
    // Grain size slider
    Slider grainSizeSlider;
    
    // Gain slider
    Slider gainSlider;
    
    // Drop-down for algorithm type
    ComboBox algSelector;
    // Once inheriting behavior like comboBox, can be used anywhere in class now
    ComboBox grainSizeSelector;
    
    
    ToggleButton mutateButton;
    ToggleButton notMutateButton;
    
    // Variance Slider
    Slider varianceSlider;
    
    

    

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureSynthesisAudioProcessorEditor)
};
