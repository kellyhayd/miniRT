<h1 align="center"> 🎨 miniRT </h1>

<p align="center">
<img alt="Static Badge" src="https://img.shields.io/badge/42-S%C3%A3o_Paulo-orange"> <img alt="Static Badge" src="https://img.shields.io/badge/MiniLibX-required-blue"> <img alt="Static Badge" src="https://img.shields.io/badge/language-c-green">
<img alt="Static Badge" src="https://img.shields.io/badge/submitted_in-fev%2F24-orange"></p>

> A basic ray tracer project that introduces essential 3D rendering concepts, focusing on ray tracing as opposed to rasterization for visual realism.

<h2> ✏ About </h2>

```
This project is an introductory ray tracing tool, featuring basic geometry and lighting to produce 3D images. It's implemented in C using the MiniLibX library.
```

<h2> ⚙ Requirements </h2>

- Use the MiniLibX library (from system or source).
- Ensure smooth window management (e.g., minimization).
- Adapt to window resizing without altering content.
- Basic shapes required: plane, sphere, cylinder.
- Handle transformations (translation, rotation) for objects, lights, and cameras (except for rotations on spheres and lights).
- Implement ambient and diffuse lighting; manage shadows and ambient light.
- Ensure clean window exit on ESC key or window close.

<h2> 🖥️ Scene Configuration </h2>

- Input a `.rt` scene file with object, light, and camera configurations.
- Allow object definitions in any order, separated by line breaks.
- Required elements: 
  - **Ambient light** (`A`): `A 0.2 255,255,255`
  - **Camera** (`C`): `C -50.0,0,20 0,0,1 70`
  - **Light** (`L`): `L -40.0,50.0,0.0 0.6 10,0,255`
  - **Sphere** (`sp`): `sp 0.0,0.0,20.6 12.6 10,0,255`
  - **Plane** (`pl`): `pl 0.0,0.0,-10.0 0,1.0,0 0,0,225`
  - **Cylinder** (`cy`): `cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255`

<h2> 🌟 Bonus Features </h2>

Optional enhancements include:
- Specular reflection (Phong model).
- Checkerboard color pattern.
- Multiple colored light sources.
- Additional shapes like cone, hyperboloid, or paraboloid.
- Support for bump map textures.
 
<h2> Image I </h2>

![Image](https://github.com/user-attachments/assets/43424bcb-eefe-48fe-b201-9e0baae6c644)

<h2> Image II </h2>

![Image](https://github.com/user-attachments/assets/2a1ac2f6-107c-4505-81d8-baa28a0e363f)

<h2> Image III </h2>

![Image](https://github.com/user-attachments/assets/8118a825-2ba7-4565-a757-f45605c57142)

<h2> Image IV </h2>

![Image](https://github.com/user-attachments/assets/457cc172-fdf9-4888-ae10-c42c6f8c27ad)


--- 
