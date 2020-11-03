#include "Rosewood.h"
#include "glm/glm.hpp"

using namespace Rosewood;

class Sofa
{
    
public:
    Ref<Texture> Top, Arm, Front, Thing, Seat, Back, blank;
    Ref<Texture> Top_n, Arm_n, Front_n, Thing_n, Seat_n, Back_n, Blank_n;
    Ref<RenderMesh> Top_m, Arm_m, Front_m, Thing_m, Seat_m, Back_m, Blank_m;
    float scale = 5.0f;
    void Load(AssetManager asset)
    {
        Top   = asset.Load<Texture>("Content/Room/Sofa_Top.png", "Top");
        Arm   = asset.Load<Texture>("Content/Room/Sofa_ArmRest.png", "Arm");
        Front = asset.Load<Texture>("Content/Room/Sofa_Front.png", "Front");
        Thing = asset.Load<Texture>("Content/Room/Sofa_Thing.png", "Thing");
        Seat  = asset.Load<Texture>("Content/Room/Sofa_Seat.png", "Seat");
        Back  = asset.Load<Texture>("Content/Room/Sofa_Back.png", "Back");
        
        Top_n   = asset.Load<Texture>("Content/Room/Sofa_Normal_Top.png", "Top_n");
        Arm_n   = asset.Load<Texture>("Content/Room/Sofa_Normal_ArmRest.png", "Arm_n");
        Front_n = asset.Load<Texture>("Content/Room/Sofa_Normal_Front.png", "Front_n");
        Thing_n = asset.Load<Texture>("Content/Room/Sofa_Normal_Thing.png", "Thing_n");
        Seat_n  = asset.Load<Texture>("Content/Room/Sofa_Normal_Seat.png", "Seat_n");
        Back_n  = asset.Load<Texture>("Content/Room/Sofa_Normal_Back.png", "Back_n");
        
        blank = asset.Load<Texture>("Content/Room/blank.png", "blank");
        Blank_n = asset.Load<Texture>("Content/Room/blank_n.png", "blank_n");

        
        Top_m   = RenderMesh::CreateFlatQuad(std::vector<Ref<Texture>>{Top  , Top_n  , blank});
        Arm_m   = RenderMesh::CreateFlatQuad(std::vector<Ref<Texture>>{Arm  , Arm_n  , blank});
        Front_m = RenderMesh::CreatePerpendicularQuad(std::vector<Ref<Texture>>{Front, Front_n, blank});
        Thing_m = RenderMesh::CreateFlatQuad(std::vector<Ref<Texture>>{Thing, Thing_n, blank});
        Seat_m  = RenderMesh::CreateFlatQuad(std::vector<Ref<Texture>>{Seat , Seat_n , blank});
        Back_m  = RenderMesh::CreatePerpendicularQuad(std::vector<Ref<Texture>>{Back , Back_n , blank});
        Blank_m  = RenderMesh::CreateFlatQuad(std::vector<Ref<Texture>>{blank , Blank_n , blank});

        
    }
	void Draw(glm::vec3 pos)
    {
        DeferredRenderer::Submit(Blank_m, pos + glm::vec3(-5000.0f, -5000.0f, -4830.0f), {10000, 10000, 10000});

        DeferredRenderer::Submit(Top_m, pos + glm::vec3(0.0f, 0.0f, 0.0f)      * scale, {Top->GetWidth()   * scale, Top->GetHeight()   * scale, Top->GetHeight()   * scale});
        DeferredRenderer::Submit(Arm_m, pos + glm::vec3(0.0f, 21.0f, -18.0f)     * scale, {Arm->GetWidth()   * scale, Arm->GetHeight()   * scale, Arm->GetHeight()   * scale});
        DeferredRenderer::Submit(Front_m, pos + glm::vec3(0.0f, 34.0f, -18.0f)   * scale, {Front->GetWidth() * scale, Front->GetHeight() * scale, Front->GetHeight() * scale});
        DeferredRenderer::Submit(Thing_m, pos + glm::vec3(24.0f, 23.0f, -18.0f)  * scale, {Thing->GetWidth() * scale, Thing->GetHeight() * scale, Thing->GetHeight() * scale});
        DeferredRenderer::Submit(Seat_m, pos + glm::vec3(8.0f, 25.0f, -18.0f)    * scale, {Seat->GetWidth()  * scale, Seat->GetHeight()  * scale, Seat->GetHeight()  * scale});
        DeferredRenderer::Submit(Back_m, pos + glm::vec3(0.0f, 6.0f, 0.0f)     * scale, {Back->GetWidth()  * scale, Back->GetHeight()  * scale, Back->GetHeight()  * scale});


    }
    
};
