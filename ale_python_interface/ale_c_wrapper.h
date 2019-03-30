#ifndef __ALE_C_WRAPPER_H__
#define __ALE_C_WRAPPER_H__

#include <ale_interface.hpp>

extern "C" {
  // Declares int rgb_palette[256]
  ALE_API ALEInterface *ALE_new() {return new ALEInterface();}
  ALE_API void ALE_del(ALEInterface *ale){delete ale;}
  ALE_API const char *getString(ALEInterface *ale, const char *key){return ale->getString(key).c_str();}
  ALE_API int getInt(ALEInterface *ale,const char *key) {return ale->getInt(key);}
  ALE_API bool getBool(ALEInterface *ale,const char *key){return ale->getBool(key);}
  ALE_API float getFloat(ALEInterface *ale,const char *key){return ale->getFloat(key);}
  ALE_API void setString(ALEInterface *ale,const char *key,const char *value){ale->setString(key,value);}
  ALE_API void setInt(ALEInterface *ale,const char *key,int value){ale->setInt(key,value);}
  ALE_API void setBool(ALEInterface *ale,const char *key,bool value){ale->setBool(key,value);}
  ALE_API void setFloat(ALEInterface *ale,const char *key,float value){ale->setFloat(key,value);}
  ALE_API void loadROM(ALEInterface *ale,const char *rom_file){ale->loadROM(rom_file);}
  ALE_API int act(ALEInterface *ale,int action){return ale->act((Action)action);}
  ALE_API bool game_over(ALEInterface *ale){return ale->game_over();}
  ALE_API void reset_game(ALEInterface *ale){ale->reset_game();}
  ALE_API void getAvailableModes(ALEInterface *ale,int *availableModes) {
    ModeVect modes_vect = ale->getAvailableModes();
    for(unsigned int i = 0; i < ale->getAvailableModes().size(); i++){
      availableModes[i] = modes_vect[i];
    }
  }
  ALE_API int getAvailableModesSize(ALEInterface *ale) {return ale->getAvailableModes().size();}
  ALE_API void setMode(ALEInterface *ale, int mode) {ale->setMode(mode);}
  ALE_API void getAvailableDifficulties(ALEInterface *ale,int *availableDifficulties) {
    DifficultyVect difficulties_vect = ale->getAvailableDifficulties();
    for(unsigned int i = 0; i < ale->getAvailableDifficulties().size(); i++){
      availableDifficulties[i] = difficulties_vect[i];
    }
  }
  ALE_API int getAvailableDifficultiesSize(ALEInterface *ale) {return ale->getAvailableDifficulties().size();}
  ALE_API void setDifficulty(ALEInterface *ale, int difficulty) {ale->setDifficulty(difficulty);}
  ALE_API void getLegalActionSet(ALEInterface *ale,int *actions) {
    ActionVect action_vect = ale->getLegalActionSet();
    for(unsigned int i = 0; i < ale->getLegalActionSet().size(); i++){
      actions[i] = action_vect[i];
    }
  }
  ALE_API int getLegalActionSize(ALEInterface *ale){return ale->getLegalActionSet().size();}
  ALE_API void getMinimalActionSet(ALEInterface *ale,int *actions){
    ActionVect action_vect = ale->getMinimalActionSet();
    for(unsigned int i = 0;i < ale->getMinimalActionSet().size();i++){
      actions[i] = action_vect[i];
    }
  }
  ALE_API int getMinimalActionSize(ALEInterface *ale){return ale->getMinimalActionSet().size();}
  ALE_API int getFrameNumber(ALEInterface *ale){return ale->getFrameNumber();}
  ALE_API int lives(ALEInterface *ale){return ale->lives();}
  ALE_API int getEpisodeFrameNumber(ALEInterface *ale){return ale->getEpisodeFrameNumber();}
  ALE_API void getScreen(ALEInterface *ale,unsigned char *screen_data){
    int w = ale->getScreen().width();
    int h = ale->getScreen().height();
    pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
    memcpy(screen_data,ale_screen_data,w*h*sizeof(pixel_t));
  }
  ALE_API void getRAM(ALEInterface *ale,unsigned char *ram){
    unsigned char *ale_ram = ale->getRAM().array();
    int size = ale->getRAM().size();
    memcpy(ram,ale_ram,size*sizeof(unsigned char));
  }
  ALE_API int getRAMSize(ALEInterface *ale){return ale->getRAM().size();}
  ALE_API int getScreenWidth(ALEInterface *ale){return ale->getScreen().width();}
  ALE_API int getScreenHeight(ALEInterface *ale){return ale->getScreen().height();}

  ALE_API void getScreenRGB(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteRGB(output_buffer, ale_screen_data, screen_size );
  }

  ALE_API void getScreenGrayscale(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteGrayscale(output_buffer, ale_screen_data, screen_size);
  }

  ALE_API void saveState(ALEInterface *ale){ale->saveState();}
  ALE_API void loadState(ALEInterface *ale){ale->loadState();}
  ALE_API ALEState* cloneState(ALEInterface *ale){return new ALEState(ale->cloneState());}
  ALE_API void restoreState(ALEInterface *ale, ALEState* state){ale->restoreState(*state);}
  ALE_API ALEState* cloneSystemState(ALEInterface *ale){return new ALEState(ale->cloneSystemState());}
  ALE_API void restoreSystemState(ALEInterface *ale, ALEState* state){ale->restoreSystemState(*state);}
  ALE_API void deleteState(ALEState* state){delete state;}
  ALE_API void saveScreenPNG(ALEInterface *ale,const char *filename){ale->saveScreenPNG(filename);}

  // Encodes the state as a raw bytestream. This may have multiple '\0' characters
  // and thus should not be treated as a C string. Use encodeStateLen to find the length
  // of the buffer to pass in, or it will be overrun as this simply memcpys bytes into the buffer.
  ALE_API void encodeState(ALEState *state, char *buf, int buf_len);
  ALE_API int encodeStateLen(ALEState *state);
  ALE_API ALEState *decodeState(const char *serialized, int len);

  // 0: Info, 1: Warning, 2: Error
  ALE_API void setLoggerMode(int mode) { ale::Logger::setMode(ale::Logger::mode(mode)); }
}

#endif
