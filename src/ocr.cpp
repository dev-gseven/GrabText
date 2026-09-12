#include "ocr.h"

OCR::OCR(const QPixmap image, const char *lang)
{
//    const QPixmap image =
//    Pix *image = pixRead(imagePath);

    // initializes the api
    if (api.Init(nullptr, lang)){
        qDebug() << "Erro ao iniciar\n";
        return;
    }

    // starts here

    tesseractApi.SetImage(image);

    char* outText = api.GetUTF8Text();

    qDebug() << outText << "\n";

    delete[] outText;
//    pixDestroy(&image);

    api.End();
}
