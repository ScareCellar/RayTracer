#include "Renderer.h"
#include "Framebuffer.h"
#include "Object.h"
#include "Sphere.h"
#include "Scene.h"
#include "Material.h"
#include "Random.h"
#include "Camera.h"
#include <iostream>
#include <memory>
int main() {
	constexpr int SCREEN_WIDTH = 1280;
	constexpr int SCREEN_HEIGHT = 720;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	float aspectRatio = framebuffer.width / (float)framebuffer.height;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene; // after camera creation/initialization
	color3_t color1{ 0,0,1 };
	color3_t color2{ 1,0,0 };
	scene.SetSky(color1, color2);
	// update frame buffer, copy buffer pixels to texture
	framebuffer.Update();

	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::shared_ptr<Material> materials[] = {red, green, blue, light, metal};

	for (int i = 0; i < 15; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });
		int numMaterials = (sizeof(materials) / sizeof(materials[0])) - 1;

		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(Transform{ position }, random::getReal(0.2f, 1.0f), materials[random::getInt(numMaterials)]);
		scene.AddObject(std::move(sphere));
	}

	/*std::unique_ptr<Object> sphere = std::make_unique<Sphere>(glm::vec3{ -1, -3, -2 }, 2.0f, color3_t{ 1, 0, 0 });
	std::unique_ptr<Object> sphere2 = std::make_unique<Sphere>(glm::vec3{ 2, 1, -5 }, 2.0f, color3_t{ 1, 1, 0 });
	scene.AddObject(std::move(sphere));
	scene.AddObject(std::move(sphere2));*/

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		
		scene.Render(framebuffer, camera, 10);	

		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}