#include <specter/output/color/painter/match_data.h>

#include <specter/output/color/painter/token_scanner.h>



void SPECTER_NAMESPACE MatchData::next() noexcept
{
	if (end_reached_)
		return;

	// advance token index
	index_++;

	update();
}


void SPECTER_NAMESPACE MatchData::update() noexcept
{
	last_token_ = (index_ + 1 >= tokens.size());	// at last token?
	end_reached_ = (index_ >= tokens.size());		// no tokens left? (processed all)

	// update current token, if not at end
	if (!end_reached_)
		token = tokens[index_];
}