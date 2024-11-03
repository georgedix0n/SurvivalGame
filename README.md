# Unreal Engine 5 Multiplayer Survival Game

This repository contains a fully networked, multiplayer survival game built in Unreal Engine 5. This project integrates a comprehensive feature set suitable for survival gameplay, with a focus on responsive animations, user-friendly interfaces, and immersive interactions.

### How To Run
- Open uproject file from UE5, it should open `TestingLevel.umap` by default. If not, it is located in `Content/Maps`.
- Run the game as client and set number of players to 2, to test combat system.
  
## Features

### Player Movement
- **Smooth Movement Mechanics and Animations:** Includes sprinting, crouching, and walking animations for dynamic, realistic player movement.
- **Fully Networked Gameplay:** All player actions and interactions are synchronized across the network for a seamless multiplayer experience.

### Inventory System
- **Interactive Inventory UI:** Allows players to view, organize, and manage inventory items with a responsive and easy-to-use interface.
- **Looting System:** Players can acquire items from loot chests, fallen enemies, and the environment.
- **Wearable Equipment:** Equipable clothing and gear that dynamically update the character's appearance.
- **Holdable and Usable Weapons:** Weapons can be equipped and utilized in gameplay, including shooting mechanics, and interactively looting from other players.

### Combat System
- **Damage Mechanics:** Player health management, damage calculation, and feedback effects.
- **Blood Animations:** Visual feedback for player and enemy damage to enhance gameplay realism.
- **Interaction Components with UI:** Visual indicators and UI prompts for interactive items, enhancing player awareness and engagement.

### Game Overlay
- **Heads-Up Display (HUD):** Includes a compass, crosshair, and game version indicator for enhanced user experience.

### To do
- Fix bug in UI leading to oversized/ mis-aligned inventory items
- Build full map, at the minute project only includes a test arena
- Remove unnecessary/ unused files from repo
