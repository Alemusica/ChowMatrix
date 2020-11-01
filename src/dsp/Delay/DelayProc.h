#pragma once

#include <JuceHeader.h>
#include "../Distortion/Distortion.h"
#include "../ProcessorChain.h"
#include "VariableDelay.h"

/**
 * Audio processor that implements delay line with feedback,
 * including filtering and distortion in the feedback path
 */ 
class DelayProc
{
public:
    DelayProc() = default;

    // processing functions
    void prepare (const dsp::ProcessSpec& spec);
    void reset();

    template<typename ProcessContext>
    void process (const ProcessContext& context);

    // flush delay line state
    void flushDelay();

    struct Parameters
    {
        float delayMs;
        float feedback;
        float lpfFreq;
        float hpfFreq;
        float distortion;
    };

    void setParameters (const Parameters& params);
    void setDelayType (VariableDelay::DelayType type) { delay.setDelayType (type); };

private:
    VariableDelay delay { 1 << 19 };

    float fs = 44100.0f;
    
    SmoothedValue<float, ValueSmoothingTypes::Linear> delaySmooth;
    SmoothedValue<float, ValueSmoothingTypes::Linear> feedback;
    std::vector<float> state;

    enum
    {
        lpfIdx,
        hpfIdx,
        distortionIdx,
    };

    MyProcessorChain<
        dsp::IIR::Filter<float>,
        dsp::IIR::Filter<float>,
        Distortion
        > procs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayProc)
};
