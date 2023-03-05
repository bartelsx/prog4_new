#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "EllipticalMoveComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FPSCalcComponent.h"
#include "TextureComponent.h"

	dae::Scene* pScene;

void load()
{
	pScene = &dae::SceneManager::GetInstance().CreateScene("Demo");
	std::shared_ptr<dae::GameObject> titleObj;
	std::shared_ptr<dae::GameObject> backgroundObj;
	std::shared_ptr<dae::GameObject> logoObj;
	std::shared_ptr<dae::GameObject> pacmanObj;
	std::shared_ptr<dae::GameObject> ghostObj;
	std::shared_ptr<dae::GameObject> fpsObj;


	titleObj = std::make_shared<dae::GameObject>();
	backgroundObj = std::make_shared<dae::GameObject>();
	logoObj = std::make_shared<dae::GameObject>();
	pacmanObj = std::make_shared<dae::GameObject>();
	ghostObj = std::make_shared<dae::GameObject>();
	fpsObj = std::make_shared<dae::GameObject>();

	auto background = std::make_shared<TextureComponent>();
	background->SetTexture("background.tga");
	backgroundObj->AddComponent(background);
	background->SetOwner(backgroundObj); //TODO: should be done inside AddComponent


	auto logo = std::make_shared<TextureComponent>();
	logo->SetTexture("logo.tga");
	logoObj->AddComponent(logo);
	logo->SetOwner(logoObj); //TODO: should be done inside AddComponent
	logoObj->SetPosition( 216, 180);



	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<dae::TextComponent>( "Programming 4 Assignment", font);
	titleObj->AddComponent(textComponent);
	textComponent->SetOwner(titleObj); //TODO: should be done inside AddComponent
	titleObj->SetPosition( 80, 20);


	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsCounter = std::make_shared<dae::FPSCalcComponent>();
	fpsObj->AddComponent(fpsCounter);
	fpsCounter->SetOwner(fpsObj); //TODO: should be done inside AddComponent
	auto fpsText = std::make_shared<dae::TextComponent>(fpsCounter, fontFPS);
	fpsObj->SetPosition( 10, 15);
	fpsText->SetColor({ 255,255,0 });
	fpsObj->AddComponent(fpsText);
	fpsText->SetOwner(fpsObj); //TODO: should be done inside AddComponent

	auto pacmanMoveComp = std::make_shared<dae::EllipticalMoveComponent>(200.f, 50.f,10.f);
	pacmanMoveComp->SetCenter({ 320,320 });
	pacmanMoveComp->SetOwner(pacmanObj);
	pacmanObj->AddComponent(pacmanMoveComp);//TODO: should be done inside AddComponent

	auto pacmanComp = std::make_shared<TextureComponent>();
	pacmanComp->SetTexture("pacman.png");
	pacmanObj->AddComponent(pacmanComp);
	pacmanComp->SetOwner(pacmanObj); //TODO: should be done inside AddComponent


	auto ghostMoveComp = std::make_shared<dae::EllipticalMoveComponent>(30.f, 2.f);
	ghostMoveComp->SetOwner(ghostObj);
	ghostObj->AddComponent(ghostMoveComp);//TODO: should be done inside AddComponent

	auto ghostTextureComp = std::make_shared<TextureComponent>();
	ghostTextureComp->SetTexture("ghost-pink.png");
	ghostObj->AddComponent(ghostTextureComp);
	ghostTextureComp->SetOwner(ghostObj); //TODO: should be done inside AddComponent
	//ghostObj->SetPosition(34,0);

	ghostObj->SetParent(pacmanObj);

	pScene->Add(backgroundObj);
	pScene->Add(titleObj);
	pScene->Add(logoObj);
	pScene->Add(pacmanObj);
	pScene->Add(ghostObj);
	pScene->Add(fpsObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	//TODO: Ask Alex/Tom: I needed to add this code to prevent memory-leaks that (IMHO) are due to circular references (gameObj contains a shared pointer to component,
	//      component contains a shared pointer to gameObj, so none of the shared pointers have a reference count == 0 and don't delete the object they are pointing to
	for(auto obj : pScene->GetAllObjects())
	{
		while (obj->GetComponentCount())
		{
			obj->GetComponent(0)->SetOwner(nullptr);
			obj->RemoveComponent(0);
		}
	}
    return 0;
}