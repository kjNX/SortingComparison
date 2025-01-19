#ifndef SORTINGCOMPARISON_COMMONS_HPP
#define SORTINGCOMPARISON_COMMONS_HPP

#include <chrono>

typedef std::chrono::steady_clock steady_clock;

namespace Commons
{
	inline constexpr int SET_COUNT{5}; // Since this repeats so much throughout, it would be a magic number, huh?
	inline constexpr int MAX_COUNT{100000}; // The amount of cards to generate. Affects all algorithms.
	// sorted cards. sometimes hardcoding is the best way
	enum Card
	{
		card_heartAce,
		card_heart2,
		card_heart3,
		card_heart4,
		card_heart5,
		card_heart6,
		card_heart7,
		card_heart8,
		card_heart9,
		card_heart10,
		card_heartJack,
		card_heartQueen,
		card_heartKing,
		card_clubAce,
		card_club2,
		card_club3,
		card_club4,
		card_club5,
		card_club6,
		card_club7,
		card_club8,
		card_club9,
		card_club10,
		card_clubJack,
		card_clubQueen,
		card_clubKing,
		card_spadeAce,
		card_spade2,
		card_spade3,
		card_spade4,
		card_spade5,
		card_spade6,
		card_spade7,
		card_spade8,
		card_spade9,
		card_spade10,
		card_spadeJack,
		card_spadeQueen,
		card_spadeKing,
		card_diamondAce,
		card_diamond2,
		card_diamond3,
		card_diamond4,
		card_diamond5,
		card_diamond6,
		card_diamond7,
		card_diamond8,
		card_diamond9,
		card_diamond10,
		card_diamondJack,
		card_diamondQueen,
		card_diamondKing,
		card_redJoker,
		card_blackJoker,
		max_cards,
	};

};


#endif //SORTINGCOMPARISON_COMMONS_HPP
