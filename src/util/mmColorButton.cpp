/*******************************************************
 Copyright (C) 2014 Gabriele-V
 Copyright (C) 2015, 2016, 2020, 2022 Nikolay Akimov
 Copyright (C) 2022, 2023 Mark Whalley (mark@ipx.co.uk)
 Copyright (C) 2025 Klaus Wich

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ********************************************************/

#include "mmColorButton.h"

#include "base/mmUserColor.h"
#include "mmImage.h"
#include "_primitive.h"
#include <wx/colordlg.h>

wxBEGIN_EVENT_TABLE(mmColorButton, wxButton)
    EVT_MENU(wxID_ANY,   mmColorButton::onMenuSelected)
    EVT_BUTTON(wxID_ANY, mmColorButton::onColourButton)
wxEND_EVENT_TABLE()

mmColorButton::mmColorButton(
    wxWindow* parent_win,
    wxWindowID win_id,
    wxSize size,
    bool noColorAllowed
) :
    wxButton(parent_win, win_id, " ", wxDefaultPosition, size),
    m_color_id(-1),
    m_noColorAllowed(noColorAllowed)
{
}

void mmColorButton::SetColor(int color_id)
{
    m_color_id = color_id;
    SetBackgroundColour(mmUserColor::getId(m_color_id));
    SetForegroundColour(m_color_id <= 0
        ? mmUserColor::getId(m_color_id)
        : *mmUserColor::bestFontColor(mmUserColor::getId(m_color_id))
    );
    if (GetSize().GetX() > 40) {
        if (m_color_id <= 0) {
            if (m_noColorAllowed) {
                SetLabel(m_color_id == 0 ? wxString::Format(_t("&Without color")) : "");
            }
            else {
                SetLabel(wxString::Format(_t("&Clear color")));
            }
        }
        else {
            SetLabel(wxString::Format(_t("Color #&%i"), m_color_id));
        }
    }
}

void mmColorButton::onMenuSelected(wxCommandEvent& event)
{
    SetColor(event.GetId() - wxID_HIGHEST);
    event.Skip();
}

void mmColorButton::onColourButton(wxCommandEvent& event)
{
    wxColour selected_color = wxGetColourFromUser(this, GetBackgroundColour(), _t("Choose Color (RGB)"));
    if (selected_color.IsOk()) {
        SetBackgroundColour(selected_color);
        m_color_id = (selected_color.Red() << 16) | (selected_color.Green() << 8) | selected_color.Blue();
        Refresh();
    }
    event.Skip();
}
    }

    PopupMenu(&mainMenu);
    event.Skip();
}

