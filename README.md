<a href="https://www.cprogramming.com"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" height="25em" alt="C"/></a>

# MiniRT

<img src="https://github.com/user-attachments/assets/b13909e7-86f6-4651-ab07-d6226cdcad43" alt="scene1" height="200">
<img src="https://github.com/user-attachments/assets/e96eac53-3da1-49f3-bab4-10a56a0128fe" alt="scene2" height="200">
<img src="https://github.com/user-attachments/assets/450f47f5-e730-4e7b-b55c-e9836b3723d5" alt="scene3" height="200">

## Goal: 
Create a minimalistic ray tracer from scratch to render 3D scenes with basic objects and lighting. \
**Ray tracing**: technique used in computer graphics to generate realistic images by simulating the path of light.

## Key Features to Implement:
- **Basic Objects:**
  Render simple geometric shapes like spheres, planes, and cylinders.
- **Lighting:**
  Implement ambient, diffuse, and specular lighting to simulate how light interacts with objects.
- **Camera:**
  Define a camera to view the scene from a specific perspective.
- **Scene Parsing:**
  Read and interpret a configuration file (.rt) that describes the scene (object positions, colors, light sources, camera settings).
- **Rendering:**
  Generate a 2D image by casting rays from the camera and calculating how they interact with objects and light sources.

## Technical Challenges
- **Mathematics:** Use linear algebra (vectors, matrices) for ray-object intersections and lighting calculations.
- **Optimization:** Ensure efficient performance, especially when handling complex scenes.
- **Error Handling:** Gracefully manage invalid input files or edge cases.
  
Skills Developed
- **Graphics Concepts:** Basics of ray tracing, light simulation, and 3D rendering.
- **Mathematics:** Understand the maths behind raytracing.

## Installation

To set up this project locally, follow these steps:

1. **Clone the repository to your local machine:**
	```sh
	git clone git@github.com:casomarr/42-MiniRT.git
	```

2. **Navigate to the project directory:**
	```sh
	cd 42-MiniRT
	```

3. **Compile the project:**
	```sh
	make
	```

4. **Run the program:**
	```sh
	./miniRT <file.rt>
	```

## Usage
- In the "scene" folder, each .rt file describes the elements of the 3D scene to be rendered. Each line in the file specifies an object, light, camera, or configuration parameter.
- The file must include exactly one camera (C) and one ambient light (A).
- Each line starts with an identifier followed by parameters:

	- Camera (C):
	  	- coordinates of the position of the camera
	  	- coordinates of the point the camera is looking at
	  	- field of view (in degrees), controlling the width of the camera's view
	- Light (L):
	  	- coordinates of the light source
	  	- light intensity (from 0.0 to 1.0)
	  	- light color in RGB format (from 0 to 255)
	- Ambient Light (A):
	  	- ambient light intensity (from 0.0 to 1.0)
	  	- ambient light color in RGB format (from 0 to 255)
	- Sphere (sp):
	  	- center coordinates of the sphere
	  	- diameter of the sphere
	  	- color of the sphere in RGB format (from 0 to 255)
	- Cylinder (cy):
	  	- center coordinates of the base of the cylinder
	  	- axis vector of the cylinder
	  	- diameter of the cylinder
	  	- height of the cylinder
	  	- color of the cylinder in RGB format (from 0 to 255)
	- Plane (pl):
	  	- coordinates of a point on the plane
	  	- normal vector of the plane (perpendicular to its surface)
	  	- color of the plane in RGB format (from 0 to 255)
  
Example:
```
C     0,20,0     0,-0.7,1     70

L     0,20,20     0.9

A     0.2      255,255,255

pl     0,-2,0     0,1,0     206,206,206

cy     2,0,15     -0.916,0.9063,-0.1182     3     9     117,241,0

sp     0,0,10     5     255,0,0
```
- Output : the program generates a PNG image of the rendered scene.
