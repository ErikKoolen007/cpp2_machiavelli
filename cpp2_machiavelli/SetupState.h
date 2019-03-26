#pragma once
#include "GameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
	SetupState(GameManager& manager) : GameState(manager)
	{
		fileReader = std::make_unique<FileReader>();
	}
	void next() override;
private:
	//InGameState nextState;
	std::unique_ptr<FileReader> fileReader;
};

//random shuffle
template <class RandomAccessIterator, class URNG>
void shuffle(RandomAccessIterator first, RandomAccessIterator last, URNG&& g)
{
	for (auto i = (last - first) - 1; i > 0; --i) {
		std::uniform_int_distribution<decltype(i)> d(0, i);
		swap(first[i], first[d(g)]);
	}
}
