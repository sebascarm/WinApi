//######################################################//
// Button v2.0											//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 04/06/2020                                           //
// Evento press y release								//
//######################################################//

#pragma once
#include "C_Objeto.h"

class C_Button :public Win_Button, public C_Objeto{
protected:
	
	void	(*Funcion_Click)()			= &Function_Empty;
	void	(*Funcion_Press)()			= &Function_Empty;
	void	(*Funcion_Click_ID)(int ID) = &Function_ID_Empty;
	void	(*Funcion_Press_ID)(int ID) = &Function_ID_Empty;
	bool	Uso_Dinamico				= false;
public:
	void Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto);
	// Propiedades			
	int		Get_ID() { return C_Objeto::Get_ID(); }
	string	Get_Text() { return C_Objeto::Get_Text();}
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	// Metodos				
	void	Set_Text(string Text) {C_Objeto::Set_Text(Text);}
	void	Set_Pos(int x, int y, int ancho, int alto) { C_Objeto::Set_Pos(x, y, ancho, alto); }
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }
	// Asignar Eventos		
	void	Assign_Event_Click(void(*Function)());
	void	Assign_Event_Press(void(*Function)());
	void	Assign_Event_Click_ID(void(*Function)(int ID)); // Con envio de ID
	void	Assign_Event_Press_ID(void(*Function)(int ID)); // Con envio de ID
	// Evento				
	void	Event_Click();
	void	Event_Press();
	
};

