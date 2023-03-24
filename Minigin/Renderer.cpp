#pragma warning(push)
#pragma warning (disable: 4244)

 // used code for the imGUI from other students 

#include <stdexcept>
#include "Renderer.h"

#include <chrono>
#include <iostream>

#include "imgui.h"

#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include "imgui_plot.h"
#include "SceneManager.h"
#include "Texture2D.h"



struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	~GameObject3DAlt()
	{
		delete transform;
	}
	Transform* transform{};
	int ID{};
};

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}


void GenerateDataTrashCash(int& size ,int steps, std::vector<float>& samples)
{
	const int bufferSize{ 10000000 };
	std::pmr::vector<int>buffer{};
	buffer.resize(bufferSize);
	fill_n(buffer.begin(), bufferSize, 100);
	long stepSize = 1;
	std::vector<long long> times{};
	auto start = std::chrono::high_resolution_clock::now();
	for (stepSize = 1; stepSize < (1024 * steps); stepSize *= 2)
	{
		for (int i{}; i < bufferSize; i += stepSize)
		{
			buffer[i] *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto time = duration_cast<std::chrono::microseconds>(end - start).count();
		times.emplace_back(time);
		start = std::chrono::high_resolution_clock::now();
	}
	size = static_cast<int>(times.size());
	for (int i{}; i < size; ++i)
	{
		samples.emplace_back(static_cast<float>(times[i]));
	}
}

void GenerateDataTrashCashGameObject3D(int& size, int , std::vector<float>& samples)
{
	static float data[10]{};
	const int bufferSize{ 1000000 };
	std::vector<GameObject3D*>buffer{};
	buffer.resize(bufferSize);
	std::vector<long long> times{};
	int index{};
	do
	{
		buffer[index] = new GameObject3D();
		buffer[index]->ID = 100;
		++index;
	} while (index < bufferSize);

	int stepSize{};
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i{}; i < bufferSize; i += stepSize)
		{
			buffer[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
		times.emplace_back(elapsedTime);
	}
	size = static_cast<int>(times.size());
	for (int i{}; i < size; ++i)
	{
		samples.emplace_back(static_cast<float>(times[i]));
	}

	for (auto object : buffer)
	{
		delete object;
	}
}

void GenerateDataTrashCashGameObject3DAlt(int& size, int , std::vector<float>& samples)
{
	static float data[10]{};
	const int bufferSize{ 1000000 };
	std::vector<GameObject3DAlt*>buffer{};
	buffer.resize(bufferSize);
	std::vector<long long> times{};
	int index{};
	do
	{
		buffer[index] = new GameObject3DAlt();
		buffer[index]->ID = 100;
		buffer[index]->transform = new Transform();
		++index;
	} while (index < bufferSize);

	int stepSize{};
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i{}; i < bufferSize; i += stepSize)
		{
			buffer[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
		times.emplace_back(elapsedTime);
	}

	size = static_cast<int>(times.size());
	for (int i{}; i < size; ++i)
	{
		data[i] = static_cast<float>(times[i]);
	}

	for (int i{}; i < size; ++i)
	{
		samples.emplace_back(static_cast<float>(times[i]));
	}

	for (auto object : buffer)
	{
		delete object;
	}
}

void RenderStats(float min, float max, const float** data, int values, ImU32* colors, int count = 1)
{
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.ys_list = data;
	conf.values.ys_count = count;
	conf.values.count = values;
	conf.line_thickness = 2.f;
	conf.values.colors = colors;
	conf.scale.min = min;
	conf.scale.max = max;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(250, 100.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);
}

void RenderStats(std::vector<float> data, int values, ImU32& color)
{
	auto minIt = std::min_element(data.begin(), data.end());
	auto maxIt = std::max_element(data.begin(), data.end());
	float min = *minIt;
	float max = *maxIt;

	const float* dataFl[]{ {&data[0]} };
	ImU32 colors[1]{ {color} };

	RenderStats(min, max, dataFl, values, colors);
}

void dae::Renderer::DrawGUI()
{
	DrawPlotForTranshCash();
	DrawPlotForGameObject3D();
}

void dae::Renderer::DrawPlotForTranshCash()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
	static char   u8_v = 1;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImGui::InputScalar("samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_TrashCashSteps = static_cast<int>(u8_v);
	const char* buttonText = "Trash the cache";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_TrashCashSize = 0;
		GenerateDataTrashCash(m_TrashCashSize ,m_TrashCashSteps, m_TrashCashData);
	}

	if (m_TrashCashSize > 0)
	{
		ImU32 colorOrange = { ImColor{195,165,0} };
		RenderStats(m_TrashCashData, m_TrashCashSize, colorOrange);
	}
	ImGui::End();
}

void dae::Renderer::DrawPlotForGameObject3D()
{
	static char   u8_v = 1;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImU32 colorGreen = { ImColor{0,255,0} };
	ImU32 colorAliceBlue = { ImColor{94,97,100} };
	const bool size3DBiggerThan0 = m_TrashCashDataSizeObject3D > 0;
	const bool size3DAltBiggerThan0 = m_TrashCashDataSizeObject3DAlt > 0;


	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);
	ImGui::InputScalar("samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_TrashCashStepsObject3D = static_cast<int>(u8_v);
	const char* buttonText = "Trash the cache with GameObject3D";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_TrashCashDataSizeObject3D = 0;
		GenerateDataTrashCashGameObject3D(m_TrashCashDataSizeObject3D ,m_TrashCashStepsObject3D, m_TrashCashDataObject3D);
	}

	if (size3DBiggerThan0)
	{
		RenderStats(m_TrashCashDataObject3D, m_TrashCashDataSizeObject3D, colorGreen);
	}

	buttonText = "Trash the cache With GameObject3DAlt";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_TrashCashDataSizeObject3DAlt = 0;
		GenerateDataTrashCashGameObject3DAlt(m_TrashCashDataSizeObject3DAlt, m_TrashCashStepsObject3D, m_TrashCashDataObject3DAlt);
	}

	if (size3DAltBiggerThan0)
	{
		RenderStats(m_TrashCashDataObject3DAlt, m_TrashCashDataSizeObject3DAlt, colorAliceBlue);
	}

	if (size3DBiggerThan0 && size3DAltBiggerThan0)
	{
		float min3D = *std::min_element(m_TrashCashDataObject3D.begin(), m_TrashCashDataObject3D.end());
		float max3D = *std::max_element(m_TrashCashDataObject3D.begin(), m_TrashCashDataObject3D.end());
		float min3DAlt = *std::min_element(m_TrashCashDataObject3DAlt.begin(), m_TrashCashDataObject3DAlt.end());
		float max3DAlt = *std::max_element(m_TrashCashDataObject3DAlt.begin(), m_TrashCashDataObject3DAlt.end());

		float min = min3D < min3DAlt ? min3D : min3DAlt;
		float max = max3D > max3DAlt ? max3D : max3DAlt;
		const int totalAllowdArrayValues{ 2 };
		const float* dataFl[totalAllowdArrayValues]{ &m_TrashCashDataObject3D[0],&m_TrashCashDataObject3DAlt[0] };
		ImU32 colors[totalAllowdArrayValues]{ colorGreen,colorAliceBlue };

		RenderStats(min, max, dataFl, 10, colors, 2);
	}
	ImGui::End();
}






void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

}

void dae::Renderer::Render() {

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	DrawGUI();

	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }


#pragma warning(pop)