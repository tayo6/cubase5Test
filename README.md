# Gradient Arc Knob (VST3)

A minimal JUCE VST3 plug-in: a single rotary control drawn as a dynamic
gradient arc, bound to a 0–100 parameter. No audio processing — it's a
GUI/control demo (passthrough audio).

## Why it's built this way

Targeting **Cubase 5** as the oldest supported host shaped a few decisions:

- **Win32 (x86), not x64.** Cubase 5 on Windows is a 32-bit-only era host.
  The CI workflow configures CMake with `-A Win32`.
- **Static MSVC runtime (`/MT`).** Avoids depending on a `vcredist` version
  newer than what a Cubase 5-era machine would have installed. Set via
  `CMAKE_MSVC_RUNTIME_LIBRARY` in `CMakeLists.txt`.
- **JUCE pinned to a specific tag (7.0.12)** in the workflow, rather than
  tracking `master`. Bump deliberately and re-test old-host loading when
  you do — newer JUCE releases increasingly assume newer toolchains.
- **No newer-only VST3 features** (sample-accurate automation edge cases,
  fancy bus arrangements). Cubase 4/5 introduced VST3 with dynamic I/O and
  basic parameter automation; sticking to that baseline keeps the plugin
  inside what those hosts actually implement.

## Building locally

```bash
git clone --recurse-submodules <this-repo>
cmake -S . -B build -A Win32 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target GradientArcKnob_VST3
```

The `.vst3` will be under `build/GradientArcKnob_artefacts/Release/VST3/`.

## Building via GitHub Actions

Push to `main` or trigger the `Build VST3 (Windows x86, Cubase 5 compatible)`
workflow manually. It checks out JUCE, configures for Win32, builds, and
uploads the `.vst3` as a workflow artifact.

## Testing against Cubase 5

CI can build the binary, but it can't verify it loads in an actual Cubase 5
instance — that has to be tested manually on a machine (or VM) with Cubase 5
installed. Copy the built `.vst3` into
`C:\Program Files (x86)\Common Files\VST3\` and check Cubase's plug-in
manager / blacklist log if it fails to scan.
