#include "Game.hpp"

int main() {
	try
	{
		Game game;
		game.run();
	}
	catch (Exception & e)
	{
		std::cout << "Error occured: " << e.getMessage() << std::endl << std::endl << "Please contact with developers." << std::endl << "Press any key.";
		std::cin.ignore();
	}
	catch (...)
	{
		std::cout << "Unknown error occured. Please contact with developers." << std::endl << "Press any key.";
		std::cin.ignore();
	}
	return 0;
}