//######################################################//
// Label v2.1											//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 05/06/2020                                           //
// Set_TextColor										//
// Correccion en Set_Text (limpieza						//
// Text Size & BackColor								//
//######################################################//

#pragma once
#include "C_Objeto.h"


class C_Label :public Win_Label, public C_Objeto {
protected:
	//Valores propios	
	W_Align Align = W_Align::A_IZQ;
public:
	void Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto, W_Align Align);
	// Propiedades		
	string	Get_Text() { return C_Objeto::Get_Text(); }
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	// Metodos			
	void	Set_Text(string Text);
	void    Set_Text_Size(int Text_Size) { C_Objeto::Set_Text_Size(Text_Size); };
	void	Set_Pos(int x, int y, int ancho, int alto) { C_Objeto::Set_Pos(x, y, ancho, alto); }
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }
	// Motodo propio	
	void	Set_TextColor(COLORREF Color);
	void	Set_BackColor(COLORREF Color);
};

