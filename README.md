# raytracer-from-scratch

A raytracer, which uses left-hand coordinate system, and in which camera looks in `+Z` direction by default. Visualization of the simple scene I made in GeoGebra: https://www.geogebra.org/calculator/zfexqajh

## TODO
New features
- [x] Add basic raytracing for a sphere (probably should delete `Object` for now, just `Sphere`, because there is no other primitives for now)
- [ ] Add light
    - [x] Diffuse Reflection (matte)
    - [x] Specular Reflection (shiny)
    - [x] Understand mathematical models of Diffuse and Specular reflections
    - [x] Colored light (need to have multiple light intensities)
        - [ ] Test and bigfix it if needed
            - [ ] `Scene::calculate_color` (comment)
- [ ] Add shadows
- [ ] Add reflections
- [ ] Add other primitives

Bugfixes/improvements
- [ ] `Scene::cast_ray` bug (see comment there)
- [x] `+Y` direction is not upwards (messed up coordinate system)
- [x] Fix `unsigned char` overflow in `color_t` arithmetic (add 0 and 255 clamping)
- [x] Abstract similar code in `PointLight` and `DirectionalLight`'s `calculate_intensity` method
- [ ] Refactor `vec` structs
    - [ ] Try to templatize number of elements
    - [ ] Make operators `friend`s and non-members?
- [ ] Add `Scene::render`
- [ ] Configure camera by FOV and near plane distance

Potential bug causes
- [ ] `alpha` parameter is changing during `color_t` arithmetic
