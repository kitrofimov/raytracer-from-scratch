# raytracer-from-scratch

A raytracer, which uses left-hand coordinate system, and in which camera looks in `+Z` direction by default. Visualization of the simple scene I made in GeoGebra: https://www.geogebra.org/calculator/zfexqajh

## TODO/NOTES
New features
- [x] Add shadows
    - [x] `PointLight`
    - [x] Test
- [ ] Add reflections
- [ ] Add other primitives

Bugfixes/improvements
- [x] `Scene::cast_ray` bug

Potential bug causes
- [ ] `alpha` parameter is changing during `color_t` arithmetic
