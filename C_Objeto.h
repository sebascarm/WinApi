//######################################################//
// OBJETO GLOBAL v2.2									//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 29/05/2020                                           //
// Text Size & BackColor								//
// Habilitar y deshabilitar objetos						//
// SetFont												//
// Creacion                                             //
//######################################################//

#pragma once
#include <Windows.h>
#include <string>
#include "WinApi.h"

#include "Contenedor.h"

class C_Objeto {
protected:
	int	 ID			 = NULL;				// Numero de elemento en Windows (distinto al hWnd)
	unsigned __int64 Elemento;				// Numero de elemento - distinto al ID
	HWND hWnd		 = nullptr;
	HWND *hWnd_Padre = nullptr;
	int	 x = 0, y = 0, ancho = 0, alto = 0;	// Posicion
	std::string	Texto;
	// Detalles del objeto
	std::string Tipo;
	DWORD		Estilo;
	HFONT		hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	string		Fuente		= "Arial";
	int			Text_Size	= 14;
	COLORREF	BackColor   = RGB(250, 250, 250);

	// Funcion para los objetos
	void Contener(C_Button& Button);
	void Contener(C_Label& Label);
	void Contener(C_GroupBox& GroupBox);
	void Contener(C_TextBox& GroupBox);
	void Contener(C_Menu& Menu, int Elementos);
	void Contener(C_MultiLine& MultiLine);
	void Contener(C_ListBox& ListBox);
	void Contener(C_RichText& Objeto);
	void Contener(C_Shape& Objeto);
	//lo llama el contenedor		
	void Draw();
	// Funcion vacia para callback	
	static void Function_Empty();
	static void Function_ID_Empty(int ID);
	// Funciones especiales			
	HBRUSH ColorEdit(WPARAM& wParam);	//Color de fondo
	//Clase Amiga
	friend Contenedor;

public:
	void Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto);
	//Propiedades comunes no expuestas
	int		Get_ID();
	HWND*	Get_hWnd();
	HWND*   Get_hWnd_Padre();
	// Propiedades comunues	
	string	Get_Text();
	int		Get_Pos_X();
	int		Get_Pos_Y();
	// Metodos comunes		
	void Set_Text(string Text);
	void Set_Text_Size(int Text_Size);
	void Set_Pos(int x, int y, int ancho, int alto);
	void Set_Font(string Fuente);
	void Set_Enable();
	void Set_Disable();
};

