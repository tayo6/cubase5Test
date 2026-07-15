#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/**
    Draws a rotary slider as an arc that fills from the start angle to the
    current value, coloured with a gradient that sweeps through the arc
    (e.g. cool colour at 0, hot colour at 100). The gradient's end colours
    can be tweaked to taste.
*/
class GradientArcLookAndFeel : public juce::LookAndFeel_V4
{
public:
    GradientArcLookAndFeel();

    void drawRotarySlider (juce::Graphics& g,
                            int x, int y, int width, int height,
                            float sliderPosProportional,
                            float rotaryStartAngle,
                            float rotaryEndAngle,
                            juce::Slider& slider) override;

    // Colours that the arc gradient sweeps between at value = 0 and value = 100.
    juce::Colour lowColour  { juce::Colour::fromRGB (0x29, 0xB6, 0xF6) }; // cool blue
    juce::Colour highColour { juce::Colour::fromRGB (0xFF, 0x52, 0x52) }; // hot red
};
