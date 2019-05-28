#pragma once
#include "utils/FileSystem.hpp"

enum PopupStatus
{
	NONE = 0,
	OK = 1,
	SAVE_AS = 2,
	CANCEL = 3
};

// SaveAs
PopupStatus ShowSaveAsPopup()
{
	PopupStatus popup_status = PopupStatus::NONE;

	static char project_name[64] = ""; // project to save
	static bool project_already_exists = false;
	static bool project_empty = true;

	ImGui::OpenPopup("Save as current project ?");
	if (ImGui::BeginPopupModal("Save as current project ?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Here is a list of all your projects:\n");
		ImGui::BeginChildFrame(ImGui::GetID("SaveAsPopupProjectList"), ImVec2(0, 100));
		{
			// TODO: In further updates, check if the project is a valid project before displaying it as a 'project"
			// List all items in project :)
			for (auto &paths : utils::filesystem::get_directory_entries("projects"))
			{
			    std::cout << "P: " << paths << std::endl;

				ImGui::Text("%s", paths.c_str());
			}
		}

		ImGui::EndChildFrame();

		ImGui::Separator();
		ImGui::Text("The current opened project\nhas not been registered yet.\n\nWould you like to save now ?");
		static char editorbuffer[1024];

		if (ImGui::InputText("Project name", project_name, sizeof(project_name)))
		{
		    // TODO: Implement this
			// FLAG ! to go to InputText implementation
//			project_already_exists = FolderExists(project_name);
//			// NOTE: in this statemet, it does not check for emptyness directly when the popup shows
//			project_empty = (project_name[0] == '\0');
		}

		if (project_already_exists)
		{
			ImGui::TextColored(ImVec4(0.6f, 0.0f, 0.0f, 1.0f), "Project '%s' already exists !", project_name);
		}
		if (project_empty)
		{
			ImGui::TextColored(ImVec4(0.6f, 0.0f, 0.0f, 1.0f), "The project need a name !");
		}
		if (project_already_exists || project_empty)
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}

		if (ImGui::Button("Save as", ImVec2(120, 0)))
		{		// project not already exists && name not empty
			if (!project_already_exists && !project_empty)
			{
				popup_status = PopupStatus::SAVE_AS;
			}
			else
			{
				popup_status = PopupStatus::NONE;
			}
			ImGui::CloseCurrentPopup();
		}

		if (project_already_exists || project_empty)
		{
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			popup_status = PopupStatus::CANCEL;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	return popup_status;
}

bool SaveAs()
{
	return true;
}

// Save
PopupStatus ShowSavePopup();

// TODO: Save in BDD with Mongo
bool Save()
{
	return true;
}
