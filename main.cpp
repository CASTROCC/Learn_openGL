#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./src/Utils/Camera.hpp"
#include "src/Utils/Common_Func.hpp"
#include "./src/sharderUtils/SharderClass.hpp"
#include "./src/Utils/template_Camera.hpp"

#include "src/chapter_01/lession_1.hpp"
#include "src/chapter_01/lession_2.hpp"
#include "src/exercise/lession02_drawRectangle.hpp"
#include "src/chapter_01/lession_3_uniform.hpp"
#include "src/chapter_01/lession_3_uniform_2.hpp"
#include "src/chapter_01/lession_3_sharderClassUse.hpp"
#include "src/chapter_01/lession_4_texture.hpp"
#include "src/chapter_01/lession_4_2texture_mix.hpp"
#include "src/chapter_01/lession_5_matrix_trans.hpp"
#include "src/chapter_01/lession_6_matrix_coordsystem.hpp"
#include "src/chapter_01/lession_7_matrix_lookAt.hpp"
#include "src/chapter_01/lession_8_matrix_selflookAt.hpp"

#include "src/chapter_02/lession_01_chapter2_light.hpp"
#include "src/chapter_02/lession_02_chapter2_pongLight.hpp"
#include "src/chapter_02/lession_03_chapter2_Materials.hpp"
#include "src/chapter_02/lession_04_chapter2_LightMaps.hpp"
#include "src/chapter_02/lession_05_chapter2_Light.hpp"
#include "src/chapter_02/lession_06_chapter2_MuplityLight.hpp"

using namespace template_camera;
using namespace lession_01_chapter02_light;
using namespace lession_02_chapter02_Pong;
using namespace lession_03_chapter02_Materials;
using namespace lession_04_chapter02_LightMaps;
using namespace lession_05_chapter02_Light;
using namespace lession_06_chapter2_MuplityLight;

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    lession_01();
//    lession_02();
//    lession02_drawRectangle();
//    lession_3_uniform();
//    lession_3_uniform_2();
//        lession_3_sharderClassUse();
//    lession_4_texture();
//    lession_4_2texture_mix();
//    lession_5_matrix_trans();
//    lession_6_mattix_coordsystem();
//    lession_7_matrix_lookAt();
//      lession_8_matrix_selflookAt();
//    template_cam();
//    lightDemo();
//    Pong_lightDemo();
//    MaterialsDemo();
//    LightMap_Demo();
    Spot_Light_Demo();
//    muplityLight_Demo();
    return 0;

}