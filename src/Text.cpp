#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

struct IVec2 {
  float x = 0;
  float y = 0;
};

static struct Characters {
  uint32 textureID[128];
  IVec2 size[128];
  IVec2 bearing[128];
  uint32 advance[128];
} characters;

void render_text(Object* object, const char* text, float x, float y, float r, float g, float b) {
  glUseProgram(object->program);

  glUniform3f(glGetUniformLocation(object->program, "textColor"), r, g, b);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(object->vertexArray);

  float scale = 0.005f;

  for(uint32 i = 0; i < strlen(text); i++) {
    uint32& texture = characters.textureID[text[i]];   
    IVec2& size= characters.size[text[i]];   
    IVec2& bearing = characters.bearing[text[i]];   
    uint32& advance = characters.advance[text[i]];   

    float xpos = x + bearing.x * scale;
    float ypos = y + (size.y - bearing.y) * scale;

    float w = size.x * scale;
    float h = size.y * scale;
  
    float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 0.0f },            
      { xpos,     ypos,       0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 1.0f },

      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos + w, ypos,       1.0f, 1.0f },
      { xpos + w, ypos + h,   1.0f, 0.0f }           
    };

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, object->vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (advance >> 6) * scale;
  }


  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0); //could be optimised
  glDisableVertexAttribArray(0); //could be optimised

}

void load_font(const FT_Library& ft, const char* fontPath) {
  FT_Face face;
  char fPath[512];
  full_path(fPath, fontPath);


  if(FT_New_Face(ft, fPath, 0, &face)) {
    printf("Failed to load font\n");
    return;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for(uint32 c = 0; c < 128; c++) {
    if(FT_Load_Char(face, (char)c, FT_LOAD_RENDER)) {
      printf("Couldn't load glyph 'X'\n");
      return;
    }
   
    FT_Bitmap& bitmap = face->glyph->bitmap;

    uint32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 
	0,
	GL_RED,
	bitmap.width,
	bitmap.rows,
	0,
	GL_RED,
	GL_UNSIGNED_BYTE,
	bitmap.buffer
	);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    characters.textureID[c] = texture;
    characters.size[c] = { (float)bitmap.width, (float)bitmap.rows };
    characters.bearing[c] = { (float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top };
    characters.advance[c] = face->glyph->advance.x;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void text_init() {
  FT_Library ft;
  if(FT_Init_FreeType(&ft)) {
    printf("Failed to init freetype\n");
    return;
  }

  load_font(ft, "res/fonts/arial.ttf");
} 


