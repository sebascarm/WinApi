#include "C_Graphic.h"


void C_Graphic::Create(Win_Frame* pFrame, string Imagen_bmp, int x, int y, int ancho, int alto) {
    // Crear y contener
    C_Objeto::Create(pFrame, "", x, y, ancho, alto);
    C_Objeto::Contener(*this);
    // Cargamos el grafico
    this->Imagen = Imagen_bmp;
    this->hBitmap = (HBITMAP)LoadImage(NULL, 
        this->Imagen.c_str(),
        IMAGE_BITMAP,
        0, 
        0, 
        LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        OutputDebugString("GRAPHIC IMAGE NOT FOUND\n");
    };

    this->Redibujar = true;

}


//*********************************************
//*** (El loop debe llamarlo)	            ***
//*** No se activa solo						***
//*********************************************
void C_Graphic::Draw_Shape(HDC hdc) {
    hdcMem = CreateCompatibleDC(hdc);
    oldBitmap = SelectObject(hdcMem, hBitmap);
    
    GetObject(hBitmap, sizeof(bitmap), &bitmap);
    BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight,
        hdcMem, 0, 0, SRCCOPY);
    
    SelectObject(hdcMem, oldBitmap);
    DeleteDC(hdcMem);

    this->Redibujar = false;
}