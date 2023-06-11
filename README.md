# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. These patterns need to be applied (when applicable) as well as all (most) [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project. None of the patterns discussed in the course are used (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.

# Extensions I made to the engine

I added: 
- Components 
- Commands
- GameObjects
- Event queue
- Observers
- State

# Design goals

I strived for maximum reusability of the added components. Therefore, there are a lot of small components that do a small task, but can be combined to build complex behavior without the need of adding new classes or even changing existing classes.

For instance, in the Pacman game, there is a bonus pickup that appears at some point and stays on the screen for a few seconds. When on visible, collisions between pacman and the fruit pickup should be detected. This can be accomplished by first building a CompositeComponent that holds the fruit's behavior when it's active: 

```
	//... when active
	auto activeFruitComp = CompositeComponent::Create();
	activeFruitComp->Add(TextureComponent::Create(m_pTextureManager->GetTexture(Textures::FruitTexture)));
	auto collComp = CollisionComponent::Create(EventType::FRUIT_PICKUP, false, false, Settings::CollisionTolerance);
	collComp->AddWatchedObject(pacmanObj);
	activeFruitComp->Add(collComp);

```

This CompositeComponent holds a standard TextureComponent that will render the fruit and a standard CollisionComponent that will fire the FRUIT_PICKUP event when the watched object (pacmanObj) comes too close.

When the fruit bonus is not active, it should not show on screen and should not detect collisions. In fact, it shouldn't do anything. At that moment, an 'empty' component (delivered by BaseComponent::Empty()) should be active.

The active state and the inactive (empty) state can be used to build a StateComponent, that will switch states when certain Events are received:

```
	//Combine in StateComp
	auto fruitStateComp = StateComponent::Create();
	fruitStateComp->Set(EventType::DISABLE_FRUIT, BaseComponent::Empty()); //nothing to show
	fruitStateComp->Set(EventType::ENABLE_FRUIT, activeFruitComp);
	fruitStateComp->Set(EventType::FRUIT_PICKUP, BaseComponent::Empty());

```

This sets up a 'mini' state machine that will switch to desired state when Events are received.
