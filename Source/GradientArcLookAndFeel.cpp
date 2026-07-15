#include "GradientArcLookAndFeel.h"

GradientArcLookAndFeel::GradientArcLookAndFeel()
{
    setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
}

void GradientArcLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                                int x, int y, int width, int height,
                                                float sliderPosProportional,
                                                float rotaryStartAngle,
                                                float rotaryEndAngle,
                                                juce::Slider& slider)
{
    juce::ignoreUnused (slider);

    auto bounds = juce::Rectangle<float> (static_cast<float> (x),
                                           static_cast<float> (y),
                                           static_cast<float> (width),
                                           static_cast<float> (height)).reduced (10.0f);

    const auto diameter   = juce::jmin (bounds.getWidth(), bounds.getHeight());
    const auto radius     = diameter * 0.5f;
    const auto centre     = bounds.getCentre();
    const auto arcRadius  = radius - 6.0f;
    const auto lineWidth  = juce::jmax (4.0f, radius * 0.18f);

    const auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // --- Background track (full arc, dim) ---------------------------------
    juce::Path backgroundArc;
    backgroundArc.addCentredArc (centre.x, centre.y, arcRadius, arcRadius,
                                  0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (juce::Colours::white.withAlpha (0.12f));
    g.strokePath (backgroundArc, juce::PathStrokeType (lineWidth,
                                                         juce::PathStrokeType::curved,
                                                         juce::PathStrokeType::rounded));

    // --- Dynamic gradient value arc ----------------------------------------
    if (sliderPosProportional > 0.0001f)
    {
        juce::Path valueArc;
        valueArc.addCentredArc (centre.x, centre.y, arcRadius, arcRadius,
                                 0.0f, rotaryStartAngle, toAngle, true);

        // Gradient endpoints follow the arc's start/end points so the
        // colour sweeps around the arc as the value changes, rather than
        // being a static left-to-right gradient.
        const auto startPoint = centre.getPointOnCircumference (arcRadius, rotaryStartAngle);
        const auto endPoint   = centre.getPointOnCircumference (arcRadius, toAngle);

        juce::ColourGradient gradient (lowColour, startPoint.x, startPoint.y,
                                        highColour, endPoint.x, endPoint.y,
                                        false);

        // Add a mid stop so the sweep reads as a smooth hue transition
        // rather than a flat two-colour blend.
        gradient.addColour (0.5, lowColour.interpolatedWith (highColour, 0.5f));

        g.setGradientFill (gradient);
        g.strokePath (valueArc, juce::PathStrokeType (lineWidth,
                                                        juce::PathStrokeType::curved,
                                                        juce::PathStrokeType::rounded));

        // Soft glow at the current value's tip for a "live" feel.
        g.setColour (lowColour.interpolatedWith (highColour, sliderPosProportional).withAlpha (0.9f));
        g.fillEllipse (juce::Rectangle<float> (10.0f, 10.0f).withCentre (endPoint));
    }

    // --- Centre readout ------------------------------------------------
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (juce::FontOptions (radius * 0.42f, juce::Font::bold)));
    const auto value = juce::jmap (sliderPosProportional, 0.0f, 1.0f, 0.0f, 100.0f);
    g.drawFittedText (juce::String (juce::roundToInt (value)),
                       bounds.toNearestInt(),
                       juce::Justification::centred, 1);
}
