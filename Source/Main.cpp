#include "Renderer.h"
#include "Framebuffer.h"
#include "Object.h"
#include "Sphere.h"
#include "Scene.h"
#include <iostream>
#include "Camera.h"
int main() {
	constexpr int SCREEN_WIDTH = 1280;
	constexpr int SCREEN_HEIGHT = 720;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	

	float aspectRatio = framebuffer.width / framebuffer.height;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene; // after camera creation/initialization
	color3_t color1{ 0,0,1 };
	color3_t color2{ 1,0,0 };
	scene.SetSky(color1, color2);
	// update frame buffer, copy buffer pixels to texture
	framebuffer.Update();

	std::unique_ptr<Object> sphere = std::make_unique<Sphere>(glm::vec3{ -1, -3, -2 }, 2.0f, color3_t{ 1, 0, 0 });
	std::unique_ptr<Object> sphere2 = std::make_unique<Sphere>(glm::vec3{ 2, 1, -5 }, 2.0f, color3_t{ 1, 1, 0 });
	scene.AddObject(std::move(sphere));
	scene.AddObject(std::move(sphere2));

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

		
		scene.Render(framebuffer, camera);	

		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}