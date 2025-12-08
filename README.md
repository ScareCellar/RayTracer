# RayTracer

A simple CPU ray tracer written in modern C++ (C++20) that renders spheres and planes with basic materials (Lambertian, Metal, Dielectric, Emissive). Uses SDL3 for window/texture presentation and GLM for math. The project is organized for development in Visual Studio 2022.

## Features
- Per-pixel multi-sample ray tracing
- Materials: diffuse (Lambertian), metal (with fuzz), dielectric (refraction), emissive lights
- Camera with configurable FOV and view transform
- Simple scene construction via `Scene::AddObject`
- Random utilities (shared mt19937) in `Source\Random.h`
- Framebuffer backed by an SDL texture for display

## Quick start (Visual Studio 2022)
Prerequisites:
- Visual Studio 2022 with C++ workload (MSVC)
- SDL3 development libraries (include + lib + SDL3.dll for runtime)
- GLM (a copy is included under `ThirdParty\glm`)

1. __Open Project__: open `RayTracer.sln` (or `RayTracer.vcxproj`) in Visual Studio.
2. Select appropriate platform (x64 recommended) and configuration (__Debug__ or __Release__). Use __Configuration Manager__ if needed.
3. Ensure project properties:
   - __C/C++ > Language > C++ Language Standard__ = `C++20` (or later)
   - __VC++ Directories > Include Directories__ contains the SDL3 include folder and `ThirdParty\glm`
   - __Linker > General > Additional Library Directories__ contains SDL3 lib folder
   - __Linker > Input > Additional Dependencies__ includes `SDL3.lib` (and `SDL3main.lib` if required by your SDL3 distribution)
4. Make sure `SDL3.dll` is next to the built executable (or in your PATH) before running.
5. Build the solution (__Build > Build Solution__) or press __Start Debugging__ / __Start Without Debugging__ to run.

## Runtime controls
- Close window or press `Escape` to exit.
- Scene parameters (resolution, number of samples, objects) are configured in `Source\Main.cpp`:
  - `SCREEN_WIDTH`, `SCREEN_HEIGHT`
  - `scene.Render(framebuffer, camera, numSamples)` — `numSamples` controls anti-aliasing / sampling per pixel
  - Objects are created and added to the scene in `Main.cpp`

## Project layout (key files)
- `Source\Main.cpp` — entry, scene setup, main loop
- `Source\Renderer.*` — SDL window/renderer wrapper
- `Source\Framebuffer.*` — pixel buffer and SDL texture update
- `Source\Scene.*` — scene traversal, ray tracing loop
- `Source\Object.h` — base type for hittable objects
- `Source\Sphere.*`, `Source\Plane.*` — concrete geometry
- `Source\Material.*` — material models and scattering
- `Source\Camera.*` — camera and view plane generation
- `Source\Random.h` — random utilities (shared generator)
- `Source\Transform.h` — position/rotation/scale for objects
- `ThirdParty\glm` — included GLM math library
