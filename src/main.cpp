#include <LIDAR/LidarEngine.h>
#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, const char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("WindowX", 800, 600, 0);
  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, "");
  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  
  LidarEngine lidarEngine(500);
  WorldObject worldObject(glm::vec3(50.0f, 34.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.0f), false);
  
  lidarEngine.addObject(worldObject);
  lidarEngine.setCameraPosition(glm::vec3(800.0f, 600.0f, 0.0f));
  
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    SDL_RenderClear(renderer);

    // Render code here
    lidarEngine.fireRays(false);
    lidarEngine.renderMarkers(renderer);

    SDL_SetRenderDrawColor(renderer, 155, 100, 0, 255);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

/*
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lidar Engine");

    if (!gladLoadGL()) {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    enginePtr = new LidarEngine(5000);
    enginePtr->setCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    enginePtr->addObject(WorldObject(glm::vec3(0.0f, 0.0f, -0.5f),
glm::vec3(1.0f, 1.0f, 1.0f), false));
    enginePtr->addObject(WorldObject(glm::vec3(2.0f, 0.0f, -1.0f),
glm::vec3(1.0f, 1.0f, 1.0f), true));

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();

    delete enginePtr;
    return 0;
}
*/
