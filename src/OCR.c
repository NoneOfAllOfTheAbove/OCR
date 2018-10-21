#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

// just for tests
#include <time.h>

#include "NeuralNetwork/NeuralNetwork.h"
#include "Preprocessing/Preprocessing.h"
#include "GUI/DemoGUI.h"
#include "Segmentation/Segmentation.h"

void PrintXORSolutions()
{
	double input1[] = {1, 0};
	double input2[] = {0, 1};
	double input3[] = {1, 1};
	double input4[] = {0, 0};

	printf("[1-0 -> 1]\n");
	Predict(input1);
	printf("[0-1 -> 1]\n");
	Predict(input2);
	printf("[1-1 -> 0]\n");
	Predict(input3);
	printf("[0-0 -> 0]\n");
	Predict(input4);
}

void TrainXOR()
{
	// Prepare XOR expected outuputs according to inputs
	double input1[] = {1, 0};
	double output1[] = {1, 0};
	double input2[] = {0, 1};
	double output2[] = {1, 0};
	double input3[] = {1, 1};
	double output3[] = {0, 1};
	double input4[] = {0, 0};
	double output4[] = {0, 1};

	// Train NN
	srand(time(NULL));
	long t;
	for (int i = 0; i < 150000; i++)
	{
		t = rand() % 4;
		if (t == 0)
		{
			Train(input1, output1);
		}
		if (t == 1)
		{
			Train(input2, output2);
		}
		if (t == 2)
		{
			Train(input3, output3);
		}
		else
		{
			Train(input4, output4);
		}
	}
}

int main(int argc, char** argv)
{
	// ----------------------------------------
	// STEP 1 : IMAGE LOADING AND PREPROCESSING
	// ----------------------------------------

	if(argc != 2) {
		errx(1, "You must start the program with one argument.");
	}

	int imageWidth, imageHeight;

	unsigned char **grayscaleImageMatrix =
		ImageToGrayscale(argv[1], &imageWidth, &imageHeight);
	unsigned char **binarizedImageMatrix =
		GrayscaleToBinarized(grayscaleImageMatrix, imageWidth, imageHeight);

	// -----------------------------
	// STEP 2 : CHARACTERS DETECTION
	// -----------------------------

	//unsigned char *characters = Labelling(binarizedImageMatrix, imageWidth, imageHeight);

	// -------------------------------
	// STEP 3 : CHARACTERS RECOGNITION
	// -------------------------------

	char nnDataPath[] = "docs/nn.data";

	// Solve XOR
	int mode = 0;
	if(mode == 0)
	{
		Start(2, 4, 2);
		printf("\n\n\nBefore training:\n\n");
		PrintXORSolutions();
		TrainXOR();
		printf("\n\n\nAfter training:\n\n");
		PrintXORSolutions();
		Save(nnDataPath);
	} else {
		Start(2, 4, 2);
		Load(nnDataPath);
		printf("\n\n\nPredictions of loaded NN:\n\n");
		PrintXORSolutions();
	}

	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------

	StartDemoGUI(
		imageWidth,
		imageHeight,
		grayscaleImageMatrix,
		binarizedImageMatrix
	);

	return 0;
}
