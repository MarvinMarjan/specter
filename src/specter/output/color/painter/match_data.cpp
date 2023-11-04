#include <specter/output/color/painter/match_data.h>

#include <specter/output/color/painter/token_scanner.h>



void SPECTER_NAMESPACE MatchData::next() noexcept
{
	if (end_reached)
		return;

	index++;

	update();
}


void SPECTER_NAMESPACE MatchData::update() noexcept
{
	last_token = (index + 1 >= tokens.size());
	end_reached = (index >= tokens.size());

	if (!end_reached)
		token = tokens[index];
}