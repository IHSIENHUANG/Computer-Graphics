#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color;
    // TODO: determine the color
    /*
    Noramlly R = 2*(LN)*N-L // L is light
    However, here we need to count by the ray
    color will add orignal color and the closest_intersection hitted by the reflection Ray
    Keep reflection

    */
         vec3 CR;
         vec3 C0;
         vec3 R;
         vec3 RD = (-1.0)*ray.direction;
         R = 2.0*dot(RD.normalized(),same_side_normal)*same_side_normal-RD.normalized();
         Ray New_Ray(intersection_point,R);
         CR = world.Cast_Ray(New_Ray,++recursion_depth);
         C0 = this->shader->Shade_Surface(ray,intersection_point,same_side_normal,recursion_depth,is_exiting);
         color = C0 + reflectivity*(CR-C0); 
    return color;
}
