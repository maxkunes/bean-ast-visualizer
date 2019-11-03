#pragma once
#include "imgui.h"
#include <iostream>
#include <bean_ast.hpp>

float rootX = 2560.0 / 3.0;
float rootY = 200;

std::string get_type(const std::shared_ptr<ast>& tree)
{
	return typeid(*tree.get()).name();
}

inline void draw_ast(const std::shared_ptr<ast>& tree, const float oldX, const float oldY, const float curX, const float curY)
{
	std::stringstream stream;
	stream << get_type(tree) << std::endl;

	if(tree->get_value().is_valid())
	{
		stream << "Value : " << tree->get_value().get_text();
	}
	
	std::string text = stream.str();
	auto textSize = ImGui::CalcTextSize(text.c_str());

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(oldX, oldY), ImVec2(curX, curY), ImColor(0, 255, 0, 255), 5);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(curX - (textSize.x), curY - (textSize.y)), ImVec2(curX + (textSize.x), curY + (textSize.y)), ImColor(0, 0, 0, 255), 10.0f);
	
	ImGui::GetOverlayDrawList()->AddText(ImVec2(curX - textSize.x/2, curY - textSize.y/2), ImColor(255, 255, 255, 255), text.c_str());

	if (tree->get_left())
		draw_ast(tree->get_left(), curX, curY + textSize.y * 1.5, curX - 400, curY + 200);
	if (tree->get_right())
		draw_ast(tree->get_right(), curX, curY + textSize.y * 1.5, curX + 400, curY + 200);
}

inline void visualize_ast(const std::string& script)
{
	bean_state state;

	const auto tokens = tokenizer::tokenize(script);

	const auto ast = ast_builder::parse(tokens, state);

	draw_ast(ast, rootX, rootY, rootX, rootY);
}
