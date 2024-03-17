// This code is a part of an online multiplayer game where a server script can send and receive arrays of characters from instances of a client script
// By default, there is no unique identifier for which client sent a specific array

void Client::run()
{
  running = true;
  std::thread input_thread ([&]{
                             input(*socket);
  });
  input_thread.detach();

  // receive messages
  while (running && connected)
  {
    char static_buffer[1028];
    while (connected)
    {
      std::size_t received;
      auto status = socket->receive(static_buffer, 1028, received);

      if(status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break;
      }
      else
      {

        // the first two characters of each message indicate the type of order
        // and the signature of the client that sent the order

        if (received < 1028) static_buffer[received] = '\0';

        std::cout << static_buffer << "\n";

        // a = allocate order (interprets the next character as this client's
        // signature if it doesn't have one already)

        if (static_buffer[0] == 'a')
        {
          if (signature == 'n')
          {
            signature = static_buffer[1];
          }
          else
          {
            need_position = true;
          }
        }

        // i = input order (interprets the next 4 characters as wasd input)

        else if (static_buffer[0] == 'i')
        {
          receiveInput(static_buffer);
        }

        // m = message order (adds a message to the chat from a specific player)

        else if (static_buffer[0] == 'm')
        {
          newest_chat = std::string(static_buffer);
          newest_chat.erase(0,2);
          pending_message = true;
        }

        // w = warp order (warps the sending player to specific co-ordinates)

        else if (static_buffer[0] == 'w')
        {
          // converts the position in pixels to 3 characters

          // 48 is subtracted from each characters value because they are sent as the numbers in ascii form so subtracted 48 gives the actual value
          int target_signature = (int)static_buffer[1] - 48;

          warp_positions[0][target_signature] = ((int)static_buffer[2] - 48) * 100 +
                                                ((int)static_buffer[3] - 48) * 10 +
                                                ((int)static_buffer[4] - 48);

          warp_positions[1][target_signature] = ((int)static_buffer[5] - 48) * 100 +
                                                ((int)static_buffer[6] - 48) * 10 +
                                                ((int)static_buffer[7] - 48);

          need_warp = true;

        }

      }
    }
  }
}
