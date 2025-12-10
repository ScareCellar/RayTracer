#include "Renderer.h"
#include "Framebuffer.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
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
	camera.SetView({ 0, 2, 5 }, { 0, 0, 0 });

	Scene scene;

	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f, 0.5f, 0.5f));
	scene.AddObject(std::make_unique<Plane>(Transform{ { 0.0f, 0.0f, 0.0f } }, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			glm::vec3 position(a + 0.9f * random::getReal(), 0.2f, b + 0.9f * random::getReal());

			if ((position - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				std::shared_ptr<Material> sphere_material;

				auto choose_mat = random::getReal();
				if (choose_mat < 0.8f) {
					// diffuse
					auto albedo = HSVtoRGB({ 360.0f * random::getReal(), 1.0f, 1.0f });
					sphere_material = std::make_shared<Lambertian>(albedo);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95f) {
					// metal
					auto albedo = color3_t{ random::getReal(0.5f, 1.0f) };
					auto fuzz = random::getReal(0.5f);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<Dielectric>(HSVtoRGB(360.0f * random::getReal(), 1.0f, 1.0f), 1.0f);
					scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(color3_t{ 1.0f, 1.0f, 1.0f }, 1.5f);
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 0.0f, 1.0f, 0.0f } }, 1.0f, material1));

	auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ -4.0f, 1.0f, 0.0f } }, 1.0f, material2));

	auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
	scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 4.0f, 1.0f, 0.0f } }, 1.0f, material3));

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

		
		scene.Render(framebuffer, camera, 100);	

		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}