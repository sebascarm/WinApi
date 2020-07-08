//######################################################//
// TextBox v2.3											//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 12/06/2020                                           //
// Evento Text Change con ID							//
// Cambiar el tamaño del texto							//
// Configuracion para admitir enter						//
// Evento Text Change									//
//######################################################//

#pragma once
#include "C_Objeto.h"

class C_TextBox :public Win_TextBox, public C_Objeto {
protected:
	void	(*Funcion_Text_Change_ID)(int ID) = &Function_ID_Empty;
public:
	void Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto);
	// Propiedades
	int		Get_ID() { return C_Objeto::Get_ID(); }
	string	Get_Text() { return C_Objeto::Get_Text(); }
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	// Metodos
	void	Set_Text(string Text) { C_Objeto::Set_Text(Text); }
	void    Set_Text_Size(int Text_Size) { C_Objeto::Set_Text_Size(Text_Size); };
	void	Set_Pos(int x, int y, int ancho, int alto) { C_Objeto::Set_Pos(x, y, ancho, alto); }
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }
	// Asignar Eventos		
	void	Assign_Event_Text_Change_ID(void(*Function)(int ID));
	// Evento				
	void	Event_Text_Change();
};

