# raytracer-from-scratch

A raytracer, which uses left-hand coordinate system, and in which camera looks in `+Z` direction by default. Visualization of the simple scene I made in GeoGebra: https://www.geogebra.org/calculator/zfexqajh

## TODO/NOTES
New features
- [ ] Add shadows
- [ ] Add reflections
- [ ] Add other primitives

Bugfixes/improvements
- [ ] `Scene::cast_ray` bug (see comment there)

Potential bug causes
- [ ] `alpha` parameter is changing during `color_t` arithmetic
