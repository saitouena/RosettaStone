/*************************************************************************
> File Name: Interface.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_INTERFACE_H
#define HEARTHSTONEPP_INTERFACE_H

#include <Agents/GameAgent.h>
#include <Enums/Enums.h>
#include <Flatbuffers/MetaData_generated.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskMeta.h>

#include <array>
#include <functional>
#include <iostream>
#include <map>

namespace Hearthstonepp
{
//	struct GameResult
//	{
//		std::string winnerID;
//	};

	class GameInterface
	{
	public:
		GameInterface(
				GameAgent& agent,
				std::ostream& output = std::cout,
				std::istream& input = std::cin);

		GameResult StartGame();

	private:
		const size_t HANDLE_CONTINUE = 0;
		const size_t HANDLE_STOP = 1;

		GameAgent& m_agent;
		TaskMeta m_buffer;
		// FlatData::BriefTaskMeta m_briefCache;

		std::ostream& m_ostream;
		std::istream& m_istream;

		// user id
		std::string m_users[2];

		size_t HandleMessage(const TaskMeta& meta);
		std::ostream& LogWriter(const std::string& name);

		template <std::size_t SIZE>
		void ShowMenus(std::array<std::string, SIZE> menus);

		using CardVector = flatbuffers::Vector<flatbuffers::Offset<FlatData::Card>>;
		void ShowCards(const CardVector& cards, int size);

		void HandleInvalid(const TaskMeta& meta);
		void HandleUserSetting(const TaskMeta& meta);
		void HandleSwap(const TaskMeta& meta);
		void HandleShuffle(const TaskMeta& meta);
		void HandleDraw(const TaskMeta& meta);
//		void HandleMulligan(const TaskMeta& meta);
//		void HandleManaModification(const TaskMeta& meta);
//		void HandleHealthModification(const TaskMeta& meta);
//		void HandleSummonMinion(const TaskMeta& meta);
//		void HandleCombat(const TaskMeta& meta);
		void HandleRequire(const TaskMeta& meta);
//		void HandleBrief(const TaskMeta& meta);
		void HandleTaskTuple(const TaskMeta& meta);
//		void HandleGameEnd(const TaskMeta& meta);

//		void InputMulligan(const FlatData::RequireTaskMeta& meta);
//		void InputSelectMenu(const FlatData::RequireTaskMeta& meta);
//		void InputSelectCard(const FlatData::RequireTaskMeta& meta);
//		void InputTargeting(const FlatData::RequireTaskMeta& meta);

		std::map<TaskID, std::function<void(GameInterface&, const TaskMeta&)>> m_handler =
		{
			{ TaskID::INVALID, 			&GameInterface::HandleInvalid },
			{ TaskID::USER_SETTING, 	&GameInterface::HandleUserSetting },
			{ TaskID::SWAP, 			&GameInterface::HandleSwap },
			{ TaskID::SHUFFLE, 			&GameInterface::HandleShuffle },
			{ TaskID::DRAW, 			&GameInterface::HandleDraw },
//			{ TaskID::MULLIGAN, 		&GameInterface::HandleMulligan },
//			{ TaskID::MANA_MOD, 		&GameInterface::HandleManaModification },
//			{ TaskID::SUMMON_MINION, 	&GameInterface::HandleHealthModification },
//			{ TaskID::COMBAT, 			&GameInterface::HandleSummonMinion },
//			{ TaskID::HEALTH_MOD, 		&GameInterface::HandleCombat },
			{ TaskID::REQUIRE, 			&GameInterface::HandleRequire },
//			{ TaskID::BRIEF, 			&GameInterface::HandleBrief },
			{ TaskID::TASK_TUPLE, 		&GameInterface::HandleTaskTuple },
//			{ TaskID::GAME_END, 		&GameInterface::HandleGameEnd },
 		};

//		std::map<TaskID, std::function<void(GameInterface&, const FlatData::RequireTaskMeta&)>> m_inputHandler =
//		{
//			{ TaskID::MULLIGAN, 		&GameInterface::InputMulligan },
//			{ TaskID::SELECT_MENU, 		&GameInterface::InputSelectMenu },
//			{ TaskID::SELECT_CARD, 		&GameInterface::InputSelectCard },
//			{ TaskID::SELECT_TARGETING,	&GameInterface::InputTargeting },
//		};

		std::array<std::string, GAME_MAIN_MENU_SIZE> m_mainMenuStr =
		{
			"1. Use Card",
			"2. Combat",
			"3. Stop"
		};
	};
}

#endif
