#include <algorithm>
#include <array>
#include <iostream>
#include <optional>
#include <string_view>

// board.h
using Position = std::array<int, 2>;

// game.h
struct Move
{
  Position from;
  Position to;
};

// game.cpp
namespace
{
	std::optional<Move> parseMove(std::string_view input)
	{
		if (input.size() != 4)
		{
			return std::nullopt;
		}

		char fromFile { input[0] };
		char fromRank { input[1] };
		char toFile { input[2] };
		char toRank { input[3] };

		if (fromFile < 'a' || fromFile > 'h' || toFile < 'a' || toFile > 'h')
		{
			return std::nullopt;
		}

		if (fromRank < '1' || fromRank > '8' || toRank < '1' || toRank > '8')
		{
			return std::nullopt;
		}

		int fromRow { fromRank - '1' };
		int fromCol { fromFile - 'a' };
		int toRow { toRank - '1' };
		int toCol { toFile - 'a' };

		Position from { fromRow, fromCol };
		Position to { toRow, toCol };

		Move move { .from = from, .to = to };

		return move;
	}
}

std::optional<Move> getUserMove()
{
  std::string input {};
  std::getline(std::cin, input);

  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

  auto move { parseMove(input) };

  return move;
}

int main()
{
	// printPrompt()?
  std::cout << "Enter your move: ";

  auto move { getUserMove() };

  if (!move)
  {
    std::cout << "Bad input! Use continue/return/break\n";
    return 0;
  }

	std::cout << "From:\n";
  std::cout << "row: " << move->from[0] << ' ';
  std::cout << "col: " << move->from[1] << '\n';
	std::cout << "\nTo:\n";
  std::cout << "row: " << move->to[0] << ' ';
  std::cout << "col: " << move->to[1] << '\n';

  return 0;
}
