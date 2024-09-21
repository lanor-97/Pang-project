# 🎮 PangDiSpagna

## Overview

This is a **C++** game, developed for the course "Programmazione ad Oggetti" @Università della Calabria, inspired by the classic arcade game **Super Pang (Super Buster Bros.)**.
The goal is to clear each level by shooting and splitting all the bouncing bubbles, but beware—they split into smaller ones until they disappear entirely!

### Built With
- **C++**: Core game logic and mechanics are implemented in C++.
- **Allegro5**: Used as the primary graphics, audio, and input library for handling game assets and interactions.

---

## 🚀 Getting Started

### Installing compiler and graphic library
```bash
  sudo apt update
  sudo apt install g++ liballegro5-dev
```

### Compiling
Execute this command from the src folder
```bash
  g++ *cpp -o main -lallegro -lallegro_main -lallegro_ttf -lallegro_image -lallegro_font -lallegro_audio -lallegro_acodec  -std=c++11
```

### Launch the game
Execute this command from the src folder
```bash
  chmod +x main && ./main
```

---

## 📜 How to Play

Your objective is to clear all bubbles to advance to the next level. As you progress, collect power-ups to gain extra abilities and survive the challenges.

### Controls
- **Move Left/Right/Up/Down**: Arrow keys (Use **Up** and **Down** keys to navigate stairs)
- **Shoot**: `Spacebar`
- **Pause the Game**: `ESC`
- **Mute/Unmute Audio**: `M`
- **Toggle Fullscreen Mode**: `F`

## 🎥 Gameplay Video
Check out the gameplay in the video below:

[![Gameplay Video](http://img.youtube.com/vi/lyXhlEFHASY/0.jpg)](https://www.youtube.com/watch?v=lyXhlEFHASY)
