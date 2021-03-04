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
    
    // Button for randomizing permutations
    void buttonClicked(Button * button) override;
    


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularTextureSynthesisAudioProcessor& audioProcessor;
    
    ImageComponent mImageComponent;

    
    //Rectangle mRectangle;
    
    // Visual meter
    SimpleMeter meter1;
    SimpleMeter meter2;
    
    
    void timerCallback() override;
    
    
    
    // Grain size slider
    Slider grainSizeSlider;
    
    // Drop-down for algorithm type
    ComboBox algSelector;
    // Once inheriting behavior like comboBox, can be used anywhere in class now
    
    ToggleButton mutateButton;
    ToggleButton notMutateButton;
    

    
    

    

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureSynthesisAudioProcessorEditor)
};
