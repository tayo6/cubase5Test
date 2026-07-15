cmake_minimum_required(VERSION 3.22)

project(GradientArcKnob VERSION 1.0.0)

# ---------------------------------------------------------------------------
# Old-host (Cubase 5 / Windows) compatibility settings
# ---------------------------------------------------------------------------
# Cubase 5 (2009) is a 32-bit-only era host on Windows. Build Win32 (x86),
# not x64. Set this via the CMake generator platform in CI
# (cmake -A Win32), not here, since it must be chosen before project().

# Statically link the MSVC runtime so the plugin doesn't depend on a
# vcredist version newer than what a Cubase 5 era machine would have.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Keep the C++ standard conservative; JUCE 7.x still supports this fine
# and it avoids pulling in newer-only Windows SDK/runtime expectations.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE)

juce_add_plugin(GradientArcKnob
    COMPANY_NAME "YourCompany"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Ycmp
    PLUGIN_CODE Gark
    FORMATS VST3
    PRODUCT_NAME "Gradient Arc Knob"
    VST3_CATEGORIES "Fx"
    # VST3 in a single-file bundle is simplest for old hosts to scan.
    VST3_AUTO_MANIFEST TRUE
)

juce_generate_juce_header(GradientArcKnob)

target_sources(GradientArcKnob
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/GradientArcLookAndFeel.cpp
)

target_compile_definitions(GradientArcKnob
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(GradientArcKnob
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
