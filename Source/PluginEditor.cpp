#include "PluginEditor.h"

GradientArcKnobAudioProcessorEditor::GradientArcKnobAudioProcessorEditor (GradientArcKnobAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setLookAndFeel (&gradientLookAndFeel);

    titleLabel.setText ("GRADIENT ARC", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.7f));
    addAndMakeVisible (titleLabel);

    valueSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    valueSlider.setRange (0.0, 100.0, 0.01);
    valueSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 24);
    valueSlider.setTextValueSuffix ("");
    valueSlider.setDoubleClickReturnValue (true, 50.0);
    addAndMakeVisible (valueSlider);

    valueAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        processorRef.apvts, GradientArcKnobAudioProcessor::valueParamID, valueSlider);

    // Resizable within sensible bounds; defaults to a compact square window.
    setResizable (true, true);
    setResizeLimits (220, 260, 600, 640);
    setSize (280, 320);
}

GradientArcKnobAudioProcessorEditor::~GradientArcKnobAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void GradientArcKnobAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient backgroundGradient (juce::Colour::fromRGB (0x22, 0x22, 0x2A), 0.0f, 0.0f,
                                              juce::Colour::fromRGB (0x12, 0x12, 0x16),
                                              static_cast<float> (getWidth()),
                                              static_cast<float> (getHeight()), true);
    g.setGradientFill (backgroundGradient);
    g.fillAll();
}

void GradientArcKnobAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced (16);

    titleLabel.setBounds (bounds.removeFromTop (28));
    bounds.removeFromTop (8);

    const auto knobSize = juce::jmin (bounds.getWidth(), bounds.getHeight() - 30);
    auto knobArea = bounds.withSizeKeepingCentre (knobSize, knobSize + 30)
                           .withY (bounds.getY());

    valueSlider.setBounds (knobArea);
}