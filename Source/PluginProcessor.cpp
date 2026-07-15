#include "PluginProcessor.h"
#include "PluginEditor.h"

GradientArcKnobAudioProcessor::GradientArcKnobAudioProcessor()
    : AudioProcessor (BusesProperties()
                        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

GradientArcKnobAudioProcessor::~GradientArcKnobAudioProcessor() = default;

juce::AudioProcessorValueTreeState::ParameterLayout GradientArcKnobAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { valueParamID, 1 },
        "Value",
        juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f),
        50.0f));

    return { params.begin(), params.end() };
}

void GradientArcKnobAudioProcessor::prepareToPlay (double, int) {}
void GradientArcKnobAudioProcessor::releaseResources() {}

bool GradientArcKnobAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void GradientArcKnobAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    // This plugin is a GUI/control demo — pass audio straight through.
    juce::ignoreUnused (buffer);
}

juce::AudioProcessorEditor* GradientArcKnobAudioProcessor::createEditor()
{
    return new GradientArcKnobAudioProcessorEditor (*this);
}

bool GradientArcKnobAudioProcessor::hasEditor() const { return true; }

const juce::String GradientArcKnobAudioProcessor::getName() const { return JucePlugin_Name; }

bool GradientArcKnobAudioProcessor::acceptsMidi() const { return false; }
bool GradientArcKnobAudioProcessor::producesMidi() const { return false; }
bool GradientArcKnobAudioProcessor::isMidiEffect() const { return false; }
double GradientArcKnobAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GradientArcKnobAudioProcessor::getNumPrograms() { return 1; }
int GradientArcKnobAudioProcessor::getCurrentProgram() { return 0; }
void GradientArcKnobAudioProcessor::setCurrentProgram (int) {}
const juce::String GradientArcKnobAudioProcessor::getProgramName (int) { return {}; }
void GradientArcKnobAudioProcessor::changeProgramName (int, const juce::String&) {}

void GradientArcKnobAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto state = apvts.copyState(); state.isValid())
    {
        if (auto xml = state.createXml())
            copyXmlToBinary (*xml, destData);
    }
}

void GradientArcKnobAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GradientArcKnobAudioProcessor();
}
