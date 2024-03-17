void Game::load(const std::string filename_blocks,const std::string filename_coins)
{
  loadBlocks(filename_blocks);
  loadCoins(filename_coins);
  loadEnemies();
}

void Game::loadBlocks(const std::string filename)
{
  /// loads a level from a file
  int file_line = 0;
  int file_index = 0;
  float previous_content = 0;

  number_of_blocks = 0;
  current_level.open(filename);

  while (current_level)
  {
    current_level >> current_level_contents;

    if (file_line == 0)
    {
      // places the player and flag (second line)
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
          std::cout << "something has gone wrong placing the player and flag";
          break;
      }
    }
    else
    {
      switch(file_index)
      {
        case 0:
          number_of_blocks++;
          previous_content = std::stof(current_level_contents);
          file_index++;
          break;
        case 1:
          blocks[file_line - 1].init(previous_content,
                                     std::stof(current_level_contents));
          file_index++;
          break;
        case 2:
          previous_content = std::stof(current_level_contents);
          file_index++;
          break;
        case 3:
          blocks[file_line - 1].setPosition(previous_content,
                                            std::stof(current_level_contents));
          file_index = 0;
          file_line++;
          std::cout << "placed a block \n";
          break;
        default:
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
        number_of_coins++;
        previous_content = std::stof(current_level_contents);
        file_index = 1;
        break;
      case 1:
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
