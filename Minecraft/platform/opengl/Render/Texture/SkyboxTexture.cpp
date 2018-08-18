//
//  SkyboxTexture.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "SkyboxTexture.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

SkyboxTexture::SkyboxTexture()
:textureID(-1)
{
    
}

SkyboxTexture::~SkyboxTexture() {
    glDeleteTextures(1, &textureID);
}

void SkyboxTexture::load(const std::string& skyboxName) {
    loadDDS(skyboxName);
}

void SkyboxTexture::bind() {
    if (textureID == -1) {
        std::cout << "SkyboxTexture::bind invalid textureId:" << textureID << std::endl;
        return;
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void SkyboxTexture::loadDDS(const std::string& skyboxName) {
    // Create one OpenGL texture
    glGenTextures(1, &textureID);
    
    glActiveTexture(GL_TEXTURE0);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    loadTextureOnMemory(skyboxName + "_side2.dds", Side2);
    loadTextureOnMemory(skyboxName + "_side4.dds", Side4);
    loadTextureOnMemory(skyboxName + "_top.dds", Top);
    loadTextureOnMemory(skyboxName + "_bottom.dds", Bottom);
    loadTextureOnMemory(skyboxName + "_side3.dds", Side3);
    loadTextureOnMemory(skyboxName + "_side1.dds", Side1);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void SkyboxTexture::loadTextureOnMemory(const std::string& fileName, Direction direction) {
    unsigned char header[124];
    
    FILE *fp;
    
    /* try to open the file */
    fp = fopen(fileName.c_str(), "rb");
    if (fp == NULL){
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", fileName.c_str()); getchar();
        return;
    }
    
    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return;
    }
    
    /* get the surface desc */
    fread(&header, 124, 1, fp);
    
    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
    
    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);
    
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return;
    }
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    
    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        std::cout << "SkyboxTexture::loadTextureOnMemory fileName:" << fileName << " target:" << GL_TEXTURE_CUBE_MAP_POSITIVE_X + direction << std::endl;
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + direction, level, format, width, height,
                               0, size, buffer + offset);
        
        offset += size;
        width  /= 2;
        height /= 2;
        
        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if(width < 1) width = 1;
        if(height < 1) height = 1;
    }
    free(buffer);
}
