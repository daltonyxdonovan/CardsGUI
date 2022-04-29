#include <SFML/Graphics.hpp>
#include <iostream>
#include <csv.hpp>
#include <atlstr.h>

//include HWND
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <shobjidl.h> 




using namespace std;
using namespace csv;



const int WIDTH{ 1920 };
const int HEIGHT{ 1080 };
bool mat_teal{ false };
bool mat_green{ false };
bool mat_red{ false };
bool mat_blue{ false };
bool mat_brown{ false };
bool mat_purple{ false };
bool mat_orange{ false };
bool mat_pink{ true };
bool shifting{ false };
bool themed{ false };
int theme_x{ 1920 };
int theme_x_limit{ 1870 };
bool spawned{ false };
int last_added{ -850 };
bool finished_making{ false };
int offset{ 4 };
int closer{ 0 };
int slider{ 0 };
int tickers{ 0 };
string fname;



int main()
{
	wchar_t filename[MAX_PATH];

	OPENFILENAMEW ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = L"CSV Files\0*.csv\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameW(&ofn))
	{
		
		fname = CW2A(filename);
		Sleep(1000);
		
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}

	//wait one second
	


	
	vector<sf::RectangleShape> rects;
	if (finished_making)
		{
			HWND hWnd = GetConsoleWindow();
			ShowWindow(hWnd, SW_HIDE);
		}
	//hide command prompt window
	
	
	vector<int> material_teal;
	material_teal.push_back(0);
	material_teal.push_back(150);
	material_teal.push_back(136);
	vector<int> material_red;
	material_red.push_back(244);
	material_red.push_back(67);
	material_red.push_back(54);
	vector<int> material_blue;
	material_blue.push_back(33);
	material_blue.push_back(150);
	material_blue.push_back(243);
	vector<int> material_green;
	material_green.push_back(76);
	material_green.push_back(175);
	material_green.push_back(80);
	vector<int> material_brown;
	material_brown.push_back(121);
	material_brown.push_back(85);
	material_brown.push_back(72);
	vector<int> material_purple;
	material_purple.push_back(156);
	material_purple.push_back(39);
	material_purple.push_back(176);
	vector<int> material_orange;
	material_orange.push_back(255);
	material_orange.push_back(152);
	material_orange.push_back(0);
	vector<int> material_pink;
	material_pink.push_back(233);
	material_pink.push_back(30);
	material_pink.push_back(99);
	
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Card_test", sf::Style::Fullscreen);

	//set the initial point of the scrollbar
    int scrollbar_pos{ 0 };
	
	
	

	//initialize the png(s)
	sf::Texture card_texture;
    if (!card_texture.loadFromFile("includes/card.png"))
    {
		cout << "Error loading card.png" << endl;
    }
	sf::Texture theme_texture;
	if (!theme_texture.loadFromFile("includes/card_theme.png"))
	{
		cout << "Error loading theme.png" << endl;
	}
	sf::Texture theme_icon_texture;
	if (!theme_icon_texture.loadFromFile("includes/theme_icon.png"))
	{
		cout << "Error loading theme_icon.png" << endl;
	}
    sf::Font font;
	if (!font.loadFromFile("includes/Arial.ttf"))
	{
		cout << "Error loading arial.ttf" << endl;
	}
	sf::Image image;
	if (!image.loadFromFile("includes/eevee.png"))
	{
		cout << "Error loading eevee.png" << endl;
	}
	sf::Texture debug;
	if (!debug.loadFromFile("includes/debug.png"))
		cout << "debug unloaded" << endl;
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	



	//set card_texture smooth
	card_texture.setSmooth(true);
	theme_texture.setSmooth(true);
	theme_icon_texture.setSmooth(true);

	vector<int> card_list;
	vector<int> card_listy;
	vector<int> closing;
	vector<string> woid;
	vector<string> reference_num;
	vector<string> city;
	vector<string> state;
	vector<string> opened;
	vector<string> date_for;
	vector<string> statused;

	
	

	//make fname equal the first file with dataexport in it's name
	
	
	
	
	
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	//find file that contains "dataexport"
	
	

	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			
			row.clear();
			stringstream str(line);
			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";
	for (int i = offset; i < content.size(); i++)
	{
		for (int j = offset; j < content[i].size(); j++)
		{	
			
			card_list.push_back(last_added);
			card_listy.push_back(50);
			last_added = last_added + 225;
			
			
		}
	}
	for (int i = 0; i < content.size(); i++)
		closing.push_back(0);


	





    while (window.isOpen())
    {	
		int mouse_x{ sf::Mouse::getPosition().x }, mouse_y{ sf::Mouse::getPosition().y };
		
		
		
        if (scrollbar_pos > 0)
            scrollbar_pos = 0;

		
		if (mat_teal)
			window.clear(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
		else if (mat_blue)
			window.clear(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
		else if (mat_green)
			window.clear(sf::Color(material_green[0], material_green[1], material_green[2]));
		else if (mat_red)
			window.clear(sf::Color(material_red[0], material_red[1], material_red[2]));
		else if (mat_brown)
			window.clear(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
		else if (mat_purple)
			window.clear(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
		else if (mat_orange)
			window.clear(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
		else if (mat_pink)
			window.clear(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
		else
			window.clear(sf::Color(76, 76, 76));

		//cards loop begins
        for (int i = offset; i < content.size(); i++)
        {	
			
			
			int spawn{ scrollbar_pos + card_list[i] - 250 };
			int spawn_limit{ scrollbar_pos + card_list[i] };
			spawned = true;
		    sf::Sprite card_sprite;
			card_sprite.setTexture(card_texture);
			
			card_sprite.setPosition(card_listy[i], scrollbar_pos + card_list[i]);
			window.draw(card_sprite);

			sf::RectangleShape seperator(sf::Vector2f(500, 5));
			if (mat_teal)
				seperator.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (mat_blue)
				seperator.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (mat_green)
				seperator.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (mat_red)
				seperator.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (mat_brown)
				seperator.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (mat_purple)
				seperator.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (mat_orange)
				seperator.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (mat_pink)
				seperator.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else
				seperator.setFillColor(sf::Color(76, 76, 76));
			seperator.setPosition(card_sprite.getPosition().x + 670, card_sprite.getPosition().y + 60);
			window.draw(seperator);


//maintech num
			sf::Text mt_num;
			mt_num.setFont(font);
			//setString to the first item in the row in file
			
			mt_num.setString(content[i][0]);
			mt_num.setCharacterSize(50);
			//center mt_num in card_sprite
			mt_num.setPosition(card_sprite.getPosition().x - slider + (card_sprite.getGlobalBounds().width/2) - (mt_num.getGlobalBounds().width/2), card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height/2) - ((mt_num.getGlobalBounds().height/2)+90));
			
			if (mat_teal)
				mt_num.setFillColor(sf::Color(material_teal[0],material_teal[1],material_teal[2]));
			else if (mat_blue)
				mt_num.setFillColor(sf::Color(material_blue[0],material_blue[1],material_blue[2]));
			else if (mat_green)
				mt_num.setFillColor(sf::Color(material_green[0],material_green[1],material_green[2]));
			else if (mat_red)
				mt_num.setFillColor(sf::Color(material_red[0],material_red[1],material_red[2]));
			else if (mat_brown)
				mt_num.setFillColor(sf::Color(material_brown[0],material_brown[1],material_brown[2]));
			else if (mat_purple)
				mt_num.setFillColor(sf::Color(material_purple[0],material_purple[1],material_purple[2]));
			else if (mat_orange)
				mt_num.setFillColor(sf::Color(material_orange[0],material_orange[1],material_orange[2]));
			else if (mat_pink)
				mt_num.setFillColor(sf::Color(material_pink[0],material_pink[1],material_pink[2]));
			else
				mt_num.setFillColor(sf::Color(76, 76, 76));
			window.draw(mt_num);
//title/task#
			sf::Text title;
			title.setFont(font);
			title.setString(content[i][2]);
			title.setCharacterSize(50);
			//center title in card_sprite
			title.setPosition(card_sprite.getPosition().x + 30 - slider, card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height/2) - ((title.getGlobalBounds().height/2)) - 20);
			if (mat_teal)
				title.setFillColor(sf::Color(material_teal[0],material_teal[1],material_teal[2]));
			else if (mat_blue)
				title.setFillColor(sf::Color(material_blue[0],material_blue[1],material_blue[2]));
			else if (mat_green)
				title.setFillColor(sf::Color(material_green[0],material_green[1],material_green[2]));
			else if (mat_red)
				title.setFillColor(sf::Color(material_red[0],material_red[1],material_red[2]));
			else if (mat_brown)
				title.setFillColor(sf::Color(material_brown[0],material_brown[1],material_brown[2]));
			else if (mat_purple)
				title.setFillColor(sf::Color(material_purple[0],material_purple[1],material_purple[2]));
			else if (mat_orange)
				title.setFillColor(sf::Color(material_orange[0],material_orange[1],material_orange[2]));
			else if (mat_pink)
				title.setFillColor(sf::Color(material_pink[0],material_pink[1],material_pink[2]));
			else
				title.setFillColor(sf::Color(76, 76, 76));
			
			window.draw(title);
			
//city, and state
			sf::Text city_state;
			city_state.setFont(font);
			city_state.setString(content[i][6] + "\n" + content[i][7]);
			city_state.setCharacterSize(50);
			city_state.setPosition((card_sprite.getPosition().x-100 - slider) + card_sprite.getGlobalBounds().width - (city_state.getGlobalBounds().width), card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height / 2) - ((city_state.getGlobalBounds().height / 2)) - 20);
			if (mat_teal)
				city_state.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (mat_blue)
				city_state.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (mat_green)
				city_state.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (mat_red)
				city_state.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (mat_brown)
				city_state.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (mat_purple)
				city_state.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (mat_orange)
				city_state.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (mat_pink)
				city_state.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else
				city_state.setFillColor(sf::Color(76, 76, 76));
			window.draw(city_state);
			
//status
			sf::Text status;
			status.setFont(font);
			status.setString("Opened on: " + content[i][12]);
			status.setCharacterSize(30);
			//center status in card_sprite on right side
			status.setPosition(card_sprite.getPosition().x - slider + card_sprite.getGlobalBounds().width - (status.getGlobalBounds().width + 730), card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height/2) - ((status.getGlobalBounds().height/2)) - 20);
			if (mat_teal)
				status.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (mat_blue)
				status.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (mat_green)
				status.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (mat_red)
				status.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (mat_brown)
				status.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (mat_purple)
				status.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (mat_orange)
				status.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (mat_pink)
				status.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else
				status.setFillColor(sf::Color(76, 76, 76));
			window.draw(status);
			
//held and date
			sf::Text held_date;
			held_date.setFont(font);
			if (content[i][1] == "HF")
			{
				held_date.setString("Date set for: " + content[i][13]);
				held_date.setCharacterSize(30);
				held_date.setPosition(card_sprite.getPosition().x - slider + card_sprite.getGlobalBounds().width - (held_date.getGlobalBounds().width + 730), card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height / 2) - ((held_date.getGlobalBounds().height / 2)) + 20);
				if (mat_teal)
					held_date.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
				else if (mat_blue)
					held_date.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
				else if (mat_green)
					held_date.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
				else if (mat_red)
					held_date.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
				else if (mat_brown)
					held_date.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
				else if (mat_purple)
					held_date.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
				else if (mat_orange)
					held_date.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
				else if (mat_pink)
					held_date.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
				else
					held_date.setFillColor(sf::Color(76, 76, 76));
				window.draw(held_date);
			}
				

			sf::RectangleShape checkmark1(sf::Vector2f(20, 4));
			checkmark1.setRotation(45);
			checkmark1.setPosition(card_sprite.getPosition().x + 10 - slider, card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height / 2) - ((title.getGlobalBounds().height / 2)) - 60);
			if (mat_teal)
				checkmark1.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (mat_blue)
				checkmark1.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (mat_green)
				checkmark1.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (mat_red)
				checkmark1.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (mat_brown)
				checkmark1.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (mat_purple)
				checkmark1.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (mat_orange)
				checkmark1.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (mat_pink)
				checkmark1.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else
				checkmark1.setFillColor(sf::Color(76, 76, 76));
			window.draw(checkmark1);

			sf::RectangleShape checkmark2(sf::Vector2f(40, 4));
			checkmark2.setRotation(-45);
			checkmark2.setPosition(card_sprite.getPosition().x + 20 - slider, card_sprite.getPosition().y + (card_sprite.getGlobalBounds().height / 2) - ((title.getGlobalBounds().height / 2)) - 46);
			if (mat_teal)
				checkmark2.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (mat_blue)
				checkmark2.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (mat_green)
				checkmark2.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (mat_red)
				checkmark2.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (mat_brown)
				checkmark2.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (mat_purple)
				checkmark2.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (mat_orange)
				checkmark2.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (mat_pink)
				checkmark2.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else
				checkmark2.setFillColor(sf::Color(76, 76, 76));
			window.draw(checkmark2);

			sf::Sprite debuggers;
			debuggers.setTexture(debug);
			debuggers.setPosition(card_sprite.getPosition().x + 7 - slider, card_sprite.getPosition().y + 10);
			window.draw(debuggers);
			//make a rect for debuggers
			sf::RectangleShape debugsy;
			debugsy.setPosition(card_sprite.getPosition().x + 7 - slider, card_sprite.getPosition().y + 10);
			debugsy.setSize(sf::Vector2f(50, 50));
			rects.push_back(debugsy);
			
			//check if mouse intersects with debuggers
			
			if (debugsy.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{	
					cout << "clicked a debug" << endl;
					closing[i] = 1;
				}
			}
			if (closing[i] == 1)
			{

				card_listy[i] -= 100;
				
				if (card_listy[i] < -1999)
				{
					tickers += 1;
					for (int j = i; j < card_listy.size(); j++)
					{

						card_list[j] -= 25;

					}
					if (tickers == 9)
					{
							//delete entire card and data from csv
						
						closing[i] = 0;
						tickers = 0;
					}
					
					
						
				}
				
				
					
			}
			
			
			
        }
		
		sf::Sprite theme_icon;
		theme_icon.setTexture(theme_icon_texture);
		theme_icon.setPosition(1860, 5);
		window.draw(theme_icon);
		
		sf::Sprite theme_sprite;
		theme_sprite.setTexture(theme_texture);
		theme_sprite.setPosition(sf::Vector2f(theme_x, 0));
		window.draw(theme_sprite);
		
		if (themed)
			if (theme_x > theme_x_limit)
				theme_x -= 5;
		if (!themed)
			if (theme_x < 1920)
				theme_x += 5;
		sf::Text versions;
		versions.setFont(font);
		versions.setPosition(5, scrollbar_pos + 5);
		versions.setFillColor(sf::Color::White);
		versions.setString("daltonyx-v0.99");
		versions.setCharacterSize(15);
		window.draw(versions);
		
		for (int k{ 0 }; k < 9; k++)
		{
			sf::RectangleShape theme_square;
			theme_square.setSize(sf::Vector2f(25, 25));
			theme_square.setPosition(sf::Vector2f(theme_x+12, k*115+70));
			if (k == 0)
				theme_square.setFillColor(sf::Color(material_blue[0], material_blue[1], material_blue[2]));
			else if (k == 1)
				theme_square.setFillColor(sf::Color(material_green[0], material_green[1], material_green[2]));
			else if (k == 2)
				theme_square.setFillColor(sf::Color(material_red[0], material_red[1], material_red[2]));
			else if (k == 3)
				theme_square.setFillColor(sf::Color(material_brown[0], material_brown[1], material_brown[2]));
			else if (k == 4)
				theme_square.setFillColor(sf::Color(material_purple[0], material_purple[1], material_purple[2]));
			else if (k == 5)
				theme_square.setFillColor(sf::Color(material_orange[0], material_orange[1], material_orange[2]));
			else if (k == 6)
				theme_square.setFillColor(sf::Color(material_pink[0], material_pink[1], material_pink[2]));
			else if (k == 7)
				theme_square.setFillColor(sf::Color(material_teal[0], material_teal[1], material_teal[2]));
			else if (k == 8)
				theme_square.setFillColor(sf::Color(76, 76, 76));
			theme_square.setOutlineColor(sf::Color(76,76,76));
			theme_square.setOutlineThickness(1);
			window.draw(theme_square);
			
			
		}
		

		

		
        window.display();
		window.setFramerateLimit(60);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (scrollbar_pos <= 0)
				{
					if (event.mouseWheelScroll.delta > 0)
					{
						scrollbar_pos += 50;
					}
					else
					{
						scrollbar_pos -= 50;
					}
				}

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int mouse_x{ event.mouseButton.x };
					int mouse_y{ event.mouseButton.y };
					if (themed)
					{
						if (mouse_x > 1860 && mouse_x < 1910 && mouse_y > 5 && mouse_y < 50)
							themed = false;
						if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 70 && mouse_y < 95)
						{
							if (!mat_blue)
							{
								mat_teal = false;
								mat_green = false;
								mat_red = false;
								mat_blue = true;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 185 && mouse_y < 210)
						{
							if (!mat_green)
							{
								mat_green = true;
								mat_teal = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 300 && mouse_y < 325)
						{
							if (!mat_red)
							{
								mat_red = true;
								mat_teal = false;
								mat_green = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 415 && mouse_y < 440)
						{
							if (!mat_brown)
							{
								mat_brown = true;
								mat_teal = false;
								mat_green = false;
								mat_red = false;
								mat_blue = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 530 && mouse_y < 555)
						{
							if (!mat_purple)
							{
								mat_purple = true;
								mat_teal = false;
								mat_green = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 645 && mouse_y < 670)
						{
							if (!mat_orange)
							{
								mat_orange = true;
								mat_teal = false;
								mat_green = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 760 && mouse_y < 785)
						{
							if (!mat_pink)
							{
								mat_pink = true;
								mat_teal = false;
								mat_green = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 875 && mouse_y < 900)
						{
							if (!mat_teal)
							{
								mat_teal = true;
								mat_green = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
						else if (mouse_x > 1880 && mouse_x < 1905 && mouse_y > 990 && mouse_y < 1015)
						{
							if (mat_blue || mat_green || mat_orange || mat_pink || mat_brown || mat_red || mat_purple || mat_teal)
							{
								mat_green = false;
								mat_teal = false;
								mat_red = false;
								mat_blue = false;
								mat_brown = false;
								mat_purple = false;
								mat_orange = false;
								mat_pink = false;
								themed = false;
							}
						}
					}
					if (!themed)
					{
						if (mouse_x > 1860 && mouse_x < 1910 && mouse_y > 5 && mouse_y < 50)
							themed = true;
						
						
						
						
						
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
    }

    return 0;
}