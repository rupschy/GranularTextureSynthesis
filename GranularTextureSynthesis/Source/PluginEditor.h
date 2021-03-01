/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GranularTextureSynthesisAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                      public juce::Slider::Listener,
                                                      public juce::ComboBox::Listener
//                                                      public juce::ToggleButton::Listener
{
public:
    GranularTextureSynthesisAudioProcessorEditor (GranularTextureSynthesisAudioProcessor&);
    ~GranularTextureSynthesisAudioProcessorEditor() override;

    //==============================================================================


    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    static const Font& getAirstrikeFont()
        {
            static Font Airstrike3D (Font (Typeface::createSystemTypefaceFor (BinaryData::airstrike3d_ttf,
                                                                        BinaryData::airstrike3d_ttfSize)));
            return Airstrike3D;
        }
    // Slider for grain size
    void sliderValueChanged(Slider * slider) override;
    
    // Drop-down for algorithm typing
     void comboBoxChanged(juce::ComboBox * comboBox) override;
    
    //Button for continuous variation
//    void buttonClicked(Button * button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularTextureSynthesisAudioProcessor& audioProcessor;
    
    ImageComponent mImageComponent;
    

    
    
    // Grain size slider
    Slider grainSizeSlider;
    
    // Drop-down for algorithm type
    ComboBox algSelector;
    
//    ToggleButton continuousButton;
//    ToggleButton notContinuousButton;
    

    
    

    

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureSynthesisAudioProcessorEditor)
};
