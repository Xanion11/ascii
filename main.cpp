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

void ParsingBrightness(unsigned char *input, std::vector<uint16_t> *vector, int imagex, int imagey) {
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
        // vector->push_back(-1);
    }

}

void Write_File(std::vector<uint16_t> *vec, int width, int height, unsigned char *ret){
    // quadruple nested for loops are no more (yay)
    // memset(ret, 0x00, width*height*8*8);
    // std::cout << vec->max_size() << ' ' << vec->size() << '\n';
    // std::cout << font[20][4] << '\n';
    int mask = 1;
    for (int j =0;j<8*height;j+=8) {
        for (int i =0;i<8*width;i+=8) {
            // ret[8*j*width+i] = 0xff; // vec->at((j*width+i)%vec->size());
            for (int y = 0; y <8; y++) {
                uint16_t curr_char = font[vec->at(j*width/8 + i/8)][y];
                for (int x = 0; x <8; x++) {
                    if ((curr_char & mask) == 1) {
                        ret[8*j*width+i +y*width*8+ x] = 0xff;
                    }
                    curr_char = curr_char >> 1;
                }

            }
        }
    }
}


int main(int argc, const char *argv[]) {
    int x, y, n = 0;

    #ifdef LOGGING
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    #endif
    // char out_name[] = "output.png";

    unsigned char *data = stbi_load(argv[1],&x,&y,&n,1);
    if (data == nullptr) {
        return 1;
    }
    std::vector<uint16_t> character_strip;

    ParsingBrightness(data, &character_strip, x, y);
    stbi_image_free(data);

    const size_t arrsize = 8*y*x*8;

    unsigned char *image_data = new unsigned char[arrsize];

    Write_File(&character_strip, x, y, image_data);
    stbi_write_png_compression_level =8;
    stbi_write_png("output.png", 8*x, 8*y, 1, image_data, x*8);

    delete[] image_data;


    return 0;
}
