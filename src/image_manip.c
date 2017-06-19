#include "image_manip.h"

void read_header_BMP(FILE *img, BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header){	
    int eoftrash;
    strcpy(file_header->bfType, "");
    rewind(img);
    eoftrash = fread(&(*file_header).bfType, sizeof(file_header->bfType)-1, 1, img);
    if(strcmp(file_header->bfType, "BM") != 0){
        printf("Not a bmp format!!\n");
        abort();
    }
    eoftrash = fread(&(*file_header).bfSize, sizeof(file_header->bfSize), 1, img);
    eoftrash = fread(&(*file_header).bfReserved1, sizeof(file_header->bfReserved1), 1, img);
    eoftrash = fread(&(*file_header).bfReserved2, sizeof(file_header->bfReserved2), 1, img);
    eoftrash = fread(&(*file_header).bfOffBits, sizeof(file_header->bfOffBits), 1, img);
    eoftrash = fread(&(*info_header).biSize, sizeof(info_header->biSize), 1, img);
    eoftrash = fread(&(*info_header).biWidth, sizeof(info_header->biWidth), 1, img);
    eoftrash = fread(&(*info_header).biHeight, sizeof(info_header->biHeight), 1, img);
    eoftrash = fread(&(*info_header).biPlanes, sizeof(info_header->biPlanes), 1, img);
    eoftrash = fread(&(*info_header).biBitCount, sizeof(info_header->biBitCount), 1, img);
    eoftrash = fread(&(*info_header).biCompression, sizeof(info_header->biCompression), 1, img);
    eoftrash = fread(&(*info_header).biSizeImage, sizeof(info_header->biSizeImage), 1, img);
    eoftrash = fread(&(*info_header).biXPelsPerMeter, sizeof(info_header->biXPelsPerMeter), 1, img);
    eoftrash = fread(&(*info_header).biYPelsPerMeter, sizeof(info_header->biYPelsPerMeter), 1, img);
    eoftrash = fread(&(*info_header).biClrUsed, sizeof(info_header->biClrUsed), 1, img);
    eoftrash = fread(&(*info_header).biClrImportant, sizeof(info_header->biClrImportant), 1, img);
    if(eoftrash == EOF) abort();

}

void write_header_BMP(FILE *img, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header){
	rewind(img);
	fwrite(&file_header.bfType, sizeof(file_header.bfType)-1, 1,img);
    fwrite(&file_header.bfSize, sizeof(file_header.bfSize), 1,img);
    fwrite(&file_header.bfReserved1, sizeof(file_header.bfReserved1), 1,img);
    fwrite(&file_header.bfReserved2, sizeof(file_header.bfReserved2), 1,img);
    fwrite(&file_header.bfOffBits, sizeof(file_header.bfOffBits), 1,img);
    fwrite(&info_header.biSize, sizeof(info_header.biSize), 1,img);
    fwrite(&info_header.biWidth, sizeof(info_header.biWidth), 1,img);
    fwrite(&info_header.biHeight, sizeof(info_header.biHeight), 1,img);
    fwrite(&info_header.biPlanes, sizeof(info_header.biPlanes), 1,img);
    fwrite(&info_header.biBitCount, sizeof(info_header.biBitCount), 1,img);
    fwrite(&info_header.biCompression, sizeof(info_header.biCompression), 1,img);
    fwrite(&info_header.biSizeImage, sizeof(info_header.biSizeImage), 1,img);
    fwrite(&info_header.biXPelsPerMeter, sizeof(info_header.biXPelsPerMeter), 1,img);
    fwrite(&info_header.biYPelsPerMeter, sizeof(info_header.biYPelsPerMeter), 1,img);
    fwrite(&info_header.biClrUsed, sizeof(info_header.biClrUsed), 1,img);
    fwrite(&info_header.biClrImportant, sizeof(info_header.biClrImportant), 1,img);
}

void read_header_PPM(FILE *img, PPMFILEHEADER *header){
    int eoftrash;
    rewind(img);
    eoftrash = fscanf(img, "%s", (*header).type);
    if(!(strcmp(header->type, "P6") == 0 || strcmp(header->type, "P2") == 0)){
        printf("Not a ppm valid format!!\n");
        abort();
    }
    eoftrash = fscanf(img, "%u %u %u", &(*header).height, &(*header).width, &(*header).range);
    fgetc(img);
    if(eoftrash == EOF) abort();
    (*header).offset = ftell(img);
}

void write_header_PPM(FILE *img, PPMFILEHEADER header){
    rewind(img);
    fprintf(img, "%s\n", header.type);
    fprintf(img, "%u %u\n%u\n", header.height, header.width, header.range);
}

void read_pixels(RGBQUAD ***matriz, int height, int width, FILE *img, int offset){
    int i, j;
    char type[3];
    strcpy(type, "");
    rewind(img);
    i = fscanf(img, "%c%c", &type[0], &type[1]);
    type[2] = '\0';
    rewind(img);
    fseek(img, offset, SEEK_SET);
    *matriz=(RGBQUAD**)malloc(height*sizeof(RGBQUAD*));
    for(i = 0; i < height; i++){
        (*matriz)[i]=(RGBQUAD*)malloc(width*sizeof(RGBQUAD));
        for(j = 0; j < width; j++){
            (*matriz)[i][j].rgbReserved = fscanf(img,"%c%c%c",&(*matriz)[i][j].rgbRed, &(*matriz)[i][j].rgbGreen, &(*matriz)[i][j].rgbBlue);
        }
        if(strcmp(type,"BM") == 0){
            j = fread(&(*matriz)[i][j].rgbReserved, width%4, 1, img);
        }
    }
}

void write_pixels(RGBQUAD **matriz, int height, int width, FILE *img, int offset){
    int i, j;
    char type[3];
    strcpy(type, "");
    rewind(img);
    i = fscanf(img, "%c%c", &type[0], &type[1]);
    type[2] = '\0';
    rewind(img);
    fseek(img, offset, SEEK_SET);
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            fprintf(img,"%c%c%c",matriz[i][j].rgbRed, matriz[i][j].rgbGreen, matriz[i][j].rgbBlue);
        }
        if(strcmp(type,"BM") == 0){
            fwrite(&matriz[i][j].rgbReserved, width%4, 1, img);
        }
    }
}