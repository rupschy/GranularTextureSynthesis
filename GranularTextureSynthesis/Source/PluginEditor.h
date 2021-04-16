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
    Label overlapSelectorLabel;
    Label wetDrySliderLabel;
    
    // Visual meter
    SimpleMeter inputMeter;
    SimpleMeter outputMeter;
    
    void timerCallback() override;

    Slider varianceSlider;
    Slider gainSlider;
    Slider wetDrySlider;
    

    ComboBox algSelector;
    ComboBox grainSizeSelector;
    ComboBox overlapSelector;
    
    ToggleButton smoothButton;
    ToggleButton notSmoothButton;

    
    
public: // this will get rid of attachment first and then slider
    
    
    //AudioValueTree Info
    //slider attachments
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>> comboBoxAttachments;
    
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment>> buttonAttachments;
    

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureSynthesisAudioProcessorEditor)
};
