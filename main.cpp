#include <cstdint>
#include <iostream>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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


int main() {
    int x, y, n = 0;
    std::vector<float> image_vector;

    unsigned char *data = stbi_load("test.png",&x,&y,&n,1);
    if (data == nullptr) {
        return 1;
    }
    std::vector<int> character_strip;

    ParsingBrightness(data, &character_strip, x, y);


    return 0;
}
