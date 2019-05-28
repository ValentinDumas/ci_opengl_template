//#pragma once
//#include "ImGui/imgui.h"
//#include <experimental/filesystem>
//#include <HUD/popups.h>
//
//void ShowWindowMenubar()
//{
//
//	//@TODO faire un menu qui ne prend pas de rectangle noir en dessous
//	ImGuiWindowFlags my_menubar_flags = 0;
//	my_menubar_flags |= ImGuiWindowFlags_MenuBar;
//	my_menubar_flags |= ImGuiWindowFlags_NoTitleBar;
//	my_menubar_flags |= ImGuiWindowFlags_NoCollapse;
//	my_menubar_flags |= ImGuiWindowFlags_NoMove;
//	my_menubar_flags |= ImGuiWindowFlags_NoResize;
//
//	ImGui::Begin("MenuBar", nullptr, my_menubar_flags);
//	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
//	ImGui::SetWindowSize(ImVec2(m_glfw_environment->get_width(), 0));
//
//	if (ImGui::BeginMenuBar()) {
//		if (ImGui::BeginMenu("Project"))
//		{
//			ShowMenubarMenuProject();
//
//			ImGui::EndMenu();
//		}
//		if (ImGui::BeginMenu("Edit"))
//		{
//			ImGui::EndMenu();
//		}
//		ImGui::EndMenuBar();
//	}
//
//	if (query_save_as)
//	{
//		// TODO: Return more info (PopupAnswer) from popup response
//		PopupStatus std::experimental::filesystem::status = ShowSaveAsPopup();
//		if (status == PopupStatus::CANCEL) { query_save_as = false; }
//		if (status == PopupStatus::SAVE_AS)
//		{
//			// TODO: Thomas save all data in documents on filesystem (nosql documents) here !
//			////	if (SaveAs()) // Success
//			////	{
//			////		std::cout << "Project successfully saved !" << std::endl;
//			////	}
//			query_save_as = false;
//		}
//	}
//
//	ImGui::BeginGroup();
//	{
//		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
//		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.1f));
//		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));
//		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
//
//		const Texture texture_button_play = ResourceManager::GetTexture("play");
//		if (ImGui::ImageButton((void*)(intptr_t)texture_button_play.ID, ImVec2(32.0f, 32.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0, ImVec4())) {
//			if (m_scene_manager.getRunningConfigEnum() == CONFIG && m_scene_manager.getRunningConfigEnum() != RUNNING)
//			{
//				m_scene_manager.setRunningConfigEnum(RUNNING);
//			}
//		}
//
//		ImGui::SameLine();
//
//		const Texture texture_button_stop = ResourceManager::GetTexture("stop");
//		if (ImGui::ImageButton((void*)(intptr_t)texture_button_stop.ID, ImVec2(32.0f, 32.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0)) {
//			if (m_scene_manager.getRunningConfigEnum() == RUNNING && m_scene_manager.getRunningConfigEnum() != CONFIG)
//			{
//				m_scene_manager.setRunningConfigEnum(CONFIG);
//			}
//		}
//
//		ImGui::PopStyleColor(4);
//	}
//	ImGui::EndGroup();
//
//	this->UpdateCurrentWindowRectData(&m_window_menubar);
//
//	ImGui::End();
//}