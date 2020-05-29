#pragma once

enum class TipoObjeto {
	T_FRAME,
	T_BUTTON,
	T_MULTILINE,
	T_TEXTBOX,
	T_MENU,
	T_LABEL,
	T_GROUPBOX,
	T_LISTBOX,
	T_RICHTEXT,
	T_SHAPE
};

enum class W_Align {
	A_IZQ,
	A_DER,
	A_CENT
};

// Shape Text Align			
enum class S_Align {
	S_IZQ,
	S_DER,
	S_CENT,
	S_UP,
	S_DOWN
};

// Shape Style				
enum class S_Style {
	S_LINE,
	S_RECTANGLE,
	S_CIRCLE,
	S_FREE
};


enum class M_Message {
	M_OK,
	M_OKCANCEL,
	M_YESNO,
};