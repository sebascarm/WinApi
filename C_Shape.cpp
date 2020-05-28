#include "C_Shape.h"

void C_Shape::Create(Win_Frame* pFrame, S_Style Style, int x, int y, int ancho, int alto) {
	// Crear y contener
	C_Objeto::Create(pFrame, "", x, y, ancho, alto);
	C_Objeto::Contener(*this);
	//Detalles del objeto
	//Tipo = "WinApi";
	//Estilo = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    S_Estilo = Style;   // Line, Rect, Circle
}

//*********************************************
//*** EVENTO CLICK (El loop debe llamarlo)	***
//*** No se activa solo						***
//*********************************************
void C_Shape::Draw_Shape() {
    PAINTSTRUCT PStruc;
    //RECT Rect;
    //GetClientRect(*hWnd_Padre, &Rect);
    //if (Rect.bottom == 0) {
    //    return;
    //}
    HDC hdc = BeginPaint(*hWnd_Padre, &PStruc);
    
    HGDIOBJ hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HGDIOBJ holdPen = SelectObject(hdc, hPen);
    
    HGDIOBJ hBrush1 = CreateSolidBrush(RGB(200, 200, 200));
    HGDIOBJ holdBrush = SelectObject(hdc, hBrush1);

    switch (S_Estilo) {
    case S_Style::S_RECTANGLE:
        Rectangle(hdc, x, y, x + ancho, y + alto);
        break;
    case S_Style::S_CIRCLE:
        Ellipse(hdc, x, y, x + ancho, y + alto);
        break;
    }

    
    
    
    DeleteObject(hPen);
    DeleteObject(hBrush1); 
    DeleteObject(holdPen);
    DeleteObject(holdBrush);
    
    //for (int i = 0; i < 1000; i++) {
    //    int x = rand() % Rect.right;
    //    int y = rand() % Rect.bottom;
    //    SetPixel(hdc, x, y, RGB(255, 0, 0));
    //}
    EndPaint(*hWnd_Padre, &PStruc);
}
