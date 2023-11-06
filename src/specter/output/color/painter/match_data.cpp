#include <specter/output/color/painter/match_data.h>

#include <specter/input/istream.h>



void SPECTER_NAMESPACE MatchData::next() noexcept
{
	if (end_reached_)
		return;

	// advance token index
	index_++;

	update_token_data();
	update_cursor_data();
}



SPECTER_NAMESPACE PaintRule* SPECTER_NAMESPACE MatchData::update_rule_data(const std::vector<PaintRule*>& rules, const size_t current_index) noexcept
{
	// invalid index
	if (current_index >= rules.size())
		return nullptr;

	// rule at index
	PaintRule* rule = rules[current_index];

	// force a rule to match, if it is not nullptr
	if (forcing_rule)
		rule = forcing_rule;

	// is at last rule iteration?
	last_rule_ = (current_index + 1 >= rules.size());
	current_rule_ = rule;

	return rule;
}


void SPECTER_NAMESPACE MatchData::update_all() noexcept
{
	update_token_data();
	update_cursor_data();
}


void SPECTER_NAMESPACE MatchData::update_token_data() noexcept
{
	last_token_ = (index_ + 1 >= tokens.size());	// at last token?
	end_reached_ = (index_ >= tokens.size());		// no tokens left? (processed all)

	// update current token, if not at end
	if (!end_reached_)
		token = tokens[index_];
}


void SPECTER_NAMESPACE MatchData::update_cursor_data() noexcept
{
	if (!cursor)
		return;

	cursor_index_ = cursor->pos.index;
	relative_cursor_index_ = cursor_index_ - token.begin;
}