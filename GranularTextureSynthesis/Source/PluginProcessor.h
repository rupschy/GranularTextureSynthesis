/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Granulate.h"
#include "VUAnalysis.h"
//==============================================================================
/**
*/
class GranularTextureSynthesisAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    GranularTextureSynthesisAudioProcessor();
    ~GranularTextureSynthesisAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // ComboBox values and the variables they change
    int grainSizeSelectionValue = 5;
    // 1: 64 2: 128 3: 256 4: 512 5: 1024 6: 2048 7: 4096 8: 8192
    int grainSize = 1024;
    
    int algSelectionValue = 1; //1: async 2:sync 3:smart
    int algorithm = 1;
    
    int overlapSelectionValue = 1;
    float overlapPercent = 0.f;

    
    //For Simple Meter
    std::atomic<float> meterValueInput;
    std::atomic<float> meterValueOutput;
    


//    Button Bools
    bool smoothState = false;
    bool notSmoothState = true;
    

    
    

    
    
    //AudioProcessorValueTreeState Save/Recall info
    AudioProcessorValueTreeState state;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    
private:
    Granulate granulate;
    
    
    VUAnalysis vuAnalysisInput;
    VUAnalysis vuAnalysisOutput;
    
    juce::AudioPlayHead * playHead;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureSynthesisAudioProcessor)
};
