/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class BeamformingSpeechEnhancerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BeamformingSpeechEnhancerAudioProcessor();
    ~BeamformingSpeechEnhancerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	void updateBeamformer(String filename);
	void updatePostFilter(String filename);
	void disableBypass() {
		isBypassed = false;
	};
	void enableBypass() {
		isBypassed = true;
	};
private:
	// represents the beamformer impulse response
	dsp::ProcessorChain<dsp::Convolution> beamformerFilter;
	dsp::ProcessorChain<dsp::ProcessorChain<dsp::Convolution>,dsp::Convolution> postFilter;
	int srate;
	int blocksize;
	bool postFilterReady;
	bool bfFilterReady;
	bool isBypassed;

	Array<float> ylKArr;
	Array<float> yrKArr;
	Array<float> zKArr;
	AudioBuffer<float> giBuff;
    //==============================================================================

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BeamformingSpeechEnhancerAudioProcessor)
};
