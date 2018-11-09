#include <stdio.h>
#include <SDL2/SDL.h>

#include "../Preprocessing/Preprocessing.h"
#include "../Segmentation/Segmentation.h"

void WaitSDL()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	while(event.type != SDL_KEYDOWN || event.key.keysym.sym != SDLK_RETURN)
	{
		SDL_PollEvent(&event);
	}
}

void DrawMatrix(SDL_Renderer *renderer, Image image)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			int color = 0;
			if(image.binarized[y][x] == 0)
			{
				color = 255;
			}
			SDL_SetRenderDrawColor(renderer, color, color, color, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	//SDL_RenderPresent(renderer);
}

void StartDemoGUI(Image image, Text text)
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(image.width, image.height, 0, &window, &renderer);

	DrawMatrix(renderer, image);
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		// Paragraphs
		Paragraph paragraph = text.paragraphs[i];
		SDL_Rect rect;
		rect.x = paragraph.x;
		rect.y = paragraph.y;
		rect.w = paragraph.width;
		rect.h = paragraph.height;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);

		// Lines
		for(int j = 0; j < paragraph.numberOfLines; j++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(
					renderer,
					paragraph.x,
					paragraph.lines[j].y2,
					paragraph.x + paragraph.width,
					paragraph.lines[j].y2
			);
			SDL_RenderDrawLine(
					renderer,
					paragraph.x,
					paragraph.lines[j].y1,
					paragraph.x + paragraph.width,
					paragraph.lines[j].y1
			);

			for(int k = 0; k < paragraph.lines[j].numberOfCharacters; k++)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				Character c = paragraph.lines[j].characters[k];
				SDL_Rect rect;
				rect.x = c.x1;
				rect.y = c.y1;
				rect.w = c.x2 - c.x1;
				rect.h = c.y2 - c.y1;
				SDL_RenderDrawRect(renderer, &rect);
			}

		}
	}
	SDL_RenderPresent(renderer);

	WaitSDL();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
