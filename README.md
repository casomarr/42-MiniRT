<a href="https://www.cprogramming.com"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" height="25em" alt="C"/></a>

# MiniRT

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
  Read and interpret a configuration file (.rt) that describes the scene (e.g., object positions, colors, light sources, camera settings).
- **Rendering:**
  Generate a 2D image by casting rays from the camera and calculating how they interact with objects and light sources.

## Technical Challenges
- **Mathematics:** Use linear algebra (vectors, matrices) for ray-object intersections and lighting calculations.
- **Optimization:** Ensure efficient performance, especially when handling complex scenes.
- **Error Handling:** Gracefully manage invalid input files or edge cases.
- 
Skills Developed
- **C Programming:** Deep understanding of memory management and data structures.
- **Graphics Concepts:** Basics of ray tracing, light simulation, and 3D rendering.
- **Problem Solving:** Implementing complex mathematical algorithms in code.

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

4. **Run the shell:**
	```sh
	./minirt
	```

# Usage
- change the [filename]'s data to change the image (EXPLIQUER CHAQUE LIGNE avec photo)
- **Output** : The program generates a PNG image of the rendered scene
