/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Granulate.h"
#include "GrainCreator.h"
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
                       )
#endif
{
    
}

GranularTextureSynthesisAudioProcessor::~GranularTextureSynthesisAudioProcessor()
{
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
     playHead->getCurrentPosition(currentPositionInfo);
    
//    granulate.setLenIn(buffer.getNumSamples());
  
    
//    float * leftChannel = buffer.getWritePointer(0);
//    float * rightChannel = buffer.getWritePointer(1);
//    int N = buffer.getNumSamples();
//    granulate.splitBuffer(leftChannel, rightChannel, N);
    granulate.splitBuffer(buffer);
    
//    mutateState = false;
//    if (mutateState == true){
//        granulate.setPermutation(permutation);
    
    
//    continuousProc = false;
        //granulate.setGrainSize(grainSize);
    
    //granulate.setVarianceValue(variance);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        for (int n = 0; n < buffer.getNumSamples(); ++n){
            float x = buffer.getReadPointer(channel)[n];
            meterValueInput = vuAnalysisInput.processSample(x,channel);
            
            
            
            
            
//            x = granulate.processSample(x, channel);
            buffer.getWritePointer(channel)[n] = x;

            
            if (smoothState == true){
                granulate.smoothFilter(x,channel);
            }
            if (smoothState == false){
                
            }
            meterValueOutput = vuAnalysisOutput.processSample(x,channel);
        }
        

        float * channelData = buffer.getWritePointer(channel);
        granulate.processSignal(channelData, buffer.getNumSamples(), channel);
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
}

void GranularTextureSynthesisAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularTextureSynthesisAudioProcessor();
}
