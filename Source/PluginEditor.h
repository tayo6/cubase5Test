#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "GradientArcLookAndFeel.h"

class GradientArcKnobAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit GradientArcKnobAudioProcessorEditor (GradientArcKnobAudioProcessor&);
    ~GradientArcKnobAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GradientArcKnobAudioProcessor& processorRef;

    GradientArcLookAndFeel gradientLookAndFeel;

    juce::Slider valueSlider;
    juce::Label  titleLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> valueAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GradientArcKnobAudioProcessorEditor)
};
