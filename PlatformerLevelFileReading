// this code was designed to import the layouts of levels of a platformer game from text files as an alternative to hard-coding them

void Game::load(const std::string filename_blocks,const std::string filename_coins)
{
  // run the subroutines that load the parts of the level
  loadBlocks(filename_blocks);
  loadCoins(filename_coins);
}

void Game::loadBlocks(const std::string filename)
{
  // loads a level from a file
  int file_line = 0;
  int file_index = 0;
  float previous_content = 0;

  // each line is numbers seperated by spaces
  // file_line is the current line we're looking at
  // file index is the current number within the line we're looking at

  number_of_blocks = 0;
  // open the text file
  current_level.open(filename);

  while (current_level)
  {
    current_level >> current_level_contents;

    // the first line of the text file is ordered "Flag's X, Flag's Y, Player's X, Player's Y"
    if (file_line == 0)
    {
      switch(file_index)
      {
        case 0:
          flag_x = std::stof(current_level_contents);
          file_index++;
          break;
        case 1:
          flag_y = std::stof(current_level_contents);
          file_index++;
          break;
        case 2:
          player_x = std::stof(current_level_contents);
          file_index++;
          break;
        case 3:
          player_y = std::stof(current_level_contents);
          file_index = 0;
          file_line++;
          std::cout << "placed the flag and player \n";
          break;
        default:
          // there should only be four numbers on the first line of the level file
          std::cout << "something has gone wrong placing the player and flag";
          break;
      }
    }
    else
    {

      // every line after the first describes a block ordered "Block's X Scale, Block's Y Scale, Block's X Position, Block's Y Position"

      switch(file_index)
      {
        case 0:
          // storing the first number of the line into previous content ready to be used to init the block

          number_of_blocks++;
          previous_content = std::stof(current_level_contents);
          file_index++;
          break;
        case 1:
          // using previous content (which contains the X scale) and the Y scale, the block can now be instantiated

          blocks[file_line - 1].init(previous_content,
                                     std::stof(current_level_contents));
          file_index++;
          break;
        case 2:
          // now storing the third number of the line in previous content to use when setting the position of the block

          previous_content = std::stof(current_level_contents);
          file_index++;
          break;
        case 3:
          // set the position of the block using previous content (which contains the X position) and the Y position, the block's position can be correctly set
          
          blocks[file_line - 1].setPosition(previous_content,
                                            std::stof(current_level_contents));
          file_index = 0;
          file_line++;
          std::cout << "placed a block \n";
          break;
        default:
          // should only be four numbers in a line
          
          std::cout << "something has broken when setting up blocks";
          break;
      }
    }
  }
  std::cout << "done blocks \n";
  current_level.close();
  std::cout << "file closed\n";

}

void Game::loadCoins(std::string filename)
{
  // Coins are pulled from a seperate file to blocks where each line is two numbers seperated by a space, the X position and then the Y position

  int file_line = 0;
  int file_index = 0;
  float previous_content = 0;

  number_of_coins = 0;
  current_level.open(filename);

  while (current_level)
  {
    current_level >> current_level_contents;
    switch(file_index)
    {
      case 0:
        // store the X position in previous_content for now

        number_of_coins++;
        previous_content = std::stof(current_level_contents);
        file_index = 1;
        break;
      case 1:
        // use the X position from previous_content and the Y position to correctly place the coin
      
        coins[file_line].init();
        coins[file_line].setPosition(previous_content,
                                     std::stof(current_level_contents));
        coins[file_line].setVisibility(true);
        file_index = 0;
        file_line++;
        std::cout << "placed coin\n";
        break;
    }
  }

  std::cout << "done placing\n";
  current_level.close();
  std::cout << "file closed\n";
}
