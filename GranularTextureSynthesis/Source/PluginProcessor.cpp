/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Granulate.h"
#include <JuceHeader.h>


//==============================================================================
GranularTextureSynthesisAudioProcessor::GranularTextureSynthesisAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "GranulateParams", createParameterLayout())
#endif
{
    
}

GranularTextureSynthesisAudioProcessor::~GranularTextureSynthesisAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout
    // AUDIO PROCESSOR VALUE TREE STATE
    GranularTextureSynthesisAudioProcessor::createParameterLayout(){
        
    // vector of pointers made up of different parameters
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    // Matches parameters set in Editor.cpp
        params.push_back(std::make_unique<AudioParameterFloat>("wetDryValue","Dry/Wet",0.f,1.f,0.5f));
    // can add additional parameters using params.push_back(std::make_unique<AudioParameterInt> ("param ID","name",0,1,0.5);
        params.push_back(std::make_unique<AudioParameterInt> ("varianceValue", "Variance Seed", 1,8,4));
        params.push_back(std::make_unique<AudioParameterFloat> ("makeupGainValue", "Make-up", 0.01f, 1.5f, 1.f));
        params.push_back(std::make_unique<AudioParameterInt> ("algSelectionValue", "Algorithm Selected", 1,3,1));
        params.push_back(std::make_unique<AudioParameterInt> ("grainSizeSelectionValue", "Grain Size Selected", 1,8,5));
        params.push_back(std::make_unique<AudioParameterFloat> ("overlapSelectionValue", "Algorithm Selected", 1, 4, 1));
        params.push_back(std::make_unique<AudioParameterBool> ("smoothState", "Smoothing Selected", false));
        params.push_back(std::make_unique<AudioParameterBool> ("notSmoothState", "Not Smoothing Selected", true));
        
    
    return {params.begin(),params.end()};
    
}

//==============================================================================
const juce::String GranularTextureSynthesisAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularTextureSynthesisAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularTextureSynthesisAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularTextureSynthesisAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularTextureSynthesisAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularTextureSynthesisAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularTextureSynthesisAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularTextureSynthesisAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GranularTextureSynthesisAudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularTextureSynthesisAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GranularTextureSynthesisAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    granulate.prepare(sampleRate);
    vuAnalysisInput.setSampleRate(sampleRate);
    vuAnalysisOutput.setSampleRate(sampleRate);

    

    
    
    

}

void GranularTextureSynthesisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularTextureSynthesisAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GranularTextureSynthesisAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
     playHead = this->getPlayHead();
//     playHead->getCurrentPosition(currentPositionInfo);
    float wetDryValue = *state.getRawParameterValue("wetDryValue");
    granulate.setWetDryValue(wetDryValue);
    int varianceValue = *state.getRawParameterValue("varianceValue");
    granulate.setVarianceValue(varianceValue);
    float makeupGainValue  = *state.getRawParameterValue("makeupGainValue");
    granulate.setMakeupGainValue(makeupGainValue);
    
    // ComboBox value setting
    int algSelectionValue = *state.getRawParameterValue("algSelectionValue");
    granulate.setAlgorithm(algSelectionValue);
    float overlapSelectionValue = *state.getRawParameterValue("overlapSelectionValue");
    granulate.setOverlap(overlapSelectionValue);
    int grainSizeSelectionValue = *state.getRawParameterValue("grainSizeSelectionValue");
    granulate.setGrainSize(grainSizeSelectionValue);
    
    // Button value setting
    bool smoothState = *state.getRawParameterValue("smoothState");
    bool notSmoothState = *state.getRawParameterValue("notSmoothState");
    granulate.setSmoothState(smoothState,notSmoothState);
    
    
    granulate.setPermParameters(grainSize);
    granulate.setPermutationSet(grainSize);
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        for (int n = 0; n < buffer.getNumSamples(); ++n){
            float x = buffer.getReadPointer(channel)[n];
            float y = buffer.getReadPointer(channel)[n];
            meterValueInput = vuAnalysisInput.processSample(x,channel);
            

            y = granulate.setInputMatrix(x, channel);
            y = granulate.outputArray(channel);
            y = granulate.processMakeupGain(y,channel);

            if (smoothState == true){
                granulate.setSmoothFilter(y,channel);
            }

//          Wet/Dry process
            float z = (y * wetDryValue) + (x * (1 - wetDryValue));
            meterValueOutput = vuAnalysisOutput.processSample(z,channel);
            z = buffer.getWritePointer(channel)[n];
        }
    }
}

//==============================================================================
bool GranularTextureSynthesisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor*GranularTextureSynthesisAudioProcessor::createEditor()
{
    return new GranularTextureSynthesisAudioProcessorEditor (*this);
}

//==============================================================================
void GranularTextureSynthesisAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto currentState = state.copyState();
    
    std::unique_ptr<XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
    //dont need to add any additional parameters because all are inside "state"
    
}

void GranularTextureSynthesisAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation()call.
    
    //Call-back for parameters
    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    
    // looks weird because state is the name of our state...
    if (xml && xml->hasTagName(state.state.getType())){
        state.replaceState(ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularTextureSynthesisAudioProcessor();
}
