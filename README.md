# raytracer-from-scratch

A hobby-level raytracer written from-scratch, featuring:
- a sphere primitive
- a variety of light sources (point, ambient, directional)
- shininess
- reflections

![Normal rendering](images/normal-rendering.png)

Terminal-based rendering (just for fun):
![Terminal rendering](images/terminal-based-rendering.png)

Implementation details:
- left-hand coordinate system
- camera looks in `+Z` direction
- a [GeoGebra scene](https://www.geogebra.org/calculator/zfexqajh) I used to debug this (proved very effective!)

# Installation
```bash
clone https://github.com/fahlerile/raytracer-from-scratch
cd raytracer-from-scratch
mkdir build
cd build
cmake ..
make
cd bin
./raytracer
```

# Use

## CLI options
- `--help` - show help message
- `--terminal-rendering` - use terminal rendering

## Scene configuration

To configure your scene, you should change `scene.json` in `bin/` directory. All available primitives and light sources are listed in [`Sphere`](Sphere/) and [`Light`](Light/) header files. In your JSON file you should put the same arguments as requested in these primitives/light sources constructors.

## Example:

From [`Light/DirectionalLight/DirectionalLight.hpp`](Light/DirectionalLight/DirectionalLight.hpp)
```cpp
DirectionalLight(double intensity, color_t color, vec3d direction);
```
That means if you want your directional light to be white, 100% intense and to "look" in +Z direction, you should put this in your scene file (to be more precise, in `light_sources` section):
```json
{
    "type": "DirectionalLight",
    "intensity": 1,
    "color": [255, 255, 255, 255],
    "direction": [0, 0, 1]
}
```

## TODO/NOTES
New features:
- [ ] Add other primitives
    - [ ] Planes
    - [ ] Mathematical functions
    - [ ] Cylinder
    - [ ] Cone
    - [ ] Torus
    - [ ] Polygon
- [ ] Camera transform (camera matrix)
- [ ] Camera configuration in `scene.json`
- [ ] Real-time rendering, camera movement

Potential bug causes:
- [ ] `alpha` parameter is changing during `color_t` arithmetic (should it?)

