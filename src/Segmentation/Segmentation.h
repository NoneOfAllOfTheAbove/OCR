#ifndef SEGMENTATION_H
#define SEGMENTATION_H

typedef struct Character Character;
struct Character
{
	int x;
	int y;
	
	unsigned char **matrix;

	char character;
};

/*typedef struct Word Word;
struct Word
{
	int spacesBefore;

	int numberOfCharacters;
	Character* characters;
};*/

typedef struct Line Line;
struct Line
{
	int y1;
	int y2;

	int numberOfCharacters;
	Character* characters;
};

typedef struct Paragraph Paragraph;
struct Paragraph
{
	int x;
	int y;
	int width;
	int height;

	int numberOfLines;
	Line *lines;
};

typedef struct Text Text;
struct Text
{
	int numberOfParagraphs;
	Paragraph *paragraphs;
};

Text Segmentation(Image);

#endif
