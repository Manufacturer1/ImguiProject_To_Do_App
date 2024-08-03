#pragma once
#include "UseImgui.h"




void get_ImGui_color_styles() {
	
	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f; 

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
}

void get_ImGui_window_border_radius_style() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 20.0f;

	style.WindowPadding = ImVec2(30.0f, 20.0f);
	style.FramePadding = ImVec2(35.0f, 7.0f);
	style.ItemSpacing = ImVec2(30.0f, 10.0f);
}

void button_styles() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = 7.0f;

	style.Colors[ImGuiCol_Button] = ImVec4(15.0f / 255.0f, 166.0f / 255.0f, 217.0f / 255.0f, 1.0f);      //15, 166, 217   9, 130, 171
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(9.0f / 255.0f, 130.0f / 255.0f, 171.0f / 255.0f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.40f, 0.85f, 1.0f);
}