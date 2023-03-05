#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FPSCalcComponent.h"
#include "TextureComponent.h"


void load()
{
	

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto gameObj = std::make_shared<dae::GameObject>();

	auto background = std::make_shared<TextureComponent>();
	background->SetTexture("background.tga");
	gameObj->AddComponent(background);


	auto logo = std::make_shared<TextureComponent>();
	logo->SetTexture("logo.tga");
	gameObj->AddComponent(logo);
	logo->SetPosition({ 216, 180, 0 });


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<dae::TextComponent>( "Programming 4 Assignment", font);
	gameObj->AddComponent(textComponent);
	textComponent->SetPosition({ 80, 20, 0 });


	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsCounter = std::make_shared<dae::FPSCalcComponent>();
	gameObj->AddComponent(fpsCounter);
	auto fpsText = std::make_shared<dae::TextComponent>(fpsCounter, fontFPS);
	fpsText->SetPosition({ 10, 15, 0 });
	fpsText->SetColor({ 255,255,0 });
	gameObj->AddComponent(fpsText);

	scene.Add(gameObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}