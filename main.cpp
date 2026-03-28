#include <cstdint>
#include <cstring>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include "font.h"
#include <bitset>

union Line {
    uint16_t asd[8];
    std::bitset<128> field;
};

void ParsingBrightness(unsigned char *input, std::vector<int> *vector, int imagex, int imagey) {
    for (int j = 0; j < imagey; j++) {

        for (int i=0 + j*imagex; i < (j+1)*imagex; i++){
            int brightness = (int)((int)(((float)input[i]/255)*100)/2.5);
            #ifdef LOGGING
            std::cout << brightness << ' ';
            #endif
            vector->push_back(brightness);
        }
        #ifdef LOGGING
        std::cout << '\n' <<  "----------" << '\n';
        #endif
        vector->push_back(-1);
    }

}

void Write_File(std::vector<int> *vec, int width, int height, unsigned char *ret){
    // repeat for x pixels y times
    // for each pixel write 8x8 square from font.h depending on the value
    // quadruple nested for loop (god help me)
    //TODO make run fast
    //
    //
    //
    //
    // memset(ret, 0x00, width*height*8*8);
    int i = 0;
    while (i < width*height*8*8) {
        ret[i] = 0xff;
    }


}


int main() {
    int x, y, n = 0;

    unsigned char *data = stbi_load("test.png",&x,&y,&n,1);
    if (data == nullptr) {
        return 1;
    }
    std::vector<int> character_strip;

    ParsingBrightness(data, &character_strip, x, y);
    stbi_image_free(data);

    const size_t arrsize = 8*y*x*8;

    unsigned char *image_data = new unsigned char[arrsize];

    Write_File(&character_strip, x, y, image_data);

    stbi_write_jpg("output.jpg", 8*x, 8*y, 1, image_data, 100);

    delete[] image_data;


    return 0;
}
