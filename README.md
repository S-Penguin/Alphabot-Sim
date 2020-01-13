# Alphabot-Sim
A Basic openGl simulation of an alphabot

*This app use numerous dependencies*
# Installation on linux
Install dependencies
```console
sudo apt install -y xorg-dev libgl1-mesa-dev libglu-dev libassimp-dev
```
Install GLFW
```console
git clone https://github.com/glfw/glfw.git
cd glfw
cmake ./
make
sudo make install
```
Install GLAD
```console
git clone https://github.com/Dav1dde/glad.git
cd glad
cmake ./
make
sudo cp -a include /usr/local/
```
Install GLM
```console
git clone https://github.com/g-truc/glm.git
cd glm
cmake ./
make
sudo make install
```
Install Assimp
```console
git clone https://github.com/assimp/assimp.git
cd assimp
cmake ./
make
sudo make install
```
#Compilation
```console
make
```

#run
```console
make run
```

# Basic instruction in main.cpp
* create a skybox
Skybox skybox

* create a ground
Cube ground
ground.set_as_ground()

* create a cube considered as an obstacle
Cube cube
cube.set_as_obstacle()

* instantiate Alphabot
Alphabot alphabot

* alphabot.check() and camera.check() check if the previous instruction is done

* get cube_as_ground(view, projection, size_of_the_ground) and get cube_as_obstacle(view, projection, cubePositions, length_of_cubePositions) change the settings.

* Camera.move() and alphabot.generate() are essential : they are moving the camera or alphabot if the position target is different than the actual position

the file stb_image.h is from https://github.com/nothings/stb/blob/master/stb_image.h

