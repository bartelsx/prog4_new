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

Hence, the _augmented reusability_ is realized by prefering _composition over inheritance_.

For instance, in the Pacman game, there is a bonus pickup that appears at some point and stays on the screen for a few seconds. When visible, collisions between pacman and the fruit pickup should be detected. This can be accomplished by first building a CompositeComponent that holds the fruit's behavior when it's active: 

```cpp
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

```cpp
	//Combine in StateComp
	auto fruitStateComp = StateComponent::Create();
	fruitStateComp->Set(EventType::DISABLE_FRUIT, BaseComponent::Empty()); //nothing to show
	fruitStateComp->Set(EventType::ENABLE_FRUIT, activeFruitComp);
	fruitStateComp->Set(EventType::FRUIT_PICKUP, BaseComponent::Empty());

```

This sets up a 'mini' state machine that will switch to desired state when Events are received.

# Some important classes in (this extended version of) Minigin

## GameObject

This is the basis for each (independent) element on the scene. A GameObject has a location, calculates transformations and can be part of an hierarchy by adding child GameObjects. 

GameObjects can hold other GameObjects that are positioned relative to their parent.

GameObjects can also hold Components that help in the Update() and Render() cycles and thus determine the behavior of the GameObject.

The GameObject is final, so other objects can't inherit from GameObject. Different behavior can be accomplished by adding different components to a GameObject.

## BaseComponent

This is a base class for other Component implementations.

Components help in the Update() and Render() cycle and can, when correctly combined, give relatively complex behavior to GameObjects.

All components hold a (shared) pointer to the GameObject that owns them.

## StateComponent

As described above, this class switches the active Component when it receives an Event. The Update() and Render() calls are only relayed to the active component. The non-active components do not receive those calls

## Collision component

The collision component will detect a collision between its owner (a GameObject) and one of its 'watched' objects. When the two object collide, a given Event will be fired.

## Texture component

The TextureComponent will render a given Texture at the location of its owner.

## DelayedEventComponent

The DelayedEventComponent will listen (being an Observer) for a given Event, and will then publish another event after a configured delay.

## MoveComponent

Given a speed and direction, the MoveComponent will calculate the next position of its owner in each Update() cycle.

## TextComponent

The TextComponent renders text on the Scene. Text, Font and Color can be set.

## GoToComponent

The GoToComponent immediately changes the position of its owner, not taking speed or direction into account. (e.g. in Pacman, the ghost revert to their spawn location each time pacman is hit)

## EditBoxComponent

EditBoxComponent allows the user to type some text (e.g. the users name for highscore list)

## TriggerComponent

The TriggerComponent will Execute() a command when a given Event is published.

## Command

The command is a baseclass for other commands. Each command has an Execute() and a Release() method, typically executed when a key is pressed (Execute) or released (Release).

But Commands are also used to bind Controller buttons or thumb sticks to certain actions.

A command can be considered the Object Oriented Equivalent of a callback function.

## MoveCommand

The MoveCommand will set the speed and direction of the MoveComponent it is bound to, when a key is pressed or a controller input is received.

## ControllerInputHandler and KeyboardInputHandler

These classes (Singleton) can be used to bind Keyboard events or Controller events to Commands.

## EventManager / Event / EventWithPayload<T>

The EventManager holds a queue of events that will be Processed after the current Update() and Render() cycles. Events can be published from anywhere in the code by use of one of the Publish overloads.

Events can cary some data (see the templated EventWithPayload class), e.g. a pointer to the owning GameObject of the Component that Published the event.

## SoundSystem

The SoundSystem class can play AudioClips on a separate Thread.

